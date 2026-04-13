#include "system_manager_task.h"
#include "system_service.h"
#include "mqtt_service.h"
#include "imu_service.h"
#include "w25q32_task.h"
#include "log.h"
#include "cmsis_os.h"
#include <stdio.h>

/* ========================================================================================
 * SECTION: Private Variables
 * ======================================================================================== */

#define STATIONARY_SLEEP_TIMEOUT_S  15  /**< Sau 15s đứng yên thì đi ngủ */

/* ========================================================================================
 * SECTION: Private Functions
 * ======================================================================================== */

static void System_Manager_Entry(void const * argument);
static void Handle_AppCommands(void);

/* ========================================================================================
 * SECTION: Public API
 * ======================================================================================== */

void System_Manager_Task_Init(void) {
    osThreadDef(SysManager, System_Manager_Entry, osPriorityAboveNormal, 0, 1024);
    osThreadCreate(osThread(SysManager), NULL);
}

/* ========================================================================================
 * SECTION: Task Body
 * ======================================================================================== */

static void System_Manager_Entry(void const * argument) {
    LOG_INFO("[SYS_MGR] Task Started");
    
    uint32_t last_report_tick = 0; 
    bool first_report_done = false;
    uint32_t stationary_seconds = 0;
    SystemConfig_t config;
    SystemData_t data;
    SystemMode_t last_mode = SYS_MODE_INIT;

    while (1) {
        /* 1. Cập nhật trạng thái hệ thống (ACTIVE/STATIONARY) */
        System_Service_UpdateMotion(IMU_Service_IsMoving());
        System_Service_UpdateState();
        
        /* 2. Lấy snapshot dữ liệu và cấu hình */
        System_Service_GetConfig(&config);
        System_Service_GetSnapshot(&data);

        /* 2a. Đồng bộ chế độ IMU nếu Mode hệ thống thay đổi */
        if (data.mode != last_mode) {
            if (data.mode == SYS_MODE_ACTIVE) {
                IMU_Service_SetMode(IMU_MODE_DRIVING);
                stationary_seconds = 0;
            } else {
                IMU_Service_SetMode(IMU_MODE_PARKED);
                stationary_seconds = 0;
            }
            last_mode = data.mode;
        }

        /* 2b. Quản lý bộ đếm thời gian đứng yên để đi ngủ */
        if (data.mode == SYS_MODE_STATIONARY) {
            stationary_seconds++;
            if (stationary_seconds >= STATIONARY_SLEEP_TIMEOUT_S) {
                /* System no longer enters sleep mode. Just reset the counter or do nothing. */
                stationary_seconds = 0; 
                LOG_INFO("[SYS_MGR] System remains active (Sleep Disabled)");
            }
        } else {
            stationary_seconds = 0;
        }

        /* 3. Logic gửi dữ liệu định kỳ */
        uint32_t current_tick = osKernelSysTick();
        uint32_t interval_ms = (data.mode == SYS_MODE_ACTIVE) ? 
                               (config.active_interval_s > 0 ? config.active_interval_s * 1000 : 30000) : 
                               (config.stationary_interval_s > 0 ? config.stationary_interval_s * 1000 : 300000);

        if (interval_ms > 3600000) interval_ms = 30000;

        bool trigger = false;
        if (!first_report_done) {
            if (current_tick > 15000) { 
                trigger = true;
                first_report_done = true;
            }
        } else {
            if ((current_tick - last_report_tick) >= interval_ms) {
                trigger = true;
            }
        }

        if (System_Service_CheckForceReport()) {
            trigger = true;
            LOG_INFO("[SYS_MGR] Force report triggered");
        }

        if (trigger) {
            static char json_buf[512];
            System_Service_ToJSON(json_buf, sizeof(json_buf));
            MQTT_Service_QueuePublish("data", json_buf);
            
            last_report_tick = current_tick;
            LOG_INFO("[SYS_MGR] Data report queued (Interval: %ds)", (int)(interval_ms / 1000));
        }

        /* 4. Xử lý cảnh báo tức thời */
        if (data.sensor.alert_type != ALERT_NONE) {
            if ((current_tick - data.sensor.alert_tick) < 30000) {
                const char* alert_str[] = {"NONE", "THEFT", "CRASH", "LOW_BAT"};
                const char* severity_str[] = {"NONE", "LIGHT", "MEDIUM", "SEVERE"};
                
                char alert_buf[128];
                snprintf(alert_buf, sizeof(alert_buf), "{\"alert\":\"%s\",\"severity\":\"%s\"}", 
                         alert_str[data.sensor.alert_type > 3 ? 0 : data.sensor.alert_type], 
                         severity_str[data.sensor.alert_remain > 3 ? 0 : data.sensor.alert_remain]);
                         
                MQTT_Service_QueuePublish("alarm", alert_buf);
                LOG_INFO("[SYS_MGR] ALARM report queued: %s", alert_buf);
                
                /* Quan trọng: Xóa Alert sau khi đã gửi để tránh gửi lặp lại */
                System_Service_ClearAlert();
            }
        }

        /* 5. Xử lý lệnh từ App (Stub) */
        Handle_AppCommands();
        osDelay(1000);
    }
}

static void Handle_AppCommands(void) {
    /* Handle CLI/APP commands if any */
}
