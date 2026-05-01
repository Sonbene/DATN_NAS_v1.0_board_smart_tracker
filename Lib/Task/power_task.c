#include "power_task.h"
#include "system_manager_task.h"
#include "system_service.h"
#include "log.h"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "atgm336h_task.h"
#include "sim_task.h"
#include "mqtt_service.h"
#include "imu_service.h"
#include "w25q32_task.h"

/* ========================================================================================
 * SECTION: Private Variables
 * ======================================================================================== */
static EventGroupHandle_t g_PowerEventGroup = NULL;

extern void SystemClock_Config(void);

extern UART_HandleTypeDef huart1; /* LOG */
extern UART_HandleTypeDef huart2; /* SIM */
extern UART_HandleTypeDef huart3; /* GPS */
extern ADC_HandleTypeDef hadc1;   /* BATTERY */
extern RTC_HandleTypeDef hrtc;    /* RTC for periodic wakeup */

/* ========================================================================================
 * SECTION: Private Functions
 * ======================================================================================== */
static void Power_Task_Entry(void const * argument);
static void Power_DisablePeripherals(void);
static void Power_EnablePeripherals(void);

/* ========================================================================================
 * SECTION: Public API
 * ======================================================================================== */

void Power_Task_Init(void) {
    g_PowerEventGroup = xEventGroupCreate();
    if (g_PowerEventGroup != NULL) {
        /* Mặc định tất cả các task đều đang bận (Clear bits) */
        xEventGroupClearBits(g_PowerEventGroup, POWER_BITS_ALL);
        
        osThreadDef(PowerTask, Power_Task_Entry, osPriorityLow, 0, 512);
        osThreadCreate(osThread(PowerTask), NULL);
        LOG_INFO("[POWER TASK] Initialized Event Group & Task.");
    }
}

void Power_Task_SetState(uint32_t task_bit, bool is_idle) {
    if (g_PowerEventGroup == NULL) return;
    
    if (is_idle) {
        xEventGroupSetBits(g_PowerEventGroup, task_bit);
    } else {
        xEventGroupClearBits(g_PowerEventGroup, task_bit);
    }
}

/* ========================================================================================
 * SECTION: Task Body
 * ======================================================================================== */

static void Power_Task_Entry(void const * argument) {
    uint32_t park_counter = 0;
    bool sleep_notify_triggered = false;
    
    while (1) {
        SystemData_t data;
        SystemConfig_t cfg;
        System_Service_GetSnapshot(&data);
        System_Service_GetConfig(&cfg);
        
        if (data.mode == SYS_MODE_STATIONARY) {
            park_counter++;
            
            /* Khi đạt đến sleep_delay, gửi thông điệp báo Sleep lên server (chỉ gửi 1 lần) */
            if (park_counter >= cfg.sleep_delay_s && !sleep_notify_triggered) {
                LOG_INFO("[POWER TASK] Sending sleep notification to server...");
                MQTT_Service_QueuePublish("status", "{\"status\":\"sleeping\"}");
                
                /* Báo bận SIMTask ngay lập tức để chặn PowerTask sleep luôn trong iteration này */
                Power_Task_SetState(POWER_BIT_SIM, false);
                sleep_notify_triggered = true;
            }
            
            /* SAU KHI ĐÃ ĐẾN GIÂY HẸN THÌ VÀO MODE WAIT TO SLEEP */
            if (park_counter >= cfg.sleep_delay_s) {
                
                /* KIỂM TRA ĐIỀU KIỆN: CÁC TASK ĐỀU RẢNH */
                EventBits_t uxBits = xEventGroupWaitBits(
                    g_PowerEventGroup, 
                    POWER_BITS_ALL, 
                    pdFALSE, /* Do not clear on exit */
                    pdTRUE,  /* Wait for all bits */
                    0        /* Return immediately */
                );
                
                if ((uxBits & POWER_BITS_ALL) == POWER_BITS_ALL) {
                    LOG_INFO("[POWER TASK] === SLEEP SEQUENCE START ===");
                    LOG_INFO("[POWER TASK] All tasks idle (0x%X). Preparing peripherals...", (unsigned int)uxBits);
                    
                    /* Chờ để Log kịp xả ra UART */
                    osDelay(200);
                    
                    /* KIỂM TRA LẠI LẦN NỮA (Phòng TOCTOU): 
                     * Đề phòng SysManager vừa đẩy Mail cho SIMTask trong lúc ta delay */
                    uxBits = xEventGroupGetBits(g_PowerEventGroup);
                    if ((uxBits & POWER_BITS_ALL) != POWER_BITS_ALL) {
                        LOG_WARN("[POWER TASK] Tasks became busy (%X) during prep. Aborting sleep!", (unsigned int)uxBits);
                        continue;
                    }
                    
                    /* ----- BƯỚC 1: ĐƯA MODULE NGOẠI VI VÀO CHẾ ĐỘ TIẾT KIỆM ----- */
                    ATGM336H_Task_Standby(true);
                    LOG_INFO("[POWER TASK] GPS -> Standby OK");
                    
                    SIM_Task_SetSleep(true);
                    LOG_INFO("[POWER TASK] SIM -> Power Off OK");
                    
                    /* Chờ module tắt nguồn hoàn toàn */
                    osDelay(1000);
                    
                    /* ----- BƯỚC 1: CẤU HÌNH RTC WAKEUP TIMER (NẾU CÓ) ----- */
                    if (cfg.stationary_interval_s > 0) {
                        /* Tắt timer cũ nếu đang chạy */
                        HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
                        
                        /* Xóa sạch các cờ ngắt RTC cũ */
                        __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&hrtc, RTC_FLAG_WUTF);
                        __HAL_RTC_WAKEUPTIMER_EXTI_CLEAR_FLAG();
                        
                        /* Thiết lập chu kỳ thức dậy (1Hz clock, counter = seconds - 1) 
                         * Sử dụng 16BITS để tránh bị cộng thêm 65536 giây (như bản 17BITS) */
                        if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, cfg.stationary_interval_s - 1, RTC_WAKEUPCLOCK_CK_SPRE_16BITS) != HAL_OK) {
                            LOG_ERROR("[POWER TASK] Failed to set RTC Wakeup Timer!");
                        } else {
                            /* Ép kích hoạt ngắt EXTI Line 20 (RTC Wakeup) để đảm bảo wakeup từ STOP2 */
                            __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_IT();
                            __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_RISING_EDGE();

                            LOG_INFO("[POWER TASK] RTC Wakeup set for %d seconds. (Mode: 16-bit)", cfg.stationary_interval_s);
                            
                            /* QUAN TRỌNG: Đợi đủ lâu để RTC kịp đồng bộ giá trị counter mới */
                            osDelay(50); 
                        }
                    }

                    LOG_INFO("[POWER TASK] Disabling MCU peripherals...");
                    osDelay(100); /* Cho Log cuối cùng kịp in */
                    
                    /* ----- BƯỚC 2: TẮT NGOẠI VI MCU ----- */
                    Power_DisablePeripherals();
                    
                    /* Dừng HAL Tick (TIM7) */
                    HAL_SuspendTick();
                    
                    /* *** QUAN TRỌNG: Tắt SysTick interrupt ***
                     * HAL_SuspendTick() chỉ tắt TIM7 (HAL timebase).
                     * FreeRTOS dùng SysTick làm scheduler tick → nếu không tắt,
                     * SysTick interrupt sẽ đánh thức CPU ngay lập tức! */
                    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
                    
                    /* Dọn sạch trạng thái cảm biến IMU (để INT pin về HIGH) */
                    IMU_Service_ClearStatus();
                    
                    /* Tắt tất cả interrupt để tránh race condition giữa việc
                     * clear pending bits và lệnh WFI. WFI vẫn wake-on-interrupt 
                     * dù PRIMASK = 1, nhưng handler sẽ không chạy cho tới __enable_irq(). */
                    __disable_irq();
                    
                    /* Clear NVIC pending bits của các ngoại vi đã tắt */
                    NVIC_ClearPendingIRQ(USART1_IRQn);
                    NVIC_ClearPendingIRQ(USART2_IRQn);
                    NVIC_ClearPendingIRQ(USART3_IRQn);
                    NVIC_ClearPendingIRQ(DMA1_Channel1_IRQn);  /* ADC DMA */
                    NVIC_ClearPendingIRQ(DMA1_Channel2_IRQn);  /* SPI1 TX */
                    NVIC_ClearPendingIRQ(DMA1_Channel3_IRQn);  /* SPI1 RX */
                    NVIC_ClearPendingIRQ(DMA1_Channel5_IRQn);  /* USART1 RX DMA */
                    NVIC_ClearPendingIRQ(DMA1_Channel6_IRQn);  /* USART2 RX DMA */
                    NVIC_ClearPendingIRQ(DMA1_Channel7_IRQn);  /* USART2 TX DMA */
                    NVIC_ClearPendingIRQ(DMA2_Channel3_IRQn);  /* USART3 RX DMA */
                    NVIC_ClearPendingIRQ(DMA2_Channel4_IRQn);  /* USART3 TX DMA */
                    NVIC_ClearPendingIRQ(ADC1_IRQn);
                    NVIC_ClearPendingIRQ(RTC_WKUP_IRQn);       /* RTC Wakeup */
                    NVIC_ClearPendingIRQ(SysTick_IRQn);        /* Đề phòng SysTick còn sót */
                    

                    /* Tắt tạm thời ngắt RI (PA5) để tránh ngắt rác khi SIM tắt nguồn hoàn toàn */
                    EXTI->IMR1 &= ~GPIO_PIN_5;

                    /* XÓA TẤT CẢ cờ ngắt EXTI đang tồn đọng (bao gồm cả Line 20 cho RTC) */
                    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);  /* IMU INT1 */
                    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5);  /* SIM RI   */
                    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_9);  /* IMU INT2 */
                    __HAL_RTC_WAKEUPTIMER_EXTI_CLEAR_FLAG();
                    __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&hrtc, RTC_FLAG_WUTF);

                    /* Đảm bảo các lệnh trước đó đã hoàn tất */
                    __DSB();
                    __ISB();

                    /* CPU dừng tại đây. Thức khi có ngắt EXTI: PA0 (IMU), PB9 (IMU), hoặc Line 20 (RTC) */
                    HAL_PWREx_EnterSTOP2Mode(PWR_STOPENTRY_WFI);
                    
                    /* === HỆ THỐNG THỨC DẬY TẠI ĐÂY === */
                    
                    /* Ghi lại nguồn đánh thức NGAY LẬP TỨC (TRƯỚC KHI BẬT LẠI INTERRUPT) 
                     * Để tránh việc HAL ISR tự động clear các cờ này khi interrupts enabled. */
                    uint32_t wakeup_pr1 = EXTI->PR1;
                    bool rtc_wakeup = __HAL_RTC_WAKEUPTIMER_EXTI_GET_FLAG();
                    
                    /* TẮT LED ngay khi thức dậy: LED TẮT = ĐÃ THỨC */
                    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
                    
                    /* ============================================================
                     *    HỆ THỐNG ĐÃ THỨC DẬY TẠI ĐÂY
                     * ============================================================ */
                    
                    /* Khôi phục lại ngắt RI */
                    EXTI->IMR1 |= GPIO_PIN_5;

                    /* Bật lại interrupt trước tiên */
                    __enable_irq();
                    
                    /* ----- BƯỚC 4: KHÔI PHỤC CLOCK ----- */
                    /* Sau Stop Mode 2, clock bị reset về MSI 4MHz. Phải cấu hình lại PLL 80MHz */
                    SystemClock_Config();
                    HAL_ResumeTick();
                    
                    /* Bật lại SysTick interrupt cho FreeRTOS */
                    SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
                    
                    /* ----- BƯỚC 5: KHÔI PHỤC NGOẠI VI MCU ----- */
                    Power_EnablePeripherals();
                    
                    /* ----- BƯỚC 6: NẠP LẠI CẤU HÌNH TỪ FLASH ----- */
                    LOG_INFO("[POWER TASK] Reloading config from Flash...");
                    W25Q32_Task_LoadConfig();
                    
                    LOG_INFO("[POWER TASK] === WAKEUP SEQUENCE COMPLETE ===");
                    LOG_INFO("[POWER TASK] Clock, peripherals and configuration restored.");
                    
                    /* In thông tin nguồn đánh thức */
                    if (wakeup_pr1 & GPIO_PIN_0) LOG_INFO("[POWER TASK] Wakeup Source: IMU INT1 (PA0)");
                    if (wakeup_pr1 & GPIO_PIN_5) LOG_INFO("[POWER TASK] Wakeup Source: SIM RI (PA5)");
                    if (wakeup_pr1 & GPIO_PIN_9) LOG_INFO("[POWER TASK] Wakeup Source: IMU INT2 (PB9)");
                    
                    /* Check RTC Wakeup (EXTI Line 20) */
                    if (rtc_wakeup) {
                        LOG_INFO("[POWER TASK] Wakeup Source: RTC Periodic Timer (Line 20)");
                        
                        /* Xử lý cờ ngắt RTC */
                        HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);
                        __HAL_RTC_WAKEUPTIMER_EXTI_CLEAR_FLAG();
                        __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&hrtc, RTC_FLAG_WUTF);
                    }
                    
                    if (wakeup_pr1 == 0 && !rtc_wakeup) LOG_INFO("[POWER TASK] Wakeup Source: Unknown / Other");
                    
                    /* ----- BƯỚC 6: ĐÁNH THỨC MODULE NGOẠI VI ----- */
                    SIM_Task_SetSleep(false);
                    LOG_INFO("[POWER TASK] SIM power-on sequence triggered.");
                    
                    ATGM336H_Task_Standby(false);
                    LOG_INFO("[POWER TASK] GPS -> Wakeup OK");
                    
                    /* ----- BƯỚC 7: YÊU CẦU GỬI DATA ----- */
                    /* Note: SIM task sẽ tự reconnect MQTT qua state machine (CHECK_COMM → MQTT_CONNECT).
                     * Force report được queue, sẽ gửi khi MQTT ready. */
                    System_Service_SetForceReport(true);
                    System_Service_SetWakeup(true); // Gửi thêm message wakeup riêng
                    LOG_INFO("[POWER TASK] === WAKEUP COMPLETE ===");
                    
                    /* Reset counter và flag để chuẩn bị cho chu kỳ sau */
                    park_counter = 0;
                    sleep_notify_triggered = false;
                } else {
                    LOG_INFO("[POWER TASK] Cannot sleep - Tasks: SIM=%s, GPS=%s, MGR=%s",
                             (uxBits & POWER_BIT_SIM)     ? "IDLE" : "BUSY",
                             (uxBits & POWER_BIT_GPS)     ? "IDLE" : "BUSY",
                             (uxBits & POWER_BIT_SYS_MGR) ? "IDLE" : "BUSY");
                }
            }
        } else {
            if (park_counter > 0) {
                LOG_INFO("[POWER TASK] Motion detected, sleep counter reset (was %ds)", (int)park_counter);
            }
            park_counter = 0;
            sleep_notify_triggered = false;
        }
        
        osDelay(1000);
    }
}

/* ========================================================================================
 * SECTION: Peripheral Control
 * ======================================================================================== */

static void Power_DisablePeripherals(void) {
    /* 1. Tắt UART Debug (LOG) — sau dòng này LOG_INFO sẽ KHÔNG hoạt động */
    HAL_UART_DeInit(&huart1);
    
    /* 2. Tắt ADC (đo pin) */
    HAL_ADC_DeInit(&hadc1);
    
    /* 3. Tắt GPS UART — tránh nhiễu từ chân RX đánh thức MCU */
    HAL_UART_DeInit(&huart3);
    
    /* 4. Tắt SIM UART — AT+CSCLK=1 đã gửi xong, DMA phải dừng
     *    để tránh URC "OK" cuối cùng trigger DMA interrupt -> CPU thức dậy */
    HAL_UART_DeInit(&huart2);
    
    /* 5. Đưa Flash vào chế độ Deep Power-Down (tiết kiệm ~15uA) 
     *    Lưu ý: KHÔNG TẮT SPI bus vì chân MOSI/SCK thả nổi sẽ làm Flash và IMU rò dòng. */
    W25Q32_Task_Sleep();
}

static void Power_EnablePeripherals(void) {
    /* 1. Khôi phục UART Debug (LOG) — ưu tiên bật đầu tiên để debug */
    HAL_UART_Init(&huart1);
    
    /* 2. Khôi phục ADC (bỏ qua lệnh Calibrate vì sụt áp đầu chu kỳ Wakeup sẽ làm sai lệch Offset) */
    HAL_ADC_Init(&hadc1);
    
    /* 3. Khôi phục GPS UART */
    HAL_UART_Init(&huart3);
    
    /* 4. Khôi phục SIM UART + khởi động lại DMA Circular RX */
    HAL_UART_Init(&huart2);
    SIM_Task_RestoreUART();
    
    /* 5. Đánh thức Flash W25Q32 */
    W25Q32_Task_Wakeup();
}
//sleep
//ok




