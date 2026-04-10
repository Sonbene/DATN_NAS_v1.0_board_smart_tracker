#include "mqtt_service.h"
#include "log.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Lưu trữ thông số cấu hình và callback */
static MQTT_Config_t g_mqtt_config;
static MQTT_DataCallback_t g_mqtt_cb = NULL;

/* State machine cho việc xử lý URC đa dòng của A7670 */
typedef enum {
    URC_IDLE,
    URC_WAIT_TOPIC,
    URC_WAIT_PAYLOAD
} MQTT_URC_State_t;

static MQTT_URC_State_t g_urc_state = URC_IDLE;
static char g_rx_topic[128];
static uint16_t g_rx_payload_len = 0;

MQTT_Status_t MQTT_Service_Init(SIM_Handle_t *sim, const MQTT_Config_t *config) {
    if (sim == NULL || config == NULL) return MQTT_ERROR;
    memcpy(&g_mqtt_config, config, sizeof(MQTT_Config_t));

    LOG_INFO("[MQTT] Activating 4G Network Context...");
    /* 1. Kiểm tra xem có Context nào đang Active không (0-3) */
    char cnaction_res[128];
    int active_cid = -1;
    if (SIM_SendATCommandEx(sim, "AT+CNACT?\r\n", "OK", cnaction_res, sizeof(cnaction_res), 2000) == SIM_OK) {
        /* Phản hồi dạng: +CNACT: <cid>,<status>,"<ip>"... */
        for (int i = 0; i < 4; i++) {
            char search_pattern[16];
            snprintf(search_pattern, sizeof(search_pattern), "+CNACT: %d,1", i);
            if (strstr(cnaction_res, search_pattern)) {
                active_cid = i;
                LOG_INFO("[MQTT] Active Network Context found: CID %d", active_cid);
                break;
            }
        }
    }

    if (active_cid == -1) {
        /* Thử kích hoạt Auto-APN trên context 1 */
        LOG_INFO("[MQTT] Attempting Network activation (CID 1)...");
        SIM_SendATCommand(sim, "AT+CNACT=1,1\r\n", "OK", 5000);
        osDelay(2000);
        
        if (SIM_SendATCommand(sim, "AT+CNACT?\r\n", "+CNACT: 1,1", 2000) == SIM_OK) {
            active_cid = 1;
        } else {
            LOG_INFO("[MQTT] Trying fallback APN 'v-internet'...");
            SIM_SendATCommand(sim, "AT+CNACT=1,\"v-internet\"\r\n", "OK", 5000);
            osDelay(2000);
            if (SIM_SendATCommand(sim, "AT+CNACT?\r\n", "+CNACT: 1,1", 2000) == SIM_OK) active_cid = 1;
        }
    }

    if (active_cid != -1) {
        LOG_INFO("[MQTT] Network Ready (IP OK)");
    } else {
        LOG_WARN("[MQTT] No active network context found. MQTT might fail.");
    }

    LOG_INFO("[MQTT] Configuring SSL for HiveMQ Cloud...");
    /* 2. Cấu hình SSL: TLS 1.2, No cert verify, Enable SNI 
     * Lưu ý: Thử cú pháp không ngoặc kép cho tham số đầu tiên nếu có lỗi */
    if (SIM_SendATCommand(sim, "AT+CSSLCFG=\"sslversion\",0,4\r\n", "OK", 1000) != SIM_OK) return MQTT_ERROR;
    if (SIM_SendATCommand(sim, "AT+CSSLCFG=\"authmode\",0,0\r\n", "OK", 1000) != SIM_OK) return MQTT_ERROR;
    if (SIM_SendATCommand(sim, "AT+CSSLCFG=\"enableSNI\",0,1\r\n", "OK", 1000) != SIM_OK) return MQTT_ERROR;

    /* 3. Khởi động dịch vụ MQTT chuẩn A7670 */
    /* Luôn đảm bảo Release Client cũ trước khi Init để Reset STM32 không bị lỗi */
    SIM_SendATCommand(sim, "AT+CMQTTREL=0\r\n", "OK", 1000);

    /* Kiểm tra xem dịch vụ MQTT đã khởi động chưa trước khi gửi lệnh START */
    if (SIM_SendATCommand(sim, "AT+CMQTTSTART?\r\n", "+CMQTTSTART: 1", 2000) != SIM_OK) {
        LOG_INFO("[MQTT] Starting MQTT Service...");
        SIM_SendATCommand(sim, "AT+CMQTTSTART\r\n", "OK", 5000);
        /* Nếu vẫn lỗi, thử STOP rồi START lại một lần nữa cho chắc chắn */
        if (RingBuffer_Search(&sim->rx_rb, "ERROR")) {
            SIM_SendATCommand(sim, "AT+CMQTTSTOP\r\n", "OK", 2000);
            SIM_SendATCommand(sim, "AT+CMQTTSTART\r\n", "OK", 5000);
        }
    }

    /* 4. Kích hoạt chân RI (PA5) nháy khi có MQTT Message */
    SIM_SendATCommand(sim, "AT+CMQTTRI=1\r\n", "OK", 1000);

    return MQTT_OK;
}

MQTT_Status_t MQTT_Service_Connect(SIM_Handle_t *sim) {
    if (sim == NULL) return MQTT_ERROR;
    char cmd[256];

    LOG_INFO("[MQTT] Connecting to %s:%d (SSL Mode)...", g_mqtt_config.host, g_mqtt_config.port);
    
    /* 1. Dọn dẹp triệt để phiên cũ (đặc biệt quan trọng sau khi Reset STM32) */
    /* Thử ngắt kết nối (Disconnect) và giải phóng (Release) Client */
    SIM_SendATCommand(sim, "AT+CMQTTDISC=0,60\r\n", "OK", 1000);
    SIM_SendATCommand(sim, "AT+CMQTTREL=0\r\n", "OK", 1000);
    osDelay(500);
    
    /* 2. Acquire client - server_type = 1 cho SSL (HiveMQ Cloud yêu cầu SSL) */
    snprintf(cmd, sizeof(cmd), "AT+CMQTTACCQ=0,\"%s\",1\r\n", g_mqtt_config.client_id);
    if (SIM_SendATCommand(sim, cmd, "OK", 2000) != SIM_OK) {
        LOG_WARN("[MQTT] Failed to acquire client 0, retrying with extra cleanup...");
        /* Nếu lỗi, thử reset lại toàn bộ MQTT Engine */
        SIM_SendATCommand(sim, "AT+CMQTTSTOP\r\n", "OK", 2000);
        SIM_SendATCommand(sim, "AT+CMQTTSTART\r\n", "OK", 2000);
        
        if (SIM_SendATCommand(sim, cmd, "OK", 2000) != SIM_OK) {
            LOG_ERROR("[MQTT] Critical: Failed to acquire client 0 after reset");
            return MQTT_ERROR;
        }
    }

    /* 3. Bind SSL Context cho MQTT client */
    /* Sử dụng SSL context 0 đã cấu hình trong Init */
    SIM_SendATCommand(sim, "AT+CMQTTSSLCFG=0,0\r\n", "OK", 1000);

    /* 3. Connect tới Broker */
    LOG_INFO("[MQTT] Connecting to %s:%d...", g_mqtt_config.host, g_mqtt_config.port);
    snprintf(cmd, sizeof(cmd), "AT+CMQTTCONNECT=%d,\"tcp://%s:%d\",%d,1,\"%s\",\"%s\"\r\n",
             g_mqtt_config.client_index, g_mqtt_config.host, g_mqtt_config.port,
             g_mqtt_config.keepalive_sec, g_mqtt_config.username, g_mqtt_config.password);

    if (SIM_SendATCommand(sim, cmd, "+CMQTTCONNECT: 0,0", 30000) != SIM_OK) {
        LOG_ERROR("[MQTT] Connection failed");
        return MQTT_ERROR;
    }

    LOG_INFO("[MQTT] Connected successfully!");
    return MQTT_OK;
}

MQTT_Status_t MQTT_Service_Disconnect(SIM_Handle_t *sim) {
    if (sim == NULL) return MQTT_ERROR;
    char cmd[64];
    LOG_INFO("[MQTT] Disconnecting...");
    snprintf(cmd, sizeof(cmd), "AT+CMQTTDISC=%d,60\r\n", g_mqtt_config.client_index);
    SIM_SendATCommand(sim, cmd, "OK", 5000);
    
    snprintf(cmd, sizeof(cmd), "AT+CMQTTREL=%d\r\n", g_mqtt_config.client_index);
    SIM_SendATCommand(sim, cmd, "OK", 2000);
    
    SIM_SendATCommand(sim, "AT+CMQTTSTOP\r\n", "OK", 2000);
    return MQTT_OK;
}

MQTT_Status_t MQTT_Service_Publish(SIM_Handle_t *sim, const char *topic, const uint8_t *payload, uint16_t len, MQTT_QoS_t qos) {
    if (sim == NULL || topic == NULL || payload == NULL || len == 0) return MQTT_ERROR;
    char cmd[128];

    /* Bước 1: Set Topic */
    snprintf(cmd, sizeof(cmd), "AT+CMQTTTOPIC=%d,%d\r\n", g_mqtt_config.client_index, (int)strlen(topic));
    if (SIM_SendATWithData(sim, cmd, (const uint8_t*)topic, strlen(topic), "OK", 5000, 5000) != SIM_OK) return MQTT_ERROR;

    /* Bước 2: Set Payload */
    snprintf(cmd, sizeof(cmd), "AT+CMQTTPAYLOAD=%d,%d\r\n", g_mqtt_config.client_index, len);
    if (SIM_SendATWithData(sim, cmd, payload, len, "OK", 5000, 5000) != SIM_OK) return MQTT_ERROR;

    /* Bước 3: Đăng tin */
    snprintf(cmd, sizeof(cmd), "AT+CMQTTPUB=%d,%d,60\r\n", g_mqtt_config.client_index, qos);
    if (SIM_SendATCommand(sim, cmd, "+CMQTTPUB: 0,0", 10000) != SIM_OK) return MQTT_ERROR;

    return MQTT_OK;
}

MQTT_Status_t MQTT_Service_Subscribe(SIM_Handle_t *sim, const char *topic, MQTT_QoS_t qos, MQTT_DataCallback_t cb) {
    if (sim == NULL || topic == NULL) return MQTT_ERROR;
    char cmd[128];
    g_mqtt_cb = cb;

    /* A7670 Sub logic: TOPIC -> SUB */
    snprintf(cmd, sizeof(cmd), "AT+CMQTTSUBTOPIC=%d,%d,%d\r\n", g_mqtt_config.client_index, (int)strlen(topic), qos);
    if (SIM_SendATWithData(sim, cmd, (const uint8_t*)topic, strlen(topic), "OK", 5000, 5000) != SIM_OK) return MQTT_ERROR;

    snprintf(cmd, sizeof(cmd), "AT+CMQTTSUB=%d\r\n", g_mqtt_config.client_index);
    if (SIM_SendATCommand(sim, cmd, "+CMQTTSUB: 0,0", 5000) != SIM_OK) return MQTT_ERROR;

    return MQTT_OK;
}

void MQTT_Service_HandleURC(SIM_Handle_t *sim, char *line) {
    if (line == NULL) return;

    /* Máy trạng thái xử lý chuỗi URC đa dòng của A7670 */
    /* Trình tự: +CMQTTRXSTART -> +CMQTTRXTOPIC -> DATA -> +CMQTTRXPAYLOAD -> DATA -> +CMQTTRXEND */
    
    if (strstr(line, "+CMQTTRXSTART:")) {
        g_urc_state = URC_WAIT_TOPIC;
        return;
    }

    if (g_urc_state == URC_WAIT_TOPIC) {
        if (strstr(line, "+CMQTTRXTOPIC:")) {
            /* Dòng tiếp theo sẽ là Topic, nhưng cơ chế ReadLine đã lấy nó rồi? 
             * Không, driver đang nạp từng dòng. Ta cần dòng TIẾP THEO. */
        } else {
            strncpy(g_rx_topic, line, sizeof(g_rx_topic)-1);
            g_urc_state = URC_WAIT_PAYLOAD;
        }
        return;
    }

    if (g_urc_state == URC_WAIT_PAYLOAD) {
        if (strstr(line, "+CMQTTRXPAYLOAD:")) {
             char *p = strstr(line, ",");
             if (p) g_rx_payload_len = atoi(p + 1);
        } else if (strstr(line, "+CMQTTRXEND:")) {
            g_urc_state = URC_IDLE;
        } else {
            /* Đây chính là Payload */
            if (g_mqtt_cb) {
                MQTT_Message_t msg;
                strncpy(msg.topic, g_rx_topic, sizeof(msg.topic)-1);
                msg.payload = (uint8_t*)line;
                msg.payload_len = g_rx_payload_len;
                g_mqtt_cb(&msg);
            }
            g_urc_state = URC_IDLE; // Reset sau khi xử lý xong payload
        }
        return;
    }
}
