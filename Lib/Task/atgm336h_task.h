#ifndef __ATGM336H_TASK_H__
#define __ATGM336H_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "bsp_uart.h"
#include "atgm336h.h"

/**
 * @brief BSP Handle của GPS UART (USART1).
 *        Được expose để main.c routing HAL_UARTEx_RxEventCallback → BSP.
 */
extern BSP_UART_Handle_t gps_uart_bus;

/**
 * @brief Khởi tạo BSP UART1 cho GPS, tạo FreeRTOS task đọc NMEA định kỳ.
 *        Gọi hàm này trong main.c tại USER CODE BEGIN RTOS_THREADS.
 */
void ATGM336H_Task_Init(void);

/**
 * @brief Lấy bản sao dữ liệu GPS mới nhất (thread-safe memcpy).
 *        Có thể gọi từ bất kỳ task nào.
 * @param out Pointer nhận kết quả
 * @return true nếu dữ liệu GPS hiện tại đang hợp lệ (is_valid)
 */
bool ATGM336H_Task_GetLatestInfo(ATGM336H_Info_t *out);

/**
 * @brief Điều khiển chế độ Standby của GPS qua tập lệnh NMEA.
 * @param enable true để vào Standby, false để thức dậy (gửi byte bất kỳ).
 */
void ATGM336H_Task_Standby(bool enable);

/**
 * @brief Khôi phục trạng thái nhận dữ liệu GPS sau khi Chip thức dậy từ STOP mode.
 *        Hàm này khởi động lại DMA Receive to Idle.
 */
void ATGM336H_Task_Wakeup(void);

#ifdef __cplusplus
}
#endif

#endif /* __ATGM336H_TASK_H__ */
