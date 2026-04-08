#ifndef __BSP_SPI_H__
#define __BSP_SPI_H__

#include "stm32l4xx_hal.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "stdint.h"

typedef enum{
    BSP_SPI_OK = 0,
    BSP_SPI_BUSY,
    BSP_SPI_ERROR,
    BSP_SPI_TIMEOUT
}BSP_SPI_Status_t;

typedef enum {
    BSP_SPI_EVENT_DONE,
    BSP_SPI_EVENT_ERROR
} BSP_SPI_Event_t;

typedef void (*BSP_SPI_Callback_t)(BSP_SPI_Event_t event, BaseType_t * xHigherPriorityTaskWoken);

/**
 * @brief SPI Bus structure (Physical Resource)
 *        - Đại diện cho 1 cổng SPI vật lý.
 *        - Chứa Mutex dùng chung cho tất cả thiết bị trên Bus này.
 */
typedef struct {
    SPI_HandleTypeDef *hspi;        /**< Pointer to HAL SPI handle */
    SemaphoreHandle_t mutex;        /**< Shared mutex for the bus */
    void *active_handle;            /**< Current active BSP_SPI_Handle_t using the bus */
} BSP_SPI_Bus_t;

/**
 * @brief SPI Device Handle (Device Interface)
 *        - Đại diện cho 1 thiết bị trên Bus (ví dụ IMU, Flash).
 *        - Mỗi thiết bị có Callback riêng.
 */
typedef struct {
    BSP_SPI_Bus_t *bus;             /**< Pointer to the bus this device is attached to */
    TaskHandle_t task_to_notify;    /**< ID of the task waiting for this device's transfer */
    BSP_SPI_Callback_t callback;    /**< Persistent callback for this device */
} BSP_SPI_Handle_t;

/**
 * @brief Khởi tạo Bus SPI (Gọi 1 lần cho mỗi cổng SPI vật lý)
 */
BSP_SPI_Status_t BSP_SPI_Bus_Init(BSP_SPI_Bus_t *bus, SPI_HandleTypeDef *hspi);

/**
 * @brief Khởi tạo Handle cho thiết bị (Gọi cho mỗi linh kiện trên Bus)
 */
BSP_SPI_Status_t BSP_SPI_Handle_Init(BSP_SPI_Handle_t *handle, BSP_SPI_Bus_t *bus);

/**
 * @brief Khóa bus SPI (Gán active_handle tự động)
 */
BSP_SPI_Status_t BSP_SPI_LockBus(BSP_SPI_Handle_t *handle, uint32_t timeout);

/**
 * @brief Giải phóng bus SPI
 */
void BSP_SPI_UnlockBus(BSP_SPI_Handle_t *handle);

/**
 * @brief Truyền và nhận dữ liệu (Polling)
 */
BSP_SPI_Status_t BSP_SPI_Transmit(BSP_SPI_Handle_t *handle, uint8_t* tx_buf, uint16_t len, uint32_t timeout);
BSP_SPI_Status_t BSP_SPI_Receive(BSP_SPI_Handle_t *handle, uint8_t* rx_buf, uint16_t len, uint32_t timeout);

BSP_SPI_Status_t BSP_SPI_TransmitReceive(BSP_SPI_Handle_t *handle, uint8_t* tx_buf, uint8_t* rx_buf, uint16_t len, uint32_t timeout);

/**
 * @brief Truyền và nhận dữ liệu (Interrupt)
 */
BSP_SPI_Status_t BSP_SPI_TransmitReceive_IT(BSP_SPI_Handle_t *handle, uint8_t* tx_buf, uint8_t* rx_buf, uint16_t len);

/**
 * @brief Truyền và nhận dữ liệu (DMA)
 */
BSP_SPI_Status_t BSP_SPI_TransmitReceive_DMA(BSP_SPI_Handle_t *handle, uint8_t* tx_buf, uint8_t* rx_buf, uint16_t len);

/**
 * @brief Đợi cho đến khi quá trình IT/DMA hoàn tất
 */
BSP_SPI_Status_t BSP_SPI_WaitDone(BSP_SPI_Handle_t *handle, uint32_t timeout);

/**
 * @brief Đăng ký hàm xử lý sự kiện cho thiết bị
 */
void BSP_SPI_RegisterCallback(BSP_SPI_Handle_t *handle, BSP_SPI_Callback_t callback);

/**
 * @brief Hàm thông báo hoàn tất truyền nhận (Gọi từ HAL_SPI_TxRxCpltCallback trong Application)
 * @param handle: Tham số truyền vào nên là bus->active_handle 
 */
void BSP_SPI_TxRxCpltCallback(BSP_SPI_Handle_t *handle);

/**
 * @brief Hàm thông báo lỗi truyền nhận (Gọi từ HAL_SPI_ErrorCallback trong Application)
 */
void BSP_SPI_ErrorCallback(BSP_SPI_Handle_t *handle);

/**
 * @brief Dừng khẩn cấp
 */
void BSP_SPI_Abort(BSP_SPI_Handle_t *handle);

#endif /* __BSP_SPI_H__ */

