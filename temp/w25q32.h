#ifndef __W25Q32_H
#define __W25Q32_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

/* --------------------------------------------------------------------------
 * Hardware definitions mapping based on prompt:
 * SPI = SPI1
 * CS  = PB6
 * -------------------------------------------------------------------------- */
#define W25Q_CS_PORT          GPIOB
#define W25Q_CS_PIN           GPIO_PIN_6

extern SPI_HandleTypeDef hspi1;
#define W25Q_SPI_HANDLE       &hspi1

#define W25Q_CS_LOW()         HAL_GPIO_WritePin(W25Q_CS_PORT, W25Q_CS_PIN, GPIO_PIN_RESET)
#define W25Q_CS_HIGH()        HAL_GPIO_WritePin(W25Q_CS_PORT, W25Q_CS_PIN, GPIO_PIN_SET)

/* --------------------------------------------------------------------------
 * W25Q32 Commands
 * -------------------------------------------------------------------------- */
#define W25Q_CMD_JEDEC_ID     0x9F
#define W25Q_CMD_WRITE_ENABLE 0x06
#define W25Q_CMD_READ_STAT1   0x05
#define W25Q_CMD_SECTOR_ERASE 0x20
#define W25Q_CMD_PAGE_PROGRAM 0x02
#define W25Q_CMD_READ_DATA    0x03

/* --------------------------------------------------------------------------
 * Function Prototypes
 * -------------------------------------------------------------------------- */
/**
 * @brief Initialize CS pin for W25Q32
 */
void W25Q32_Init(void);

/**
 * @brief Read JEDEC ID (Manufacturer ID + Memory Type + Capacity)
 * @param id Pointer to a 3-byte array to store ID
 *           W25Q32 expected: 0xEF (Winbond), 0x40 (SPI), 0x16 (Capacity 32M)
 */
void W25Q32_Read_ID(uint8_t *id);

/**
 * @brief Test communication by reading and checking JEDEC ID
 * @return 1 if ID matches W25Q32, 0 otherwise
 */
uint8_t W25Q32_Test(void);

/**
 * @brief Wait until WIP (Write In Progress) bit is 0
 */
void W25Q32_WaitBusy(void);

/**
 * @brief Send Write Enable command
 */
void W25Q32_WriteEnable(void);

/**
 * @brief Erase a 4KB sector
 * @param sectorAddr Absolute address of the sector (must be a multiple of 4KB)
 */
void W25Q32_SectorErase(uint32_t sectorAddr);

/**
 * @brief Write data to a page (max 256 bytes)
 * @param pBuffer Pointer to data to write
 * @param writeAddr Absolute address to write to
 * @param numByteToWrite Number of bytes (max 256)
 */
void W25Q32_PageProgram(uint8_t* pBuffer, uint32_t writeAddr, uint16_t numByteToWrite);

/**
 * @brief Read data from Flash
 * @param pBuffer Pointer to buffer to store data
 * @param readAddr Absolute address to read from
 * @param numByteToRead Number of bytes to read
 */
void W25Q32_ReadData(uint8_t* pBuffer, uint32_t readAddr, uint16_t numByteToRead);


#ifdef __cplusplus
}
#endif

#endif /* __W25Q32_H */
