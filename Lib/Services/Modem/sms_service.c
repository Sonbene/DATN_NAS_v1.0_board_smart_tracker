#include "sms_service.h"
#include "log.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static SMS_ReceivedCallback_t g_sms_cb = NULL;

SMS_Status_t SMS_Service_Init(SIM_Handle_t *sim) {
    if (sim == NULL) return SMS_ERROR;

    LOG_INFO("[SMS] Initializing SMS Service...");
    
    /* 1. Set Text Mode */
    if (SIM_SendATCommand(sim, "AT+CMGF=1\r\n", "OK", 2000) != SIM_OK) {
        LOG_ERROR("[SMS] Failed to set SMS Text Mode");
        return SMS_ERROR;
    }

    /* 2. Cấu hình hiển thị tin nhắn mới (URC)
     * AT+CNMI=<mode>,<mt>,<bm>,<ds>,<bfr>
     * mt=1: Thông báo chỉ số index lưu trong SIM (+CMTI)
     * mt=2: Hiển thị trực tiếp nội dung tin nhắn (+CMT)
     */
    if (SIM_SendATCommand(sim, "AT+CNMI=2,1,0,0,0\r\n", "OK", 2000) != SIM_OK) {
        LOG_WARN("[SMS] Failed to configure SMS URC (CNMI)");
    }

    /* 3. Kích hoạt chân RI (PA5) nháy khi có SMS */
    SIM_SendATCommand(sim, "AT+CFGRI=1\r\n", "OK", 1000);

    /* 3. Chọn bộ nhớ lưu trữ mặc định là SIM card ("SM") */
    SIM_SendATCommand(sim, "AT+CPMS=\"SM\",\"SM\",\"SM\"\r\n", "OK", 2000);

    LOG_INFO("[SMS] Service Initialized OK");
    return SMS_OK;
}

SMS_Status_t SMS_Service_Send(SIM_Handle_t *sim, const char *phone, const char *content) {
    if (sim == NULL || phone == NULL || content == NULL) return SMS_ERROR;

    if (SIM_SendSMS(sim, phone, content) == SIM_OK) {
        LOG_INFO("[SMS] Message sent to %s successfully", phone);
        return SMS_OK;
    } else {
        LOG_ERROR("[SMS] Failed to send message to %s", phone);
        return SMS_ERROR;
    }
}

void SMS_Service_RegisterCallback(SMS_ReceivedCallback_t cb) {
    g_sms_cb = cb;
}

void SMS_Service_HandleURC(SIM_Handle_t *sim, char *line) {
    if (line == NULL) return;

    /* Trường hợp 1: Có tin nhắn mới lưu ở bộ nhớ (+CMTI: "SM",<index>) */
    if (strstr(line, "+CMTI:")) {
        char *p = strstr(line, ",");
        if (p) {
            int index = atoi(p + 1);
            LOG_INFO("[SMS] New SMS at index %d. Reading...", index);
            
            SMS_Message_t msg;
            memset(&msg, 0, sizeof(msg));
            
            if (SIM_ReadSMS(sim, index, msg.phone, msg.timestamp, msg.content, sizeof(msg.content)) == SIM_OK) {
                LOG_INFO("[SMS] From: %s, Time: %s", msg.phone, msg.timestamp);
                LOG_INFO("[SMS] Content: %s", msg.content);
                
                if (g_sms_cb) {
                    g_sms_cb(&msg);
                }
                
                /* Tự động xóa tin nhắn sau khi đọc để giải phóng bộ nhớ SIM */
                SIM_DeleteSMS(sim, index);
            }
        }
    }
    /* Trường hợp 2: Tin nhắn đẩy thẳng (+CMT: ...) -> Cần parser phức tạp hơn */
    else if (strstr(line, "+CMT:")) {
        LOG_INFO("[SMS] Direct SMS received (CMT).");
        /* CMT URC thường đi kèm nội dung ở dòng tiếp theo. 
         * Logic hiện tại của SIM_A7670C_Process có thể cần tinh chỉnh để gộp dòng. */
    }
}
