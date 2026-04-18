#include "sim_a7670c.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "log.h"
#include "system_service.h"

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

    /* Force a hardware reset to ensure clean state after cold boot */
    LOG_INFO("[SIM] Executing hardware power-on/reset...");

    LOG_INFO("[SIM] Module not responding, executing hardware power-on...");

    /* 2. Hardware Reset Pulse */
    HAL_GPIO_WritePin(handle->rst_port, handle->rst_pin, GPIO_PIN_SET);
    osDelay(300); 
    HAL_GPIO_WritePin(handle->rst_port, handle->rst_pin, GPIO_PIN_RESET);
    osDelay(1500);

    /* 3. PWRKEY sequence: Pulse LOW (Active) then return HIGH (Idle) */
    HAL_GPIO_WritePin(handle->pwr_port, handle->pwr_pin, GPIO_PIN_RESET);
    osDelay(1500); 
    HAL_GPIO_WritePin(handle->pwr_port, handle->pwr_pin, GPIO_PIN_SET);
    
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
    /* Pulse LOW (Active) then return HIGH (Idle) */
    HAL_GPIO_WritePin(handle->rst_port, handle->rst_pin, GPIO_PIN_RESET);
    osDelay(500);
    HAL_GPIO_WritePin(handle->rst_port, handle->rst_pin, GPIO_PIN_SET);
    osDelay(2000); // Chờ ổn định sau reset 
}

SIM_Status_t SIM_SendATCommandEx(SIM_Handle_t *handle, const char *command, const char *expected_response, char *out_buf, uint16_t out_len, uint32_t timeout_ms) {
    if (handle == NULL || command == NULL) return SIM_ERROR;

    /* Dùng Mutex để khoá độc quyền UART, ngăn chặn Race Condition khi nhiều Task gọi lệnh AT */
    if (BSP_UART_LockTx(handle->uart_handle, timeout_ms) != BSP_UART_OK) {
        return SIM_BUSY;
    }

    RingBuffer_Flush(&handle->rx_rb);
    handle->is_waiting_resp = true;

    if (BSP_UART_Transmit(handle->uart_handle, (uint8_t*)command, strlen(command), 100) != BSP_UART_OK) {
        handle->is_waiting_resp = false;
        BSP_UART_UnlockTx(handle->uart_handle);
        return SIM_ERROR;
    }

    uint32_t start_time = HAL_GetTick();
    while (HAL_GetTick() - start_time < timeout_ms) {
        if (expected_response != NULL && RingBuffer_Search(&handle->rx_rb, expected_response)) {
            if (out_buf && out_len > 0) {
                RingBuffer_PeekMulti(&handle->rx_rb, (uint8_t*)out_buf, out_len - 1);
                out_buf[out_len - 1] = '\0';
            }
            handle->is_waiting_resp = false;
            BSP_UART_UnlockTx(handle->uart_handle);
            return SIM_OK;
        }
        if (RingBuffer_Search(&handle->rx_rb, "ERROR")) {
            handle->is_waiting_resp = false;
            BSP_UART_UnlockTx(handle->uart_handle);
            return SIM_ERROR;
        }
        osDelay(5); /* Giảm xuống 1ms để bắt phản hồi nhanh nhất có thể */
    }
    handle->is_waiting_resp = false;
    BSP_UART_UnlockTx(handle->uart_handle);
    return SIM_TIMEOUT;
}

SIM_Status_t SIM_SendATCommand(SIM_Handle_t *handle, const char *command, const char *expected_response, uint32_t timeout_ms) {
    return SIM_SendATCommandEx(handle, command, expected_response, NULL, 0, timeout_ms);
}

SIM_Status_t SIM_GetIMEI(SIM_Handle_t *handle, char *out, uint16_t max_len) {
    if (handle == NULL || out == NULL || max_len < 16) return SIM_ERROR;

    char buf[64];
    /* AT+GSN trả về chuỗi IMEI trực tiếp */
    if (SIM_SendATCommandEx(handle, "AT+GSN\r\n", "OK", buf, sizeof(buf), 2000) == SIM_OK) {
        /* Bỏ qua các ký tự trắng/newline ở đầu nếu có */
        char *p = buf;
        while (*p == '\r' || *p == '\n') p++;
        
        uint16_t len = 0;
        while (p[len] >= '0' && p[len] <= '9' && len < max_len - 1) {
            out[len] = p[len];
            len++;
        }
        out[len] = '\0';
        
        if (len >= 14) { // IMEI thường có 15 số
            LOG_INFO("[SIM] IMEI: %s", out);
            return SIM_OK;
        }
    }
    return SIM_ERROR;
}

SIM_Status_t SIM_TestAlive(SIM_Handle_t *handle) {
    return SIM_SendATCommand(handle, "AT\r\n", "OK", 1000);
}

SIM_Status_t SIM_EchoOff(SIM_Handle_t *handle) {
    return SIM_SendATCommand(handle, "ATE0\r\n", "OK", 1000);
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

SIM_Status_t SIM_ReadSMS(SIM_Handle_t *handle, int index, char *out_phone, char *out_time, char *out_msg, uint16_t max_len) {
    char cmd[32];
    snprintf(cmd, sizeof(cmd), "AT+CMGR=%d\r\n", index);
    
    char buf[512];
    if (SIM_SendATCommandEx(handle, cmd, "OK", buf, sizeof(buf), 5000) == SIM_OK) {
        /* Phản hồi thực tế thường là: \r\n+CMGR: "REC UNREAD","+84...","","..."\r\nNội dung\r\nOK */
        
        char *p_cmgr = strstr(buf, "+CMGR:");
        if (!p_cmgr) return SIM_ERROR;

        char *p_line_end = strstr(p_cmgr, "\r\n");
        if (!p_line_end) return SIM_ERROR;
        
        *p_line_end = '\0'; // Ngắt chuỗi tại cuối dòng +CMGR để parse header

        /* 1. Parse header (SĐT và Thời gian) */
        char *quotes[10];
        int quote_count = 0;
        char *p = p_cmgr;
        while ((p = strchr(p, '\"')) != NULL && quote_count < 10) {
            quotes[quote_count++] = p;
            p++;
        }

        // SĐT thường nằm ở ngoặc kép thứ 3 và 4
        if (quote_count >= 4 && out_phone) {
            int len = quotes[3] - quotes[2] - 1;
            if (len > 19) len = 19;
            if (len > 0) {
                memcpy(out_phone, quotes[2] + 1, len);
                out_phone[len] = '\0';
            }
        }

        // Thời gian thường nằm ở ngoặc kép thứ 7 và 8
        if (quote_count >= 8 && out_time) {
            int len = quotes[7] - quotes[6] - 1;
            if (len > 31) len = 31;
            if (len > 0) {
                memcpy(out_time, quotes[6] + 1, len);
                out_time[len] = '\0';
            }
        }

        /* 2. Parse nội dung thực tế (bắt đầu sau p_line_end cũ) */
        char *p_content = p_line_end + 2;
        char *p_ok = strstr(p_content, "\r\nOK");
        if (p_ok) {
            uint16_t len = p_ok - p_content;
            if (len >= max_len) len = max_len - 1;
            memcpy(out_msg, p_content, len);
            out_msg[len] = '\0';
            
            /* Xử lý an toàn cho JSON: Thay thế " thành ' */
            for (int i = 0; i < len; i++) {
                if (out_msg[i] == '\"') out_msg[i] = '\'';
                if (out_msg[i] == '\r' || out_msg[i] == '\n') out_msg[i] = ' '; // Xóa xuống dòng trong content
            }
            return SIM_OK;
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
    /* Lệnh tắt nguồn cho SIMCom A7670C là AT+CPOF (Trả về OK rồi sập nguồn) */
    return SIM_SendATCommand(handle, "AT+CPOF\r\n", "OK", 5000);
}

SIM_Status_t SIM_SetSleepMode(SIM_Handle_t *handle, bool enable) {
    if (handle == NULL) return SIM_ERROR;

    if (enable) {
        /* 1. Kích hoạt chế độ ngủ bằng lệnh AT */
        if (SIM_SendATCommand(handle, "AT+CSCLK=1\r\n", "OK", 1000) != SIM_OK) {
            return SIM_ERROR;
        }
        /* 2. Kéo chân DTR lên CAO để module có thể đi ngủ */
        HAL_GPIO_WritePin(handle->dtr_port, handle->dtr_pin, GPIO_PIN_SET);
        LOG_INFO("[SIM] Sleep Mode Enabled (DTR High)");
    } else {
        /* 1. ÉP ĐÁNH THỨC PHẦN CỨNG: Hạ DTR xuống Thấp */
        HAL_GPIO_WritePin(handle->dtr_port, handle->dtr_pin, GPIO_PIN_RESET);
        
        /* Toggles DTR để đảm bảo module nhận diện được sự thay đổi trạng thái nếu nó đang kẹt */
        HAL_GPIO_WritePin(handle->dtr_port, handle->dtr_pin, GPIO_PIN_SET);
        osDelay(100);
        HAL_GPIO_WritePin(handle->dtr_port, handle->dtr_pin, GPIO_PIN_RESET);
        
        osDelay(800); // Tăng thời gian chờ module ổn định UART sau khi thức dậy
        
        /* 2. Tắt chế độ ngủ tự động */
        SIM_SendATCommand(handle, "AT+CSCLK=0\r\n", "OK", 1000);
        LOG_INFO("[SIM] Module Wakeup (DTR Low forced)");
    }
    return SIM_OK;
}

SIM_Status_t SIM_SendATWithData(SIM_Handle_t *handle, const char *command, const uint8_t *data, uint16_t data_len, const char *expected_response, uint32_t prompt_timeout_ms, uint32_t resp_timeout_ms) {
    if (handle == NULL || command == NULL || data == NULL) return SIM_ERROR;

    /* Dùng Mutex để khoá độc quyền UART, đảm bảo không ai xen ngang AT+CLBS=1 vào giữa quá trình gửi Payload */
    if (BSP_UART_LockTx(handle->uart_handle, prompt_timeout_ms + resp_timeout_ms) != BSP_UART_OK) {
        return SIM_BUSY;
    }

    RingBuffer_Flush(&handle->rx_rb);

    /* 1. Gửi lệnh AT */
    LOG_INFO("[SIM] AT Send (Wait Prompt): %s", command);
    if (BSP_UART_Transmit(handle->uart_handle, (uint8_t*)command, strlen(command), 100) != BSP_UART_OK) {
        BSP_UART_UnlockTx(handle->uart_handle);
        return SIM_ERROR;
    }

    /* 2. Đợi ký tự '>' hoặc lỗi ERROR */
    bool prompt_received = false;
    uint32_t start_time = HAL_GetTick();
    while (HAL_GetTick() - start_time < prompt_timeout_ms) {
        if (RingBuffer_Search(&handle->rx_rb, ">")) {
            prompt_received = true;
            break;
        }
        if (RingBuffer_Search(&handle->rx_rb, "ERROR") || RingBuffer_Search(&handle->rx_rb, "+CME ERROR")) {
            LOG_ERROR("[SIM] Command rejected with ERROR (no prompt)");
            BSP_UART_UnlockTx(handle->uart_handle);
            return SIM_ERROR;
        }
        osDelay(10);
    }

    if (!prompt_received) {
        LOG_ERROR("[SIM] Timeout waiting for '>' prompt");
        BSP_UART_UnlockTx(handle->uart_handle);
        return SIM_TIMEOUT;
    }

    /* Xóa buffer cũ trước khi nhận kết quả của data */
    RingBuffer_Flush(&handle->rx_rb);

    /* 3. Phản hồi Payload */
    LOG_INFO("[SIM] Prompt received (>), sending %d bytes payload...", data_len);
    if (BSP_UART_Transmit(handle->uart_handle, (uint8_t*)data, data_len, 500) != BSP_UART_OK) {
        BSP_UART_UnlockTx(handle->uart_handle);
        return SIM_ERROR;
    }

    /* 4. Đợi phản hồi cuối cùng (vd OK/ERROR) */
    start_time = HAL_GetTick();
    while (HAL_GetTick() - start_time < resp_timeout_ms) {
        if (expected_response != NULL && RingBuffer_Search(&handle->rx_rb, expected_response)) {
            BSP_UART_UnlockTx(handle->uart_handle);
            return SIM_OK;
        }
        if (expected_response == NULL && RingBuffer_Search(&handle->rx_rb, "OK")) {
            BSP_UART_UnlockTx(handle->uart_handle);
            return SIM_OK;
        }
        if (RingBuffer_Search(&handle->rx_rb, "ERROR")) {
            BSP_UART_UnlockTx(handle->uart_handle);
            return SIM_ERROR;
        }
        osDelay(10);
    }

    LOG_ERROR("[SIM] Data Response Timeout");
    BSP_UART_UnlockTx(handle->uart_handle);
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
    
    /* Nếu đang chờ phản hồi lệnh AT đồng bộ ở task khác, 
       tạm dừng xử lý URC để tránh "tranh giành" dữ liệu trong RingBuffer */
    if (handle->is_waiting_resp) return;

    static bool g_mqtt_rx_ongoing = false;
    char line[256];
    while (RingBuffer_ReadLine(&handle->rx_rb, line, sizeof(line))) {
        /* Bỏ qua các dòng trống */
        if (strlen(line) <= 2) continue;
        
        LOG_INFO("[SIM URC] %s", line);

        /* --- 1. Nhóm MQTT (Hỗ trợ cả MQTT Standard và CMQTT Stack) --- */
        bool is_mqtt_line = false;
        if (strstr(line, "+CMQPUBLISH:") != NULL || strstr(line, "+CMQTTRX") != NULL || strstr(line, "+CMQTTCONNLOST:") != NULL) {
            is_mqtt_line = true;
            if (strstr(line, "+CMQTTRXSTART:")) g_mqtt_rx_ongoing = true;
            if (strstr(line, "+CMQTTRXEND:")) g_mqtt_rx_ongoing = false;
        } else if (g_mqtt_rx_ongoing) {
            /* Nếu đang trong luồng nhận MQTT, các dòng dữ liệu thô (Topic/Payload) cũng phải được gửi đi */
            is_mqtt_line = true;
        }

        if (is_mqtt_line) {
            if (handle->event_cb) {
                SIM_Message_t msg;
                msg.event = SIM_EVENT_MQTT_MSG;
                msg.data = (uint8_t*)line;
                msg.len = strlen(line);
                handle->event_cb(&msg);
            }
            continue;
        }
        
        /* --- 2. Nhóm SMS --- */
        if (strstr(line, "+CMTI:") != NULL || strstr(line, "+CMT:") != NULL) {
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
        
        /* --- 4. Nhóm LBS (Vị trí trạm phát sóng) --- */
        else if (strstr(line, "+CLBS:") != NULL) {
            float lbs_lat = 0, lbs_lon = 0;
            int res = -1, prec = 0;
            int ty=0, tmon=0, td=0, th=0, tmin=0, ts=0;

            /* Thử parse định dạng đầy đủ (10 trường) */
            int matched = sscanf(line, "+CLBS: %d,%f,%f,%d,%d/%d/%d,%d:%d:%d", 
                                 &res, &lbs_lat, &lbs_lon, &prec, &ty, &tmon, &td, &th, &tmin, &ts);
            
            if (matched < 10) {
                /* Nếu không đủ 10, thử parse định dạng ngắn (4 trường) */
                matched = sscanf(line, "+CLBS: %d,%f,%f,%d", &res, &lbs_lat, &lbs_lon, &prec);
            }

            if (res == 0 && matched >= 3) {
                LOG_INFO("[SIM] LBS URC Auto-Update: %.6f, %.6f", lbs_lat, lbs_lon);
                
                /* Lấy dữ liệu snapshot hiện tại để giữ lại thông tin thời gian nếu LBS không có time */
                SystemData_t data;
                System_Service_GetSnapshot(&data);
                
                if (matched < 10) {
                    ty = data.gps.year; tmon = data.gps.month; td = data.gps.day;
                    th = data.gps.hour; tmin = data.gps.min; ts = data.gps.sec;
                }

                System_Service_UpdateGPS(lbs_lat, lbs_lon, 0, 1, 0, 
                                        (uint8_t)th, (uint8_t)tmin, (uint8_t)ts, 
                                        (uint8_t)td, (uint8_t)tmon, (uint8_t)ty, 
                                        POS_SOURCE_LBS);
            } else {
                LOG_WARN("[SIM] LBS URC parsing failed: %s", line);
            }
        }
        
        /* --- 5. Nhóm Hệ thống (Reboot/Ready) --- */
        else if (strstr(line, "*ATREADY: 1") != NULL) {
            LOG_WARN("[SIM] Modem Reboot Detected (*ATREADY)");
            if (handle->event_cb) {
                SIM_Message_t msg = {SIM_EVENT_MODEM_RESET, NULL, 0};
                handle->event_cb(&msg);
            }
        }
    }
}

SIM_Status_t SIM_MQTT_IsConnected(SIM_Handle_t *handle) {
    if (handle == NULL) return SIM_ERROR;
    
    char resp[128];
    /* Kiểm tra trạng thái kết nối của client 0 */
    if (SIM_SendATCommandEx(handle, "AT+CMQTTCONNECT?\r\n", "OK", resp, sizeof(resp), 2000) == SIM_OK) {
        /* Phản hồi mong đợi khi có kết nối: +CMQTTCONNECT: 0,"tcp://...",... */
        if (strstr(resp, "+CMQTTCONNECT: 0,\"tcp")) {
            return SIM_OK;
        }
    }
    return SIM_ERROR;
}

SIM_Status_t SIM_GetLBSPosition(SIM_Handle_t *handle, float *lat, float *lon,
                                 uint8_t *y, uint8_t *mon, uint8_t *d,
                                 uint8_t *h, uint8_t *min, uint8_t *s) {
    if (handle == NULL) return SIM_ERROR;

    /* AT+CLBS=1: Kích hoạt truy vấn vị trí. 
       Kết quả sẽ được trả về dạng URC (+CLBS: ...) và được xử lý tự động trong SIM_A7670C_Process.
       Hàm này trả về OK nếu module chấp nhận lệnh. */
    return SIM_SendATCommand(handle, "AT+CLBS=1\r\n", "OK", 5000);
}
