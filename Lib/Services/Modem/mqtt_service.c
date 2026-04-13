#include "mqtt_service.h"
#include "log.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Lưu trữ thông số cấu hình và callback */
static MQTT_Config_t g_mqtt_config;
static MQTT_DataCallback_t g_mqtt_cb = NULL;

/* Mail Queue nội bộ: Tăng từ 4 lên 10 để tránh mất bản tin khi task bận */
osMailQDef(mqtt_mail_pool, 6, MQTT_Mail_t);
static osMailQId mqtt_mail_pool_id = NULL;

static char g_service_imei[20] = "UNKNOWN";
static volatile int g_mqtt_pending_count = 0;
static volatile bool g_mqtt_is_busy = false;

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

    /* Khởi tạo hàng đợi Mail nếu chưa có */
    if (mqtt_mail_pool_id == NULL) {
        mqtt_mail_pool_id = osMailCreate(osMailQ(mqtt_mail_pool), NULL);
        if (mqtt_mail_pool_id == NULL) return MQTT_ERROR;
    }

    LOG_INFO("[MQTT] Configuring SSL for HiveMQ Cloud...");
    /* 2. Cấu hình SSL: TLS 1.2, No cert verify, Enable SNI */
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
    g_mqtt_is_busy = true;
    char cmd[256];

    LOG_INFO("[MQTT] Connecting to %s:%d (SSL Mode)...", g_mqtt_config.host, g_mqtt_config.port);
    
    /* 1. Reset client (Ignore errors here) */
    SIM_SendATCommand(sim, "AT+CMQTTDISC=0,60\r\n", "OK", 1000);
    SIM_SendATCommand(sim, "AT+CMQTTREL=0\r\n", "OK", 1000);
    
    /* 2. Acquire client */
    snprintf(cmd, sizeof(cmd), "AT+CMQTTACCQ=0,\"%s\",1\r\n", g_mqtt_config.client_id);
    if (SIM_SendATCommand(sim, cmd, "OK", 2000) != SIM_OK) {
        /* Nếu lỗi, thử reset Engine rổi Acquire lại lần cuối */
        SIM_SendATCommand(sim, "AT+CMQTTSTOP\r\n", "OK", 2000);
        SIM_SendATCommand(sim, "AT+CMQTTSTART\r\n", "OK", 3000);
        if (SIM_SendATCommand(sim, cmd, "OK", 2000) != SIM_OK) return MQTT_ERROR;
    }

    /* 3. Bind SSL Context */
    SIM_SendATCommand(sim, "AT+CMQTTSSLCFG=0,0\r\n", "OK", 1000);

    /* 4. Kết nối tới Broker */
    snprintf(cmd, sizeof(cmd), "AT+CMQTTCONNECT=%d,\"tcp://%s:%d\",%d,1,\"%s\",\"%s\"\r\n",
             g_mqtt_config.client_index, g_mqtt_config.host, g_mqtt_config.port,
             g_mqtt_config.keepalive_sec, g_mqtt_config.username, g_mqtt_config.password);

    if (SIM_SendATCommand(sim, cmd, "+CMQTTCONNECT: 0,0", 30000) != SIM_OK) {
        LOG_ERROR("[MQTT] Connection failed");
        return MQTT_ERROR;
    }

    LOG_INFO("[MQTT] Connected successfully!");
    g_mqtt_is_busy = false;
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

    /* Bước 3: Đăng tin - Tăng Timeout lên 20s cho các gói tin dài */
    snprintf(cmd, sizeof(cmd), "AT+CMQTTPUB=%d,%d,60\r\n", g_mqtt_config.client_index, qos);
    g_mqtt_is_busy = true;
    if (SIM_SendATCommand(sim, cmd, "+CMQTTPUB: 0,0", 20000) != SIM_OK) {
        g_mqtt_is_busy = false;
        return MQTT_ERROR;
    }

    g_mqtt_is_busy = false;
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

void MQTT_Service_SetDeviceID(const char *imei) {
    if (imei) strncpy(g_service_imei, imei, sizeof(g_service_imei) - 1);
}

void MQTT_Service_QueuePublish(const char *type, const char *json_payload) {
    /* Khởi tạo hàng đợi nếu Task khác gọi QueuePublish trước khi Init xong */
    if (mqtt_mail_pool_id == NULL) {
        mqtt_mail_pool_id = osMailCreate(osMailQ(mqtt_mail_pool), NULL);
        if (mqtt_mail_pool_id == NULL) return;
    }
    
    if (type == NULL || json_payload == NULL) return;
    
    /* Avoid sending data if identification is not complete */
    if (strcmp(g_service_imei, "UNKNOWN") == 0) {
        LOG_WARN("[MQTT] Skip queuing %s: Device ID unknown", type);
        return;
    }

    MQTT_Mail_t *mail = (MQTT_Mail_t *)osMailAlloc(mqtt_mail_pool_id, 0);
    if (mail != NULL) {
        /* Tự động ghép Topic: Son/<IMEI>/<type> */
        snprintf(mail->topic, sizeof(mail->topic), "Son/%s/%s", g_service_imei, type);
        strncpy(mail->payload, json_payload, sizeof(mail->payload) - 1);
        g_mqtt_pending_count++;
        osMailPut(mqtt_mail_pool_id, mail);
    } else {
        LOG_ERROR("[MQTT] Failed to alloc mail! Queue might be FULL. (Topic: %s)", type);
    }
}

osEvent MQTT_Service_GetMail(uint32_t timeout_ms) {
    if (mqtt_mail_pool_id == NULL) return (osEvent){.status = osErrorResource};
    return osMailGet(mqtt_mail_pool_id, timeout_ms);
}

void MQTT_Service_FreeMail(void *mail_ptr) {
    if (mqtt_mail_pool_id && mail_ptr) {
        if (g_mqtt_pending_count > 0) g_mqtt_pending_count--;
        osMailFree(mqtt_mail_pool_id, mail_ptr);
    }
}

bool MQTT_Service_IsQueueEmpty(void) {
    return (g_mqtt_pending_count <= 0);
}

void MQTT_Service_HandleURC(SIM_Handle_t *sim, char *line) {
    if (line == NULL) return;

    /* Phát hiện rớt kết nối MQTT từ phía Modem */
    if (strstr(line, "+CMQTTCONNLOST:")) {
        LOG_WARN("[MQTT] URC: Connection lost! (Reason: %s)", line);
        /* Ta không cần làm gì ở đây, vì hàm Publish sẽ fail và tự reconnect, 
           hoặc ta có thể đặt 1 flag nếu cần. */
    }

    /* Máy trạng thái xử lý chuỗi URC đa dòng của A7670 */
    /* Trình tự: +CMQTTRXSTART -> +CMQTTRXTOPIC -> DATA -> +CMQTTRXPAYLOAD -> DATA -> +CMQTTRXEND */
    
    if (strstr(line, "+CMQTTRXSTART:")) {
        g_urc_state = URC_IDLE; // Reset trước khi nhận mới
        g_urc_state = URC_WAIT_TOPIC;
        return;
    }

    if (g_urc_state == URC_WAIT_TOPIC) {
        if (strstr(line, "+CMQTTRXTOPIC:")) {
            /* Dòng tiếp theo sẽ là Topic */
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
            g_urc_state = URC_IDLE;
        }
        return;
    }
}

MQTT_Status_t MQTT_Service_IsConnected(SIM_Handle_t *sim) {
    if (sim == NULL) return MQTT_ERROR;
    if (SIM_MQTT_IsConnected(sim) == SIM_OK) {
        return MQTT_OK;
    }
    return MQTT_NOT_CONNECTED;
}

bool MQTT_Service_IsStable(void) {
    /* Trạng thái ổn định là khi không còn tin nhắn chờ gửi và Modem không bận lệnh mạng */
    return (g_mqtt_pending_count == 0 && !g_mqtt_is_busy);
}
