#ifndef W25Q32_TASK_H
#define W25Q32_TASK_H

#include "main.h"
#include "system_service.h"

typedef enum {
    W25Q_CMD_LOG = 0,
    W25Q_CMD_SAVE_CONFIG,
    W25Q_CMD_LOAD_CONFIG
} W25Q_Cmd_t;

typedef struct {
    W25Q_Cmd_t cmd;
    TrackerLog_t log;   /* Dùng cho lệnh LOG */
    osSemaphoreId sem;  /* Dùng để báo hoàn thành cho lệnh đồng bộ (Save/Load) */
} W25Q_Msg_t;

void W25Q32_Task_Init(void);

/**
 * @brief Gửi yêu cầu lưu log vào Flash (Không đồng bộ)
 */
void W25Q32_Task_Log(TrackerLog_t *log);

/**
 * @brief Lưu cấu hình hệ thống (Đồng bộ - Chờ đến khi xong)
 * @return true nếu thành công
 */
bool W25Q32_Task_SaveConfig(void);

/**
 * @brief Load cấu hình hệ thống (Đồng bộ - Chờ đến khi xong)
 * @return true nếu thành công
 */
bool W25Q32_Task_LoadConfig(void);

#endif
