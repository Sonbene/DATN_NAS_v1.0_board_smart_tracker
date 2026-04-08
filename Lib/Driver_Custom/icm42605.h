/**
 * @file    icm42605.h
 * @brief   ICM-42605 6-Axis IMU (Accel + Gyro) SPI Driver
 * @details Driver cho cảm biến ICM-42605 của TDK InvenSense, giao tiếp qua SPI.
 *          Hỗ trợ đầy đủ:
 *          - Đọc accelerometer, gyroscope, nhiệt độ (riêng lẻ và batch)
 *          - Cấu hình ODR, Full-Scale Range, Power Mode
 *          - Cấu hình ngắt INT1/INT2 với các nguồn ngắt đa dạng
 *          - Wake-on-Motion (WOM), FIFO watermark, Data Ready
 *          - Chuyển Bank register (Bank 0-4)
 *          - Self-test
 *
 * @note    Sử dụng BSP_SPI layer để giao tiếp, thread-safe với RTOS.
 *          SPI Mode 0 hoặc Mode 3, tốc độ tối đa 24MHz.
 *
 * @author  DATN_NAS
 * @version 1.0
 * @date    2026-04-08
 */

#ifndef __ICM42605_H__
#define __ICM42605_H__

#include <stdint.h>
#include <stdbool.h>
#include "bsp_spi.h"

/* ========================================================================================
 * SECTION: SPI Protocol Constants
 * ======================================================================================== */

/** @brief Bit[7] = 1 cho lệnh đọc SPI */
#define ICM42605_SPI_READ_BIT               0x80

/** @brief Expected WHO_AM_I value cho ICM-42605 */
#define ICM42605_WHO_AM_I_VALUE             0x42

/* ========================================================================================
 * SECTION: Register Map - Bank 0 (Default)
 * ======================================================================================== */

/* --- Device Info --- */
#define ICM42605_REG_DEVICE_CONFIG          0x11    /**< Device Configuration */
#define ICM42605_REG_DRIVE_CONFIG           0x13    /**< Drive Configuration (slew rate) */
#define ICM42605_REG_INT_CONFIG             0x14    /**< Interrupt Configuration */
#define ICM42605_REG_FIFO_CONFIG            0x16    /**< FIFO Configuration */

/* --- Temperature Data --- */
#define ICM42605_REG_TEMP_DATA1             0x1D    /**< Temperature Data [15:8] */
#define ICM42605_REG_TEMP_DATA0             0x1E    /**< Temperature Data [7:0] */

/* --- Accelerometer Data --- */
#define ICM42605_REG_ACCEL_DATA_X1          0x1F    /**< Accel X [15:8] */
#define ICM42605_REG_ACCEL_DATA_X0          0x20    /**< Accel X [7:0] */
#define ICM42605_REG_ACCEL_DATA_Y1          0x21    /**< Accel Y [15:8] */
#define ICM42605_REG_ACCEL_DATA_Y0          0x22    /**< Accel Y [7:0] */
#define ICM42605_REG_ACCEL_DATA_Z1          0x23    /**< Accel Z [15:8] */
#define ICM42605_REG_ACCEL_DATA_Z0          0x24    /**< Accel Z [7:0] */

/* --- Gyroscope Data --- */
#define ICM42605_REG_GYRO_DATA_X1           0x25    /**< Gyro X [15:8] */
#define ICM42605_REG_GYRO_DATA_X0           0x26    /**< Gyro X [7:0] */
#define ICM42605_REG_GYRO_DATA_Y1           0x27    /**< Gyro Y [15:8] */
#define ICM42605_REG_GYRO_DATA_Y0           0x28    /**< Gyro Y [7:0] */
#define ICM42605_REG_GYRO_DATA_Z1           0x29    /**< Gyro Z [15:8] */
#define ICM42605_REG_GYRO_DATA_Z0           0x2A    /**< Gyro Z [7:0] */

/* --- Timestamp --- */
#define ICM42605_REG_TMST_FSYNCH            0x2B    /**< Timestamp / FSYNC high byte */
#define ICM42605_REG_TMST_FSYNCL            0x2C    /**< Timestamp / FSYNC low byte */

/* --- Interrupt Status --- */
#define ICM42605_REG_INT_STATUS             0x2D    /**< Interrupt Status (Data Ready, FIFO, PLL, Reset) */
#define ICM42605_REG_INT_STATUS2            0x37    /**< Interrupt Status 2 (WOM X/Y/Z, SMD) */
#define ICM42605_REG_INT_STATUS3            0x38    /**< Interrupt Status 3 (Tap, Tilt, Step) */

/* --- FIFO --- */
#define ICM42605_REG_FIFO_COUNTH            0x2E    /**< FIFO Count [15:8] */
#define ICM42605_REG_FIFO_COUNTL            0x2F    /**< FIFO Count [7:0] */
#define ICM42605_REG_FIFO_DATA              0x30    /**< FIFO Read Data */

/* --- Signal Path Reset --- */
#define ICM42605_REG_SIGNAL_PATH_RESET      0x4B    /**< Signal Path Reset & Abort */

/* --- INTF Config --- */
#define ICM42605_REG_INTF_CONFIG0            0x4C    /**< Interface Configuration 0 */
#define ICM42605_REG_INTF_CONFIG1            0x4D    /**< Interface Configuration 1 */

/* --- Power Management --- */
#define ICM42605_REG_PWR_MGMT0             0x4E    /**< Power Management 0 */

/* --- Gyro & Accel Configuration --- */
#define ICM42605_REG_GYRO_CONFIG0           0x4F    /**< Gyro Config 0 (FS_SEL + ODR) */
#define ICM42605_REG_ACCEL_CONFIG0          0x50    /**< Accel Config 0 (FS_SEL + ODR) */
#define ICM42605_REG_GYRO_CONFIG1           0x51    /**< Gyro Config 1 (filter BW) */
#define ICM42605_REG_GYRO_ACCEL_CONFIG0     0x52    /**< Gyro/Accel Config 0 (filter order) */
#define ICM42605_REG_ACCEL_CONFIG1          0x53    /**< Accel Config 1 (filter BW) */

/* --- Timestamp Config --- */
#define ICM42605_REG_TMST_CONFIG            0x54    /**< Timestamp Config */

/* --- APEX Config --- */
#define ICM42605_REG_APEX_CONFIG0           0x56    /**< APEX Config 0 (DMP power, tilt/pedo enable) */

/* --- SMD Config --- */
#define ICM42605_REG_SMD_CONFIG             0x57    /**< Significant Motion Detection Config */

/* --- FIFO Config 1-3 --- */
#define ICM42605_REG_FIFO_CONFIG1           0x5F    /**< FIFO Config 1 (mode, resume, count) */
#define ICM42605_REG_FIFO_CONFIG2           0x60    /**< FIFO Watermark [7:0] */
#define ICM42605_REG_FIFO_CONFIG3           0x61    /**< FIFO Watermark [11:8] */

/* --- INT Source Config --- */
#define ICM42605_REG_INT_SOURCE0            0x65    /**< INT1 source: UI DRDY, FIFO THS, FIFO FULL, PLL, RESET */
#define ICM42605_REG_INT_SOURCE1            0x66    /**< INT1 source: WOM_X/Y/Z, SMD */
#define ICM42605_REG_INT_SOURCE3            0x68    /**< INT2 source: UI DRDY, FIFO THS, FIFO FULL, PLL, RESET */
#define ICM42605_REG_INT_SOURCE4            0x69    /**< INT2 source: WOM_X/Y/Z, SMD */

/* --- INT Source 6/7 (APEX to INT1/INT2) --- */
#define ICM42605_REG_INT_SOURCE6            0x4D    /**< APEX INT1 source (Tap, Tilt, Step, DMP) -- Bank 4 */
#define ICM42605_REG_INT_SOURCE7            0x4E    /**< APEX INT2 source (Tap, Tilt, Step, DMP) -- Bank 4 */

/* --- Self Test Config --- */
#define ICM42605_REG_SELF_TEST_CONFIG       0x70    /**< Self-Test Configuration */

/* --- WHO_AM_I --- */
#define ICM42605_REG_WHO_AM_I               0x75    /**< Device ID register */

/* --- Bank Select --- */
#define ICM42605_REG_REG_BANK_SEL           0x76    /**< Register Bank Selection */

/* ========================================================================================
 * SECTION: Register Map - Bank 1
 * ======================================================================================== */

#define ICM42605_REG_SENSOR_CONFIG0_B1      0x03    /**< Sensor Config 0 (Bank1) */
#define ICM42605_REG_GYRO_CONFIG_STATIC2    0x0B    /**< Gyro Config Static 2 (Bank1) */
#define ICM42605_REG_GYRO_CONFIG_STATIC3    0x0C    /**< Gyro Config Static 3 (Bank1) */
#define ICM42605_REG_GYRO_CONFIG_STATIC4    0x0D    /**< Gyro Config Static 4 (Bank1) */
#define ICM42605_REG_GYRO_CONFIG_STATIC5    0x0E    /**< Gyro Config Static 5 (Bank1) */
#define ICM42605_REG_INTF_CONFIG5_B1        0x7B    /**< Interface Config 5 (Bank1) - Pin config */

/* ========================================================================================
 * SECTION: Register Map - Bank 2
 * ======================================================================================== */

#define ICM42605_REG_ACCEL_CONFIG_STATIC2   0x03    /**< Accel Config Static 2 (Bank2) */
#define ICM42605_REG_ACCEL_CONFIG_STATIC3   0x04    /**< Accel Config Static 3 (Bank2) */
#define ICM42605_REG_ACCEL_CONFIG_STATIC4   0x05    /**< Accel Config Static 4 (Bank2) */

/* ========================================================================================
 * SECTION: Register Map - Bank 4
 * ======================================================================================== */

#define ICM42605_REG_APEX_CONFIG1_B4        0x40    /**< APEX Config 1 (Bank4) - DMP ODR */
#define ICM42605_REG_APEX_CONFIG2_B4        0x41    /**< APEX Config 2 (Bank4) - WOM threshold */
#define ICM42605_REG_APEX_CONFIG3_B4        0x42    /**< APEX Config 3 (Bank4) - Pedo params */
#define ICM42605_REG_APEX_CONFIG4_B4        0x43    /**< APEX Config 4 (Bank4) - Tilt wait time */
#define ICM42605_REG_APEX_CONFIG5_B4        0x44    /**< APEX Config 5 (Bank4) - Tap & mount */
#define ICM42605_REG_APEX_CONFIG6_B4        0x45    /**< APEX Config 6 (Bank4) */
#define ICM42605_REG_APEX_CONFIG7_B4        0x46    /**< APEX Config 7 (Bank4) */
#define ICM42605_REG_APEX_CONFIG8_B4        0x47    /**< APEX Config 8 (Bank4) */
#define ICM42605_REG_APEX_CONFIG9_B4        0x48    /**< APEX Config 9 (Bank4) */
#define ICM42605_REG_ACCEL_WOM_X_THR_B4    0x4A    /**< WOM X Threshold (Bank4) */
#define ICM42605_REG_ACCEL_WOM_Y_THR_B4    0x4B    /**< WOM Y Threshold (Bank4) */
#define ICM42605_REG_ACCEL_WOM_Z_THR_B4    0x4C    /**< WOM Z Threshold (Bank4) */
#define ICM42605_REG_INT_SOURCE6_B4        0x4D    /**< INT1: APEX ints (Bank4) */
#define ICM42605_REG_INT_SOURCE7_B4        0x4E    /**< INT2: APEX ints (Bank4) */

/* ========================================================================================
 * SECTION: Bit Masks & Bit Positions
 * ======================================================================================== */

/* PWR_MGMT0 (0x4E) */
#define ICM42605_PWR_TEMP_DIS_BIT           5       /**< Temperature sensor disable bit */
#define ICM42605_PWR_IDLE_BIT               4       /**< Idle mode bit */
#define ICM42605_PWR_GYRO_MODE_MASK         0x0C    /**< Gyro mode [3:2] */
#define ICM42605_PWR_GYRO_MODE_SHIFT        2
#define ICM42605_PWR_ACCEL_MODE_MASK        0x03    /**< Accel mode [1:0] */
#define ICM42605_PWR_ACCEL_MODE_SHIFT       0

/* INT_CONFIG (0x14) */
#define ICM42605_INT1_MODE_BIT              2       /**< INT1 mode: 0=pulsed, 1=latched */
#define ICM42605_INT1_DRIVE_BIT             1       /**< INT1 drive: 0=open-drain, 1=push-pull */
#define ICM42605_INT1_POLARITY_BIT          0       /**< INT1 polarity: 0=active-low, 1=active-high */
#define ICM42605_INT2_MODE_BIT              5       /**< INT2 mode: 0=pulsed, 1=latched */
#define ICM42605_INT2_DRIVE_BIT             4       /**< INT2 drive */
#define ICM42605_INT2_POLARITY_BIT          3       /**< INT2 polarity */

/* INT_STATUS (0x2D) */
#define ICM42605_INT_STATUS_RESET_DONE      (1 << 4)
#define ICM42605_INT_STATUS_DATA_RDY        (1 << 3)
#define ICM42605_INT_STATUS_FIFO_THS        (1 << 2)
#define ICM42605_INT_STATUS_FIFO_FULL       (1 << 1)
#define ICM42605_INT_STATUS_PLL_RDY         (1 << 0)  /**< AGC Ready / PLL Ready */

/* INT_STATUS2 (0x37) */
#define ICM42605_INT_STATUS2_SMD            (1 << 3)
#define ICM42605_INT_STATUS2_WOM_Z          (1 << 2)
#define ICM42605_INT_STATUS2_WOM_Y          (1 << 1)
#define ICM42605_INT_STATUS2_WOM_X          (1 << 0)

/* INT_STATUS3 (0x38) */
#define ICM42605_INT_STATUS3_STEP_DET       (1 << 5)
#define ICM42605_INT_STATUS3_STEP_OVF       (1 << 4)
#define ICM42605_INT_STATUS3_TILT_DET       (1 << 3)
#define ICM42605_INT_STATUS3_TAP_DET        (1 << 0)

/* INT_SOURCE0 (0x65) - INT1 sources */
#define ICM42605_INT_SRC0_UI_DRDY           (1 << 3)
#define ICM42605_INT_SRC0_FIFO_THS          (1 << 2)
#define ICM42605_INT_SRC0_FIFO_FULL         (1 << 1)
#define ICM42605_INT_SRC0_PLL_RDY           (1 << 0)
#define ICM42605_INT_SRC0_RESET_DONE        (1 << 4)

/* INT_SOURCE1 (0x66) - INT1 sources WOM/SMD */
#define ICM42605_INT_SRC1_SMD               (1 << 3)
#define ICM42605_INT_SRC1_WOM_Z             (1 << 2)
#define ICM42605_INT_SRC1_WOM_Y             (1 << 1)
#define ICM42605_INT_SRC1_WOM_X             (1 << 0)

/* INT_SOURCE3 (0x68) - INT2 sources */
#define ICM42605_INT_SRC3_UI_DRDY           (1 << 3)
#define ICM42605_INT_SRC3_FIFO_THS          (1 << 2)
#define ICM42605_INT_SRC3_FIFO_FULL         (1 << 1)
#define ICM42605_INT_SRC3_PLL_RDY           (1 << 0)
#define ICM42605_INT_SRC3_RESET_DONE        (1 << 4)

/* INT_SOURCE4 (0x69) - INT2 sources WOM/SMD */
#define ICM42605_INT_SRC4_SMD               (1 << 3)
#define ICM42605_INT_SRC4_WOM_Z             (1 << 2)
#define ICM42605_INT_SRC4_WOM_Y             (1 << 1)
#define ICM42605_INT_SRC4_WOM_X             (1 << 0)

/* INT_SOURCE6 (Bank4, 0x4D) - APEX INT1 */
#define ICM42605_INT_SRC6_STEP_DET          (1 << 5)
#define ICM42605_INT_SRC6_STEP_OVF          (1 << 4)
#define ICM42605_INT_SRC6_TILT_DET          (1 << 3)
#define ICM42605_INT_SRC6_TAP_DET           (1 << 0)

/* INT_SOURCE7 (Bank4, 0x4E) - APEX INT2 */
#define ICM42605_INT_SRC7_STEP_DET          (1 << 5)
#define ICM42605_INT_SRC7_STEP_OVF          (1 << 4)
#define ICM42605_INT_SRC7_TILT_DET          (1 << 3)
#define ICM42605_INT_SRC7_TAP_DET           (1 << 0)

/* SIGNAL_PATH_RESET (0x4B) */
#define ICM42605_ABORT_AND_RESET            (1 << 3)
#define ICM42605_TMST_STROBE               (1 << 2)
#define ICM42605_FIFO_FLUSH                 (1 << 1)

/* DEVICE_CONFIG (0x11) */
#define ICM42605_SOFT_RESET_CONFIG          (1 << 0)
#define ICM42605_SPI_MODE_BIT               4       /**< 0=Mode0&3, 1=Mode1&2 */

/* SMD_CONFIG (0x57) */
#define ICM42605_SMD_MODE_MASK              0x03    /**< SMD mode [1:0] */
#define ICM42605_WOM_INT_MODE_BIT           3       /**< WOM: 0=initial, 1=previous */
#define ICM42605_WOM_MODE_BIT               2       /**< WOM: 0=OR, 1=AND */

/* ========================================================================================
 * SECTION: Enumerations
 * ======================================================================================== */

/**
 * @brief ICM42605 return status codes
 */
typedef enum {
    ICM42605_OK = 0,        /**< Thành công */
    ICM42605_ERROR,         /**< Lỗi chung */
    ICM42605_BUSY,          /**< Bus SPI đang bận */
    ICM42605_TIMEOUT,       /**< Hết thời gian chờ */
    ICM42605_INVALID_ID     /**< WHO_AM_I không khớp */
} ICM42605_Status_t;

/**
 * @brief Register Bank selection (0-4)
 */
typedef enum {
    ICM42605_BANK_0 = 0,    /**< Bank 0 (default) */
    ICM42605_BANK_1 = 1,    /**< Bank 1 */
    ICM42605_BANK_2 = 2,    /**< Bank 2 */
    ICM42605_BANK_3 = 3,    /**< Bank 3 (reserved) */
    ICM42605_BANK_4 = 4     /**< Bank 4 */
} ICM42605_Bank_t;

/**
 * @brief Accelerometer Full-Scale Range
 */
typedef enum {
    ICM42605_ACCEL_FS_16G = 0,  /**< ±16g */
    ICM42605_ACCEL_FS_8G  = 1,  /**< ±8g */
    ICM42605_ACCEL_FS_4G  = 2,  /**< ±4g */
    ICM42605_ACCEL_FS_2G  = 3   /**< ±2g */
} ICM42605_AccelFS_t;

/**
 * @brief Gyroscope Full-Scale Range
 */
typedef enum {
    ICM42605_GYRO_FS_2000DPS = 0,   /**< ±2000°/s */
    ICM42605_GYRO_FS_1000DPS = 1,   /**< ±1000°/s */
    ICM42605_GYRO_FS_500DPS  = 2,   /**< ±500°/s */
    ICM42605_GYRO_FS_250DPS  = 3,   /**< ±250°/s */
    ICM42605_GYRO_FS_125DPS  = 4,   /**< ±125°/s */
    ICM42605_GYRO_FS_62_5DPS = 5,   /**< ±62.5°/s */
    ICM42605_GYRO_FS_31_25DPS = 6,  /**< ±31.25°/s */
    ICM42605_GYRO_FS_15_625DPS = 7  /**< ±15.625°/s */
} ICM42605_GyroFS_t;

/**
 * @brief Output Data Rate (ODR) cho Accel và Gyro
 */
typedef enum {
    ICM42605_ODR_32KHZ = 1,     /**< 32 kHz (chỉ LN mode) */
    ICM42605_ODR_16KHZ = 2,     /**< 16 kHz (chỉ LN mode) */
    ICM42605_ODR_8KHZ  = 3,     /**< 8 kHz (chỉ LN mode) */
    ICM42605_ODR_4KHZ  = 4,     /**< 4 kHz (chỉ LN mode) */
    ICM42605_ODR_2KHZ  = 5,     /**< 2 kHz (chỉ LN mode) */
    ICM42605_ODR_1KHZ  = 6,     /**< 1 kHz (LN mode default) */
    ICM42605_ODR_200HZ = 7,     /**< 200 Hz */
    ICM42605_ODR_100HZ = 8,     /**< 100 Hz */
    ICM42605_ODR_50HZ  = 9,     /**< 50 Hz */
    ICM42605_ODR_25HZ  = 10,    /**< 25 Hz */
    ICM42605_ODR_12_5HZ = 11,   /**< 12.5 Hz */
    ICM42605_ODR_6_25HZ  = 12,  /**< 6.25 Hz (chỉ Accel LP mode) */
    ICM42605_ODR_3_125HZ = 13,  /**< 3.125 Hz (chỉ Accel LP mode) */
    ICM42605_ODR_1_5625HZ = 14, /**< 1.5625 Hz (chỉ Accel LP mode) */
    ICM42605_ODR_500HZ = 15     /**< 500 Hz */
} ICM42605_ODR_t;

/**
 * @brief Accelerometer Power Mode
 */
typedef enum {
    ICM42605_ACCEL_MODE_OFF  = 0,   /**< Tắt */
    ICM42605_ACCEL_MODE_LP   = 2,   /**< Low Power */
    ICM42605_ACCEL_MODE_LN   = 3    /**< Low Noise (hiệu năng cao) */
} ICM42605_AccelMode_t;

/**
 * @brief Gyroscope Power Mode
 */
typedef enum {
    ICM42605_GYRO_MODE_OFF       = 0,   /**< Tắt */
    ICM42605_GYRO_MODE_STANDBY   = 1,   /**< Standby (giữ PLL hoạt động) */
    ICM42605_GYRO_MODE_LN        = 3    /**< Low Noise */
} ICM42605_GyroMode_t;

/**
 * @brief Interrupt pin selection
 */
typedef enum {
    ICM42605_INT_PIN_1 = 0,     /**< Chân INT1 */
    ICM42605_INT_PIN_2 = 1      /**< Chân INT2 */
} ICM42605_IntPin_t;

/**
 * @brief Interrupt drive type
 */
typedef enum {
    ICM42605_INT_OPEN_DRAIN = 0,    /**< Open-drain */
    ICM42605_INT_PUSH_PULL  = 1     /**< Push-pull */
} ICM42605_IntDrive_t;

/**
 * @brief Interrupt polarity
 */
typedef enum {
    ICM42605_INT_ACTIVE_LOW  = 0,   /**< Active low */
    ICM42605_INT_ACTIVE_HIGH = 1    /**< Active high */
} ICM42605_IntPolarity_t;

/**
 * @brief Interrupt mode (pulsed / latched)
 */
typedef enum {
    ICM42605_INT_PULSED  = 0,   /**< Pulsed (auto clear) */
    ICM42605_INT_LATCHED = 1    /**< Latched (phải đọc status register để clear) */
} ICM42605_IntMode_t;

/**
 * @brief Wake-on-Motion mode
 */
typedef enum {
    ICM42605_WOM_MODE_OR  = 0,  /**< Bất kỳ trục nào vượt ngưỡng → trigger */
    ICM42605_WOM_MODE_AND = 1   /**< Tất cả các trục phải vượt ngưỡng → trigger */
} ICM42605_WomMode_t;

/**
 * @brief WOM comparison reference
 */
typedef enum {
    ICM42605_WOM_REF_INITIAL  = 0,  /**< So sánh với mẫu đầu tiên */
    ICM42605_WOM_REF_PREVIOUS = 1   /**< So sánh với mẫu trước đó */
} ICM42605_WomRef_t;

/**
 * @brief Significant Motion Detection mode
 */
typedef enum {
    ICM42605_SMD_DISABLED = 0,  /**< Tắt SMD */
    ICM42605_SMD_WOM_OLD  = 1,  /**< WOM original mode */
    ICM42605_SMD_WOM_SHORT = 2, /**< WOM + short duration */
    ICM42605_SMD_WOM_LONG  = 3  /**< WOM + long duration */
} ICM42605_SmdMode_t;

/**
 * @brief FIFO mode
 */
typedef enum {
    ICM42605_FIFO_MODE_BYPASS       = 0,    /**< FIFO tắt */
    ICM42605_FIFO_MODE_STREAM       = 1,    /**< Stream mode */
    ICM42605_FIFO_MODE_STOP_ON_FULL = 2     /**< Dừng khi đầy */
} ICM42605_FifoMode_t;

/* ========================================================================================
 * SECTION: Data Structures
 * ======================================================================================== */

/**
 * @brief Cấu hình interrupt pin
 */
typedef struct {
    ICM42605_IntDrive_t     drive;      /**< Open-drain / Push-pull */
    ICM42605_IntPolarity_t  polarity;   /**< Active-low / Active-high */
    ICM42605_IntMode_t      mode;       /**< Pulsed / Latched */
} ICM42605_IntPinConfig_t;

/**
 * @brief Cấu hình Wake-on-Motion
 */
typedef struct {
    ICM42605_WomMode_t  wom_mode;       /**< OR / AND mode */
    ICM42605_WomRef_t   wom_ref;        /**< So sánh initial hay previous */
    uint8_t             threshold_x;    /**< Ngưỡng trục X (0-255, đơn vị ~4mg/LSB ở ±4g) */
    uint8_t             threshold_y;    /**< Ngưỡng trục Y */
    uint8_t             threshold_z;    /**< Ngưỡng trục Z */
} ICM42605_WomConfig_t;

/* Forward declaration */
struct ICM42605_Handle_s;

/**
 * @brief Callback function cho ngắt INT1 hoặc INT2
 * @param handle Pointer tới handle của IC đã trigger ngắt
 */
typedef void (*ICM42605_IntCallback_t)(struct ICM42605_Handle_s *handle);

/**
 * @brief Dữ liệu thô 3 trục (raw int16)
 */
typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} ICM42605_RawData_t;

/**
 * @brief Dữ liệu đã chuyển đổi (float, đơn vị thực)
 */
typedef struct {
    float x;
    float y;
    float z;
} ICM42605_ScaledData_t;

/**
 * @brief Dữ liệu IMU tổng hợp (cả accel + gyro + temp)
 */
typedef struct {
    ICM42605_RawData_t  accel_raw;      /**< Raw accelerometer data */
    ICM42605_RawData_t  gyro_raw;       /**< Raw gyroscope data */
    int16_t             temp_raw;       /**< Raw temperature data */
    ICM42605_ScaledData_t accel;        /**< Scaled accel (g) */
    ICM42605_ScaledData_t gyro;         /**< Scaled gyro (dps) */
    float               temp_degC;     /**< Temperature (°C) */
} ICM42605_AllData_t;

/**
 * @brief ICM-42605 Device Handle
 * @details Giữ tất cả thông tin cần thiết để vận hành IC.
 *          Mỗi IC vật lý cần 1 handle riêng.
 */
typedef struct ICM42605_Handle_s {
    BSP_SPI_Handle_t    *spi_handle;    /**< Pointer tới SPI bus handle */
    GPIO_TypeDef        *cs_port;       /**< CS pin GPIO port */
    uint16_t            cs_pin;         /**< CS pin number */
    uint32_t            timeout;        /**< SPI transaction timeout (ms) */

    /* Current configuration state */
    ICM42605_AccelFS_t  accel_fs;       /**< Full-scale range hiện tại của Accel */
    ICM42605_GyroFS_t   gyro_fs;        /**< Full-scale range hiện tại của Gyro */
    ICM42605_ODR_t      accel_odr;      /**< ODR hiện tại của Accel */
    ICM42605_ODR_t      gyro_odr;       /**< ODR hiện tại của Gyro */

    /* Sensitivity (pre-calculated for fast conversion) */
    float               accel_sensitivity;  /**< Accel LSB/g */
    float               gyro_sensitivity;   /**< Gyro LSB/dps */

    /* Current bank tracking */
    ICM42605_Bank_t     current_bank;   /**< Bank hiện đang active */

    /* Interrupt callbacks (tách riêng cho INT1 và INT2) */
    ICM42605_IntCallback_t int1_callback; /**< Callback khi INT1 trigger (VD: WOM) */
    ICM42605_IntCallback_t int2_callback; /**< Callback khi INT2 trigger (VD: FIFO WM) */
} ICM42605_Handle_t;

/* ========================================================================================
 * SECTION: Public API - Initialization
 * ======================================================================================== */

/**
 * @brief   Khởi tạo driver ICM-42605
 * @details Gán GPIO CS, SPI handle, soft-reset chip, verify WHO_AM_I,
 *          cấu hình mặc định (Accel ±4g, Gyro ±500dps, ODR 100Hz, LN mode)
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   spi_handle Pointer tới BSP_SPI_Handle_t đã được init
 * @param   cs_port GPIO port của chân CS
 * @param   cs_pin GPIO pin của chân CS
 * @return  ICM42605_OK nếu thành công, ICM42605_INVALID_ID nếu WHO_AM_I sai
 */
ICM42605_Status_t ICM42605_Init(ICM42605_Handle_t *handle,
                                BSP_SPI_Handle_t *spi_handle,
                                GPIO_TypeDef *cs_port,
                                uint16_t cs_pin);

/**
 * @brief   Soft-reset toàn bộ chip (quay về cấu hình factory default)
 * @param   handle Pointer tới ICM42605_Handle_t
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_SoftReset(ICM42605_Handle_t *handle);

/**
 * @brief   Đọc WHO_AM_I register để verify IC
 * @param   handle Pointer tới ICM42605_Handle_t
 * @return  Giá trị WHO_AM_I (expect 0x42 cho ICM-42605)
 */
uint8_t ICM42605_ReadWhoAmI(ICM42605_Handle_t *handle);

/* ========================================================================================
 * SECTION: Public API - Power Management
 * ======================================================================================== */

/**
 * @brief   Cấu hình power mode cho Accelerometer
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   mode Chế độ: OFF, Low-Power, hoặc Low-Noise
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_SetAccelMode(ICM42605_Handle_t *handle, ICM42605_AccelMode_t mode);

/**
 * @brief   Cấu hình power mode cho Gyroscope
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   mode Chế độ: OFF, Standby, hoặc Low-Noise
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_SetGyroMode(ICM42605_Handle_t *handle, ICM42605_GyroMode_t mode);

/**
 * @brief   Bật/tắt cảm biến nhiệt độ
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   disable true = tắt, false = bật
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_SetTempDisable(ICM42605_Handle_t *handle, bool disable);

/**
 * @brief   Đưa chip vào Idle mode (giảm power, giữ register)
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   idle true = idle mode, false = normal
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_SetIdleMode(ICM42605_Handle_t *handle, bool idle);

/* ========================================================================================
 * SECTION: Public API - Sensor Configuration
 * ======================================================================================== */

/**
 * @brief   Cấu hình Accelerometer (FS range + ODR)
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   fs Full-scale range (±2g, ±4g, ±8g, ±16g)
 * @param   odr Output data rate
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_ConfigAccel(ICM42605_Handle_t *handle,
                                       ICM42605_AccelFS_t fs,
                                       ICM42605_ODR_t odr);

/**
 * @brief   Cấu hình Gyroscope (FS range + ODR)
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   fs Full-scale range (±15.625 ~ ±2000 °/s)
 * @param   odr Output data rate
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_ConfigGyro(ICM42605_Handle_t *handle,
                                      ICM42605_GyroFS_t fs,
                                      ICM42605_ODR_t odr);

/* ========================================================================================
 * SECTION: Public API - Data Reading (Individual)
 * ======================================================================================== */

/**
 * @brief   Đọc accelerometer raw data (3 trục)
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   data Output: raw data 3 trục
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_ReadAccelRaw(ICM42605_Handle_t *handle, ICM42605_RawData_t *data);

/**
 * @brief   Đọc gyroscope raw data (3 trục)
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   data Output: raw data 3 trục
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_ReadGyroRaw(ICM42605_Handle_t *handle, ICM42605_RawData_t *data);

/**
 * @brief   Đọc accelerometer đã chuyển đổi (đơn vị: g)
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   data Output: scaled data (g)
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_ReadAccelScaled(ICM42605_Handle_t *handle, ICM42605_ScaledData_t *data);

/**
 * @brief   Đọc gyroscope đã chuyển đổi (đơn vị: °/s)
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   data Output: scaled data (dps)
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_ReadGyroScaled(ICM42605_Handle_t *handle, ICM42605_ScaledData_t *data);

/**
 * @brief   Đọc nhiệt độ (°C)
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   temp_degC Output: nhiệt độ (°C)
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_ReadTemperature(ICM42605_Handle_t *handle, float *temp_degC);

/* ========================================================================================
 * SECTION: Public API - Data Reading (Batch / All-in-one)
 * ======================================================================================== */

/**
 * @brief   Đọc toàn bộ dữ liệu (accel + gyro + temp) trong 1 lần SPI burst read
 * @details Đọc 14 bytes liên tiếp từ TEMP_DATA1 → GYRO_DATA_Z0.
 *          Hiệu quả hơn so với đọc riêng lẻ, đảm bảo dữ liệu cùng thời điểm.
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   data Output: tất cả dữ liệu raw + scaled
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_ReadAllData(ICM42605_Handle_t *handle, ICM42605_AllData_t *data);

/* ========================================================================================
 * SECTION: Public API - Interrupt Configuration
 * ======================================================================================== */

/**
 * @brief   Cấu hình thuộc tính chân ngắt (drive, polarity, mode)
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   pin Chọn INT1 hoặc INT2
 * @param   config Cấu hình drive/polarity/mode
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_ConfigIntPin(ICM42605_Handle_t *handle,
                                         ICM42605_IntPin_t pin,
                                         const ICM42605_IntPinConfig_t *config);

/**
 * @brief   Bật Data Ready interrupt trên chân INT chỉ định
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   pin Chọn INT1 hoặc INT2
 * @param   enable true = bật, false = tắt
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_EnableDataReadyInt(ICM42605_Handle_t *handle,
                                               ICM42605_IntPin_t pin,
                                               bool enable);

/**
 * @brief   Bật FIFO Threshold interrupt trên chân INT chỉ định
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   pin Chọn INT1 hoặc INT2
 * @param   enable true = bật, false = tắt
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_EnableFifoThresholdInt(ICM42605_Handle_t *handle,
                                                   ICM42605_IntPin_t pin,
                                                   bool enable);

/**
 * @brief   Bật FIFO Full interrupt trên chân INT chỉ định
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   pin Chọn INT1 hoặc INT2
 * @param   enable true = bật, false = tắt
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_EnableFifoFullInt(ICM42605_Handle_t *handle,
                                              ICM42605_IntPin_t pin,
                                              bool enable);

/**
 * @brief   Bật Wake-on-Motion interrupt trên chân INT chỉ định
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   pin Chọn INT1 hoặc INT2
 * @param   enable true = bật, false = tắt
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_EnableWomInt(ICM42605_Handle_t *handle,
                                         ICM42605_IntPin_t pin,
                                         bool enable);

/**
 * @brief   Bật Significant Motion Detection interrupt trên chân INT
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   pin Chọn INT1 hoặc INT2
 * @param   enable true = bật, false = tắt
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_EnableSmdInt(ICM42605_Handle_t *handle,
                                         ICM42605_IntPin_t pin,
                                         bool enable);

/**
 * @brief   Đăng ký callback cho ngắt INT1 (VD: Wake-on-Motion)
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   callback Hàm callback, được gọi từ Task context
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_RegisterINT1Callback(ICM42605_Handle_t *handle, ICM42605_IntCallback_t callback);

/**
 * @brief   Đăng ký callback cho ngắt INT2 (VD: FIFO Watermark)
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   callback Hàm callback, được gọi từ Task context
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_RegisterINT2Callback(ICM42605_Handle_t *handle, ICM42605_IntCallback_t callback);

/**
 * @brief   Đọc dữ liệu từ FIFO bằng DMA
 * @details Hiệu quả ưu việt cho bulk read (> 100 bytes).
 *          Chân CS được giữ ổn định trong suốt quá trình DMA.
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   buffer Output buffer
 * @param   len Số bytes cần đọc
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_ReadFifoDMA(ICM42605_Handle_t *handle, uint8_t *buffer, uint16_t len);

/**
 * @brief   Đọc thanh ghi INT_STATUS (0x2D) - tự động clear latched interrupts
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   status Output: giá trị thanh ghi
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_ReadIntStatus(ICM42605_Handle_t *handle, uint8_t *status);

/**
 * @brief   Đọc thanh ghi INT_STATUS2 (0x37) - WOM/SMD status
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   status Output: giá trị thanh ghi
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_ReadIntStatus2(ICM42605_Handle_t *handle, uint8_t *status);

/**
 * @brief   Đọc thanh ghi INT_STATUS3 (0x38) - APEX (Tap/Tilt/Step) status
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   status Output: giá trị thanh ghi
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_ReadIntStatus3(ICM42605_Handle_t *handle, uint8_t *status);

/* ========================================================================================
 * SECTION: Public API - Wake-on-Motion (WOM)
 * ======================================================================================== */

/**
 * @brief   Cấu hình và bật Wake-on-Motion
 * @details Cấu hình ngưỡng WOM cho cả 3 trục, SMD mode, và WOM compare mode.
 *          Yêu cầu Accel đang ở LN mode, ODR phải ≥ 200Hz.
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   config Cấu hình WOM (ngưỡng + mode)
 * @param   smd_mode Chế độ Significant Motion Detection
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_ConfigWom(ICM42605_Handle_t *handle,
                                      const ICM42605_WomConfig_t *config,
                                      ICM42605_SmdMode_t smd_mode);

/* ========================================================================================
 * SECTION: Public API - FIFO
 * ======================================================================================== */

/**
 * @brief   Cấu hình FIFO mode
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   mode Stream, Stop-on-Full, hoặc Bypass
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_ConfigFifo(ICM42605_Handle_t *handle, ICM42605_FifoMode_t mode);

/**
 * @brief   Cấu hình FIFO watermark level
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   watermark Số records (0-2048)
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_SetFifoWatermark(ICM42605_Handle_t *handle, uint16_t watermark);

/**
 * @brief   Đọc số lượng records hiện có trong FIFO
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   count Output: FIFO count
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_ReadFifoCount(ICM42605_Handle_t *handle, uint16_t *count);

/**
 * @brief   Đọc dữ liệu từ FIFO
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   buffer Output buffer
 * @param   len Số bytes cần đọc
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_ReadFifoData(ICM42605_Handle_t *handle, uint8_t *buffer, uint16_t len);

/**
 * @brief   Flush (xoá) toàn bộ FIFO
 * @param   handle Pointer tới ICM42605_Handle_t
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_FlushFifo(ICM42605_Handle_t *handle);

/* ========================================================================================
 * SECTION: Public API - Self-Test
 * ======================================================================================== */

/**
 * @brief   Chạy self-test cho Accelerometer và Gyroscope
 * @details So sánh output trước và sau khi bật self-test.
 *          Kết quả PASS nếu delta nằm trong ngưỡng factory.
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   accel_pass Output: true nếu accel pass
 * @param   gyro_pass Output: true nếu gyro pass
 * @return  ICM42605_OK nếu procedure thành công (kết quả test qua output params)
 */
ICM42605_Status_t ICM42605_SelfTest(ICM42605_Handle_t *handle,
                                     bool *accel_pass,
                                     bool *gyro_pass);

/* ========================================================================================
 * SECTION: Public API - Low-Level Register Access
 * ======================================================================================== */

/**
 * @brief   Đọc 1 register (Bank 0)
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   reg Địa chỉ register
 * @param   value Output: giá trị đọc được
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_ReadReg(ICM42605_Handle_t *handle, uint8_t reg, uint8_t *value);

/**
 * @brief   Ghi 1 register (Bank 0)
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   reg Địa chỉ register
 * @param   value Giá trị cần ghi
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_WriteReg(ICM42605_Handle_t *handle, uint8_t reg, uint8_t value);

/**
 * @brief   Đọc nhiều registers liên tiếp
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   reg Địa chỉ register bắt đầu
 * @param   buffer Output buffer
 * @param   len Số bytes cần đọc
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_ReadRegs(ICM42605_Handle_t *handle, uint8_t reg, uint8_t *buffer, uint16_t len);

/**
 * @brief   Chuyển bank register
 * @param   handle Pointer tới ICM42605_Handle_t
 * @param   bank Bank cần chuyển (0-4)
 * @return  ICM42605_OK nếu thành công
 */
ICM42605_Status_t ICM42605_SelectBank(ICM42605_Handle_t *handle, ICM42605_Bank_t bank);

#endif /* __ICM42605_H__ */
