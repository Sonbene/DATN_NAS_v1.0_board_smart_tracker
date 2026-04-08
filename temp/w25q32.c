#include "w25q32.h"
#include "../Utils/log.h"

void W25Q32_Init(void)
{
    /* Initialize CS GPIO. Assumes Clock for GPIOB is already enabled in main.c */
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = W25Q_CS_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(W25Q_CS_PORT, &GPIO_InitStruct);

    /* Deselect Flash (CS High) */
    W25Q_CS_HIGH();
}

void W25Q32_Read_ID(uint8_t *id)
{
    uint8_t cmd = W25Q_CMD_JEDEC_ID;
    
    W25Q_CS_LOW();
    HAL_SPI_Transmit(W25Q_SPI_HANDLE, &cmd, 1, 100);
    HAL_SPI_Receive(W25Q_SPI_HANDLE, id, 3, 100);
    W25Q_CS_HIGH();
}

uint8_t W25Q32_Test(void)
{
    uint8_t jedec_id[3] = {0};
    
    W25Q32_Read_ID(jedec_id);
    
    LOG_INFO("W25Q32 Raw ID: 0x%02X 0x%02X 0x%02X", jedec_id[0], jedec_id[1], jedec_id[2]);

    /* Winbond manufacturer ID: 0xEF
     * specific to W25Q32: 0x40 (Memory Type), 0x16 (Capacity) */
    if (jedec_id[0] == 0xEF && jedec_id[1] == 0x40 && jedec_id[2] == 0x16)
    {
        return 1; // Test pass
    }
    
    return 0; // Test fail
}

void W25Q32_WaitBusy(void)
{
    uint8_t cmd = W25Q_CMD_READ_STAT1;
    uint8_t status = 0;
    
    W25Q_CS_LOW();
    HAL_SPI_Transmit(W25Q_SPI_HANDLE, &cmd, 1, 100);
    do {
        HAL_SPI_Receive(W25Q_SPI_HANDLE, &status, 1, 100);
    } while ((status & 0x01) == 0x01); // Wait for WIP bit to clear
    W25Q_CS_HIGH();
}

void W25Q32_WriteEnable(void)
{
    uint8_t cmd = W25Q_CMD_WRITE_ENABLE;
    W25Q_CS_LOW();
    HAL_SPI_Transmit(W25Q_SPI_HANDLE, &cmd, 1, 100);
    W25Q_CS_HIGH();
}

void W25Q32_SectorErase(uint32_t sectorAddr)
{
    W25Q32_WriteEnable();
    W25Q32_WaitBusy();

    uint8_t cmd[4];
    cmd[0] = W25Q_CMD_SECTOR_ERASE;
    cmd[1] = (sectorAddr & 0xFF0000) >> 16;
    cmd[2] = (sectorAddr & 0xFF00) >> 8;
    cmd[3] = (sectorAddr & 0xFF);

    W25Q_CS_LOW();
    HAL_SPI_Transmit(W25Q_SPI_HANDLE, cmd, 4, 100);
    W25Q_CS_HIGH();

    W25Q32_WaitBusy();
}

void W25Q32_PageProgram(uint8_t* pBuffer, uint32_t writeAddr, uint16_t numByteToWrite)
{
    if(numByteToWrite > 256) return; // Page restriction

    W25Q32_WriteEnable();
    W25Q32_WaitBusy();

    uint8_t cmd[4];
    cmd[0] = W25Q_CMD_PAGE_PROGRAM;
    cmd[1] = (writeAddr & 0xFF0000) >> 16;
    cmd[2] = (writeAddr & 0xFF00) >> 8;
    cmd[3] = (writeAddr & 0xFF);

    W25Q_CS_LOW();
    HAL_SPI_Transmit(W25Q_SPI_HANDLE, cmd, 4, 100);
    HAL_SPI_Transmit(W25Q_SPI_HANDLE, pBuffer, numByteToWrite, 1000);
    W25Q_CS_HIGH();

    W25Q32_WaitBusy();
}

void W25Q32_ReadData(uint8_t* pBuffer, uint32_t readAddr, uint16_t numByteToRead)
{
    uint8_t cmd[4];
    cmd[0] = W25Q_CMD_READ_DATA;
    cmd[1] = (readAddr & 0xFF0000) >> 16;
    cmd[2] = (readAddr & 0xFF00) >> 8;
    cmd[3] = (readAddr & 0xFF);

    W25Q_CS_LOW();
    HAL_SPI_Transmit(W25Q_SPI_HANDLE, cmd, 4, 100);
    HAL_SPI_Receive(W25Q_SPI_HANDLE, pBuffer, numByteToRead, 1000);
    W25Q_CS_HIGH();
}
