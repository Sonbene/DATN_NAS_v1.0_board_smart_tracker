/**
 * @file    icm42605_task.h
 * @brief   FreeRTOS Task cho ICM-42605 IMU
 * @details Quản lý vòng đời driver + service, bridging ISR→Task.
 *
 * @author  DATN_NAS
 * @version 1.0
 * @date    2026-04-09
 */

#ifndef __ICM42605_TASK_H__
#define __ICM42605_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Khởi tạo và tạo IMU Task
 * @details Init driver → Init service → Create FreeRTOS task.
 *          Gọi hàm này trong main() trước osKernelStart().
 */
void ICM42605_Task_Init(void);

/**
 * @brief Notify task từ EXTI ISR khi INT1 trigger (WOM)
 * @note  Gọi trong HAL_GPIO_EXTI_Callback, ISR-safe
 */
void ICM42605_Task_NotifyINT1FromISR(void);

/**
 * @brief Notify task từ EXTI ISR khi INT2 trigger (FIFO WM)
 * @note  Gọi trong HAL_GPIO_EXTI_Callback, ISR-safe
 */
void ICM42605_Task_NotifyINT2FromISR(void);

#ifdef __cplusplus
}
#endif

#endif /* __ICM42605_TASK_H__ */
