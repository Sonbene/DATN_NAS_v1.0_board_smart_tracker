#include "w25q32.h"
#include "log.h"
#include "cmsis_os.h"
#include <string.h>

/* Private function prototypes */
static void W25Q_WriteEnable(W25Q_Handle_t *handle);

static inline void W25Q_Select(W25Q_Handle_t *handle) {
    HAL_GPIO_WritePin(handle->cs_port, handle->cs_pin, GPIO_PIN_RESET);
}

static inline void W25Q_Deselect(W25Q_Handle_t *handle) {
    HAL_GPIO_WritePin(handle->cs_port, handle->cs_pin, GPIO_PIN_SET);
}

W25Q_Status_t W25Q_Init(W25Q_Handle_t *handle, BSP_SPI_Handle_t *spi_handle, GPIO_TypeDef *cs_port, uint16_t cs_pin)
{
    if (handle == NULL || spi_handle == NULL) return W25Q_ERROR;

    handle->spi_bus = spi_handle;
    handle->cs_port = cs_port;
    handle->cs_pin = cs_pin;
    handle->timeout = 1000;

    /* Ensure Flash is deselected initially */
    W25Q_Deselect(handle);
    
    /* Small delay for power stabilization */
    osDelay(10);
    
    return W25Q_OK;
}

uint32_t W25Q_ReadID(W25Q_Handle_t *handle)
{
    uint8_t tx[6] = {W25Q_DEVICE_ID, 0, 0, 0, 0, 0};
    uint8_t rx[6] = {0, 0, 0, 0, 0, 0};
    uint32_t id = 0;

    if (BSP_SPI_LockBus(handle->spi_bus, handle->timeout) != BSP_SPI_OK) return 0;

    W25Q_Select(handle);
    if (BSP_SPI_TransmitReceive(handle->spi_bus, tx, rx, 6, handle->timeout) == BSP_SPI_OK) {
        id = (rx[4] << 8) | rx[5];
    }
    W25Q_Deselect(handle);

    BSP_SPI_UnlockBus(handle->spi_bus);

    return id;
}

uint32_t W25Q_ReadJEDECID(W25Q_Handle_t *handle)
{
    uint8_t tx[4] = {W25Q_JEDEC_ID, 0, 0, 0};
    uint8_t rx[4] = {0, 0, 0, 0};
    uint32_t id = 0;

    if (BSP_SPI_LockBus(handle->spi_bus, handle->timeout) != BSP_SPI_OK) return 0;

    W25Q_Select(handle);
    if (BSP_SPI_TransmitReceive(handle->spi_bus, tx, rx, 4, handle->timeout) == BSP_SPI_OK) {
        id = (rx[1] << 16) | (rx[2] << 8) | rx[3];
    }
    W25Q_Deselect(handle);

    BSP_SPI_UnlockBus(handle->spi_bus);

    return id;
}

W25Q_Status_t W25Q_WaitForReady(W25Q_Handle_t *handle, uint32_t timeout_ms)
{
    uint8_t tx[2] = {W25Q_READ_STATUS_REG1, 0x00};
    uint8_t rx[2] = {0, 0};
    uint8_t status = 0;
    uint32_t start_tick = osKernelSysTick();

    if (BSP_SPI_LockBus(handle->spi_bus, timeout_ms) != BSP_SPI_OK) return W25Q_BUSY;

    W25Q_Select(handle);
    /* Initial read handles the dummy FIFO byte on STM32L4 */
    if (BSP_SPI_TransmitReceive(handle->spi_bus, tx, rx, 2, handle->timeout) == BSP_SPI_OK) {
        status = rx[1];
    }
    
    while ((status & W25Q_SR1_BUSY_MASK) != 0) {
        if ((osKernelSysTick() - start_tick) > pdMS_TO_TICKS(timeout_ms)) {
            W25Q_Deselect(handle);
            BSP_SPI_UnlockBus(handle->spi_bus);
            return W25Q_TIMEOUT;
        }
        /* Continuously receive status bit while CS is LOW */
        if (BSP_SPI_Receive(handle->spi_bus, &status, 1, handle->timeout) != BSP_SPI_OK) break;
        osDelay(1);
    }

    W25Q_Deselect(handle);
    BSP_SPI_UnlockBus(handle->spi_bus);

    return W25Q_OK;
}

static void W25Q_WriteEnable(W25Q_Handle_t *handle)
{
    uint8_t cmd = W25Q_WRITE_ENABLE;
    if (BSP_SPI_LockBus(handle->spi_bus, handle->timeout) != BSP_SPI_OK) return;

    W25Q_Select(handle);
    BSP_SPI_Transmit(handle->spi_bus, &cmd, 1, handle->timeout);
    W25Q_Deselect(handle);

    BSP_SPI_UnlockBus(handle->spi_bus);
}

W25Q_Status_t W25Q_EraseSector(W25Q_Handle_t *handle, uint32_t sector_addr)
{
    W25Q_WaitForReady(handle, handle->timeout);
    W25Q_WriteEnable(handle);

    uint8_t cmd[4];
    cmd[0] = W25Q_SECTOR_ERASE;
    cmd[1] = (uint8_t)(sector_addr >> 16);
    cmd[2] = (uint8_t)(sector_addr >> 8);
    cmd[3] = (uint8_t)(sector_addr);

    if (BSP_SPI_LockBus(handle->spi_bus, handle->timeout) != BSP_SPI_OK) return W25Q_BUSY;

    W25Q_Select(handle);
    BSP_SPI_Transmit(handle->spi_bus, cmd, 4, handle->timeout);
    W25Q_Deselect(handle);

    BSP_SPI_UnlockBus(handle->spi_bus);

    return W25Q_WaitForReady(handle, handle->timeout);
}

W25Q_Status_t W25Q_Write(W25Q_Handle_t *handle, uint32_t addr, uint8_t *buffer, uint32_t len)
{
    uint32_t bytes_to_write;
    uint32_t page_offset;
    
    while (len > 0) {
        page_offset = addr % W25Q_PAGE_SIZE;
        bytes_to_write = W25Q_PAGE_SIZE - page_offset;
        if (len < bytes_to_write) bytes_to_write = len;

        W25Q_WaitForReady(handle, handle->timeout);
        W25Q_WriteEnable(handle);
        
        uint8_t cmd[4];
        cmd[0] = W25Q_PAGE_PROGRAM;
        cmd[1] = (uint8_t)(addr >> 16);
        cmd[2] = (uint8_t)(addr >> 8);
        cmd[3] = (uint8_t)(addr);

        if (BSP_SPI_LockBus(handle->spi_bus, handle->timeout) != BSP_SPI_OK) return W25Q_BUSY;
        
        W25Q_Select(handle);
        BSP_SPI_Transmit(handle->spi_bus, cmd, 4, handle->timeout);
        BSP_SPI_Transmit(handle->spi_bus, buffer, bytes_to_write, handle->timeout);
        W25Q_Deselect(handle);
        
        BSP_SPI_UnlockBus(handle->spi_bus);

        W25Q_WaitForReady(handle, handle->timeout);

        addr += bytes_to_write;
        buffer += bytes_to_write;
        len -= bytes_to_write;
    }

    return W25Q_OK;
}

W25Q_Status_t W25Q_Read(W25Q_Handle_t *handle, uint32_t addr, uint8_t *buffer, uint32_t len)
{
    uint8_t cmd[4];
    cmd[0] = W25Q_READ_DATA;
    cmd[1] = (uint8_t)(addr >> 16);
    cmd[2] = (uint8_t)(addr >> 8);
    cmd[3] = (uint8_t)(addr);

    if (BSP_SPI_LockBus(handle->spi_bus, handle->timeout) != BSP_SPI_OK) return W25Q_BUSY;

    W25Q_Select(handle);
    BSP_SPI_Transmit(handle->spi_bus, cmd, 4, handle->timeout);
    BSP_SPI_Receive(handle->spi_bus, buffer, len, handle->timeout);
    W25Q_Deselect(handle);

    BSP_SPI_UnlockBus(handle->spi_bus);
    return W25Q_OK;
}

bool W25Q_IsBusy(W25Q_Handle_t *handle)
{
    uint8_t tx[2] = {W25Q_READ_STATUS_REG1, 0x00};
    uint8_t rx[2] = {0, 0};

    if (BSP_SPI_LockBus(handle->spi_bus, handle->timeout) != BSP_SPI_OK) return true;

    W25Q_Select(handle);
    BSP_SPI_TransmitReceive(handle->spi_bus, tx, rx, 2, handle->timeout);
    W25Q_Deselect(handle);

    BSP_SPI_UnlockBus(handle->spi_bus);

    return (rx[1] & W25Q_SR1_BUSY_MASK) != 0;
}
