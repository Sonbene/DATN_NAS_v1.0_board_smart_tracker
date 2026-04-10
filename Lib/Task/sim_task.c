#include "sim_task.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
#include "sim_a7670c.h"
#include "mqtt_service.h"
#include "sms_service.h"
#include "secrets.h"
#include "log.h"
#include <string.h>
#include <stdio.h>

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

#define SIM_SIG_RI    (1 << 0)

static void SIM_Task_Entry(void const * argument);
static void SIM_Event_Callback(SIM_Message_t *msg);

void SIM_Task_Init(UART_HandleTypeDef *huart) {
    /* 1. Khởi tạo BSP và Driver ngay tại đây */
    BSP_UART_Init(&sim_uart_bus, huart);
    SIM_Init(&sim_modem, &sim_uart_bus);
    
    /* 2. Kích hoạt DMA Receive to Idle (Circular) */
    HAL_UARTEx_ReceiveToIdle_DMA(huart, sim_rx_dma_buf, 512);
    __HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT); /* Tắt ngắt Half-Transfer */

    LOG_INFO("[SIM TASK] Handles initialized. Circular DMA started.");

    /* 3. Tạo Task */
    osThreadDef(SIMTask, SIM_Task_Entry, osPriorityAboveNormal, 0, 512);
    g_sim_task_id = osThreadCreate(osThread(SIMTask), NULL);
}

void SIM_Task_NotifyRIFromISR(void) {
    if (g_sim_task_id != NULL) {
        osSignalSet(g_sim_task_id, SIM_SIG_RI);
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
    if (msg->event == SIM_EVENT_MQTT_MSG) {
        LOG_INFO("[SIM TASK] MQTT Message Received via URC");
        MQTT_Service_HandleURC(&sim_modem, (char*)msg->data);
    } else if (msg->event == SIM_EVENT_SMS_MSG) {
        LOG_INFO("[SIM TASK] SMS Event Received via URC");
        SMS_Service_HandleURC(&sim_modem, (char*)msg->data);
    }
}

/* ========================================================================== *
 * State Handlers
 * ========================================================================== */
static SIM_State_t SIM_Handle_PowerOn(void) {
    SIM_PowerOn(&sim_modem);
    return SIM_ST_CHECK_COMM;
}

static SIM_State_t SIM_Handle_CheckComm(void) {
    if (SIM_SendATCommand(&sim_modem, "AT\r\n", "OK", 1000) == SIM_OK) {
        LOG_INFO("[SIM TASK] Module responding!");
        return SIM_ST_WAIT_NET;
    }
    LOG_INFO("[SIM TASK] Waiting for module response...");
    osDelay(2000);
    return SIM_ST_CHECK_COMM;
}

static SIM_State_t SIM_Handle_WaitNet(void) {
    if (sim_modem.is_net_ready) {
        LOG_INFO("[SIM TASK] Network registered!");
        return SIM_ST_SERVICES_INIT;
    }
    
    LOG_INFO("[SIM TASK] Waiting for network registration... (CREG?)");
    /* Polling CREG manual if URC not catched yet */
    static uint8_t reg_retry = 0;
    SIM_SendATCommand(&sim_modem, "AT+CREG?\r\n", "OK", 1000);
    
    if (++reg_retry > 10) {
        LOG_WARN("[SIM TASK] Network taking too long, forcing search...");
        SIM_SendATCommand(&sim_modem, "AT+COPS=0\r\n", "OK", 5000);
        reg_retry = 0;
    }
    osDelay(3000);
    return SIM_ST_WAIT_NET;
}

static SIM_State_t SIM_Handle_ServicesInit(void) {
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
        
        return SIM_ST_MQTT_CONNECT;
    }
    LOG_ERROR("[SIM TASK] MQTT Service Init Failed, retrying in 5s...");
    osDelay(5000);
    return SIM_ST_SERVICES_INIT;
}

static SIM_State_t SIM_Handle_MQTTConnect(void) {
    if (MQTT_Service_Connect(&sim_modem) == MQTT_OK) {
        /* Subscribe thử một topic với QoS 1 */
        MQTT_Service_Subscribe(&sim_modem, "tracker/cmd", MQTT_QOS1, NULL);
        return SIM_ST_READY;
    }
    LOG_ERROR("[SIM TASK] MQTT Connection Failed, retrying...");
    osDelay(10000);
    return SIM_ST_MQTT_CONNECT;
}

static SIM_State_t SIM_Handle_Ready(uint32_t *last_pub_tick) {
    /* Phục vụ MQTT, publish message định kỳ 10 giây/lần */
    if ((xTaskGetTickCount() - *last_pub_tick) > pdMS_TO_TICKS(10000)) {
        static uint32_t msg_counter = 0;
        static uint8_t fail_cnt = 0;
        msg_counter++;
        
        char payload[128];
        snprintf(payload, sizeof(payload), "{\"id\":\"%s\",\"cnt\":%lu,\"uptime\":%lu}", 
                 MQTT_CLIENT_ID, msg_counter, xTaskGetTickCount() / 1000);
                 
        if (MQTT_Service_Publish(&sim_modem, "tracker/sensor", (const uint8_t*)payload, strlen(payload), MQTT_QOS1) == MQTT_OK) {
            LOG_INFO("[SIM TASK] MQTT TX #%lu OK", msg_counter);
            fail_cnt = 0;
        } else {
            fail_cnt++;
            LOG_ERROR("[SIM TASK] MQTT TX FAIL (%d/3)", fail_cnt);
            if (fail_cnt >= 3) {
                LOG_WARN("[SIM TASK] Too many failures, forcing reconnect...");
                fail_cnt = 0;
                MQTT_Service_Disconnect(&sim_modem);
                return SIM_ST_MQTT_CONNECT;
            }
        }
        *last_pub_tick = xTaskGetTickCount();
    }
    return SIM_ST_READY;
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
        
        switch (state) {
            case SIM_ST_POWER_ON:     state = SIM_Handle_PowerOn();      break;
            case SIM_ST_CHECK_COMM:   state = SIM_Handle_CheckComm();    break;
            case SIM_ST_WAIT_NET:     state = SIM_Handle_WaitNet();      break;
            case SIM_ST_SERVICES_INIT:state = SIM_Handle_ServicesInit(); break;
            case SIM_ST_MQTT_CONNECT: state = SIM_Handle_MQTTConnect();  break;
            case SIM_ST_READY:        state = SIM_Handle_Ready(&last_pub_tick); break;
            case SIM_ST_ERROR:
                LOG_ERROR("[SIM TASK] Critical Error! Resetting...");
                SIM_HardReset(&sim_modem);
                state = SIM_ST_POWER_ON;
                break;
        }
    }
}
