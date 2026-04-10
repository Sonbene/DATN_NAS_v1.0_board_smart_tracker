#include "sim_a7670c.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "log.h"

void SIM_Init(SIM_Handle_t *handle, BSP_UART_Handle_t *uart) {
    if (handle == NULL || uart == NULL) return;
    
    memset(handle, 0, sizeof(SIM_Handle_t));
    handle->uart_handle = uart;
    
    /* Khởi tạo Ring Buffer */
    RingBuffer_Init(&handle->rx_rb, handle->rb_mem, SIM_RING_BUF_SIZE);

    /* Gán chân GPIO theo thông tin người dùng cung cấp */
    handle->rst_port = GPIOA;
    handle->rst_pin = GPIO_PIN_4;
    
    handle->ri_port = GPIOA;
    handle->ri_pin = GPIO_PIN_5;
    
    handle->dtr_port = GPIOA;
    handle->dtr_pin = GPIO_PIN_6;
    
    handle->pwr_port = GPIOA;
    handle->pwr_pin = GPIO_PIN_7;
    
    handle->is_power_on = false;
}

void SIM_PowerOn(SIM_Handle_t *handle) {
    LOG_INFO("[SIM] Starting Smart Power-On Sequence...");

    /* 1. Kiểm tra xem module đã bật sẵn chưa */
    if (SIM_TestAlive(handle) == SIM_OK) {
        LOG_INFO("[SIM] Module already alive, skipping power sequence.");
        handle->is_power_on = true;
        return;
    }

    LOG_INFO("[SIM] Module not responding, executing hardware power-on...");

    /* 2. Hardware Reset Pulse */
    HAL_GPIO_WritePin(handle->rst_port, handle->rst_pin, GPIO_PIN_SET);
    osDelay(300); 
    HAL_GPIO_WritePin(handle->rst_port, handle->rst_pin, GPIO_PIN_RESET);
    osDelay(1500);

    /* 3. PWRKEY sequence */
    HAL_GPIO_WritePin(handle->pwr_port, handle->pwr_pin, GPIO_PIN_SET);
    osDelay(1500); 
    HAL_GPIO_WritePin(handle->pwr_port, handle->pwr_pin, GPIO_PIN_RESET);
    
    /* 4. Đợi phản hồi AT (Thử trong 15 giây với nhịp độ 1s như temp_mqtt) */
    LOG_INFO("[SIM] Waiting for SIM to respond (up to 15s)...");
    osDelay(3000); // Chờ boot UART
    
    bool boot_ok = false;
    for (int i = 0; i < 15; i++) {
        /* Xóa sạch buffer trước khi hỏi AT để tránh nhiễu URC */
        RingBuffer_Flush(&handle->rx_rb);
        
        if (SIM_TestAlive(handle) == SIM_OK) {
            boot_ok = true;
            break;
        }
        LOG_INFO("[SIM] Still booting... (%d/15)", i+1);
        osDelay(1000);
    }

    if (boot_ok) {
        LOG_INFO("[SIM] Power On Success!");
        handle->is_power_on = true;
        
        /* Cấu hình các tham số giúp hệ thống điện ổn định (Giống temp_mqtt) */
        LOG_INFO("[SIM] Optimizing power and error reporting...");
        SIM_SendATCommand(handle, "ATE0\r\n", "OK", 1000);         // Tắt echo
        SIM_SendATCommand(handle, "AT+CMEE=2\r\n", "OK", 1000);   // Bật lỗi chi tiết
        SIM_SendATCommand(handle, "AT+CVAUXS=0\r\n", "OK", 1000); // Tắt nguồn Antenna chủ động để giảm dòng sụt áp
    } else {
        LOG_ERROR("[SIM] Failed to Power On!");
    }
}

void SIM_HardReset(SIM_Handle_t *handle) {
    LOG_WARN("[SIM] Hard resetting module...");
    HAL_GPIO_WritePin(handle->rst_port, handle->rst_pin, GPIO_PIN_SET);
    osDelay(500);
    HAL_GPIO_WritePin(handle->rst_port, handle->rst_pin, GPIO_PIN_RESET);
    osDelay(2000);
}

SIM_Status_t SIM_SendATCommandEx(SIM_Handle_t *handle, const char *command, const char *expected_response, char *out_buf, uint16_t out_len, uint32_t timeout_ms) {
    if (handle == NULL || command == NULL) return SIM_ERROR;

    RingBuffer_Flush(&handle->rx_rb);

    if (BSP_UART_Transmit(handle->uart_handle, (uint8_t*)command, strlen(command), 100) != BSP_UART_OK) {
        return SIM_ERROR;
    }

    uint32_t start_time = HAL_GetTick();
    while (HAL_GetTick() - start_time < timeout_ms) {
        if (expected_response != NULL && RingBuffer_Search(&handle->rx_rb, expected_response)) {
            if (out_buf && out_len > 0) {
                RingBuffer_PeekMulti(&handle->rx_rb, (uint8_t*)out_buf, out_len - 1);
                out_buf[out_len - 1] = '\0';
            }
            return SIM_OK;
        }
        if (RingBuffer_Search(&handle->rx_rb, "ERROR")) return SIM_ERROR;
        osDelay(10);
    }
    return SIM_TIMEOUT;
}

SIM_Status_t SIM_SendATCommand(SIM_Handle_t *handle, const char *command, const char *expected_response, uint32_t timeout_ms) {
    return SIM_SendATCommandEx(handle, command, expected_response, NULL, 0, timeout_ms);
}

SIM_Status_t SIM_TestAlive(SIM_Handle_t *handle) {
    return SIM_SendATCommand(handle, "AT\r\n", "OK", 1000);
}

SIM_Status_t SIM_EchoOff(SIM_Handle_t *handle) {
    return SIM_SendATCommand(handle, "ATE0\r\n", "OK", 1000);
}

SIM_Status_t SIM_GetIMEI(SIM_Handle_t *handle, char *out, uint16_t max_len) {
    return SIM_SendATCommandEx(handle, "AT+GSN\r\n", "OK", out, max_len, 2000);
}

SIM_Status_t SIM_GetCSQ(SIM_Handle_t *handle, int *rssi, int *ber) {
    char buf[64];
    if (SIM_SendATCommandEx(handle, "AT+CSQ\r\n", "OK", buf, sizeof(buf), 2000) == SIM_OK) {
        char *p = strstr(buf, "+CSQ:");
        if (p) {
            sscanf(p, "+CSQ: %d,%d", rssi, ber);
            return SIM_OK;
        }
    }
    return SIM_ERROR;
}

SIM_Status_t SIM_CheckSIMCard(SIM_Handle_t *handle) {
    return SIM_SendATCommand(handle, "AT+CPIN?\r\n", "READY", 2000);
}

SIM_Status_t SIM_GetNetworkReg(SIM_Handle_t *handle, int *stat) {
    char buf[64];
    if (SIM_SendATCommandEx(handle, "AT+CREG?\r\n", "OK", buf, sizeof(buf), 2000) == SIM_OK) {
        char *p = strstr(buf, "+CREG:");
        if (p) {
            int n;
            sscanf(p, "+CREG: %d,%d", &n, stat);
            return SIM_OK;
        }
    }
    return SIM_ERROR;
}

SIM_Status_t SIM_GetOperator(SIM_Handle_t *handle, char *out, uint16_t max_len) {
    return SIM_SendATCommandEx(handle, "AT+COPS?\r\n", "OK", out, max_len, 2000);
}

SIM_Status_t SIM_SendSMS(SIM_Handle_t *handle, const char *phone, const char *msg) {
    char cmd[64];
    /* Đảm bảo đang ở chế độ Text Mode */
    SIM_SendATCommand(handle, "AT+CMGF=1\r\n", "OK", 1000);
    snprintf(cmd, sizeof(cmd), "AT+CMGS=\"%s\"\r\n", phone);
    
    LOG_INFO("[SIM] Sending SMS to %s...", phone);
    if (SIM_SendATCommand(handle, cmd, ">", 2000) == SIM_OK) {
        BSP_UART_Transmit(handle->uart_handle, (uint8_t*)msg, strlen(msg), 500);
        uint8_t ctrl_z = 0x1A;
        BSP_UART_Transmit(handle->uart_handle, &ctrl_z, 1, 100);
        return SIM_SendATCommand(handle, NULL, "OK", 10000);
    }
    return SIM_ERROR;
}

SIM_Status_t SIM_ReadSMS(SIM_Handle_t *handle, int index, char *out_msg, uint16_t max_len) {
    char cmd[32];
    snprintf(cmd, sizeof(cmd), "AT+CMGR=%d\r\n", index);
    
    char buf[512];
    if (SIM_SendATCommandEx(handle, cmd, "OK", buf, sizeof(buf), 5000) == SIM_OK) {
        /* Phản hồi có dạng: +CMGR: "REC READ","+84xxx",,"24/04/10,22:00:00+28"\r\nNội dung tin nhắn\r\nOK */
        char *p = strstr(buf, "\r\n");
        if (p) {
            p += 2; // Bỏ qua \r\n sau dòng +CMGR
            char *p_end = strstr(p, "\r\nOK");
            if (p_end) {
                uint16_t len = p_end - p;
                if (len >= max_len) len = max_len - 1;
                memcpy(out_msg, p, len);
                out_msg[len] = '\0';
                return SIM_OK;
            }
        }
    }
    return SIM_ERROR;
}

SIM_Status_t SIM_DeleteSMS(SIM_Handle_t *handle, int index) {
    char cmd[32];
    snprintf(cmd, sizeof(cmd), "AT+CMGD=%d\r\n", index);
    return SIM_SendATCommand(handle, cmd, "OK", 2000);
}

SIM_Status_t SIM_PowerDown(SIM_Handle_t *handle) {
    return SIM_SendATCommand(handle, "AT+CPOWD=1\r\n", "NORMAL POWER DOWN", 5000);
}

SIM_Status_t SIM_SendATWithData(SIM_Handle_t *handle, const char *command, const uint8_t *data, uint16_t data_len, const char *expected_response, uint32_t prompt_timeout_ms, uint32_t resp_timeout_ms) {
    if (handle == NULL || command == NULL || data == NULL) return SIM_ERROR;

    RingBuffer_Flush(&handle->rx_rb);

    /* 1. Gửi lệnh AT */
    LOG_INFO("[SIM] AT Send (Wait Prompt): %s", command);
    if (BSP_UART_Transmit(handle->uart_handle, (uint8_t*)command, strlen(command), 100) != BSP_UART_OK) {
        return SIM_ERROR;
    }

    /* 2. Đợi ký tự '>' */
    bool prompt_received = false;
    uint32_t start_time = HAL_GetTick();
    while (HAL_GetTick() - start_time < prompt_timeout_ms) {
        if (RingBuffer_Search(&handle->rx_rb, ">")) {
            prompt_received = true;
            break;
        }
        osDelay(10);
    }

    if (!prompt_received) {
        LOG_ERROR("[SIM] Timeout waiting for '>' prompt");
        return SIM_TIMEOUT;
    }

    /* Xóa buffer cũ trước khi nhận kết quả của data */
    RingBuffer_Flush(&handle->rx_rb);

    /* 3. Phản hồi Payload */
    LOG_INFO("[SIM] Prompt received (>), sending %d bytes payload...", data_len);
    if (BSP_UART_Transmit(handle->uart_handle, (uint8_t*)data, data_len, 500) != BSP_UART_OK) {
        return SIM_ERROR;
    }

    /* 4. Đợi phản hồi cuối cùng (vd OK/ERROR) */
    start_time = HAL_GetTick();
    while (HAL_GetTick() - start_time < resp_timeout_ms) {
        if (expected_response != NULL && RingBuffer_Search(&handle->rx_rb, expected_response)) {
            return SIM_OK;
        }
        if (expected_response == NULL && RingBuffer_Search(&handle->rx_rb, "OK")) {
            return SIM_OK;
        }
        if (RingBuffer_Search(&handle->rx_rb, "ERROR")) {
            return SIM_ERROR;
        }
        osDelay(10);
    }

    LOG_ERROR("[SIM] Data Response Timeout");
    return SIM_TIMEOUT;
}

void SIM_UART_Receive_Handler(SIM_Handle_t *handle, uint8_t *data, uint16_t size) {
    if (handle == NULL || data == NULL || size == 0) return;

    /* Ghi dữ liệu vào Ring Buffer */
    for (uint16_t i = 0; i < size; i++) {
        RingBuffer_Write(&handle->rx_rb, data[i]);
    }
}

void SIM_RegisterEventCallback(SIM_Handle_t *handle, SIM_EventCallback_t cb) {
    if (handle) handle->event_cb = cb;
}

void SIM_A7670C_Process(SIM_Handle_t *handle) {
    if (handle == NULL) return;

    char line[256];
    while (RingBuffer_ReadLine(&handle->rx_rb, line, sizeof(line))) {
        /* Bỏ qua các dòng trống */
        if (strlen(line) <= 2) continue;
        
        LOG_INFO("[SIM URC] %s", line);

        /* --- 1. Nhóm MQTT --- */
        /* Định dạng: +CMQPUBLISH: <index>,<topic>,<qos>,<retain>,<dup>,<len>,<data> */
        if (strstr(line, "+CMQPUBLISH:") != NULL) {
            if (handle->event_cb) {
                SIM_Message_t msg;
                msg.event = SIM_EVENT_MQTT_MSG;
                msg.data = (uint8_t*)line;
                msg.len = strlen(line);
                handle->event_cb(&msg);
            }
        }
        
        /* --- 2. Nhóm SMS --- */
        /* Định dạng: +CMTI: "SM",<index> HOẶC +CMT: ... */
        else if (strstr(line, "+CMTI:") != NULL || strstr(line, "+CMT:") != NULL) {
            if (handle->event_cb) {
                SIM_Message_t msg;
                msg.event = SIM_EVENT_SMS_MSG;
                msg.data = (uint8_t*)line;
                msg.len = strlen(line);
                handle->event_cb(&msg);
            }
        }

        /* --- 3. Nhóm Network / Trạng thái hệ thống --- */
        /* Định dạng: +CREG: <n>,<stat> */
        else if (strstr(line, "+CREG:") != NULL) {
            char *p = strstr(line, ",");
            if (p) {
                int stat = atoi(p + 1);
                if (stat == 1 || stat == 5) {
                    handle->is_net_ready = true;
                    if (handle->event_cb) {
                        SIM_Message_t msg = {SIM_EVENT_NET_READY, NULL, 0};
                        handle->event_cb(&msg);
                    }
                } else {
                    handle->is_net_ready = false;
                    if (handle->event_cb) {
                        SIM_Message_t msg = {SIM_EVENT_NET_LOST, NULL, 0};
                        handle->event_cb(&msg);
                    }
                }
            }
        }
    }
}
