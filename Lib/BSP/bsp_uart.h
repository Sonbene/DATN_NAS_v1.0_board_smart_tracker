#ifndef __BSP_UART_H__
#define __BSP_UART_H__

#include "stm32l4xx_hal.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "stdint.h"

typedef enum{
    BSP_UART_OK = 0,
    BSP_UART_BUSY,
    BSP_UART_ERROR,
    BSP_UART_TIMEOUT
}BSP_UART_Status_t;

typedef enum {
    BSP_UART_EVENT_TX_DONE,
    BSP_UART_EVENT_RX_DONE,
    BSP_UART_EVENT_ERROR,
    BSP_UART_EVENT_IDLE
} BSP_UART_Event_t;

/**
 * @brief Callback function definition for UART events.
 * @param event: The UART event that triggered the callback.
 * @param size: The number of bytes transferred (primarily for RX/IDLE events).
 * @param xHigherPriorityTaskWoken: Passed to FreeRTOS ISR functions.
 */
typedef void (*BSP_UART_Callback_t)(BSP_UART_Event_t event, uint16_t size, BaseType_t *xHigherPriorityTaskWoken);

/**
 * @brief UART Device Handle
 *        - Đại diện cho 1 cổng UART vật lý.
 *        - Chứa các Mutex độc lập cho luồng Truyền (TX) và Nhận (RX).
 */
typedef struct {
    UART_HandleTypeDef *huart;      /**< Pointer to HAL UART handle */
    SemaphoreHandle_t tx_mutex;     /**< Mutex for TX protection */
    SemaphoreHandle_t rx_mutex;     /**< Mutex for RX protection */
    TaskHandle_t tx_task_to_notify; /**< ID of the task waiting for TX completion */
    TaskHandle_t rx_task_to_notify; /**< ID of the task waiting for RX completion */
    BSP_UART_Callback_t callback;   /**< Callback for UART events */
} BSP_UART_Handle_t;

/**
 * @brief Khởi tạo BSP UART
 */
BSP_UART_Status_t BSP_UART_Init(BSP_UART_Handle_t *handle, UART_HandleTypeDef *huart);

/**
 * @brief Khóa UART để truyền (ngăn các task khác gửi dữ liệu)
 */
BSP_UART_Status_t BSP_UART_LockTx(BSP_UART_Handle_t *handle, uint32_t timeout);

/**
 * @brief Giải phóng quyền truyền UART
 */
void BSP_UART_UnlockTx(BSP_UART_Handle_t *handle);

/**
 * @brief Khóa UART để nhận (ngăn các task khác đọc dữ liệu)
 */
BSP_UART_Status_t BSP_UART_LockRx(BSP_UART_Handle_t *handle, uint32_t timeout);

/**
 * @brief Giải phóng quyền nhận UART
 */
void BSP_UART_UnlockRx(BSP_UART_Handle_t *handle);

/**
 * @brief Truyền và nhận dữ liệu (Polling - Đồng bộ)
 */
BSP_UART_Status_t BSP_UART_Transmit(BSP_UART_Handle_t *handle, uint8_t* tx_buf, uint16_t len, uint32_t timeout);
BSP_UART_Status_t BSP_UART_Receive(BSP_UART_Handle_t *handle, uint8_t* rx_buf, uint16_t len, uint32_t timeout);

/**
 * @brief Truyền và nhận dữ liệu (Interrupt - Bất đồng bộ)
 */
BSP_UART_Status_t BSP_UART_Transmit_IT(BSP_UART_Handle_t *handle, uint8_t* tx_buf, uint16_t len);
BSP_UART_Status_t BSP_UART_Receive_IT(BSP_UART_Handle_t *handle, uint8_t* rx_buf, uint16_t len);

/**
 * @brief Truyền và nhận dữ liệu (DMA - Bất đồng bộ)
 */
BSP_UART_Status_t BSP_UART_Transmit_DMA(BSP_UART_Handle_t *handle, uint8_t* tx_buf, uint16_t len);
BSP_UART_Status_t BSP_UART_Receive_DMA(BSP_UART_Handle_t *handle, uint8_t* rx_buf, uint16_t len);

/**
 * @brief Đợi cho đến khi quá trình TX hoàn tất (khi dùng IT/DMA)
 */
BSP_UART_Status_t BSP_UART_WaitTxDone(BSP_UART_Handle_t *handle, uint32_t timeout);

/**
 * @brief Đợi cho đến khi quá trình RX hoàn tất (khi dùng IT/DMA)
 */
BSP_UART_Status_t BSP_UART_WaitRxDone(BSP_UART_Handle_t *handle, uint32_t timeout);

/**
 * @brief Đăng ký hàm xử lý sự kiện
 */
void BSP_UART_RegisterCallback(BSP_UART_Handle_t *handle, BSP_UART_Callback_t callback);

/**
 * @brief Callback thông báo hoàn tất truyền (Gọi từ HAL_UART_TxCpltCallback trong Application)
 */
void BSP_UART_TxCpltCallback(BSP_UART_Handle_t *handle);

/**
 * @brief Callback thông báo hoàn tất nhận (Gọi từ HAL_UART_RxCpltCallback trong Application)
 */
void BSP_UART_RxCpltCallback(BSP_UART_Handle_t *handle, uint16_t size);

/**
 * @brief Callback thông báo lỗi (Gọi từ HAL_UART_ErrorCallback trong Application)
 */
void BSP_UART_ErrorCallback(BSP_UART_Handle_t *handle);

/**
 * @brief Callback thông báo sự kiện IDLE hoặc RxEvent (Gọi từ HAL_UARTEx_RxEventCallback trong Application)
 */
void BSP_UART_RxEventCallback(BSP_UART_Handle_t *handle, uint16_t size);

/**
 * @brief Dừng truyền/nhận khẩn cấp
 */
void BSP_UART_Abort(BSP_UART_Handle_t *handle);
void BSP_UART_AbortReceive(BSP_UART_Handle_t *handle);
void BSP_UART_AbortTransmit(BSP_UART_Handle_t *handle);

#endif /* __BSP_UART_H__ */
