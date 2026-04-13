/**
 * @file    icm42605.c
 * @brief   ICM-42605 6-Axis IMU SPI Driver Implementation
 * @details Tất cả giao tiếp SPI đều thông qua BSP_SPI layer.
 *          Thread-safe nhờ LockBus/UnlockBus trước mỗi transaction.
 *          Chip Select (CS) được quản lý riêng bằng GPIO.
 *
 * @author  DATN_NAS
 * @version 1.0
 * @date    2026-04-08
 */

#include "icm42605.h"
#include "log.h"
#include "cmsis_os.h"
#include <string.h>
#include <math.h>

/* ========================================================================================
 * SECTION: Private Constants
 * ======================================================================================== */

/** @brief Thời gian chờ sau soft-reset (ms) - datasheet yêu cầu ≥ 1ms */
#define ICM42605_RESET_DELAY_MS         10

/** @brief Thời gian chờ sau power mode change (ms) - datasheet yêu cầu 200µs */
#define ICM42605_POWER_CHANGE_DELAY_MS  1

/** @brief Default SPI timeout (ms) */
#define ICM42605_DEFAULT_TIMEOUT_MS     100

/** @brief Số bytes cho burst read toàn bộ sensor data (temp 2B + accel 6B + gyro 6B) */
#define ICM42605_ALL_DATA_SIZE          14

/** @brief Số sample trung bình cho self-test */
#define ICM42605_SELFTEST_SAMPLES       200

/** @brief Self-test thresholds (mg cho accel, dps cho gyro) theo datasheet */
#define ICM42605_ST_ACCEL_MIN_MG        50
#define ICM42605_ST_ACCEL_MAX_MG        900
#define ICM42605_ST_GYRO_MIN_DPS        60

/**
 * @brief Sensitivity lookup tables (LSB/unit)
 *        Accel: {16g, 8g, 4g, 2g} → {2048, 4096, 8192, 16384} LSB/g
 *        Gyro:  {2000, 1000, 500, 250, 125, 62.5, 31.25, 15.625} dps
 *              → {16.4, 32.8, 65.5, 131, 262, 524, 1049, 2097} LSB/dps
 */
static const float accel_sensitivity_table[] = {
    2048.0f,    /* ±16g */
    4096.0f,    /* ±8g  */
    8192.0f,    /* ±4g  */
    16384.0f    /* ±2g  */
};

static const float gyro_sensitivity_table[] = {
    16.4f,      /* ±2000 dps */
    32.8f,      /* ±1000 dps */
    65.5f,      /* ±500 dps  */
    131.0f,     /* ±250 dps  */
    262.0f,     /* ±125 dps  */
    524.3f,     /* ±62.5 dps */
    1048.6f,    /* ±31.25 dps */
    2097.2f     /* ±15.625 dps */
};

/* ========================================================================================
 * SECTION: Private Functions - Chip Select
 * ======================================================================================== */

/**
 * @brief Kéo CS xuống LOW (chọn chip)
 */
static inline void ICM42605_CS_Select(ICM42605_Handle_t *handle)
{
    HAL_GPIO_WritePin(handle->cs_port, handle->cs_pin, GPIO_PIN_RESET);
}

/**
 * @brief Kéo CS lên HIGH (bỏ chọn chip)
 */
static inline void ICM42605_CS_Deselect(ICM42605_Handle_t *handle)
{
    HAL_GPIO_WritePin(handle->cs_port, handle->cs_pin, GPIO_PIN_SET);
}

/* ========================================================================================
 * SECTION: Private Functions - SPI Low-Level Read/Write
 * ======================================================================================== */

/**
 * @brief   Đọc 1 register qua SPI
 * @details ICM-42605 SPI protocol: Byte 1 = addr | 0x80 (read), Byte 2 = dummy → nhận data
 * @note    Hàm này tự LockBus / UnlockBus, CS Select / Deselect
 */
static ICM42605_Status_t prv_ReadRegister(ICM42605_Handle_t *handle, uint8_t reg, uint8_t *value)
{
    uint8_t tx[2] = { reg | ICM42605_SPI_READ_BIT, 0x00 };
    uint8_t rx[2] = { 0, 0 };

    if (BSP_SPI_LockBus(handle->spi_handle, handle->timeout) != BSP_SPI_OK) {
        return ICM42605_BUSY;
    }

    ICM42605_CS_Select(handle);
    BSP_SPI_Status_t status = BSP_SPI_TransmitReceive(handle->spi_handle, tx, rx, 2, handle->timeout);
    ICM42605_CS_Deselect(handle);

    BSP_SPI_UnlockBus(handle->spi_handle);

    if (status != BSP_SPI_OK) {
        return ICM42605_ERROR;
    }

    *value = rx[1];
    return ICM42605_OK;
}

/**
 * @brief   Ghi 1 register qua SPI
 * @details ICM-42605 SPI protocol: Byte 1 = addr (bit7=0 → write), Byte 2 = data
 */
static ICM42605_Status_t prv_WriteRegister(ICM42605_Handle_t *handle, uint8_t reg, uint8_t value)
{
    uint8_t tx[2] = { reg & 0x7F, value }; /* Bit 7 = 0 cho write */
    uint8_t rx[2] = { 0, 0 };

    if (BSP_SPI_LockBus(handle->spi_handle, handle->timeout) != BSP_SPI_OK) {
        return ICM42605_BUSY;
    }

    ICM42605_CS_Select(handle);
    BSP_SPI_Status_t status = BSP_SPI_TransmitReceive(handle->spi_handle, tx, rx, 2, handle->timeout);
    ICM42605_CS_Deselect(handle);

    BSP_SPI_UnlockBus(handle->spi_handle);

    return (status == BSP_SPI_OK) ? ICM42605_OK : ICM42605_ERROR;
}

/**
 * @brief   Đọc nhiều registers liên tiếp (burst read)
 * @details Gửi addr | 0x80, sau đó đọc N bytes liên tiếp. IC auto-increment address.
 */
static ICM42605_Status_t prv_ReadRegisters(ICM42605_Handle_t *handle,
                                            uint8_t reg,
                                            uint8_t *buffer,
                                            uint16_t len)
{
    /* TX buffer: addr + N dummy bytes → tổng len + 1 */
    uint8_t tx_buf[1 + ICM42605_ALL_DATA_SIZE]; /* Đủ cho burst read lớn nhất */
    uint8_t rx_buf[1 + ICM42605_ALL_DATA_SIZE];

    if (len > ICM42605_ALL_DATA_SIZE) {
        return ICM42605_ERROR; /* Bảo vệ tràn buffer */
    }

    memset(tx_buf, 0, len + 1);
    tx_buf[0] = reg | ICM42605_SPI_READ_BIT;

    if (BSP_SPI_LockBus(handle->spi_handle, handle->timeout) != BSP_SPI_OK) {
        return ICM42605_BUSY;
    }

    ICM42605_CS_Select(handle);
    BSP_SPI_Status_t status = BSP_SPI_TransmitReceive(handle->spi_handle, tx_buf, rx_buf,
                                                       len + 1, handle->timeout);
    ICM42605_CS_Deselect(handle);

    BSP_SPI_UnlockBus(handle->spi_handle);

    if (status != BSP_SPI_OK) {
        return ICM42605_ERROR;
    }

    /* Data bắt đầu từ rx_buf[1] (byte đầu là dummy response cho addr byte) */
    memcpy(buffer, &rx_buf[1], len);
    return ICM42605_OK;
}

/**
 * @brief   Modify bits trong 1 register (Read-Modify-Write)
 * @param   reg Địa chỉ register
 * @param   mask Mask các bit cần modify
 * @param   value Giá trị mới (đã shift đúng vị trí)
 */
static ICM42605_Status_t prv_ModifyRegister(ICM42605_Handle_t *handle,
                                             uint8_t reg,
                                             uint8_t mask,
                                             uint8_t value)
{
    uint8_t current;
    ICM42605_Status_t ret = prv_ReadRegister(handle, reg, &current);
    if (ret != ICM42605_OK) return ret;

    current = (current & ~mask) | (value & mask);
    return prv_WriteRegister(handle, reg, current);
}

/**
 * @brief   Chuyển bank register (nội bộ, có tracking)
 */
static ICM42605_Status_t prv_SelectBank(ICM42605_Handle_t *handle, ICM42605_Bank_t bank)
{
    if (handle->current_bank == bank) {
        return ICM42605_OK; /* Đã ở bank đúng, không cần switch */
    }

    ICM42605_Status_t ret = prv_WriteRegister(handle, ICM42605_REG_REG_BANK_SEL, (uint8_t)bank);
    if (ret == ICM42605_OK) {
        handle->current_bank = bank;
    }
    return ret;
}

/**
 * @brief   Cập nhật bảng sensitivity dựa trên FS_SEL hiện tại
 */
static void prv_UpdateSensitivity(ICM42605_Handle_t *handle)
{
    if (handle->accel_fs <= ICM42605_ACCEL_FS_2G) {
        handle->accel_sensitivity = accel_sensitivity_table[handle->accel_fs];
    }
    if (handle->gyro_fs <= ICM42605_GYRO_FS_15_625DPS) {
        handle->gyro_sensitivity = gyro_sensitivity_table[handle->gyro_fs];
    }
}

/* ========================================================================================
 * SECTION: Public API - Initialization
 * ======================================================================================== */

ICM42605_Status_t ICM42605_Init(ICM42605_Handle_t *handle,
                                BSP_SPI_Handle_t *spi_handle,
                                GPIO_TypeDef *cs_port,
                                uint16_t cs_pin)
{
    if (handle == NULL || spi_handle == NULL) {
        return ICM42605_ERROR;
    }

    LOG_INFO("[ICM42605] Initializing...");

    /* Gán hardware config */
    handle->spi_handle = spi_handle;
    handle->cs_port = cs_port;
    handle->cs_pin = cs_pin;
    handle->timeout = ICM42605_DEFAULT_TIMEOUT_MS;
    handle->current_bank = ICM42605_BANK_0;

    /* CS ban đầu ở HIGH (deselect) */
    ICM42605_CS_Deselect(handle);
    osDelay(10);

    /* Debug: Đọc WHO_AM_I TRƯỚC soft-reset để verify SPI */
    uint8_t pre_id = ICM42605_ReadWhoAmI(handle);
    LOG_INFO("[ICM42605] Pre-reset WHO_AM_I = 0x%02X", pre_id);

    /* Soft-reset chip */
    ICM42605_Status_t ret = ICM42605_SoftReset(handle);
    if (ret != ICM42605_OK) {
        LOG_ERROR("[ICM42605] Soft-reset FAILED");
        return ret;
    }

    /* Verify WHO_AM_I (retry tối đa 3 lần) */
    uint8_t who_am_i = 0;
    for (int retry = 0; retry < 3; retry++) {
        who_am_i = ICM42605_ReadWhoAmI(handle);
        LOG_INFO("[ICM42605] WHO_AM_I attempt %d: 0x%02X", retry + 1, who_am_i);
        if (who_am_i == ICM42605_WHO_AM_I_VALUE) break;
        osDelay(10); /* Chờ thêm giữa các lần thử */
    }

    if (who_am_i != ICM42605_WHO_AM_I_VALUE) {
        LOG_ERROR("[ICM42605] WHO_AM_I mismatch: 0x%02X (expected 0x%02X)", who_am_i, ICM42605_WHO_AM_I_VALUE);
        return ICM42605_INVALID_ID;
    }
    LOG_INFO("[ICM42605] WHO_AM_I = 0x%02X (OK)", who_am_i);

    /* --- Cấu hình mặc định --- */

    /* Cấu hình INT pins: Open-Drain, Active-low, Pulsed cho cả INT1 và INT2 */
    uint8_t int_config = 0;
    int_config |= (ICM42605_INT_OPEN_DRAIN  << ICM42605_INT1_DRIVE_BIT);
    int_config |= (ICM42605_INT_ACTIVE_LOW  << ICM42605_INT1_POLARITY_BIT);
    int_config |= (ICM42605_INT_PULSED      << ICM42605_INT1_MODE_BIT);
    int_config |= (ICM42605_INT_OPEN_DRAIN  << ICM42605_INT2_DRIVE_BIT);
    int_config |= (ICM42605_INT_ACTIVE_LOW  << ICM42605_INT2_POLARITY_BIT);
    int_config |= (ICM42605_INT_PULSED      << ICM42605_INT2_MODE_BIT);
    prv_WriteRegister(handle, ICM42605_REG_INT_CONFIG, int_config);

    /* Xóa toàn bộ routing ngắt mặc định (tránh RESET_DONE / DATA_RDY bắn ra INT1) */
    prv_WriteRegister(handle, ICM42605_REG_INT_SOURCE0, 0x00);
    prv_WriteRegister(handle, ICM42605_REG_INT_SOURCE1, 0x00);
    prv_WriteRegister(handle, ICM42605_REG_INT_SOURCE3, 0x00);
    prv_WriteRegister(handle, ICM42605_REG_INT_SOURCE4, 0x00);

    /* Đọc để clear các cờ ngắt còn tồn đọng ngay sau khi boot / reset */
    uint8_t dummy_status;
    ICM42605_ReadIntStatus(handle, &dummy_status);

    /* Cấu hình Accel: ±4g, 100Hz */
    ICM42605_ConfigAccel(handle, ICM42605_ACCEL_FS_4G, ICM42605_ODR_100HZ);

    /* Cấu hình Gyro: ±500dps, 100Hz */
    ICM42605_ConfigGyro(handle, ICM42605_GYRO_FS_500DPS, ICM42605_ODR_100HZ);

    /* Bật cả Accel và Gyro ở Low-Noise mode */
    ICM42605_SetAccelMode(handle, ICM42605_ACCEL_MODE_LN);
    ICM42605_SetGyroMode(handle, ICM42605_GYRO_MODE_LN);

    /* Cần delay 200µs sau khi bật sensor (datasheet requirement) */
    osDelay(ICM42605_POWER_CHANGE_DELAY_MS);

    LOG_INFO("[ICM42605] Init complete (Accel:±4g@100Hz, Gyro:±500dps@100Hz)");
    return ICM42605_OK;
}

ICM42605_Status_t ICM42605_SoftReset(ICM42605_Handle_t *handle)
{
    /* Đảm bảo đang ở Bank 0 */
    prv_SelectBank(handle, ICM42605_BANK_0);

    /* Ghi bit SOFT_RESET vào DEVICE_CONFIG */
    ICM42605_Status_t ret = prv_WriteRegister(handle, ICM42605_REG_DEVICE_CONFIG, ICM42605_SOFT_RESET_CONFIG);
    if (ret != ICM42605_OK) return ret;

    /* Chờ reset hoàn tất (datasheet: 1ms minimum) */
    osDelay(ICM42605_RESET_DELAY_MS);

    /* Sau reset, bank tự về 0 */
    handle->current_bank = ICM42605_BANK_0;

    return ICM42605_OK;
}

uint8_t ICM42605_ReadWhoAmI(ICM42605_Handle_t *handle)
{
    uint8_t value = 0;
    prv_SelectBank(handle, ICM42605_BANK_0);
    prv_ReadRegister(handle, ICM42605_REG_WHO_AM_I, &value);
    return value;
}

/* ========================================================================================
 * SECTION: Public API - Power Management
 * ======================================================================================== */

ICM42605_Status_t ICM42605_SetAccelMode(ICM42605_Handle_t *handle, ICM42605_AccelMode_t mode)
{
    prv_SelectBank(handle, ICM42605_BANK_0);
    return prv_ModifyRegister(handle, ICM42605_REG_PWR_MGMT0,
                              ICM42605_PWR_ACCEL_MODE_MASK,
                              (uint8_t)mode << ICM42605_PWR_ACCEL_MODE_SHIFT);
}

ICM42605_Status_t ICM42605_SetGyroMode(ICM42605_Handle_t *handle, ICM42605_GyroMode_t mode)
{
    prv_SelectBank(handle, ICM42605_BANK_0);
    return prv_ModifyRegister(handle, ICM42605_REG_PWR_MGMT0,
                              ICM42605_PWR_GYRO_MODE_MASK,
                              (uint8_t)mode << ICM42605_PWR_GYRO_MODE_SHIFT);
}

ICM42605_Status_t ICM42605_SetTempDisable(ICM42605_Handle_t *handle, bool disable)
{
    prv_SelectBank(handle, ICM42605_BANK_0);
    return prv_ModifyRegister(handle, ICM42605_REG_PWR_MGMT0,
                              (1 << ICM42605_PWR_TEMP_DIS_BIT),
                              (disable ? 1 : 0) << ICM42605_PWR_TEMP_DIS_BIT);
}

ICM42605_Status_t ICM42605_SetIdleMode(ICM42605_Handle_t *handle, bool idle)
{
    prv_SelectBank(handle, ICM42605_BANK_0);
    return prv_ModifyRegister(handle, ICM42605_REG_PWR_MGMT0,
                              (1 << ICM42605_PWR_IDLE_BIT),
                              (idle ? 1 : 0) << ICM42605_PWR_IDLE_BIT);
}

/* ========================================================================================
 * SECTION: Public API - Sensor Configuration
 * ======================================================================================== */

ICM42605_Status_t ICM42605_ConfigAccel(ICM42605_Handle_t *handle,
                                       ICM42605_AccelFS_t fs,
                                       ICM42605_ODR_t odr)
{
    prv_SelectBank(handle, ICM42605_BANK_0);

    /*
     * ACCEL_CONFIG0 (0x50):
     *   [7:5] = ACCEL_FS_SEL
     *   [3:0] = ACCEL_ODR
     */
    uint8_t val = ((uint8_t)fs << 5) | ((uint8_t)odr & 0x0F);
    ICM42605_Status_t ret = prv_WriteRegister(handle, ICM42605_REG_ACCEL_CONFIG0, val);
    if (ret != ICM42605_OK) return ret;

    /* Cập nhật state và sensitivity */
    handle->accel_fs = fs;
    handle->accel_odr = odr;
    prv_UpdateSensitivity(handle);

    return ICM42605_OK;
}

ICM42605_Status_t ICM42605_ConfigGyro(ICM42605_Handle_t *handle,
                                      ICM42605_GyroFS_t fs,
                                      ICM42605_ODR_t odr)
{
    prv_SelectBank(handle, ICM42605_BANK_0);

    /*
     * GYRO_CONFIG0 (0x4F):
     *   [7:5] = GYRO_FS_SEL
     *   [3:0] = GYRO_ODR
     */
    uint8_t val = ((uint8_t)fs << 5) | ((uint8_t)odr & 0x0F);
    ICM42605_Status_t ret = prv_WriteRegister(handle, ICM42605_REG_GYRO_CONFIG0, val);
    if (ret != ICM42605_OK) return ret;

    /* Cập nhật state và sensitivity */
    handle->gyro_fs = fs;
    handle->gyro_odr = odr;
    prv_UpdateSensitivity(handle);

    return ICM42605_OK;
}

/* ========================================================================================
 * SECTION: Public API - Data Reading (Individual)
 * ======================================================================================== */

ICM42605_Status_t ICM42605_ReadAccelRaw(ICM42605_Handle_t *handle, ICM42605_RawData_t *data)
{
    if (handle == NULL || data == NULL) return ICM42605_ERROR;

    prv_SelectBank(handle, ICM42605_BANK_0);

    uint8_t buf[6];
    ICM42605_Status_t ret = prv_ReadRegisters(handle, ICM42605_REG_ACCEL_DATA_X1, buf, 6);
    if (ret != ICM42605_OK) return ret;

    /* Big-endian: [High byte][Low byte] */
    data->x = (int16_t)((buf[0] << 8) | buf[1]);
    data->y = (int16_t)((buf[2] << 8) | buf[3]);
    data->z = (int16_t)((buf[4] << 8) | buf[5]);

    return ICM42605_OK;
}

ICM42605_Status_t ICM42605_ReadGyroRaw(ICM42605_Handle_t *handle, ICM42605_RawData_t *data)
{
    if (handle == NULL || data == NULL) return ICM42605_ERROR;

    prv_SelectBank(handle, ICM42605_BANK_0);

    uint8_t buf[6];
    ICM42605_Status_t ret = prv_ReadRegisters(handle, ICM42605_REG_GYRO_DATA_X1, buf, 6);
    if (ret != ICM42605_OK) return ret;

    data->x = (int16_t)((buf[0] << 8) | buf[1]);
    data->y = (int16_t)((buf[2] << 8) | buf[3]);
    data->z = (int16_t)((buf[4] << 8) | buf[5]);

    return ICM42605_OK;
}

ICM42605_Status_t ICM42605_ReadAccelScaled(ICM42605_Handle_t *handle, ICM42605_ScaledData_t *data)
{
    if (handle == NULL || data == NULL) return ICM42605_ERROR;

    ICM42605_RawData_t raw;
    ICM42605_Status_t ret = ICM42605_ReadAccelRaw(handle, &raw);
    if (ret != ICM42605_OK) return ret;

    data->x = (float)raw.x / handle->accel_sensitivity;
    data->y = (float)raw.y / handle->accel_sensitivity;
    data->z = (float)raw.z / handle->accel_sensitivity;

    return ICM42605_OK;
}

ICM42605_Status_t ICM42605_ReadGyroScaled(ICM42605_Handle_t *handle, ICM42605_ScaledData_t *data)
{
    if (handle == NULL || data == NULL) return ICM42605_ERROR;

    ICM42605_RawData_t raw;
    ICM42605_Status_t ret = ICM42605_ReadGyroRaw(handle, &raw);
    if (ret != ICM42605_OK) return ret;

    data->x = (float)raw.x / handle->gyro_sensitivity;
    data->y = (float)raw.y / handle->gyro_sensitivity;
    data->z = (float)raw.z / handle->gyro_sensitivity;

    return ICM42605_OK;
}

ICM42605_Status_t ICM42605_ReadTemperature(ICM42605_Handle_t *handle, float *temp_degC)
{
    if (handle == NULL || temp_degC == NULL) return ICM42605_ERROR;

    prv_SelectBank(handle, ICM42605_BANK_0);

    uint8_t buf[2];
    ICM42605_Status_t ret = prv_ReadRegisters(handle, ICM42605_REG_TEMP_DATA1, buf, 2);
    if (ret != ICM42605_OK) return ret;

    int16_t raw = (int16_t)((buf[0] << 8) | buf[1]);

    /*
     * Công thức chuyển đổi nhiệt độ (datasheet):
     * Temperature (°C) = (TEMP_DATA / 132.48) + 25
     */
    *temp_degC = ((float)raw / 132.48f) + 25.0f;

    return ICM42605_OK;
}

/* ========================================================================================
 * SECTION: Public API - Data Reading (Batch)
 * ======================================================================================== */

ICM42605_Status_t ICM42605_ReadAllData(ICM42605_Handle_t *handle, ICM42605_AllData_t *data)
{
    if (handle == NULL || data == NULL) return ICM42605_ERROR;

    prv_SelectBank(handle, ICM42605_BANK_0);

    /*
     * Burst read 14 bytes bắt đầu từ TEMP_DATA1 (0x1D):
     * [0-1]  = TEMP_DATA (H, L)
     * [2-7]  = ACCEL_DATA (XH, XL, YH, YL, ZH, ZL)
     * [8-13] = GYRO_DATA  (XH, XL, YH, YL, ZH, ZL)
     */
    uint8_t buf[ICM42605_ALL_DATA_SIZE];
    ICM42605_Status_t ret = prv_ReadRegisters(handle, ICM42605_REG_TEMP_DATA1, buf, ICM42605_ALL_DATA_SIZE);
    if (ret != ICM42605_OK) return ret;

    /* Parse raw data */
    data->temp_raw = (int16_t)((buf[0] << 8) | buf[1]);

    data->accel_raw.x = (int16_t)((buf[2] << 8) | buf[3]);
    data->accel_raw.y = (int16_t)((buf[4] << 8) | buf[5]);
    data->accel_raw.z = (int16_t)((buf[6] << 8) | buf[7]);

    data->gyro_raw.x = (int16_t)((buf[8] << 8) | buf[9]);
    data->gyro_raw.y = (int16_t)((buf[10] << 8) | buf[11]);
    data->gyro_raw.z = (int16_t)((buf[12] << 8) | buf[13]);

    /* Chuyển đổi sang đơn vị thực */
    data->accel.x = (float)data->accel_raw.x / handle->accel_sensitivity;
    data->accel.y = (float)data->accel_raw.y / handle->accel_sensitivity;
    data->accel.z = (float)data->accel_raw.z / handle->accel_sensitivity;

    data->gyro.x = (float)data->gyro_raw.x / handle->gyro_sensitivity;
    data->gyro.y = (float)data->gyro_raw.y / handle->gyro_sensitivity;
    data->gyro.z = (float)data->gyro_raw.z / handle->gyro_sensitivity;

    data->temp_degC = ((float)data->temp_raw / 132.48f) + 25.0f;

    return ICM42605_OK;
}

/* ========================================================================================
 * SECTION: Public API - Interrupt Configuration
 * ======================================================================================== */

ICM42605_Status_t ICM42605_ConfigIntPin(ICM42605_Handle_t *handle,
                                         ICM42605_IntPin_t pin,
                                         const ICM42605_IntPinConfig_t *config)
{
    if (handle == NULL || config == NULL) return ICM42605_ERROR;

    prv_SelectBank(handle, ICM42605_BANK_0);

    uint8_t int_cfg;
    ICM42605_Status_t ret = prv_ReadRegister(handle, ICM42605_REG_INT_CONFIG, &int_cfg);
    if (ret != ICM42605_OK) return ret;

    if (pin == ICM42605_INT_PIN_1) {
        /* Xoá bits [2:0] rồi set lại */
        int_cfg &= ~(0x07); /* Clear INT1 bits */
        int_cfg |= ((uint8_t)config->mode     << ICM42605_INT1_MODE_BIT);
        int_cfg |= ((uint8_t)config->drive     << ICM42605_INT1_DRIVE_BIT);
        int_cfg |= ((uint8_t)config->polarity  << ICM42605_INT1_POLARITY_BIT);
    } else {
        /* Xoá bits [5:3] rồi set lại */
        int_cfg &= ~(0x38); /* Clear INT2 bits */
        int_cfg |= ((uint8_t)config->mode     << ICM42605_INT2_MODE_BIT);
        int_cfg |= ((uint8_t)config->drive     << ICM42605_INT2_DRIVE_BIT);
        int_cfg |= ((uint8_t)config->polarity  << ICM42605_INT2_POLARITY_BIT);
    }

    return prv_WriteRegister(handle, ICM42605_REG_INT_CONFIG, int_cfg);
}

ICM42605_Status_t ICM42605_EnableDataReadyInt(ICM42605_Handle_t *handle,
                                               ICM42605_IntPin_t pin,
                                               bool enable)
{
    prv_SelectBank(handle, ICM42605_BANK_0);

    if (pin == ICM42605_INT_PIN_1) {
        return prv_ModifyRegister(handle, ICM42605_REG_INT_SOURCE0,
                                  ICM42605_INT_SRC0_UI_DRDY,
                                  enable ? ICM42605_INT_SRC0_UI_DRDY : 0);
    } else {
        return prv_ModifyRegister(handle, ICM42605_REG_INT_SOURCE3,
                                  ICM42605_INT_SRC3_UI_DRDY,
                                  enable ? ICM42605_INT_SRC3_UI_DRDY : 0);
    }
}

ICM42605_Status_t ICM42605_EnableFifoThresholdInt(ICM42605_Handle_t *handle,
                                                   ICM42605_IntPin_t pin,
                                                   bool enable)
{
    prv_SelectBank(handle, ICM42605_BANK_0);

    if (pin == ICM42605_INT_PIN_1) {
        return prv_ModifyRegister(handle, ICM42605_REG_INT_SOURCE0,
                                  ICM42605_INT_SRC0_FIFO_THS,
                                  enable ? ICM42605_INT_SRC0_FIFO_THS : 0);
    } else {
        return prv_ModifyRegister(handle, ICM42605_REG_INT_SOURCE3,
                                  ICM42605_INT_SRC3_FIFO_THS,
                                  enable ? ICM42605_INT_SRC3_FIFO_THS : 0);
    }
}

ICM42605_Status_t ICM42605_EnableFifoFullInt(ICM42605_Handle_t *handle,
                                              ICM42605_IntPin_t pin,
                                              bool enable)
{
    prv_SelectBank(handle, ICM42605_BANK_0);

    if (pin == ICM42605_INT_PIN_1) {
        return prv_ModifyRegister(handle, ICM42605_REG_INT_SOURCE0,
                                  ICM42605_INT_SRC0_FIFO_FULL,
                                  enable ? ICM42605_INT_SRC0_FIFO_FULL : 0);
    } else {
        return prv_ModifyRegister(handle, ICM42605_REG_INT_SOURCE3,
                                  ICM42605_INT_SRC3_FIFO_FULL,
                                  enable ? ICM42605_INT_SRC3_FIFO_FULL : 0);
    }
}

ICM42605_Status_t ICM42605_EnableWomInt(ICM42605_Handle_t *handle,
                                         ICM42605_IntPin_t pin,
                                         bool enable)
{
    prv_SelectBank(handle, ICM42605_BANK_0);

    uint8_t mask = ICM42605_INT_SRC1_WOM_X | ICM42605_INT_SRC1_WOM_Y | ICM42605_INT_SRC1_WOM_Z;

    if (pin == ICM42605_INT_PIN_1) {
        return prv_ModifyRegister(handle, ICM42605_REG_INT_SOURCE1,
                                  mask, enable ? mask : 0);
    } else {
        return prv_ModifyRegister(handle, ICM42605_REG_INT_SOURCE4,
                                  mask, enable ? mask : 0);
    }
}

ICM42605_Status_t ICM42605_EnableSmdInt(ICM42605_Handle_t *handle,
                                         ICM42605_IntPin_t pin,
                                         bool enable)
{
    prv_SelectBank(handle, ICM42605_BANK_0);

    if (pin == ICM42605_INT_PIN_1) {
        return prv_ModifyRegister(handle, ICM42605_REG_INT_SOURCE1,
                                  ICM42605_INT_SRC1_SMD,
                                  enable ? ICM42605_INT_SRC1_SMD : 0);
    } else {
        return prv_ModifyRegister(handle, ICM42605_REG_INT_SOURCE4,
                                  ICM42605_INT_SRC4_SMD,
                                  enable ? ICM42605_INT_SRC4_SMD : 0);
    }
}

ICM42605_Status_t ICM42605_ReadIntStatus(ICM42605_Handle_t *handle, uint8_t *status)
{
    prv_SelectBank(handle, ICM42605_BANK_0);
    return prv_ReadRegister(handle, ICM42605_REG_INT_STATUS, status);
}

ICM42605_Status_t ICM42605_ReadIntStatus2(ICM42605_Handle_t *handle, uint8_t *status)
{
    prv_SelectBank(handle, ICM42605_BANK_0);
    return prv_ReadRegister(handle, ICM42605_REG_INT_STATUS2, status);
}

ICM42605_Status_t ICM42605_ReadIntStatus3(ICM42605_Handle_t *handle, uint8_t *status)
{
    prv_SelectBank(handle, ICM42605_BANK_0);
    return prv_ReadRegister(handle, ICM42605_REG_INT_STATUS3, status);
}

/* ========================================================================================
 * SECTION: Public API - Wake-on-Motion (WOM)
 * ======================================================================================== */

ICM42605_Status_t ICM42605_ConfigWom(ICM42605_Handle_t *handle,
                                      const ICM42605_WomConfig_t *config,
                                      ICM42605_SmdMode_t smd_mode)
{
    if (handle == NULL || config == NULL) return ICM42605_ERROR;

    ICM42605_Status_t ret;

    /*
     * Quy trình cấu hình WOM theo datasheet:
     * 1. Đảm bảo accel đang tắt
     * 2. Set Bank4 → ghi threshold X/Y/Z
     * 3. Set Bank0 → ghi SMD_CONFIG với WOM mode + SMD mode
     * 4. Bật accel ở LN mode
     * 5. Chờ accel ổn định, rồi bật WOM
     */

    /* Bước 1: Tắt accel tạm thời */
    ret = ICM42605_SetAccelMode(handle, ICM42605_ACCEL_MODE_OFF);
    if (ret != ICM42605_OK) return ret;
    osDelay(1);

    /* Bước 2: Ghi ngưỡng WOM (Bank 4) */
    ret = prv_SelectBank(handle, ICM42605_BANK_4);
    if (ret != ICM42605_OK) return ret;

    prv_WriteRegister(handle, ICM42605_REG_ACCEL_WOM_X_THR_B4, config->threshold_x);
    prv_WriteRegister(handle, ICM42605_REG_ACCEL_WOM_Y_THR_B4, config->threshold_y);
    prv_WriteRegister(handle, ICM42605_REG_ACCEL_WOM_Z_THR_B4, config->threshold_z);

    /* Bước 3: Cấu hình SMD_CONFIG (Bank 0) */
    ret = prv_SelectBank(handle, ICM42605_BANK_0);
    if (ret != ICM42605_OK) return ret;

    uint8_t smd_cfg = 0;
    smd_cfg |= ((uint8_t)config->wom_ref << ICM42605_WOM_INT_MODE_BIT);
    smd_cfg |= ((uint8_t)config->wom_mode << ICM42605_WOM_MODE_BIT);
    smd_cfg |= ((uint8_t)smd_mode & ICM42605_SMD_MODE_MASK);

    ret = prv_WriteRegister(handle, ICM42605_REG_SMD_CONFIG, smd_cfg);
    if (ret != ICM42605_OK) return ret;

    /* Bước 4: Chế độ hoạt động do Caller quyết định (mặc định bật lại LP để WOM chạy) */
    ret = ICM42605_SetAccelMode(handle, ICM42605_ACCEL_MODE_LP);
    if (ret != ICM42605_OK) return ret;
    
    osDelay(ICM42605_POWER_CHANGE_DELAY_MS);

    LOG_INFO("[ICM42605] WOM configured and Accel restored to LP (THR: X=%d Y=%d Z=%d)",
             config->threshold_x, config->threshold_y, config->threshold_z);

    return ICM42605_OK;
}

/* ========================================================================================
 * SECTION: Public API - Interrupt Callback Registration
 * ======================================================================================== */

ICM42605_Status_t ICM42605_RegisterINT1Callback(ICM42605_Handle_t *handle, ICM42605_IntCallback_t callback)
{
    if (handle == NULL) return ICM42605_ERROR;
    handle->int1_callback = callback;
    LOG_INFO("[ICM42605] INT1 callback registered");
    return ICM42605_OK;
}

ICM42605_Status_t ICM42605_RegisterINT2Callback(ICM42605_Handle_t *handle, ICM42605_IntCallback_t callback)
{
    if (handle == NULL) return ICM42605_ERROR;
    handle->int2_callback = callback;
    LOG_INFO("[ICM42605] INT2 callback registered");
    return ICM42605_OK;
}

/* ========================================================================================
 * SECTION: Public API - FIFO
 * ======================================================================================== */
ICM42605_Status_t ICM42605_ConfigFifo(ICM42605_Handle_t *handle, ICM42605_FifoMode_t mode)
{
    prv_SelectBank(handle, ICM42605_BANK_0);

    /*
     * FIFO_CONFIG (0x16):
     *   [7:6] = FIFO_MODE
     */
    ICM42605_Status_t ret = prv_ModifyRegister(handle, ICM42605_REG_FIFO_CONFIG,
                                               0xC0, (uint8_t)mode << 6);
    if (ret != ICM42605_OK) return ret;

    /*
     * FIFO_CONFIG1 (0x5F):
     * Chọn dữ liệu đẩy vào FIFO. Cần Accel + Gyro + Temp + Timestamp = 16 bytes.
     * Bit 3: TMST, Bit 2: TEMP, Bit 1: GYRO, Bit 0: ACCEL -> 0x0F
     * Nếu tắt FIFO (Bypass) thì cũng tắt luôn routing.
     */
    uint8_t fifo_cfg1 = (mode == ICM42605_FIFO_MODE_BYPASS) ? 0x00 : 0x0F;
    return prv_WriteRegister(handle, ICM42605_REG_FIFO_CONFIG1, fifo_cfg1);
}

ICM42605_Status_t ICM42605_SetFifoWatermark(ICM42605_Handle_t *handle, uint16_t watermark)
{
    prv_SelectBank(handle, ICM42605_BANK_0);

    /* FIFO_CONFIG2 = watermark [7:0], FIFO_CONFIG3 = watermark [11:8] */
    ICM42605_Status_t ret = prv_WriteRegister(handle, ICM42605_REG_FIFO_CONFIG2,
                                               (uint8_t)(watermark & 0xFF));
    if (ret != ICM42605_OK) return ret;

    return prv_WriteRegister(handle, ICM42605_REG_FIFO_CONFIG3,
                             (uint8_t)((watermark >> 8) & 0x0F));
}

ICM42605_Status_t ICM42605_ReadFifoCount(ICM42605_Handle_t *handle, uint16_t *count)
{
    if (handle == NULL || count == NULL) return ICM42605_ERROR;

    prv_SelectBank(handle, ICM42605_BANK_0);

    uint8_t buf[2];
    ICM42605_Status_t ret = prv_ReadRegisters(handle, ICM42605_REG_FIFO_COUNTH, buf, 2);
    if (ret != ICM42605_OK) return ret;

    *count = ((uint16_t)buf[0] << 8) | buf[1];
    return ICM42605_OK;
}

ICM42605_Status_t ICM42605_ReadFifoData(ICM42605_Handle_t *handle, uint8_t *buffer, uint16_t len)
{
    if (handle == NULL || buffer == NULL || len == 0) return ICM42605_ERROR;

    prv_SelectBank(handle, ICM42605_BANK_0);

    /*
     * Dùng burst read để đọc nhiều dữ liệu liên tục ra khỏi FIFO.
     * Tối ưu đọc 256 byte mỗi chunk thay vì 14 byte để tránh overhead SPI CS.
     */
    uint16_t remaining = len;
    uint16_t offset = 0;

    while (remaining > 0) {
        uint16_t chunk = (remaining > 256) ? 256 : remaining;

        /* Allocate 1 byte header + 256 bytes data */
        uint8_t tx_buf[257];
        uint8_t rx_buf[257];

        tx_buf[0] = ICM42605_REG_FIFO_DATA | ICM42605_SPI_READ_BIT;
        memset(&tx_buf[1], 0, chunk);

        if (BSP_SPI_LockBus(handle->spi_handle, handle->timeout) != BSP_SPI_OK) {
            return ICM42605_BUSY;
        }

        ICM42605_CS_Select(handle);
        BSP_SPI_Status_t spi_ret = BSP_SPI_TransmitReceive(handle->spi_handle,
                                                             tx_buf, rx_buf,
                                                             chunk + 1, handle->timeout);
        ICM42605_CS_Deselect(handle);
        BSP_SPI_UnlockBus(handle->spi_handle);

        if (spi_ret != BSP_SPI_OK) return ICM42605_ERROR;

        memcpy(&buffer[offset], &rx_buf[1], chunk);
        offset += chunk;
        remaining -= chunk;
    }

    return ICM42605_OK;
}

ICM42605_Status_t ICM42605_ReadFifoDMA(ICM42605_Handle_t *handle, uint8_t *buffer, uint16_t len)
{
    if (handle == NULL || buffer == NULL || len == 0) return ICM42605_ERROR;

    /* TX Dummy buffer chuẩn bị cho DMA (SPI Full-Duplex cần truyền để nhận) */
    static uint8_t dma_tx_dummy[256]; /* Statics được init bằng 0 */

    prv_SelectBank(handle, ICM42605_BANK_0);

    /* 1. Lock Bus */
    if (BSP_SPI_LockBus(handle->spi_handle, handle->timeout) != BSP_SPI_OK) return ICM42605_BUSY;

    /* 2. CS Select */
    ICM42605_CS_Select(handle);

    /* 3. Gửi địa chỉ thanh ghi bằng Polling (nhanh) */
    uint8_t addr = ICM42605_REG_FIFO_DATA | ICM42605_SPI_READ_BIT;
    if (BSP_SPI_Transmit(handle->spi_handle, &addr, 1, handle->timeout) != BSP_SPI_OK) {
        ICM42605_CS_Deselect(handle);
        BSP_SPI_UnlockBus(handle->spi_handle);
        return ICM42605_ERROR;
    }

    /* 4. Đọc dữ liệu bằng DMA */
    uint16_t rem = len;
    uint16_t offset = 0;
    while(rem > 0) {
        uint16_t chunk = (rem > 256) ? 256 : rem;

        if (BSP_SPI_TransmitReceive_DMA(handle->spi_handle, dma_tx_dummy, &buffer[offset], chunk) != BSP_SPI_OK) {
            ICM42605_CS_Deselect(handle);
            BSP_SPI_UnlockBus(handle->spi_handle);
            return ICM42605_ERROR;
        }

        /* Đợi DMA xong (Task vào trạng thái Blocked, chân CS vẫn LOW, Mutex vẫn giữ) */
        if (BSP_SPI_WaitDone(handle->spi_handle, handle->timeout) != BSP_SPI_OK) {
            ICM42605_CS_Deselect(handle);
            BSP_SPI_UnlockBus(handle->spi_handle);
            return ICM42605_TIMEOUT;
        }

        offset += chunk;
        rem -= chunk;
    }

    /* 5. CS Deselect */
    ICM42605_CS_Deselect(handle);

    /* 6. Unlock Bus */
    BSP_SPI_UnlockBus(handle->spi_handle);

    return ICM42605_OK;
}

ICM42605_Status_t ICM42605_FlushFifo(ICM42605_Handle_t *handle)
{
    prv_SelectBank(handle, ICM42605_BANK_0);
    return prv_ModifyRegister(handle, ICM42605_REG_SIGNAL_PATH_RESET,
                              ICM42605_FIFO_FLUSH, ICM42605_FIFO_FLUSH);
}

/* ========================================================================================
 * SECTION: Public API - Self-Test
 * ======================================================================================== */

ICM42605_Status_t ICM42605_SelfTest(ICM42605_Handle_t *handle,
                                     bool *accel_pass,
                                     bool *gyro_pass)
{
    if (handle == NULL || accel_pass == NULL || gyro_pass == NULL) {
        return ICM42605_ERROR;
    }

    ICM42605_Status_t ret;
    int32_t accel_sum_normal[3] = {0, 0, 0};
    int32_t gyro_sum_normal[3] = {0, 0, 0};
    int32_t accel_sum_st[3] = {0, 0, 0};
    int32_t gyro_sum_st[3] = {0, 0, 0};
    ICM42605_RawData_t raw;

    LOG_INFO("[ICM42605] Starting self-test...");

    /* Lưu cấu hình hiện tại */
    ICM42605_AccelFS_t saved_accel_fs = handle->accel_fs;
    ICM42605_GyroFS_t  saved_gyro_fs  = handle->gyro_fs;
    ICM42605_ODR_t     saved_accel_odr = handle->accel_odr;
    ICM42605_ODR_t     saved_gyro_odr  = handle->gyro_odr;

    /* Cấu hình self-test: ±4g, ±250dps, 1kHz */
    ICM42605_ConfigAccel(handle, ICM42605_ACCEL_FS_4G, ICM42605_ODR_1KHZ);
    ICM42605_ConfigGyro(handle, ICM42605_GYRO_FS_250DPS, ICM42605_ODR_1KHZ);
    ICM42605_SetAccelMode(handle, ICM42605_ACCEL_MODE_LN);
    ICM42605_SetGyroMode(handle, ICM42605_GYRO_MODE_LN);
    osDelay(100); /* Chờ ổn định */

    /* Bước 1: Đọc output bình thường (không có self-test) */
    for (int i = 0; i < ICM42605_SELFTEST_SAMPLES; i++) {
        ret = ICM42605_ReadAccelRaw(handle, &raw);
        if (ret == ICM42605_OK) {
            accel_sum_normal[0] += raw.x;
            accel_sum_normal[1] += raw.y;
            accel_sum_normal[2] += raw.z;
        }

        ret = ICM42605_ReadGyroRaw(handle, &raw);
        if (ret == ICM42605_OK) {
            gyro_sum_normal[0] += raw.x;
            gyro_sum_normal[1] += raw.y;
            gyro_sum_normal[2] += raw.z;
        }
        osDelay(1);
    }

    /* Bước 2: Bật self-test mode */
    prv_SelectBank(handle, ICM42605_BANK_0);
    prv_WriteRegister(handle, ICM42605_REG_SELF_TEST_CONFIG, 0x7F); /* Bật ST cho cả accel + gyro */
    osDelay(100); /* Chờ ổn định */

    /* Bước 3: Đọc output khi self-test bật */
    for (int i = 0; i < ICM42605_SELFTEST_SAMPLES; i++) {
        ret = ICM42605_ReadAccelRaw(handle, &raw);
        if (ret == ICM42605_OK) {
            accel_sum_st[0] += raw.x;
            accel_sum_st[1] += raw.y;
            accel_sum_st[2] += raw.z;
        }

        ret = ICM42605_ReadGyroRaw(handle, &raw);
        if (ret == ICM42605_OK) {
            gyro_sum_st[0] += raw.x;
            gyro_sum_st[1] += raw.y;
            gyro_sum_st[2] += raw.z;
        }
        osDelay(1);
    }

    /* Tắt self-test */
    prv_WriteRegister(handle, ICM42605_REG_SELF_TEST_CONFIG, 0x00);

    /* Bước 4: Tính delta (trung bình ST - trung bình normal) */
    float accel_delta[3], gyro_delta[3];
    for (int i = 0; i < 3; i++) {
        accel_delta[i] = (float)(accel_sum_st[i] - accel_sum_normal[i]) / ICM42605_SELFTEST_SAMPLES;
        gyro_delta[i]  = (float)(gyro_sum_st[i] - gyro_sum_normal[i]) / ICM42605_SELFTEST_SAMPLES;
    }

    /* Chuyển sang đơn vị vật lý: Accel → mg, Gyro → dps */
    float accel_sens = accel_sensitivity_table[ICM42605_ACCEL_FS_4G];
    float gyro_sens  = gyro_sensitivity_table[ICM42605_GYRO_FS_250DPS];

    *accel_pass = true;
    *gyro_pass = true;

    for (int i = 0; i < 3; i++) {
        float accel_mg = fabsf(accel_delta[i] / accel_sens * 1000.0f);
        float gyro_dps = fabsf(gyro_delta[i] / gyro_sens);

        if (accel_mg < ICM42605_ST_ACCEL_MIN_MG || accel_mg > ICM42605_ST_ACCEL_MAX_MG) {
            *accel_pass = false;
        }
        if (gyro_dps < ICM42605_ST_GYRO_MIN_DPS) {
            *gyro_pass = false;
        }
    }

    LOG_INFO("[ICM42605] Self-test: Accel=%s, Gyro=%s",
             *accel_pass ? "PASS" : "FAIL",
             *gyro_pass ? "PASS" : "FAIL");

    /* Khôi phục cấu hình gốc */
    ICM42605_ConfigAccel(handle, saved_accel_fs, saved_accel_odr);
    ICM42605_ConfigGyro(handle, saved_gyro_fs, saved_gyro_odr);

    return ICM42605_OK;
}

/* ========================================================================================
 * SECTION: Public API - Low-Level Register Access
 * ======================================================================================== */

ICM42605_Status_t ICM42605_ReadReg(ICM42605_Handle_t *handle, uint8_t reg, uint8_t *value)
{
    return prv_ReadRegister(handle, reg, value);
}

ICM42605_Status_t ICM42605_WriteReg(ICM42605_Handle_t *handle, uint8_t reg, uint8_t value)
{
    return prv_WriteRegister(handle, reg, value);
}

ICM42605_Status_t ICM42605_ReadRegs(ICM42605_Handle_t *handle, uint8_t reg, uint8_t *buffer, uint16_t len)
{
    return prv_ReadRegisters(handle, reg, buffer, len);
}

ICM42605_Status_t ICM42605_SelectBank(ICM42605_Handle_t *handle, ICM42605_Bank_t bank)
{
    return prv_SelectBank(handle, bank);
}
