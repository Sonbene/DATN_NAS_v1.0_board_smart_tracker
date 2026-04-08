/**
 * @file    w25q32.h
 * @brief   W25Q32JV SPI Flash Driver for STM32 with RTOS Support
 */

#ifndef __W25Q32_H__
#define __W25Q32_H__

#include <stdint.h>
#include <stdbool.h>
#include "bsp_spi.h"

/* W25Q32 Capacity Information */
#define W25Q_PAGE_SIZE            256
#define W25Q_SECTOR_SIZE          4096
#define W25Q_BLOCK_SIZE           65536
#define W25Q_PAGE_COUNT           16384
#define W25Q_SECTOR_COUNT         1024
#define W25Q_BLOCK_COUNT          64
#define W25Q_CAPACITY_BYTES       (4 * 1024 * 1024)

/* W25Q32 Commands */
#define W25Q_WRITE_ENABLE         0x06
#define W25Q_WRITE_DISABLE        0x04
#define W25Q_READ_STATUS_REG1     0x05
#define W25Q_READ_STATUS_REG2     0x35
#define W25Q_WRITE_STATUS_REG     0x01
#define W25Q_READ_DATA            0x03
#define W25Q_FAST_READ            0x0B
#define W25Q_PAGE_PROGRAM         0x02
#define W25Q_SECTOR_ERASE         0x20
#define W25Q_BLOCK_ERASE_32K      0x52
#define W25Q_BLOCK_ERASE_64K      0xD8
#define W25Q_CHIP_ERASE           0xC7
#define W25Q_POWER_DOWN           0xB9
#define W25Q_RELEASE_POWER_DOWN   0xAB
#define W25Q_DEVICE_ID            0x90
#define W25Q_JEDEC_ID             0x9F

/* Status Register Bits */
#define W25Q_SR1_BUSY_MASK        0x01
#define W25Q_SR1_WEL_MASK         0x02

typedef enum {
    W25Q_OK = 0,
    W25Q_ERROR,
    W25Q_BUSY,
    W25Q_TIMEOUT
} W25Q_Status_t;

typedef struct {
    BSP_SPI_Handle_t *spi_bus;
    GPIO_TypeDef *cs_port;
    uint16_t cs_pin;
    uint32_t timeout;
} W25Q_Handle_t;

/**
 * @brief Initialize W25Q32 handle
 */
W25Q_Status_t W25Q_Init(W25Q_Handle_t *handle, BSP_SPI_Handle_t *spi_handle, GPIO_TypeDef *cs_port, uint16_t cs_pin);

/**
 * @brief Read Manufacturer and Device ID
 */
uint32_t W25Q_ReadID(W25Q_Handle_t *handle);

/**
 * @brief Read JEDEC ID
 */
uint32_t W25Q_ReadJEDECID(W25Q_Handle_t *handle);

/**
 * @brief Read data from Flash
 */
W25Q_Status_t W25Q_Read(W25Q_Handle_t *handle, uint32_t addr, uint8_t *buffer, uint32_t len);

/**
 * @brief Write data to Flash (Handles page alignment automatically)
 */
W25Q_Status_t W25Q_Write(W25Q_Handle_t *handle, uint32_t addr, uint8_t *buffer, uint32_t len);

/**
 * @brief Erase a sector (4KB)
 */
W25Q_Status_t W25Q_EraseSector(W25Q_Handle_t *handle, uint32_t sector_addr);

/**
 * @brief Erase a block (64KB)
 */
W25Q_Status_t W25Q_EraseBlock(W25Q_Handle_t *handle, uint32_t block_addr);

/**
 * @brief Erase entire chip
 */
W25Q_Status_t W25Q_EraseChip(W25Q_Handle_t *handle);

/**
 * @brief Check if chip is busy (non-blocking)
 */
bool W25Q_IsBusy(W25Q_Handle_t *handle);

/**
 * @brief Wait for chip to be ready (blocking with timeout)
 */
W25Q_Status_t W25Q_WaitForReady(W25Q_Handle_t *handle, uint32_t timeout_ms);

#endif /* __W25Q32_H__ */
