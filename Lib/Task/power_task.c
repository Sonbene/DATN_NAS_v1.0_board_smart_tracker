#include "power_task.h"
#include "system_manager_task.h"
#include "system_service.h"
#include "log.h"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "atgm336h_task.h"
#include "sim_task.h"

/* ========================================================================================
 * SECTION: Private Variables
 * ======================================================================================== */
static EventGroupHandle_t g_PowerEventGroup = NULL;

extern void SystemClock_Config(void);

extern UART_HandleTypeDef huart1; /* GPS */
extern UART_HandleTypeDef huart2; /* SIM */
extern UART_HandleTypeDef huart3; /* LOG */
extern ADC_HandleTypeDef hadc1;   /* BATTERY */

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
    
    while (1) {
        SystemData_t data;
        System_Service_GetSnapshot(&data);
        
        if (data.mode == SYS_MODE_STATIONARY) {
            park_counter++;
            
            /* SAU 30 GIÂY THÌ VÀO MODE WAIT TO SLEEP */
            if (park_counter >= 30) {
                
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
                    
                    /* ----- BƯỚC 1: ĐƯA MODULE NGOẠI VI VÀO CHẾ ĐỘ TIẾT KIỆM ----- */
                    ATGM336H_Task_Standby(true);
                    LOG_INFO("[POWER TASK] GPS -> Standby OK");
                    
                    SIM_Task_SetSleep(true);
                    LOG_INFO("[POWER TASK] SIM -> Sleep OK (DTR HIGH)");
                    
                    /* Chờ SIM module xử lý xong lệnh AT+CSCLK & phản hồi OK */
                    osDelay(500);
                    
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
                    
                    /* Tắt tất cả interrupt để tránh race condition giữa việc
                     * clear pending bits và lệnh WFI. WFI vẫn wake-on-interrupt 
                     * dù PRIMASK = 1, nhưng handler sẽ không chạy cho tới __enable_irq(). */
                    __disable_irq();
                    
                    /* XÓA TẤT CẢ cờ ngắt EXTI đang tồn đọng */
                    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);  /* IMU INT1 */
                    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5);  /* SIM RI   */
                    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_9);  /* IMU INT2 */
                    
                    /* Clear NVIC pending bits của các ngoại vi đã tắt */
                    NVIC_ClearPendingIRQ(USART1_IRQn);
                    NVIC_ClearPendingIRQ(USART2_IRQn);
                    NVIC_ClearPendingIRQ(USART3_IRQn);
                    NVIC_ClearPendingIRQ(DMA1_Channel1_IRQn);  /* ADC DMA */
                    NVIC_ClearPendingIRQ(DMA1_Channel5_IRQn);  /* USART1 RX DMA */
                    NVIC_ClearPendingIRQ(DMA1_Channel6_IRQn);  /* USART2 RX DMA */
                    NVIC_ClearPendingIRQ(DMA1_Channel7_IRQn);  /* USART2 TX DMA */
                    NVIC_ClearPendingIRQ(ADC1_IRQn);
                    
                    /* ----- BƯỚC 3: VÀO STOP MODE 2 (NGỦ SÂU) ----- */
                    /* BẬT LED (PC13 active-low) để báo hiệu: LED SÁNG = ĐANG NGỦ */
                    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
                    
                    /* CPU dừng tại đây. Chỉ thức khi có ngắt EXTI thực sự trên PA0/PA5/PB9 */
                    HAL_PWREx_EnterSTOP2Mode(PWR_STOPENTRY_WFI);
                    
                    /* TẮT LED ngay khi thức dậy: LED TẮT = ĐÃ THỨC */
                    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
                    
                    /* ============================================================
                     *    HỆ THỐNG ĐÃ THỨC DẬY TẠI ĐÂY
                     * ============================================================ */
                    
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
                    
                    LOG_INFO("[POWER TASK] === WAKEUP SEQUENCE START ===");
                    LOG_INFO("[POWER TASK] Clock & peripherals restored.");
                    
                    /* ----- BƯỚC 6: ĐÁNH THỨC MODULE NGOẠI VI ----- */
                    /* SIM_Task_SetSleep(false) tự xử lý: DTR LOW → AT retry → CSCLK=0 → flag modem_needs_init */
                    SIM_Task_SetSleep(false);
                    LOG_INFO("[POWER TASK] SIM wakeup sequence done.");
                    
                    ATGM336H_Task_Standby(false);
                    LOG_INFO("[POWER TASK] GPS -> Wakeup OK");
                    
                    /* ----- BƯỚC 7: YÊU CẦU GỬI DATA ----- */
                    /* Note: SIM task sẽ tự reconnect MQTT qua state machine (CHECK_COMM → MQTT_CONNECT).
                     * Force report được queue, sẽ gửi khi MQTT ready. */
                    System_Service_SetForceReport(true);
                    LOG_INFO("[POWER TASK] === WAKEUP COMPLETE ===");
                    
                    /* Reset counter để tránh ngủ lại ngay lập tức */
                    park_counter = 0;
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
        }
        
        osDelay(1000);
    }
}

/* ========================================================================================
 * SECTION: Peripheral Control
 * ======================================================================================== */

static void Power_DisablePeripherals(void) {
    /* 1. Tắt UART Debug (LOG) — sau dòng này LOG_INFO sẽ KHÔNG hoạt động */
    HAL_UART_DeInit(&huart3);
    
    /* 2. Tắt ADC (đo pin) */
    HAL_ADC_DeInit(&hadc1);
    
    /* 3. Tắt GPS UART — tránh nhiễu từ chân RX đánh thức MCU */
    HAL_UART_DeInit(&huart1);
    
    /* 4. Tắt SIM UART — AT+CSCLK=1 đã gửi xong, DMA phải dừng
     *    để tránh URC "OK" cuối cùng trigger DMA interrupt -> CPU thức dậy */
    HAL_UART_DeInit(&huart2);
}

static void Power_EnablePeripherals(void) {
    /* 1. Khôi phục UART Debug (LOG) — ưu tiên bật đầu tiên để debug */
    HAL_UART_Init(&huart3);
    
    /* 2. Khôi phục ADC */
    HAL_ADC_Init(&hadc1);
    
    /* 3. Khôi phục GPS UART */
    HAL_UART_Init(&huart1);
    
    /* 4. Khôi phục SIM UART + khởi động lại DMA Circular RX */
    HAL_UART_Init(&huart2);
    SIM_Task_RestoreUART();
}

