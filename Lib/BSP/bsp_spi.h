#ifndef __BSP_SPI_H__
#define __BSP_SPI_H__

#include "stm32l4xx_hal.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "stdint.h"

typedef enum{
    BSP_SPI_OK = 0,
    BSP_SPI_BUSY,
    BSP_SPI_ERROR
}BSP_SPI_Status_t;

typedef enum {
    BSP_SPI_EVENT_DONE,
    BSP_SPI_EVENT_ERROR
} BSP_SPI_Event_t;

typedef void (*BSP_SPI_Callback_t)(BSP_SPI_Event_t event, BaseType_t * xHigherPriorityTaskWoken);

/**
 * @brief Khởi tạo ngoại vi SPI
 */
void BSP_SPI_Init(SPI_HandleTypeDef *hspi);

/**
 * @brief Chọn thiết bị SPI (Kéo chân CS xuống mức thấp)
 */
void BSP_SPI_Select(GPIO_TypeDef *cs_port, uint16_t cs_pin);

/**
 * @brief Bỏ chọn thiết bị SPI (Kéo chân CS lên mức cao)
 */
void BSP_SPI_Deselect(GPIO_TypeDef *cs_port, uint16_t cs_pin);

/**
 * @brief Truyền và nhận dữ liệu đồng thời (Chế độ Polling - Đợi cho đến khi xong)
 */
BSP_SPI_Status_t BSP_SPI_TransmitReceive(uint8_t* tx_buf, uint8_t* rx_buf, uint16_t len, uint32_t spi_timeout, uint32_t mutex_timeout);

/**
 * @brief Truyền và nhận dữ liệu đồng thời (Chế độ Ngắt - Interrupt)
 */
BSP_SPI_Status_t BSP_SPI_TransmitReceive_IT(uint8_t* tx_buf, uint8_t* rx_buf, uint16_t len, uint32_t mutex_timeout);

/**
 * @brief Truyền và nhận dữ liệu đồng thời (Chế độ DMA - Truy cập bộ nhớ trực tiếp)
 */
BSP_SPI_Status_t BSP_SPI_TransmitReceive_DMA(uint8_t* tx_buf, uint8_t* rx_buf, uint16_t len, uint32_t mutex_timeout);

/**
 * @brief Đăng ký hàm xử lý sự kiện (Callback)
 */
void BSP_SPI_RegisterCallback(BSP_SPI_Callback_t callback);

/**
 * @brief Hàm callback xử lý khi truyền nhận hoàn tất (Gọi trong ngắt HAL)
 */
void BSP_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi);

/**
 * @brief Hàm callback xử lý khi có lỗi SPI (Gọi trong ngắt HAL)
 */
void BSP_SPI_ErrorCallback(SPI_HandleTypeDef *hspi);

/**
 * @brief Dừng khẩn cấp quá trình truyền nhận SPI
 */
void BSP_SPI_Abort(void);



#endif /* __BSP_SPI_H__ */