#ifndef __SMS_SERVICE_H__
#define __SMS_SERVICE_H__

#include "sim_a7670c.h"
#include <stdint.h>

typedef enum {
    SMS_OK = 0,
    SMS_ERROR,
    SMS_TIMEOUT,
    SMS_FULL
} SMS_Status_t;

typedef struct {
    char phone[20];
    char content[160];
    char timestamp[32];
} SMS_Message_t;

typedef void (*SMS_ReceivedCallback_t)(SMS_Message_t *msg);

/**
 * @brief Khởi tạo dịch vụ SMS (Cấu hình Text Mode, Lưu trữ)
 */
SMS_Status_t SMS_Service_Init(SIM_Handle_t *sim);

/**
 * @brief Gửi tin nhắn SMS
 */
SMS_Status_t SMS_Service_Send(SIM_Handle_t *sim, const char *phone, const char *content);

/**
 * @brief Đăng ký callback khi có tin nhắn đến
 */
void SMS_Service_RegisterCallback(SMS_ReceivedCallback_t cb);

/**
 * @brief Xử lý URC liên quan đến SMS (+CMTI, +CMT)
 */
void SMS_Service_HandleURC(SIM_Handle_t *sim, char *line);

#endif /* __SMS_SERVICE_H__ */
