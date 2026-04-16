#include "system_service.h"
#include "log.h"
#include <string.h>
#include <time.h>

/* ========================================================================================
 * SECTION: Private Variables
 * ======================================================================================== */

/* Cấu hình mặc định */
static SystemData_t g_sys_data;
static SystemConfig_t g_sys_config = {
    .active_interval_s = DEFAULT_ACTIVE_INTERVAL_S,
    .stationary_interval_s = DEFAULT_STATIONARY_INTERVAL_S,
    .is_armed = true,
    .gps_enable = true,
    .alert_enable = true
};

/* Ngưỡng vận tốc để coi là đang di chuyển (km/h) */
#define MOVING_SPEED_THRESHOLD      2.0f
/* Thời gian đứng yên để chuyển sang mode STATIONARY (giây) */
#define STATIONARY_TIMEOUT_SEC      30

/* ========================================================================================
 * SECTION: Private Functions
 * ======================================================================================== */

static uint32_t prv_ConvertToEpoch(uint8_t h, uint8_t m, uint8_t s, uint8_t day, uint8_t mon, uint8_t yr) {
    struct tm t;
    t.tm_hour = h;
    t.tm_min = m;
    t.tm_sec = s;
    t.tm_mday = day;
    t.tm_mon = mon - 1;     // tm_mon is 0-11
    t.tm_year = 2000 + yr - 1900; // yr is years since 2000
    t.tm_isdst = -1;
    
    return (uint32_t)mktime(&t);
}

/* ========================================================================================
 * SECTION: Public Functions - Lifecycle
 * ======================================================================================== */

void System_Service_Init(void) {
    /* 1. Xóa sạch dữ liệu cũ */
    memset(&g_sys_data, 0, sizeof(SystemData_t));
    
    /* 2. Ép gán cấu hình mặc định tường minh để tránh rác bộ nhớ */
    g_sys_config.active_interval_s = DEFAULT_ACTIVE_INTERVAL_S;
    g_sys_config.stationary_interval_s = DEFAULT_STATIONARY_INTERVAL_S;
    g_sys_config.is_armed = true;
    g_sys_config.gps_enable = true;
    g_sys_config.alert_enable = true;

    /* 3. Tạo Mutex */
    osMutexDef(sysMutex);
    g_sys_data.mutex = osMutexCreate(osMutex(sysMutex));
    
    g_sys_data.mode = SYS_MODE_INIT;
    g_sys_data.gps.source = POS_SOURCE_NO_FIX;
    g_sys_data.force_report = false;
    g_sys_data.sensor.imu_update_tick = osKernelSysTick(); // Khởi đầu mốc thời gian im lặng
    strncpy(g_sys_data.imei, "UNKNOWN", sizeof(g_sys_data.imei) - 1);
    
    LOG_INFO("[SYS_SVC] Initialized and Configured (Safe Mode)");
}

void System_Service_SetIMEI(const char *imei) {
    if (imei == NULL || g_sys_data.mutex == NULL) return;
    osMutexWait(g_sys_data.mutex, osWaitForever);
    strncpy(g_sys_data.imei, imei, sizeof(g_sys_data.imei) - 1);
    osMutexRelease(g_sys_data.mutex);
}

void System_Service_GetSnapshot(SystemData_t *out) {
    if (out == NULL || g_sys_data.mutex == NULL) return;
    osMutexWait(g_sys_data.mutex, osWaitForever);
    memcpy(out, &g_sys_data, sizeof(SystemData_t));
    osMutexRelease(g_sys_data.mutex);
}

/* ========================================================================================
 * SECTION: Public Functions - Update Logic (GPS + IMU)
 * ======================================================================================== */

void System_Service_UpdateGPS(float lat, float lon, float spd, uint8_t fix, uint8_t sats,
                               uint8_t h, uint8_t m, uint8_t s, uint8_t day, uint8_t mon, uint8_t yr,
                               PositionSource_t source) {
    if (g_sys_data.mutex == NULL) return;
    osMutexWait(g_sys_data.mutex, 100);
    
    g_sys_data.gps.lat = lat;
    g_sys_data.gps.lon = lon;
    g_sys_data.gps.speed = spd;
    g_sys_data.gps.fix_quality = fix;
    g_sys_data.gps.satellites = sats;
    
    /* Cập nhật thời gian thực */
    g_sys_data.gps.hour = h;
    g_sys_data.gps.min = m;
    g_sys_data.gps.sec = s;
    g_sys_data.gps.day = day;
    g_sys_data.gps.month = mon;
    g_sys_data.gps.year = yr;
    g_sys_data.gps.utc_epoch = prv_ConvertToEpoch(h, m, s, day, mon, yr);
    
    g_sys_data.gps.last_update_tick = osKernelSysTick();
    g_sys_data.gps.source = source;

    /* Logic: Tốc độ cao + Có Fix -> Luôn coi là ACTIVE */
    if (spd > MOVING_SPEED_THRESHOLD && fix > 0) {
        g_sys_data.mode = SYS_MODE_ACTIVE;
        g_sys_data.sensor.imu_update_tick = osKernelSysTick();
    }
    
    osMutexRelease(g_sys_data.mutex);
}

void System_Service_UpdateTime(uint8_t h, uint8_t m, uint8_t s, uint8_t day, uint8_t mon, uint8_t yr) {
    if (g_sys_data.mutex == NULL) return;
    osMutexWait(g_sys_data.mutex, 100);
    
    g_sys_data.gps.hour = h;
    g_sys_data.gps.min = m;
    g_sys_data.gps.sec = s;
    g_sys_data.gps.day = day;
    g_sys_data.gps.month = mon;
    g_sys_data.gps.year = yr;
    g_sys_data.gps.utc_epoch = prv_ConvertToEpoch(h, m, s, day, mon, yr);
    
    osMutexRelease(g_sys_data.mutex);
}

void System_Service_UpdateSource(PositionSource_t source) {
    if (g_sys_data.mutex == NULL) return;
    osMutexWait(g_sys_data.mutex, 100);
    g_sys_data.gps.source = source;
    osMutexRelease(g_sys_data.mutex);
}

void System_Service_UpdateBattery(uint8_t pct, uint16_t mv) {
    if (g_sys_data.mutex == NULL) return;
    osMutexWait(g_sys_data.mutex, 100);
    g_sys_data.sensor.battery_pct = pct;
    g_sys_data.sensor.battery_mv = mv;
    g_sys_data.sensor.bat_update_tick = osKernelSysTick();
    osMutexRelease(g_sys_data.mutex);
}

void System_Service_UpdateMotion(bool moving) {
    if (g_sys_data.mutex == NULL) return;
    osMutexWait(g_sys_data.mutex, 100);
    g_sys_data.sensor.is_moving = moving;
    if (moving) {
        g_sys_data.sensor.imu_update_tick = osKernelSysTick();
        
        /* Chỉ chuyển sang ACTIVE nếu không có cảnh báo TRỘM nào đang chờ xử lý 
           Điều này giúp System Manager kịp gửi tin nhắn "Trộm" trước khi mode đổi thành "Đang chạy" */
        if (g_sys_data.mode == SYS_MODE_STATIONARY && g_sys_data.sensor.alert_type != ALERT_THEFT) {
            g_sys_data.mode = SYS_MODE_ACTIVE;
            g_sys_data.force_report = true; // Ép gửi MQTT ngay khi có chuyển động thực sự
            LOG_INFO("[SYS_SVC] Motion detected! Switched to ACTIVE mode");
        }
    }
    osMutexRelease(g_sys_data.mutex);
}

void System_Service_UpdateState(void) {
    if (g_sys_data.mutex == NULL) return;
    osMutexWait(g_sys_data.mutex, 100);
    
    uint32_t now = osKernelSysTick();
    
    /* Logic tổ hợp thông minh:
     * 1. Nếu GPS speed > Threshold -> Luôn ACTIVE
     * 2. Nếu GPS speed thấp:
     *    - Nếu IMU báo rung -> Luôn ACTIVE
     *    - Nếu cả hai im lặng -> Đếm ngược chuyển STATIONARY
     */
    bool currently_moving = (g_sys_data.gps.speed > MOVING_SPEED_THRESHOLD && g_sys_data.gps.fix_quality > 0) 
                         || (g_sys_data.sensor.is_moving);

    if (currently_moving) {
        /* Reset bộ đếm thời gian im lặng */
        g_sys_data.sensor.imu_update_tick = now;
        
        if (g_sys_data.mode != SYS_MODE_ACTIVE) {
            g_sys_data.mode = SYS_MODE_ACTIVE;
            g_sys_data.force_report = true; // Ép gửi MQTT ngay khi có chuyển động
            LOG_INFO("[SYS_SVC] Motion detected! Switched to ACTIVE mode");
        }
    } else {
        /* Nếu đang INIT hoặc ACTIVE nhưng im lặng quá lâu -> Chuyển STATIONARY */
        if (g_sys_data.mode == SYS_MODE_ACTIVE || g_sys_data.mode == SYS_MODE_INIT) {
            if ((now - g_sys_data.sensor.imu_update_tick) > (STATIONARY_TIMEOUT_SEC * 1000)) {
                g_sys_data.mode = SYS_MODE_STATIONARY;
                g_sys_data.force_report = true; // Ép gửi MQTT ngay để báo trạng thái đứng yên
                LOG_INFO("[SYS_SVC] Stationary for %ds. Switched to STATIONARY mode", STATIONARY_TIMEOUT_SEC);
            }
        }
    }
    
    osMutexRelease(g_sys_data.mutex);
}

void System_Service_SetAlert(AlertType_t type, Severity_t severity) {
    if (g_sys_data.mutex == NULL) return;
    osMutexWait(g_sys_data.mutex, 100);
    
    /* LOGIC ƯU TIÊN: 
       - Nếu đang có ALERT_THEFT chưa được Clear, không cho phép ALERT_CRASH ghi đè 
         (vì lắc máy mạnh lúc đỗ xe có thể làm Crash detector nhảy nhầm).
    */
    if (g_sys_data.sensor.alert_type == ALERT_THEFT && type == ALERT_CRASH) {
        /* Bỏ qua Va chạm nếu đang báo Trộm */
    } else {
        g_sys_data.sensor.alert_type = type;
        g_sys_data.sensor.alert_remain = severity;
        g_sys_data.sensor.alert_tick = osKernelSysTick();
    }
    osMutexRelease(g_sys_data.mutex);
}

void System_Service_ClearAlert(void) {
    if (g_sys_data.mutex == NULL) return;
    osMutexWait(g_sys_data.mutex, 100);
    g_sys_data.sensor.alert_type = ALERT_NONE;
    osMutexRelease(g_sys_data.mutex);
}

int System_Service_ToJSON(char *buf, uint16_t len) {
    if (buf == NULL || g_sys_data.mutex == NULL) return 0;
    
    int written = 0;
    osMutexWait(g_sys_data.mutex, osWaitForever);
    
    /* Đảm bảo timestamp luôn là một ngày hợp lệ (tránh 2000-00-00 làm crash server/DB) */
    uint8_t y = g_sys_data.gps.year;
    uint8_t m = g_sys_data.gps.month;
    uint8_t d = g_sys_data.gps.day;
    if (y < 24 || m == 0 || d == 0) {
        y = 24; m = 1; d = 1;
    }
    
    /* Format JSON trực tiếp từ biến toàn cục */
    written = snprintf(buf, len, 
        "{\"id\":\"%s\",\"lat\":%.6f,\"lon\":%.6f,\"spd\":%.1f,\"bat\":%d,\"st\":%d,\"src\":\"%s\",\"ts\":\"20%02d-%02d-%02d %02d:%02d:%02d\"}",
        g_sys_data.imei, g_sys_data.gps.lat, g_sys_data.gps.lon, g_sys_data.gps.speed, 
        g_sys_data.sensor.battery_pct, (int)g_sys_data.mode,
        g_sys_data.gps.source == POS_SOURCE_LBS ? "LBS" : (g_sys_data.gps.source == POS_SOURCE_NO_FIX ? "NO_FIX" : "GPS"),
        y, m, d,
        g_sys_data.gps.hour, g_sys_data.gps.min, g_sys_data.gps.sec);
    
    osMutexRelease(g_sys_data.mutex);
    return written;
}

bool System_Service_CheckForceReport(void) {
    if (g_sys_data.mutex == NULL) return false;
    osMutexWait(g_sys_data.mutex, 100);
    bool ret = g_sys_data.force_report;
    g_sys_data.force_report = false; // Xóa cờ sau khi check
    osMutexRelease(g_sys_data.mutex);
    return ret;
}

void System_Service_SetForceReport(bool force) {
    if (g_sys_data.mutex == NULL) return;
    osMutexWait(g_sys_data.mutex, 100);
    g_sys_data.force_report = force;
    osMutexRelease(g_sys_data.mutex);
}

void System_Service_GetConfig(SystemConfig_t *out) {
    if (out == NULL || g_sys_data.mutex == NULL) return;
    osMutexWait(g_sys_data.mutex, osWaitForever);
    memcpy(out, &g_sys_config, sizeof(SystemConfig_t));
    osMutexRelease(g_sys_data.mutex);
}

void System_Service_UpdateConfig(SystemConfig_t *new_cfg) {
    if (new_cfg == NULL || g_sys_data.mutex == NULL) return;
    osMutexWait(g_sys_data.mutex, osWaitForever);
    memcpy(&g_sys_config, new_cfg, sizeof(SystemConfig_t));
    osMutexRelease(g_sys_data.mutex);
}

void System_Service_VisualNotify(uint8_t count) {
    LOG_INFO("[SYS_SVC] Visual notification: blinking PC13 x%d", count);
    for (uint8_t i = 0; i < count; i++) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET); // Led ON (Active Low)
        osDelay(150);
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);   // Led OFF
        osDelay(150);
    }
}
