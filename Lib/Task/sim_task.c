#include "sim_task.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
#include "sim_a7670c.h"
#include "mqtt_service.h"
#include "sms_service.h"
#include "secrets.h"
#include "log.h"
#include "system_service.h"
#include "w25q32_task.h"
#include <string.h>
#include <stdio.h>
#include "system_service.h"
#include "power_task.h"

/* State Machine */
typedef enum {
    SIM_ST_POWER_ON,
    SIM_ST_CHECK_COMM,
    SIM_ST_WAIT_NET,
    SIM_ST_SERVICES_INIT,
    SIM_ST_MQTT_CONNECT,
    SIM_ST_READY,
    SIM_ST_ERROR
} SIM_State_t;

/* Handles nội bộ cho Task */
static BSP_UART_Handle_t sim_uart_bus;
SIM_Handle_t sim_modem;
static uint8_t sim_rx_dma_buf[512];
static uint16_t sim_last_dma_pos = 0;
static osThreadId g_sim_task_id = NULL;
static volatile bool g_sim_task_busy = false;
static volatile bool g_modem_needs_power_on = false;

static char g_sim_imei[20] = "UNKNOWN";

#define SIM_SIG_RI    (1 << 0)

static void SIM_Task_Entry(void const * argument);
static void SIM_Event_Callback(SIM_Message_t *msg);
static void prv_SMS_ReceivedCallback(SMS_Message_t *msg);

void SIM_Task_Init(UART_HandleTypeDef *huart) {
    /* 1. Khởi tạo BSP và Driver ngay tại đây */
    BSP_UART_Init(&sim_uart_bus, huart);
    SIM_Init(&sim_modem, &sim_uart_bus);
    
    /* 2. Kích hoạt DMA Receive to Idle (Circular) */
    HAL_UARTEx_ReceiveToIdle_DMA(huart, sim_rx_dma_buf, 512);
    __HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT); /* Tắt ngắt Half-Transfer */

    LOG_INFO("[SIM TASK] Handles initialized. Circular DMA started.");

    /* 3. Tạo Task */
    osThreadDef(SIMTask, SIM_Task_Entry, osPriorityAboveNormal, 0, 768); 
    g_sim_task_id = osThreadCreate(osThread(SIMTask), NULL);
}

void SIM_Task_NotifyRIFromISR(void) {
    if (g_sim_task_id != NULL) {
        osSignalSet(g_sim_task_id, SIM_SIG_RI);
    }
}

void SIM_Task_RestoreUART(void) {
    if (sim_uart_bus.huart != NULL) {
        /* 1. Reset ngoại vi (Lưu ý: Không gọi DeInit để tránh treo HAL) */
        HAL_UART_Init(sim_uart_bus.huart);
        
        /* 2. Khởi động lại DMA RX */
        sim_last_dma_pos = 0;
        HAL_UARTEx_ReceiveToIdle_DMA(sim_uart_bus.huart, sim_rx_dma_buf, 512);
        __HAL_DMA_DISABLE_IT(sim_uart_bus.huart->hdmarx, DMA_IT_HT);
        
        /* 3. Bật lại các ngắt cần thiết */
        __HAL_UART_ENABLE_IT(sim_uart_bus.huart, UART_IT_IDLE);
        __HAL_UART_ENABLE_IT(sim_uart_bus.huart, UART_IT_RXNE);
    }
}

void SIM_Task_UART_RxCallback(UART_HandleTypeDef *huart, uint16_t Size) {
    if (huart->Instance == sim_uart_bus.huart->Instance) {
        uint16_t current_pos = Size;
        if (current_pos != sim_last_dma_pos) {
            if (current_pos > sim_last_dma_pos) {
                SIM_UART_Receive_Handler(&sim_modem, &sim_rx_dma_buf[sim_last_dma_pos], current_pos - sim_last_dma_pos);
            } else {
                SIM_UART_Receive_Handler(&sim_modem, &sim_rx_dma_buf[sim_last_dma_pos], 512 - sim_last_dma_pos);
                if (current_pos > 0) {
                    SIM_UART_Receive_Handler(&sim_modem, &sim_rx_dma_buf[0], current_pos);
                }
            }
            sim_last_dma_pos = current_pos;
        }
    }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == sim_uart_bus.huart->Instance) {
        LOG_WARN("[SIM TASK] UART Error 0x%02lX! Restarting DMA...", huart->ErrorCode);
        
        /* Clear error flags to prevent infinite interrupt loop */
        __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_ORE | UART_FLAG_NE | UART_FLAG_FE | UART_FLAG_PE);
        
        /* Reset DMA write pointer and restart DMA stream */
        sim_last_dma_pos = 0;
        HAL_UARTEx_ReceiveToIdle_DMA(huart, sim_rx_dma_buf, 512);
        __HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);
    }
}

static void SIM_Event_Callback(SIM_Message_t *msg) {
    if (msg == NULL) return;
    
    switch (msg->event) {
        case SIM_EVENT_MQTT_MSG:
        MQTT_Service_HandleURC(&sim_modem, (char*)msg->data);
            break;
        case SIM_EVENT_SMS_MSG:
        SMS_Service_HandleURC(&sim_modem, (char*)msg->data);
            break;
        case SIM_EVENT_NET_READY:
            LOG_INFO("[SIM TASK] Network registered!");
            break;
        case SIM_EVENT_NET_LOST:
            LOG_WARN("[SIM TASK] Network lost!");
            break;
        case SIM_EVENT_MODEM_RESET:
            LOG_WARN("[SIM TASK] Modem reset detected! Restarting sequence...");
            g_modem_needs_power_on = true;
            if (g_sim_task_id != NULL) {
                osSignalSet(g_sim_task_id, SIM_SIG_RI);
            }
            break;
        default: break;
    }
}

static SIM_State_t SIM_Handle_PowerOn(void) {
    LOG_INFO("[SIM] Executing MANDATORY Power-On/Reset Sequence...");
    
    g_sim_task_busy = true;
    SIM_HardReset(&sim_modem);
    osDelay(5000); // Tăng lên 5s cho module boot hoàn toàn
    
    if (SIM_TestAlive(&sim_modem) == SIM_OK) {
        LOG_INFO("[SIM TASK] Module responding!");
        g_sim_task_busy = false;
        return SIM_ST_CHECK_COMM;
    }
    
    LOG_ERROR("[SIM TASK] Module NOT responding after reset!");
    g_sim_task_busy = false;
    return SIM_ST_POWER_ON;
}

static SIM_State_t SIM_Handle_CheckComm(void) {
    SIM_EchoOff(&sim_modem);
    if (SIM_GetIMEI(&sim_modem, g_sim_imei, sizeof(g_sim_imei)) == SIM_OK) {
        /* Cập nhật IMEI cho MQTT Service và System Service để ID không còn UNKNOWN */
        MQTT_Service_SetDeviceID(g_sim_imei);
        System_Service_SetIMEI(g_sim_imei);
        
        return SIM_ST_WAIT_NET;
    }
    return SIM_ST_CHECK_COMM;
}

static SIM_State_t SIM_Handle_WaitNet(void) {
    int stat = 0;
    LOG_INFO("[SIM TASK] Waiting for network registration... (CREG?)");
    if (SIM_GetNetworkReg(&sim_modem, &stat) == SIM_OK) {
        if (stat == 1 || stat == 5) {
            return SIM_ST_SERVICES_INIT;
        }
    }
    osDelay(3000);
    return SIM_ST_WAIT_NET;
}

static SIM_State_t SIM_Handle_ServicesInit(void) {
    LOG_INFO("[SIM TASK] Initializing services (MQTT & SMS)...");
    
    /* Đồng bộ thời gian từ trạm lưu động (nếu có) trước khi chạy dịch vụ */
    char cclk_resp[64];
    if (SIM_SendATCommandEx(&sim_modem, "AT+CCLK?\r\n", "OK", cclk_resp, sizeof(cclk_resp), 2000) == SIM_OK) {
        char *p = strstr(cclk_resp, "+CCLK: \"");
        if (p) {
            p += 8; /* Bỏ qua '+CCLK: "' */
            int yr, mon, day, hr, min, sec;
            if (sscanf(p, "%02d/%02d/%02d,%02d:%02d:%02d", &yr, &mon, &day, &hr, &min, &sec) == 6) {
                /* Lọc bỏ thời gian rác khi module chưa có sóng mạng đồng bộ (vd: năm 70 tức 1970) */
                if (yr >= 24 && yr < 70) {
                    LOG_INFO("[SIM TASK] Network Time Synced: 20%02d-%02d-%02d %02d:%02d:%02d", yr, mon, day, hr, min, sec);
                    System_Service_UpdateTime(hr, min, sec, day, mon, yr);
                } else {
                    LOG_WARN("[SIM TASK] Invalid Network Time (yr=%d). Waiting for GPS/NITZ...", yr);
                }
            }
        }
    }
    
    MQTT_Config_t mqtt_cfg = {
        .client_index = 0,
        .host = MQTT_BROKER_HOST,
        .port = MQTT_BROKER_PORT,
        .client_id = MQTT_CLIENT_ID,
        .username = MQTT_USERNAME,
        .password = MQTT_PASSWORD,
        .keepalive_sec = MQTT_KEEPALIVE_SEC,
        .timeout_ms = 12000
    };
    
    LOG_INFO("[SIM TASK] Initializing services (MQTT & SMS)...");
    if (MQTT_Service_Init(&sim_modem, &mqtt_cfg) == MQTT_OK) {
        /* Khởi tạo SMS Service */
        LOG_INFO("[SIM TASK] MQTT Service Init OK, initializing SMS...");
        SMS_Service_Init(&sim_modem);
        
        /* Đăng ký Callback xử lý tin nhắn ĐẾN */
        SMS_Service_RegisterCallback(prv_SMS_ReceivedCallback);
        
        return SIM_ST_MQTT_CONNECT;
    }
    
    LOG_ERROR("[SIM TASK] Services Init Failed, retrying...");
    osDelay(5000);
    return SIM_ST_SERVICES_INIT;
}

static void prv_MQTT_CommandCallback(MQTT_Message_t *msg);

static SIM_State_t SIM_Handle_MQTTConnect(void) {
    if (MQTT_Service_Connect(&sim_modem) == MQTT_OK) {
        /* 1. Báo cáo trạng thái Online kèm thông tin IMEI khi vừa kết nối */
        char online_json[128];
        snprintf(online_json, sizeof(online_json), 
                 "{\"msg\":\"online\",\"imei\":\"%s\",\"ver\":\"1.0.0\"}", g_sim_imei);
        MQTT_Service_QueuePublish("status", online_json);
        
        /* 2. Subscribe vào topic Command riêng của thiết bị: Son/<IMEI>/cmd */
        char cmd_topic[64];
        snprintf(cmd_topic, sizeof(cmd_topic), "Son/%s/cmd", g_sim_imei);
        LOG_INFO("[SIM TASK] Subscribing to: %s", cmd_topic);
        MQTT_Service_Subscribe(&sim_modem, cmd_topic, MQTT_QOS1, prv_MQTT_CommandCallback);
        
        return SIM_ST_READY;
    }
    LOG_ERROR("[SIM TASK] MQTT Connection Failed, retrying...");
    osDelay(10000);
    return SIM_ST_MQTT_CONNECT;
}

/**
 * @brief Xử lý các lệnh điều khiển từ App Android gửi xuống qua MQTT
 */
static void prv_MQTT_CommandCallback(MQTT_Message_t *msg) {
    if (msg == NULL || msg->payload == NULL) return;
    
    LOG_INFO("[SIM TASK] Received Command: %s", (char*)msg->payload);
    
    /* Xử lý lệnh JSON đơn giản (Identify / Reboot) */
    if (strstr((char*)msg->payload, "\"cmd\":\"identify\"") || strstr((char*)msg->payload, "\"cmd\":\"ping\"")) {
        LOG_INFO("[SIM TASK] Executing Identify command");
        System_Service_VisualNotify(5); // Nháy LED 5 lần
    }
    else if (strstr((char*)msg->payload, "\"cmd\":\"reboot\"")) {
        LOG_WARN("[SIM TASK] Executing Remote Reboot...");
        osDelay(1000);
        HAL_NVIC_SystemReset();
    }
    else if (strstr((char*)msg->payload, "\"cmd\":\"force_report\"")) {
        System_Service_SetForceReport(true);
    }
}

static SIM_State_t SIM_Handle_Ready(void) {
    /* Trong trạng thái READY, Task chủ yếu đợi Mail để Publish hoặc phản hồi RI */
    osEvent evt = MQTT_Service_GetMail(100);
    if (evt.status == osEventMail) {
        g_sim_task_busy = true; /* Đánh dấu bận để ngăn Power Task đi ngủ vào lúc này */
        Power_Task_SetState(POWER_BIT_SIM, false); /* Cập nhật ngay EventGroup để PowerTask thấy */
        
        MQTT_Mail_t *mail = (MQTT_Mail_t*)evt.value.p;
        LOG_INFO("[SIM TASK] MQTT Mail received via Service! Topic: %s", mail->topic);
        
        uint8_t mqtt_ok = 0;
        if (MQTT_Service_Publish(&sim_modem, mail->topic, (uint8_t*)mail->payload, strlen(mail->payload), MQTT_QOS1) != MQTT_OK) {
            LOG_ERROR("[SIM TASK] MQTT Publish FAIL. Verifying connection...");
            /* Kiểm tra xem có bị rớt kết nối MQTT không */
            if (MQTT_Service_IsConnected(&sim_modem) != MQTT_OK) {
                LOG_WARN("[SIM TASK] MQTT Connection lost! Reconnecting...");
                MQTT_Service_FreeMail(mail);
                g_sim_task_busy = false;
                Power_Task_SetState(POWER_BIT_SIM, true);
                return SIM_ST_MQTT_CONNECT;
            }
        } else {
            LOG_INFO("[SIM TASK] MQTT Publish OK");
            mqtt_ok = 1;
        }

        /* 3. Log vào Flash */
        SystemData_t snap;
        System_Service_GetSnapshot(&snap);
        TrackerLog_t log_entry = {
            .timestamp = snap.gps.utc_epoch,
            .lat = snap.gps.lat,
            .lon = snap.gps.lon,
            .speed = snap.gps.speed,
            .mode = (uint8_t)snap.mode,
            .event = LOG_EVENT_PERIODIC, 
            .mqtt_status = mqtt_ok
        };
        W25Q32_Task_Log(&log_entry);

        MQTT_Service_FreeMail(mail);
        g_sim_task_busy = false; /* Giải phóng cờ bận */
        Power_Task_SetState(POWER_BIT_SIM, true); /* Cập nhật lại cho PowerTask */
    }
    
    return SIM_ST_READY;
}

/**
 * @brief Hàm xử lý khi có tin nhắn SMS gửi tới thiết bị.
 */
static void prv_SMS_ReceivedCallback(SMS_Message_t *msg) {
    LOG_INFO("[SIM TASK] SMS Received from %s: %s", msg->phone, msg->content);
    
    /* 1. Kiểm tra mã xác thực để Add thiết bị (Cấu trúc: "ADD <CODE>") */
    if (strncmp(msg->content, "ADD", 3) == 0 || strncmp(msg->content, "add", 3) == 0) {
        char *code_ptr = msg->content + 3;
        while (*code_ptr == ' ') code_ptr++; // Bỏ qua khoảng trắng ở đầu
        
        /* Loại bỏ ký tự xuống dòng và khoảng trắng ở cuối */
        int len = strlen(code_ptr);
        while (len > 0 && (code_ptr[len-1] == '\r' || code_ptr[len-1] == '\n' || code_ptr[len-1] == ' ')) {
            code_ptr[--len] = '\0';
        }

        if (*code_ptr != '\0') {
            LOG_INFO("[SIM TASK] Pairing request detected with code: [%s]", code_ptr);
            
            /* Nháy LED báo hiệu đã nhận lệnh */
            System_Service_VisualNotify(3);
            
            /* Gửi bản tin xác thực lên Server qua MQTT */
            char pair_json[200];
            snprintf(pair_json, sizeof(pair_json), 
                     "{\"msg\":\"pairing_request\",\"code\":\"%s\",\"phone\":\"%s\"}", 
                     code_ptr, msg->phone);
                     
            MQTT_Service_QueuePublish("status", pair_json);
            return; // Đã xử lý xong, không cần forward SMS thô nữa
        }
    }

    /* 2. Forward các tin nhắn khác lên MQTT (giữ nguyên tính năng cũ) */
    char sms_json[300];
    snprintf(sms_json, sizeof(sms_json), 
             "{\"from\":\"%s\",\"time\":\"%s\",\"content\":\"%s\"}", 
             msg->phone, msg->timestamp, msg->content);
             
    LOG_INFO("[SIM TASK] Forwarding generic SMS to MQTT (topic: sms)...");
    MQTT_Service_QueuePublish("sms", sms_json);
}

void SIM_Task_SetSleep(bool enable) {
    if (enable) {
        LOG_INFO("[SIM TASK] Suspending SIMTask to cleanly power down...");
        if (g_sim_task_id != NULL) {
            osThreadSuspend(g_sim_task_id);
        }
        
        LOG_INFO("[SIM TASK] Powering OFF Module (AT+CPOWD=1)...");
        
        /* Gửi AT+CPOWD=1 để yêu cầu module tắt nguồn 
         * (Cấm SIMTask hoạt động để tránh loạn UART khi đang sập nguồn) */
        SIM_PowerDown(&sim_modem);
        
        sim_modem.is_power_on = false;
        
        /* Chờ module sập hẳn (thường là mất 1-2s sau khi trả lời NORMAL POWER DOWN) */
        osDelay(2000);
    } else {
        LOG_INFO("[SIM TASK] Waking up: Triggering full power-on sequence...");
        
        /* Đánh dấu để State Machine quay lại trạng thái SIM_ST_POWER_ON */
        g_modem_needs_power_on = true;
        
        if (g_sim_task_id != NULL) {
            osThreadResume(g_sim_task_id);
            osSignalSet(g_sim_task_id, SIM_SIG_RI);
        }
    }
}

static void SIM_Task_Entry(void const * argument) {
    SIM_State_t state = SIM_ST_POWER_ON;
    uint32_t last_pub_tick = xTaskGetTickCount();
    uint32_t last_stats_tick = xTaskGetTickCount();
    
    LOG_INFO("[SIM TASK] Started");
    
    /* Chờ hệ thống ổn định nguồn điện sau khi cấp nguồn (Cold Boot) */
    osDelay(3000);
    
    /* Đăng ký nhận sự kiện từ driver */
    SIM_RegisterEventCallback(&sim_modem, SIM_Event_Callback);

    while (1) {
        /* Cập nhật Cờ bận/rảnh cho Power Task.
         * Khai báo bận khi state khác READY hoặc khi đang gửi MQTT / Power_on. */
        bool is_busy = g_sim_task_busy || (state != SIM_ST_READY);
        Power_Task_SetState(POWER_BIT_SIM, !is_busy);
        
        /* Đợi ngắt RI hoặc Timeout 100ms để polling */
        osSignalWait(SIM_SIG_RI, 100);
        
        /* Chạy bộ xử lý URC liên tục */
        SIM_A7670C_Process(&sim_modem);

#if LOG_ENABLE_SYS_MONITOR
        /* In thống kê hệ thống mỗi 60 giây */
        if ((xTaskGetTickCount() - last_stats_tick) > pdMS_TO_TICKS(60000)) {
            Log_PrintSystemStats();
            last_stats_tick = xTaskGetTickCount();
        }
#endif
        
        /* Kiểm tra cờ yêu cầu khởi động lại module từ đầu (sau deep sleep).
         * Cờ này check ở MỌI state để an toàn reset. */
        if (g_modem_needs_power_on) {
            g_modem_needs_power_on = false;
            LOG_WARN("[SIM TASK] Modem power-on requested. Jumping to POWER_ON...");
            state = SIM_ST_POWER_ON;
        }
        
        switch (state) {
            case SIM_ST_POWER_ON:     state = SIM_Handle_PowerOn();      break;
            case SIM_ST_CHECK_COMM:   state = SIM_Handle_CheckComm();    break;
            case SIM_ST_WAIT_NET:     state = SIM_Handle_WaitNet();      break;
            case SIM_ST_SERVICES_INIT:state = SIM_Handle_ServicesInit(); break;
            case SIM_ST_MQTT_CONNECT: state = SIM_Handle_MQTTConnect();  break;
            case SIM_ST_READY:        state = SIM_Handle_Ready(); break;
            case SIM_ST_ERROR:
                LOG_ERROR("[SIM TASK] Critical Error! Resetting...");
                SIM_HardReset(&sim_modem);
                state = SIM_ST_POWER_ON;
                break;
        }
    }
}

bool SIM_Task_IsBusy(void) {
    /* SIM bận khi đang xử lý khởi tạo hoặc MQTT đang hoạt động */
    return g_sim_task_busy || MQTT_Service_IsStable() == false;
}
