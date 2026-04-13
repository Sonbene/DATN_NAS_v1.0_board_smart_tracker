#ifndef W25Q32_TASK_H
#define W25Q32_TASK_H

#include "main.h"
#include "system_service.h"

void W25Q32_Task_Init(void);

/**
 * @brief Gửi yêu cầu lưu log vào Flash
 */
void W25Q32_Task_Log(TrackerLog_t *log);

#endif
