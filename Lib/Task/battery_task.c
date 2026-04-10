#include "battery_task.h"
#include "cmsis_os.h"
#include "bsp_adc.h"
#include "log.h"
#include "main.h"


/* Cấu hình pin 2S */
#define BAT_MAX_MV          8400    /* 8.4V - 100% */
#define BAT_MIN_MV          6400    /* 6.4V - 0% */
#define BAT_LOW_THRESHOLD   7400    /* 7.4V - ~30% Cảnh báo */


/* Biến lưu trữ trạng thái */
static uint32_t g_battery_mv = 0;
static uint8_t g_battery_pct = 0;
static BSP_ADC_Handle_t battery_adc;

static void Battery_Task_Entry(void const * argument);

void Battery_Task_Init(ADC_HandleTypeDef *hadc, uint32_t channel) {
    /* Khởi tạo BSP ADC ngay trong task layer */
    BSP_ADC_Init(&battery_adc, hadc, channel);
    LOG_INFO("[BAT] Battery ADC initialized (Channel: %lu)", (unsigned long)channel);

    osThreadDef(BatteryTask, Battery_Task_Entry, osPriorityBelowNormal, 0, 256);
    osThreadCreate(osThread(BatteryTask), NULL);
}


void Battery_Task_ADC_Callback(ADC_HandleTypeDef* hadc) {
    BSP_ADC_ConvCpltCallback(&battery_adc);
}

uint32_t Battery_GetVoltage(void) {
    return g_battery_mv;
}

uint8_t Battery_GetPercentage(void) {
    return g_battery_pct;
}

/**
 * @brief Tính toán % pin đơn giản từ điện áp
 */
static uint8_t Calculate_Percentage(uint32_t mv) {
    if (mv >= BAT_MAX_MV) return 100;
    if (mv <= BAT_MIN_MV) return 0;
    
    /* Tính toán tuyến tính sơ bộ (8.4V -> 6.4V) */
    return (uint8_t)((mv - BAT_MIN_MV) * 100 / (BAT_MAX_MV - BAT_MIN_MV));
}

static void Battery_Task_Entry(void const * argument) {
    LOG_INFO("[BAT] Battery Task Started (Mode: 2S Li-Po)");
    
    while (1) {
        /* 1. Kích hoạt chân đo Pin (PC14) */
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_SET);
        
        /* 2. Chờ một chút để tụ điện lọc ổn định áp */
        osDelay(20);
        
        /* 3. Thực hiện đo qua BSP (Sử dụng DMA + Oversampling đã viết) */
        float voltage_mv = BSP_ADC_GetBatteryVoltage(&battery_adc);
        
        /* 4. Tắt chân đo để tiết kiệm điện */
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, GPIO_PIN_RESET);
        
        /* 5. Cập nhật dữ liệu hệ thống */
        g_battery_mv = (uint32_t)voltage_mv;
        g_battery_pct = Calculate_Percentage(g_battery_mv);
        
        /* 6. Log kết quả và cảnh báo */
        if (g_battery_mv < BAT_LOW_THRESHOLD) {
            LOG_WARN("[BAT] LOW BATTERY! Level: %d%% (%d mV)", g_battery_pct, g_battery_mv);
        } else {
            LOG_INFO("[BAT] Battery Level: %d%% (%d mV)", g_battery_pct, g_battery_mv);
        }
        
        /* 7. Nghỉ 60 giây trước lần đo tiếp theo */
        osDelay(60000);
    }
}
