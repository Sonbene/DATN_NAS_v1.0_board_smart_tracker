/**
 * @file    imu_service.c
 * @brief   IMU Service Implementation — State Machine + Crash Detection
 * @details Thuật toán phát hiện tai nạn:
 *          1. Moving Average filter (N=4) để giảm nhiễu rung xe
 *          2. Accel trigger (>5g) mở cửa sổ xác nhận 50ms
 *          3. Trong cửa sổ: kiểm tra gyro (>400dps) VÀ accel vẫn cao
 *          4. Loại nhiễu: ổ gà (accel cao, gyro thấp), cua gấp (gyro cao, accel thấp)
 *          5. Phân loại 3 mức: LIGHT / MEDIUM / SEVERE
 *          6. Debounce 3 giây
 *
 * @author  DATN_NAS
 * @version 1.0
 * @date    2026-04-09
 */

#include "imu_service.h"
#include "log.h"
#include "cmsis_os.h"
#include <string.h>
#include <math.h>

/* ========================================================================================
 * SECTION: Private Types & Data
 * ======================================================================================== */

/**
 * @brief Context bộ lọc Moving Average
 */
typedef struct {
    float accel_buf[IMU_FILTER_SIZE];   /**< Circular buffer cho tổng accel */
    float gyro_buf[IMU_FILTER_SIZE];    /**< Circular buffer cho tổng gyro */
    uint8_t idx;                        /**< Index hiện tại */
    bool filled;                        /**< Buffer đã đầy lần đầu chưa */
} FilterCtx_t;

/**
 * @brief Context thuật toán crash detection
 */
typedef struct {
    FilterCtx_t filter;                 /**< Bộ lọc Moving Average */

    bool        window_active;          /**< Đang trong cửa sổ xác nhận? */
    uint8_t     window_count;           /**< Số samples đã check trong cửa sổ */
    float       peak_accel;             /**< Gia tốc đỉnh trong cửa sổ (g) */
    float       peak_gyro;              /**< Gyro đỉnh trong cửa sổ (dps) */

    uint32_t    last_crash_tick;        /**< Tick cuối trigger crash (debounce) */
} CrashCtx_t;

/**
 * @brief Service state (singleton)
 */
static struct {
    ICM42605_Handle_t   *imu;           /**< Pointer tới driver handle */
    IMU_EventCallback_t callback;       /**< Event callback cho App */
    void                *user_data;     /**< User data cho callback */
    IMU_Mode_t          mode;           /**< Chế độ hiện tại */
    CrashCtx_t          crash;          /**< Crash detection context */
    uint8_t             fifo_buf[IMU_FIFO_BUFFER_SIZE + 16]; /**< FIFO DMA buffer (+ margin) */
} svc;

/* ========================================================================================
 * SECTION: Private Functions — Moving Average Filter
 * ======================================================================================== */

/**
 * @brief Reset bộ lọc về trạng thái ban đầu
 */
static void prv_FilterReset(FilterCtx_t *f)
{
    memset(f, 0, sizeof(FilterCtx_t));
}

/**
 * @brief Thêm 1 sample vào bộ lọc và trả về giá trị đã lọc
 * @param f Pointer bộ lọc
 * @param accel_mag Tổng gia tốc magnitude (g)
 * @param gyro_mag Tổng gyro magnitude (dps)
 * @param out_accel Output: accel đã lọc
 * @param out_gyro Output: gyro đã lọc
 */
static void prv_FilterUpdate(FilterCtx_t *f,
                              float accel_mag,
                              float gyro_mag,
                              float *out_accel,
                              float *out_gyro)
{
    f->accel_buf[f->idx] = accel_mag;
    f->gyro_buf[f->idx] = gyro_mag;
    f->idx = (f->idx + 1) % IMU_FILTER_SIZE;
    if (f->idx == 0) f->filled = true;

    /* Tính trung bình */
    uint8_t count = f->filled ? IMU_FILTER_SIZE : f->idx;
    float sum_a = 0, sum_g = 0;
    for (uint8_t i = 0; i < count; i++) {
        sum_a += f->accel_buf[i];
        sum_g += f->gyro_buf[i];
    }

    *out_accel = sum_a / (float)count;
    *out_gyro = sum_g / (float)count;
}

/* ========================================================================================
 * SECTION: Private Functions — Crash Detection Algorithm
 * ======================================================================================== */

/**
 * @brief Reset crash detection context
 */
static void prv_CrashReset(CrashCtx_t *ctx)
{
    prv_FilterReset(&ctx->filter);
    ctx->window_active = false;
    ctx->window_count = 0;
    ctx->peak_accel = 0;
    ctx->peak_gyro = 0;
    /* Không reset last_crash_tick để giữ debounce */
}

/**
 * @brief Phân loại mức độ nghiêm trọng crash
 */
static CrashSeverity_t prv_ClassifySeverity(float peak_accel, float peak_gyro)
{
    /*
     * SEVERE:  a > 12g HOẶC gyro > 800dps
     * MEDIUM:  8g < a < 12g HOẶC gyro 600-800dps
     * LIGHT:   5g < a < 8g VÀ gyro 400-600dps
     */
    if (peak_accel > IMU_CRASH_ACCEL_MAX_G || peak_gyro > IMU_CRASH_GYRO_SEVERE_DPS) {
        return CRASH_SEVERITY_SEVERE;
    }
    if (peak_accel > IMU_CRASH_ACCEL_SEVERE_G || peak_gyro > IMU_CRASH_GYRO_MEDIUM_DPS) {
        return CRASH_SEVERITY_MEDIUM;
    }
    return CRASH_SEVERITY_LIGHT;
}

/**
 * @brief Xử lý 1 sample qua thuật toán crash detection
 * @param accel_g Tổng gia tốc (g), đã qua filter
 * @param gyro_dps Tổng gyro (dps), đã qua filter
 */
static void prv_CrashProcessSample(float accel_g, float gyro_dps)
{
    CrashCtx_t *ctx = &svc.crash;

    /* === Debounce check === */
    if (ctx->last_crash_tick != 0) {
        uint32_t elapsed = osKernelSysTick() - ctx->last_crash_tick;
        if (elapsed < pdMS_TO_TICKS(IMU_CRASH_DEBOUNCE_MS)) {
            return; /* Đang trong debounce period → bỏ qua */
        }
    }

    /* === Trường hợp đặc biệt: Accel cực cao (>8g) → crash severe ngay === */
    if (!ctx->window_active && accel_g > IMU_CRASH_ACCEL_SEVERE_G) {
        LOG_WARN("[IMU_SVC] SEVERE IMPACT! Accel=%.1fg (>8g threshold)", accel_g);

        IMU_EventData_t event = {
            .event = IMU_EVENT_CRASH_DETECTED,
            .severity = prv_ClassifySeverity(accel_g, gyro_dps),
            .peak_accel_g = accel_g,
            .peak_gyro_dps = gyro_dps
        };

        ctx->last_crash_tick = osKernelSysTick();

        if (svc.callback) {
            svc.callback(&event, svc.user_data);
        }
        return;
    }

    /* === Bước 1: Kiểm tra accel trigger (>5g) → mở cửa sổ === */
    if (!ctx->window_active) {
        if (accel_g > IMU_CRASH_ACCEL_TRIGGER_G) {
            ctx->window_active = true;
            ctx->window_count = 0;
            ctx->peak_accel = accel_g;
            ctx->peak_gyro = gyro_dps;
            LOG_INFO("[IMU_SVC] Accel trigger %.1fg — opening confirm window", accel_g);
        }
        return; /* Chưa đủ điều kiện, chờ tiếp */
    }

    /* === Bước 2: Đang trong cửa sổ xác nhận === */
    ctx->window_count++;

    /* Cập nhật peak values */
    if (accel_g > ctx->peak_accel) ctx->peak_accel = accel_g;
    if (gyro_dps > ctx->peak_gyro) ctx->peak_gyro = gyro_dps;

    /* Kiểm tra xác nhận crash */
    bool gyro_confirmed = (ctx->peak_gyro > IMU_CRASH_GYRO_CONFIRM_DPS);
    bool accel_confirmed = (ctx->peak_accel > IMU_CRASH_ACCEL_TRIGGER_G);

    if (gyro_confirmed && accel_confirmed) {
        /* ✅ CRASH CONFIRMED: Cả accel VÀ gyro đều vượt ngưỡng */
        CrashSeverity_t severity = prv_ClassifySeverity(ctx->peak_accel, ctx->peak_gyro);

        LOG_ERROR("[IMU_SVC] *** CRASH DETECTED! Severity=%d, Accel=%.1fg, Gyro=%.0fdps ***",
                  severity, ctx->peak_accel, ctx->peak_gyro);

        IMU_EventData_t event = {
            .event = IMU_EVENT_CRASH_DETECTED,
            .severity = severity,
            .peak_accel_g = ctx->peak_accel,
            .peak_gyro_dps = ctx->peak_gyro
        };

        ctx->last_crash_tick = osKernelSysTick();
        ctx->window_active = false;

        if (svc.callback) {
            svc.callback(&event, svc.user_data);
        }
        return;
    }

    /* Hết cửa sổ → phân tích lý do không confirm */
    if (ctx->window_count >= IMU_CRASH_WINDOW_SAMPLES) {
        if (ctx->peak_accel > IMU_CRASH_ACCEL_TRIGGER_G && ctx->peak_gyro < IMU_CRASH_GYRO_CONFIRM_DPS) {
            LOG_INFO("[IMU_SVC] Noise rejected: Accel=%.1fg but Gyro=%.0fdps (o ga / bump)",
                     ctx->peak_accel, ctx->peak_gyro);
        } else if (ctx->peak_gyro > IMU_CRASH_GYRO_CONFIRM_DPS && ctx->peak_accel < IMU_CRASH_ACCEL_TRIGGER_G) {
            LOG_INFO("[IMU_SVC] Noise rejected: Gyro=%.0fdps but Accel=%.1fg (cua gap)",
                     ctx->peak_gyro, ctx->peak_accel);
        }
        ctx->window_active = false;
    }
}

/**
 * @brief Parse 1 FIFO record (16 bytes) thành accel/gyro float values
 * @param record Pointer tới 16 bytes FIFO data
 * @param ax, ay, az, gx, gy, gz Output: giá trị thực (g, dps)
 */
static void prv_ParseFifoRecord(const uint8_t *record,
                                 float *ax, float *ay, float *az,
                                 float *gx, float *gy, float *gz)
{
    /*
     * FIFO Record layout (16 bytes):
     * [0]     = FIFO Header
     * [1..6]  = Accel X_H,X_L, Y_H,Y_L, Z_H,Z_L (Big-endian)
     * [7..12] = Gyro  X_H,X_L, Y_H,Y_L, Z_H,Z_L  (Big-endian)
     * [13]    = Temperature (8-bit)
     * [14..15] = Timestamp
     */
    int16_t raw_ax = (int16_t)((record[1] << 8) | record[2]);
    int16_t raw_ay = (int16_t)((record[3] << 8) | record[4]);
    int16_t raw_az = (int16_t)((record[5] << 8) | record[6]);
    int16_t raw_gx = (int16_t)((record[7] << 8) | record[8]);
    int16_t raw_gy = (int16_t)((record[9] << 8) | record[10]);
    int16_t raw_gz = (int16_t)((record[11] << 8) | record[12]);

    /* Sensitivity cho full-scale: ±16g → 2048 LSB/g, ±2000dps → 16.4 LSB/dps */
    *ax = (float)raw_ax / 2048.0f;
    *ay = (float)raw_ay / 2048.0f;
    *az = (float)raw_az / 2048.0f;
    *gx = (float)raw_gx / 16.4f;
    *gy = (float)raw_gy / 16.4f;
    *gz = (float)raw_gz / 16.4f;
}

/* ========================================================================================
 * SECTION: Public API Implementation
 * ======================================================================================== */

IMU_Status_t IMU_Service_Init(ICM42605_Handle_t *imu,
                               IMU_EventCallback_t callback,
                               void *user_data)
{
    if (imu == NULL) return IMU_SVC_ERROR;

    LOG_INFO("[IMU_SVC] Initializing service...");

    memset(&svc, 0, sizeof(svc));
    svc.imu = imu;
    svc.callback = callback;
    svc.user_data = user_data;
    svc.mode = IMU_MODE_PARKED; /* Mặc định PARKED (chưa apply, chờ SetMode) */

    /*
     * Không tự động gọi SetMode ở đây.
     * Driver Init đã cấu hình mặc định (Accel+Gyro LN mode).
     * Task khác sẽ gọi IMU_Service_SetMode() khi cần.
     */

    LOG_INFO("[IMU_SVC] Service initialized (mode not applied yet — waiting for SetMode)");
    return IMU_SVC_OK;
}

IMU_Status_t IMU_Service_SetMode(IMU_Mode_t mode)
{
    if (svc.imu == NULL) return IMU_SVC_ERROR;

    LOG_INFO("[IMU_SVC] Switching to mode: %s", mode == IMU_MODE_PARKED ? "PARKED" : "DRIVING");

    if (mode == IMU_MODE_PARKED) {
        /* ============================
         * MODE: PARKED (Chống trộm)
         * ============================ */

        /* 1. Tắt Gyro để tiết kiệm điện */
        ICM42605_SetGyroMode(svc.imu, ICM42605_GYRO_MODE_OFF);
        LOG_INFO("[IMU_SVC]   Gyro: OFF");

        /* 2. Accel → Low-Power mode, 25Hz, ±4g */
        ICM42605_ConfigAccel(svc.imu, ICM42605_ACCEL_FS_4G, ICM42605_ODR_25HZ);
        ICM42605_SetAccelMode(svc.imu, ICM42605_ACCEL_MODE_LP);
        LOG_INFO("[IMU_SVC]   Accel: LP 25Hz ±4g");

        /* 3. Tắt FIFO, Flush dữ liệu cũ */
        ICM42605_ConfigFifo(svc.imu, ICM42605_FIFO_MODE_BYPASS);
        ICM42605_FlushFifo(svc.imu);
        ICM42605_EnableFifoThresholdInt(svc.imu, ICM42605_INT_PIN_2, false);
        LOG_INFO("[IMU_SVC]   FIFO: Disabled, Flushed");

        /* 4. Cấu hình WOM → INT1 */
        ICM42605_WomConfig_t wom = {
            .wom_mode = ICM42605_WOM_MODE_OR,
            .wom_ref  = ICM42605_WOM_REF_PREVIOUS,
            .threshold_x = IMU_WOM_THRESHOLD_LSB,
            .threshold_y = IMU_WOM_THRESHOLD_LSB,
            .threshold_z = IMU_WOM_THRESHOLD_LSB
        };
        ICM42605_ConfigWom(svc.imu, &wom, ICM42605_SMD_WOM_SHORT);
        ICM42605_EnableWomInt(svc.imu, ICM42605_INT_PIN_1, true);
        LOG_INFO("[IMU_SVC]   WOM: Enabled, Threshold=%d LSB (~%dmg) → INT1",
                 IMU_WOM_THRESHOLD_LSB, IMU_WOM_THRESHOLD_LSB * 4);

    } else {
        /* ============================
         * MODE: DRIVING (Crash Detection)
         * ============================ */

        /* 1. Tắt WOM */
        ICM42605_EnableWomInt(svc.imu, ICM42605_INT_PIN_1, false);
        LOG_INFO("[IMU_SVC]   WOM: Disabled");

        /* 2. Accel → Low-Noise, 200Hz, ±16g (full-scale) */
        ICM42605_ConfigAccel(svc.imu, ICM42605_ACCEL_FS_16G, ICM42605_ODR_200HZ);
        ICM42605_SetAccelMode(svc.imu, ICM42605_ACCEL_MODE_LN);
        LOG_INFO("[IMU_SVC]   Accel: LN 200Hz ±16g");

        /* 3. Gyro → Low-Noise, 200Hz, ±2000dps (full-scale) */
        ICM42605_ConfigGyro(svc.imu, ICM42605_GYRO_FS_2000DPS, ICM42605_ODR_200HZ);
        ICM42605_SetGyroMode(svc.imu, ICM42605_GYRO_MODE_LN);
        LOG_INFO("[IMU_SVC]   Gyro: LN 200Hz ±2000dps");
        osDelay(1); /* Chờ sensor ổn định */

        /* 4. FIFO → Stream mode, Watermark = 20 records */
        ICM42605_FlushFifo(svc.imu);
        ICM42605_ConfigFifo(svc.imu, ICM42605_FIFO_MODE_STREAM);
        ICM42605_SetFifoWatermark(svc.imu, IMU_FIFO_WATERMARK);
        ICM42605_EnableFifoThresholdInt(svc.imu, ICM42605_INT_PIN_2, true);
        LOG_INFO("[IMU_SVC]   FIFO: Stream, WM=%d records → INT2", IMU_FIFO_WATERMARK);

        /* 5. Reset crash detection context */
        prv_CrashReset(&svc.crash);
        LOG_INFO("[IMU_SVC]   Crash detector: Reset & Ready");
    }

    svc.mode = mode;
    LOG_INFO("[IMU_SVC] Mode switch complete: %s", mode == IMU_MODE_PARKED ? "PARKED" : "DRIVING");
    return IMU_SVC_OK;
}

IMU_Mode_t IMU_Service_GetMode(void)
{
    return svc.mode;
}

void IMU_Service_HandleINT1(void)
{
    /* INT1 = WOM (mode PARKED) */
    if (svc.imu == NULL) return;

    LOG_INFO("[IMU_SVC] INT1 triggered — reading WOM status...");

    /* Đọc INT_STATUS2 để xác nhận WOM */
    uint8_t status2 = 0;
    ICM42605_ReadIntStatus2(svc.imu, &status2);

    bool wom_x = (status2 & ICM42605_INT_STATUS2_WOM_X) != 0;
    bool wom_y = (status2 & ICM42605_INT_STATUS2_WOM_Y) != 0;
    bool wom_z = (status2 & ICM42605_INT_STATUS2_WOM_Z) != 0;

    if (wom_x || wom_y || wom_z) {
        LOG_WARN("[IMU_SVC] *** WOM DETECTED! X=%d Y=%d Z=%d *** (Anti-theft alert!)",
                 wom_x, wom_y, wom_z);

        if (svc.callback) {
            IMU_EventData_t event = {
                .event = IMU_EVENT_WOM_DETECTED,
                .severity = CRASH_SEVERITY_NONE,
                .peak_accel_g = 0,
                .peak_gyro_dps = 0
            };
            svc.callback(&event, svc.user_data);
        }
    } else {
        /* Đọc INT_STATUS cũng để clear các pending bit khác */
        uint8_t status0 = 0;
        ICM42605_ReadIntStatus(svc.imu, &status0);
        LOG_INFO("[IMU_SVC] INT1: No WOM — STATUS=0x%02X, STATUS2=0x%02X", status0, status2);
    }
}

void IMU_Service_HandleINT2(void)
{
    /* INT2 = FIFO Watermark (mode DRIVING) */
    if (svc.imu == NULL) return;

    /* Đọc INT_STATUS để clear interrupt flag */
    uint8_t status0 = 0;
    ICM42605_ReadIntStatus(svc.imu, &status0);

    /* Đọc FIFO count */
    uint16_t fifo_count = 0;
    ICM42605_ReadFifoCount(svc.imu, &fifo_count);

    if (fifo_count == 0) {
        LOG_INFO("[IMU_SVC] INT2: FIFO empty (spurious?)");
        return;
    }

    /* Giới hạn đọc theo buffer size */
    uint16_t records_to_read = fifo_count;
    if (records_to_read > IMU_FIFO_WATERMARK) {
        records_to_read = IMU_FIFO_WATERMARK;
    }
    uint16_t bytes_to_read = records_to_read * IMU_FIFO_RECORD_SIZE;

    LOG_INFO("[IMU_SVC] INT2: FIFO count=%d, reading %d records (%d bytes)",
             fifo_count, records_to_read, bytes_to_read);

    /* DMA đọc FIFO */
    ICM42605_Status_t ret = ICM42605_ReadFifoDMA(svc.imu, svc.fifo_buf, bytes_to_read);
    if (ret != ICM42605_OK) {
        LOG_ERROR("[IMU_SVC] FIFO DMA read failed! (err=%d)", ret);
        /* Fallback: polling read */
        ret = ICM42605_ReadFifoData(svc.imu, svc.fifo_buf, bytes_to_read);
        if (ret != ICM42605_OK) {
            LOG_ERROR("[IMU_SVC] FIFO polling read also failed!");
            return;
        }
        LOG_INFO("[IMU_SVC] FIFO read via polling (fallback OK)");
    }

    /* Parse từng record và chạy crash detection */
    for (uint16_t i = 0; i < records_to_read; i++) {
        const uint8_t *record = &svc.fifo_buf[i * IMU_FIFO_RECORD_SIZE];

        float ax, ay, az, gx, gy, gz;
        prv_ParseFifoRecord(record, &ax, &ay, &az, &gx, &gy, &gz);

        /* Tính magnitude */
        float accel_mag = sqrtf(ax * ax + ay * ay + az * az);
        float gyro_mag = sqrtf(gx * gx + gy * gy + gz * gz);

        /* Qua bộ lọc Moving Average */
        float filtered_accel, filtered_gyro;
        prv_FilterUpdate(&svc.crash.filter, accel_mag, gyro_mag,
                         &filtered_accel, &filtered_gyro);

        /* Chạy thuật toán crash detection */
        prv_CrashProcessSample(filtered_accel, filtered_gyro);
    }
}

IMU_Status_t IMU_Service_ReadAll(ICM42605_AllData_t *data)
{
    if (svc.imu == NULL || data == NULL) return IMU_SVC_ERROR;
    ICM42605_Status_t ret = ICM42605_ReadAllData(svc.imu, data);
    return (ret == ICM42605_OK) ? IMU_SVC_OK : IMU_SVC_ERROR;
}
