#line 1 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc_ex.c"





























 

 
#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal.h"

















 

 







 
#line 1 "../Core/Inc/stm32l4xx_hal_conf.h"
 


















 
 

 







 
 

 


 


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

 
 

 

 
 
 
 
#line 94 "../Core/Inc/stm32l4xx_hal_conf.h"

 




 











 







 










 







 









 












 








 





 

 


 

#line 190 "../Core/Inc/stm32l4xx_hal_conf.h"

 



 
 

 








 
#line 242 "../Core/Inc/stm32l4xx_hal_conf.h"

 




 



 


 

#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"















 

 







 
#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_def.h"

















 

 







 
#line 1 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l4xx.h"


























 



 



 










 



 






 

#line 91 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l4xx.h"



 
#line 103 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l4xx.h"



 
#line 115 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l4xx.h"



 



 

#line 1 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"






















 



 



 










 



 








 



 




 
typedef enum
{
 
  NonMaskableInt_IRQn         = -14,     
  HardFault_IRQn              = -13,     
  MemoryManagement_IRQn       = -12,     
  BusFault_IRQn               = -11,     
  UsageFault_IRQn             = -10,     
  SVCall_IRQn                 = -5,      
  DebugMonitor_IRQn           = -4,      
  PendSV_IRQn                 = -2,      
  SysTick_IRQn                = -1,      
 
  WWDG_IRQn                   = 0,       
  PVD_PVM_IRQn                = 1,       
  TAMP_STAMP_IRQn             = 2,       
  RTC_WKUP_IRQn               = 3,       
  FLASH_IRQn                  = 4,       
  RCC_IRQn                    = 5,       
  EXTI0_IRQn                  = 6,       
  EXTI1_IRQn                  = 7,       
  EXTI2_IRQn                  = 8,       
  EXTI3_IRQn                  = 9,       
  EXTI4_IRQn                  = 10,      
  DMA1_Channel1_IRQn          = 11,      
  DMA1_Channel2_IRQn          = 12,      
  DMA1_Channel3_IRQn          = 13,      
  DMA1_Channel4_IRQn          = 14,      
  DMA1_Channel5_IRQn          = 15,      
  DMA1_Channel6_IRQn          = 16,      
  DMA1_Channel7_IRQn          = 17,      
  ADC1_IRQn                   = 18,      
  CAN1_TX_IRQn                = 19,      
  CAN1_RX0_IRQn               = 20,      
  CAN1_RX1_IRQn               = 21,      
  CAN1_SCE_IRQn               = 22,      
  EXTI9_5_IRQn                = 23,      
  TIM1_BRK_TIM15_IRQn         = 24,      
  TIM1_UP_TIM16_IRQn          = 25,      
  TIM1_TRG_COM_IRQn           = 26,      
  TIM1_CC_IRQn                = 27,      
  TIM2_IRQn                   = 28,      
  I2C1_EV_IRQn                = 31,      
  I2C1_ER_IRQn                = 32,      
  I2C2_EV_IRQn                = 33,      
  I2C2_ER_IRQn                = 34,      
  SPI1_IRQn                   = 35,      
  SPI2_IRQn                   = 36,      
  USART1_IRQn                 = 37,      
  USART2_IRQn                 = 38,      
  USART3_IRQn                 = 39,      
  EXTI15_10_IRQn              = 40,      
  RTC_Alarm_IRQn              = 41,      
  SDMMC1_IRQn                 = 49,      
  SPI3_IRQn                   = 51,      
  TIM6_DAC_IRQn               = 54,      
  TIM7_IRQn                   = 55,      
  DMA2_Channel1_IRQn          = 56,      
  DMA2_Channel2_IRQn          = 57,      
  DMA2_Channel3_IRQn          = 58,      
  DMA2_Channel4_IRQn          = 59,      
  DMA2_Channel5_IRQn          = 60,      
  COMP_IRQn                   = 64,      
  LPTIM1_IRQn                 = 65,      
  LPTIM2_IRQn                 = 66,      
  DMA2_Channel6_IRQn          = 68,      
  DMA2_Channel7_IRQn          = 69,      
  LPUART1_IRQn                = 70,      
  QUADSPI_IRQn                = 71,      
  I2C3_EV_IRQn                = 72,      
  I2C3_ER_IRQn                = 73,      
  SAI1_IRQn                   = 74,      
  SWPMI1_IRQn                 = 76,      
  TSC_IRQn                    = 77,      
  RNG_IRQn                    = 80,      
  FPU_IRQn                    = 81,      
  CRS_IRQn                    = 82       
} IRQn_Type;



 

#line 1 "../Drivers/CMSIS/Include/core_cm4.h"
 




 
















 










#line 1 "D:\\Keil_C\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
 
 





 









     
#line 27 "D:\\Keil_C\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"
     











#line 46 "D:\\Keil_C\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"





 

     

     
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       __int64 int64_t;

     
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       __int64 uint64_t;

     

     
     
typedef   signed          char int_least8_t;
typedef   signed short     int int_least16_t;
typedef   signed           int int_least32_t;
typedef   signed       __int64 int_least64_t;

     
typedef unsigned          char uint_least8_t;
typedef unsigned short     int uint_least16_t;
typedef unsigned           int uint_least32_t;
typedef unsigned       __int64 uint_least64_t;

     

     
typedef   signed           int int_fast8_t;
typedef   signed           int int_fast16_t;
typedef   signed           int int_fast32_t;
typedef   signed       __int64 int_fast64_t;

     
typedef unsigned           int uint_fast8_t;
typedef unsigned           int uint_fast16_t;
typedef unsigned           int uint_fast32_t;
typedef unsigned       __int64 uint_fast64_t;

     




typedef   signed           int intptr_t;
typedef unsigned           int uintptr_t;


     
typedef   signed     long long intmax_t;
typedef unsigned     long long uintmax_t;




     

     





     





     





     

     





     





     





     

     





     





     





     

     






     






     






     

     


     


     


     

     
#line 216 "D:\\Keil_C\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     



     






     
    
 



#line 241 "D:\\Keil_C\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"

     







     










     











#line 305 "D:\\Keil_C\\ARM\\ARMCC\\Bin\\..\\include\\stdint.h"






 
#line 35 "../Drivers/CMSIS/Include/core_cm4.h"

















 




 



 

#line 1 "../Drivers/CMSIS/Include/cmsis_version.h"
 




 
















 










 
#line 64 "../Drivers/CMSIS/Include/core_cm4.h"

 









 
#line 87 "../Drivers/CMSIS/Include/core_cm4.h"

#line 161 "../Drivers/CMSIS/Include/core_cm4.h"

#line 1 "../Drivers/CMSIS/Include/cmsis_compiler.h"
 




 
















 




#line 29 "../Drivers/CMSIS/Include/cmsis_compiler.h"



 
#line 1 "../Drivers/CMSIS/Include/cmsis_armcc.h"
 




 
















 









 













   
   

 




 
#line 110 "../Drivers/CMSIS/Include/cmsis_armcc.h"

 





















 



 





 
 






 
 





 
static __inline uint32_t __get_CONTROL(void)
{
  register uint32_t __regControl         __asm("control");
  return(__regControl);
}






 
static __inline void __set_CONTROL(uint32_t control)
{
  register uint32_t __regControl         __asm("control");
  __regControl = control;
}






 
static __inline uint32_t __get_IPSR(void)
{
  register uint32_t __regIPSR          __asm("ipsr");
  return(__regIPSR);
}






 
static __inline uint32_t __get_APSR(void)
{
  register uint32_t __regAPSR          __asm("apsr");
  return(__regAPSR);
}






 
static __inline uint32_t __get_xPSR(void)
{
  register uint32_t __regXPSR          __asm("xpsr");
  return(__regXPSR);
}






 
static __inline uint32_t __get_PSP(void)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  return(__regProcessStackPointer);
}






 
static __inline void __set_PSP(uint32_t topOfProcStack)
{
  register uint32_t __regProcessStackPointer  __asm("psp");
  __regProcessStackPointer = topOfProcStack;
}






 
static __inline uint32_t __get_MSP(void)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  return(__regMainStackPointer);
}






 
static __inline void __set_MSP(uint32_t topOfMainStack)
{
  register uint32_t __regMainStackPointer     __asm("msp");
  __regMainStackPointer = topOfMainStack;
}






 
static __inline uint32_t __get_PRIMASK(void)
{
  register uint32_t __regPriMask         __asm("primask");
  return(__regPriMask);
}






 
static __inline void __set_PRIMASK(uint32_t priMask)
{
  register uint32_t __regPriMask         __asm("primask");
  __regPriMask = (priMask);
}









 







 







 
static __inline uint32_t  __get_BASEPRI(void)
{
  register uint32_t __regBasePri         __asm("basepri");
  return(__regBasePri);
}






 
static __inline void __set_BASEPRI(uint32_t basePri)
{
  register uint32_t __regBasePri         __asm("basepri");
  __regBasePri = (basePri & 0xFFU);
}







 
static __inline void __set_BASEPRI_MAX(uint32_t basePri)
{
  register uint32_t __regBasePriMax      __asm("basepri_max");
  __regBasePriMax = (basePri & 0xFFU);
}






 
static __inline uint32_t __get_FAULTMASK(void)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  return(__regFaultMask);
}






 
static __inline void __set_FAULTMASK(uint32_t faultMask)
{
  register uint32_t __regFaultMask       __asm("faultmask");
  __regFaultMask = (faultMask & (uint32_t)1U);
}









 
static __inline uint32_t __get_FPSCR(void)
{


  register uint32_t __regfpscr         __asm("fpscr");
  return(__regfpscr);



}






 
static __inline void __set_FPSCR(uint32_t fpscr)
{


  register uint32_t __regfpscr         __asm("fpscr");
  __regfpscr = (fpscr);



}


 


 



 




 






 







 






 








 










 










 






                  





 








 

__attribute__((section(".rev16_text"))) static __inline __asm uint32_t __REV16(uint32_t value)
{
  rev16 r0, r0
  bx lr
}








 

__attribute__((section(".revsh_text"))) static __inline __asm int16_t __REVSH(int16_t value)
{
  revsh r0, r0
  bx lr
}









 









 








 
#line 561 "../Drivers/CMSIS/Include/cmsis_armcc.h"







 











 












 












 














 














 














 










 









 









 









 

__attribute__((section(".rrx_text"))) static __inline __asm uint32_t __RRX(uint32_t value)
{
  rrx r0, r0
  bx lr
}








 








 








 








 








 








 


#line 809 "../Drivers/CMSIS/Include/cmsis_armcc.h"

   


 



 



#line 880 "../Drivers/CMSIS/Include/cmsis_armcc.h"











 


#line 35 "../Drivers/CMSIS/Include/cmsis_compiler.h"




 
#line 280 "../Drivers/CMSIS/Include/cmsis_compiler.h"




#line 163 "../Drivers/CMSIS/Include/core_cm4.h"

















 
#line 207 "../Drivers/CMSIS/Include/core_cm4.h"

 






 
#line 223 "../Drivers/CMSIS/Include/core_cm4.h"

 




 













 



 






 



 
typedef union
{
  struct
  {
    uint32_t _reserved0:16;               
    uint32_t GE:4;                        
    uint32_t _reserved1:7;                
    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} APSR_Type;

 





















 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:23;               
  } b;                                    
  uint32_t w;                             
} IPSR_Type;

 






 
typedef union
{
  struct
  {
    uint32_t ISR:9;                       
    uint32_t _reserved0:1;                
    uint32_t ICI_IT_1:6;                  
    uint32_t GE:4;                        
    uint32_t _reserved1:4;                
    uint32_t T:1;                         
    uint32_t ICI_IT_2:2;                  
    uint32_t Q:1;                         
    uint32_t V:1;                         
    uint32_t C:1;                         
    uint32_t Z:1;                         
    uint32_t N:1;                         
  } b;                                    
  uint32_t w;                             
} xPSR_Type;

 

































 
typedef union
{
  struct
  {
    uint32_t nPRIV:1;                     
    uint32_t SPSEL:1;                     
    uint32_t FPCA:1;                      
    uint32_t _reserved0:29;               
  } b;                                    
  uint32_t w;                             
} CONTROL_Type;

 









 







 



 
typedef struct
{
  volatile uint32_t ISER[8U];                
        uint32_t RESERVED0[24U];
  volatile uint32_t ICER[8U];                
        uint32_t RESERVED1[24U];
  volatile uint32_t ISPR[8U];                
        uint32_t RESERVED2[24U];
  volatile uint32_t ICPR[8U];                
        uint32_t RESERVED3[24U];
  volatile uint32_t IABR[8U];                
        uint32_t RESERVED4[56U];
  volatile uint8_t  IP[240U];                
        uint32_t RESERVED5[644U];
  volatile  uint32_t STIR;                    
}  NVIC_Type;

 



 







 



 
typedef struct
{
  volatile const  uint32_t CPUID;                   
  volatile uint32_t ICSR;                    
  volatile uint32_t VTOR;                    
  volatile uint32_t AIRCR;                   
  volatile uint32_t SCR;                     
  volatile uint32_t CCR;                     
  volatile uint8_t  SHP[12U];                
  volatile uint32_t SHCSR;                   
  volatile uint32_t CFSR;                    
  volatile uint32_t HFSR;                    
  volatile uint32_t DFSR;                    
  volatile uint32_t MMFAR;                   
  volatile uint32_t BFAR;                    
  volatile uint32_t AFSR;                    
  volatile const  uint32_t PFR[2U];                 
  volatile const  uint32_t DFR;                     
  volatile const  uint32_t ADR;                     
  volatile const  uint32_t MMFR[4U];                
  volatile const  uint32_t ISAR[5U];                
        uint32_t RESERVED0[5U];
  volatile uint32_t CPACR;                   
} SCB_Type;

 















 






























 



 





















 









 


















 










































 









 


















 





















 


















 









 















 







 



 
typedef struct
{
        uint32_t RESERVED0[1U];
  volatile const  uint32_t ICTR;                    
  volatile uint32_t ACTLR;                   
} SCnSCB_Type;

 



 















 







 



 
typedef struct
{
  volatile uint32_t CTRL;                    
  volatile uint32_t LOAD;                    
  volatile uint32_t VAL;                     
  volatile const  uint32_t CALIB;                   
} SysTick_Type;

 












 



 



 









 







 



 
typedef struct
{
  volatile  union
  {
    volatile  uint8_t    u8;                  
    volatile  uint16_t   u16;                 
    volatile  uint32_t   u32;                 
  }  PORT [32U];                          
        uint32_t RESERVED0[864U];
  volatile uint32_t TER;                     
        uint32_t RESERVED1[15U];
  volatile uint32_t TPR;                     
        uint32_t RESERVED2[15U];
  volatile uint32_t TCR;                     
        uint32_t RESERVED3[32U];
        uint32_t RESERVED4[43U];
  volatile  uint32_t LAR;                     
  volatile const  uint32_t LSR;                     
        uint32_t RESERVED5[6U];
  volatile const  uint32_t PID4;                    
  volatile const  uint32_t PID5;                    
  volatile const  uint32_t PID6;                    
  volatile const  uint32_t PID7;                    
  volatile const  uint32_t PID0;                    
  volatile const  uint32_t PID1;                    
  volatile const  uint32_t PID2;                    
  volatile const  uint32_t PID3;                    
  volatile const  uint32_t CID0;                    
  volatile const  uint32_t CID1;                    
  volatile const  uint32_t CID2;                    
  volatile const  uint32_t CID3;                    
} ITM_Type;

 



 



























 









   







 



 
typedef struct
{
  volatile uint32_t CTRL;                    
  volatile uint32_t CYCCNT;                  
  volatile uint32_t CPICNT;                  
  volatile uint32_t EXCCNT;                  
  volatile uint32_t SLEEPCNT;                
  volatile uint32_t LSUCNT;                  
  volatile uint32_t FOLDCNT;                 
  volatile const  uint32_t PCSR;                    
  volatile uint32_t COMP0;                   
  volatile uint32_t MASK0;                   
  volatile uint32_t FUNCTION0;               
        uint32_t RESERVED0[1U];
  volatile uint32_t COMP1;                   
  volatile uint32_t MASK1;                   
  volatile uint32_t FUNCTION1;               
        uint32_t RESERVED1[1U];
  volatile uint32_t COMP2;                   
  volatile uint32_t MASK2;                   
  volatile uint32_t FUNCTION2;               
        uint32_t RESERVED2[1U];
  volatile uint32_t COMP3;                   
  volatile uint32_t MASK3;                   
  volatile uint32_t FUNCTION3;               
} DWT_Type;

 






















































 



 



 



 



 



 



 



























   







 



 
typedef struct
{
  volatile const  uint32_t SSPSR;                   
  volatile uint32_t CSPSR;                   
        uint32_t RESERVED0[2U];
  volatile uint32_t ACPR;                    
        uint32_t RESERVED1[55U];
  volatile uint32_t SPPR;                    
        uint32_t RESERVED2[131U];
  volatile const  uint32_t FFSR;                    
  volatile uint32_t FFCR;                    
  volatile const  uint32_t FSCR;                    
        uint32_t RESERVED3[759U];
  volatile const  uint32_t TRIGGER;                 
  volatile const  uint32_t FIFO0;                   
  volatile const  uint32_t ITATBCTR2;               
        uint32_t RESERVED4[1U];
  volatile const  uint32_t ITATBCTR0;               
  volatile const  uint32_t FIFO1;                   
  volatile uint32_t ITCTRL;                  
        uint32_t RESERVED5[39U];
  volatile uint32_t CLAIMSET;                
  volatile uint32_t CLAIMCLR;                
        uint32_t RESERVED7[8U];
  volatile const  uint32_t DEVID;                   
  volatile const  uint32_t DEVTYPE;                 
} TPI_Type;

 



 



 












 






 



 





















 






 





















 






 



 


















 






   








 



 
typedef struct
{
  volatile const  uint32_t TYPE;                    
  volatile uint32_t CTRL;                    
  volatile uint32_t RNR;                     
  volatile uint32_t RBAR;                    
  volatile uint32_t RASR;                    
  volatile uint32_t RBAR_A1;                 
  volatile uint32_t RASR_A1;                 
  volatile uint32_t RBAR_A2;                 
  volatile uint32_t RASR_A2;                 
  volatile uint32_t RBAR_A3;                 
  volatile uint32_t RASR_A3;                 
} MPU_Type;



 









 









 



 









 






























 








 



 
typedef struct
{
        uint32_t RESERVED0[1U];
  volatile uint32_t FPCCR;                   
  volatile uint32_t FPCAR;                   
  volatile uint32_t FPDSCR;                  
  volatile const  uint32_t MVFR0;                   
  volatile const  uint32_t MVFR1;                   
  volatile const  uint32_t MVFR2;                   
} FPU_Type;

 



























 



 












 
























 












 




 







 



 
typedef struct
{
  volatile uint32_t DHCSR;                   
  volatile  uint32_t DCRSR;                   
  volatile uint32_t DCRDR;                   
  volatile uint32_t DEMCR;                   
} CoreDebug_Type;

 




































 






 







































 







 






 







 


 







 

 
#line 1553 "../Drivers/CMSIS/Include/core_cm4.h"

#line 1562 "../Drivers/CMSIS/Include/core_cm4.h"









 










 


 



 





 

#line 1616 "../Drivers/CMSIS/Include/core_cm4.h"

#line 1626 "../Drivers/CMSIS/Include/core_cm4.h"




 
#line 1637 "../Drivers/CMSIS/Include/core_cm4.h"










 
static __inline void __NVIC_SetPriorityGrouping(uint32_t PriorityGroup)
{
  uint32_t reg_value;
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);              

  reg_value  =  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR;                                                    
  reg_value &= ~((uint32_t)((0xFFFFUL << 16U) | (7UL << 8U)));  
  reg_value  =  (reg_value                                   |
                ((uint32_t)0x5FAUL << 16U) |
                (PriorityGroupTmp << 8U)  );               
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR =  reg_value;
}






 
static __inline uint32_t __NVIC_GetPriorityGrouping(void)
{
  return ((uint32_t)((((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8U)) >> 8U));
}







 
static __inline void __NVIC_EnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    __memory_changed();
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    __memory_changed();
  }
}









 
static __inline uint32_t __NVIC_GetEnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISER[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}







 
static __inline void __NVIC_DisableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    do { __schedule_barrier(); __dsb(0xF); __schedule_barrier(); } while (0U);
    do { __schedule_barrier(); __isb(0xF); __schedule_barrier(); } while (0U);
  }
}









 
static __inline uint32_t __NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}







 
static __inline void __NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ISPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}







 
static __inline void __NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->ICPR[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}









 
static __inline uint32_t __NVIC_GetActive(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    return((uint32_t)(((((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IABR[(((uint32_t)IRQn) >> 5UL)] & (1UL << (((uint32_t)IRQn) & 0x1FUL))) != 0UL) ? 1UL : 0UL));
  }
  else
  {
    return(0U);
  }
}










 
static __inline void __NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
  if ((int32_t)(IRQn) >= 0)
  {
    ((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[((uint32_t)IRQn)]               = (uint8_t)((priority << (8U - 4U)) & (uint32_t)0xFFUL);
  }
  else
  {
    ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[(((uint32_t)IRQn) & 0xFUL)-4UL] = (uint8_t)((priority << (8U - 4U)) & (uint32_t)0xFFUL);
  }
}










 
static __inline uint32_t __NVIC_GetPriority(IRQn_Type IRQn)
{

  if ((int32_t)(IRQn) >= 0)
  {
    return(((uint32_t)((NVIC_Type *) ((0xE000E000UL) + 0x0100UL) )->IP[((uint32_t)IRQn)]               >> (8U - 4U)));
  }
  else
  {
    return(((uint32_t)((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHP[(((uint32_t)IRQn) & 0xFUL)-4UL] >> (8U - 4U)));
  }
}












 
static __inline uint32_t NVIC_EncodePriority (uint32_t PriorityGroup, uint32_t PreemptPriority, uint32_t SubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);    
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(4U)) ? (uint32_t)(4U) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits     = ((PriorityGroupTmp + (uint32_t)(4U)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(4U));

  return (
           ((PreemptPriority & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL)) << SubPriorityBits) |
           ((SubPriority     & (uint32_t)((1UL << (SubPriorityBits    )) - 1UL)))
         );
}












 
static __inline void NVIC_DecodePriority (uint32_t Priority, uint32_t PriorityGroup, uint32_t* const pPreemptPriority, uint32_t* const pSubPriority)
{
  uint32_t PriorityGroupTmp = (PriorityGroup & (uint32_t)0x07UL);    
  uint32_t PreemptPriorityBits;
  uint32_t SubPriorityBits;

  PreemptPriorityBits = ((7UL - PriorityGroupTmp) > (uint32_t)(4U)) ? (uint32_t)(4U) : (uint32_t)(7UL - PriorityGroupTmp);
  SubPriorityBits     = ((PriorityGroupTmp + (uint32_t)(4U)) < (uint32_t)7UL) ? (uint32_t)0UL : (uint32_t)((PriorityGroupTmp - 7UL) + (uint32_t)(4U));

  *pPreemptPriority = (Priority >> SubPriorityBits) & (uint32_t)((1UL << (PreemptPriorityBits)) - 1UL);
  *pSubPriority     = (Priority                   ) & (uint32_t)((1UL << (SubPriorityBits    )) - 1UL);
}










 
static __inline void __NVIC_SetVector(IRQn_Type IRQn, uint32_t vector)
{
  uint32_t vectors = (uint32_t )((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->VTOR;
  (* (int *) (vectors + ((int32_t)IRQn + 16) * 4)) = vector;
   
}









 
static __inline uint32_t __NVIC_GetVector(IRQn_Type IRQn)
{
  uint32_t vectors = (uint32_t )((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->VTOR;
  return (uint32_t)(* (int *) (vectors + ((int32_t)IRQn + 16) * 4));
}





 
__declspec(noreturn) static __inline void __NVIC_SystemReset(void)
{
  do { __schedule_barrier(); __dsb(0xF); __schedule_barrier(); } while (0U);                                                          
 
  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR  = (uint32_t)((0x5FAUL << 16U)    |
                           (((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->AIRCR & (7UL << 8U)) |
                            (1UL << 2U)    );          
  do { __schedule_barrier(); __dsb(0xF); __schedule_barrier(); } while (0U);                                                           

  for(;;)                                                            
  {
    __nop();
  }
}

 


 



#line 1 "../Drivers/CMSIS/Include/mpu_armv7.h"





 
















 
 





 



#line 62 "../Drivers/CMSIS/Include/mpu_armv7.h"

#line 69 "../Drivers/CMSIS/Include/mpu_armv7.h"





 












   














 
#line 110 "../Drivers/CMSIS/Include/mpu_armv7.h"












                          









  










  












  




 




 




 




 





 
typedef struct {
  uint32_t RBAR; 
  uint32_t RASR; 
} ARM_MPU_Region_t;
    


 
static __inline void ARM_MPU_Enable(uint32_t MPU_Control)
{
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->CTRL = MPU_Control | (1UL );

  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHCSR |= (1UL << 16U);

  do { __schedule_barrier(); __dsb(0xF); __schedule_barrier(); } while (0U);
  do { __schedule_barrier(); __isb(0xF); __schedule_barrier(); } while (0U);
}


 
static __inline void ARM_MPU_Disable(void)
{
  do { __schedule_barrier(); __dmb(0xF); __schedule_barrier(); } while (0U);

  ((SCB_Type *) ((0xE000E000UL) + 0x0D00UL) )->SHCSR &= ~(1UL << 16U);

  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->CTRL  &= ~(1UL );
}



 
static __inline void ARM_MPU_ClrRegion(uint32_t rnr)
{
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RNR = rnr;
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RASR = 0U;
}




    
static __inline void ARM_MPU_SetRegion(uint32_t rbar, uint32_t rasr)
{
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RBAR = rbar;
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RASR = rasr;
}





    
static __inline void ARM_MPU_SetRegionEx(uint32_t rnr, uint32_t rbar, uint32_t rasr)
{
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RNR = rnr;
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RBAR = rbar;
  ((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RASR = rasr;
}





 
static __inline void ARM_MPU_OrderedMemcpy(volatile uint32_t* dst, const uint32_t* __restrict src, uint32_t len)
{
  uint32_t i;
  for (i = 0U; i < len; ++i) 
  {
    dst[i] = src[i];
  }
}




 
static __inline void ARM_MPU_Load(ARM_MPU_Region_t const* table, uint32_t cnt) 
{
  const uint32_t rowWordSize = sizeof(ARM_MPU_Region_t)/4U;
  while (cnt > 4U) {
    ARM_MPU_OrderedMemcpy(&(((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RBAR), &(table->RBAR), 4U*rowWordSize);
    table += 4U;
    cnt -= 4U;
  }
  ARM_MPU_OrderedMemcpy(&(((MPU_Type *) ((0xE000E000UL) + 0x0D90UL) )->RBAR), &(table->RBAR), cnt*rowWordSize);
}

#line 1956 "../Drivers/CMSIS/Include/core_cm4.h"




 





 








 
static __inline uint32_t SCB_GetFPUType(void)
{
  uint32_t mvfr0;

  mvfr0 = ((FPU_Type *) ((0xE000E000UL) + 0x0F30UL) )->MVFR0;
  if      ((mvfr0 & ((0xFUL << 4U) | (0xFUL << 8U))) == 0x020U)
  {
    return 1U;            
  }
  else
  {
    return 0U;            
  }
}


 



 





 













 
static __inline uint32_t SysTick_Config(uint32_t ticks)
{
  if ((ticks - 1UL) > (0xFFFFFFUL ))
  {
    return (1UL);                                                    
  }

  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->LOAD  = (uint32_t)(ticks - 1UL);                          
  __NVIC_SetPriority (SysTick_IRQn, (1UL << 4U) - 1UL);  
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->VAL   = 0UL;                                              
  ((SysTick_Type *) ((0xE000E000UL) + 0x0010UL) )->CTRL  = (1UL << 2U) |
                   (1UL << 1U)   |
                   (1UL );                          
  return (0UL);                                                      
}



 



 





 

extern volatile int32_t ITM_RxBuffer;                               










 
static __inline uint32_t ITM_SendChar (uint32_t ch)
{
  if (((((ITM_Type *) (0xE0000000UL) )->TCR & (1UL )) != 0UL) &&       
      ((((ITM_Type *) (0xE0000000UL) )->TER & 1UL               ) != 0UL)   )      
  {
    while (((ITM_Type *) (0xE0000000UL) )->PORT[0U].u32 == 0UL)
    {
      __nop();
    }
    ((ITM_Type *) (0xE0000000UL) )->PORT[0U].u8 = (uint8_t)ch;
  }
  return (ch);
}







 
static __inline int32_t ITM_ReceiveChar (void)
{
  int32_t ch = -1;                            

  if (ITM_RxBuffer != ((int32_t)0x5AA55AA5U))
  {
    ch = ITM_RxBuffer;
    ITM_RxBuffer = ((int32_t)0x5AA55AA5U);        
  }

  return (ch);
}







 
static __inline int32_t ITM_CheckChar (void)
{

  if (ITM_RxBuffer == ((int32_t)0x5AA55AA5U))
  {
    return (0);                               
  }
  else
  {
    return (1);                               
  }
}

 










#line 149 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"
#line 1 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/system_stm32l4xx.h"
















 



 



 



 









 



 




 
  






 
extern uint32_t SystemCoreClock;             

extern const uint8_t  AHBPrescTable[16];     
extern const uint8_t  APBPrescTable[8];      
extern const uint32_t MSIRangeTable[12];     



 



 



 



 



 



 

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);


 









 



 

#line 150 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"
#line 151 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"



 



 

typedef struct
{
  volatile uint32_t ISR;           
  volatile uint32_t IER;           
  volatile uint32_t CR;            
  volatile uint32_t CFGR;          
  volatile uint32_t CFGR2;         
  volatile uint32_t SMPR1;         
  volatile uint32_t SMPR2;         
       uint32_t RESERVED1;     
  volatile uint32_t TR1;           
  volatile uint32_t TR2;           
  volatile uint32_t TR3;           
       uint32_t RESERVED2;     
  volatile uint32_t SQR1;          
  volatile uint32_t SQR2;          
  volatile uint32_t SQR3;          
  volatile uint32_t SQR4;          
  volatile uint32_t DR;            
       uint32_t RESERVED3;     
       uint32_t RESERVED4;     
  volatile uint32_t JSQR;          
       uint32_t RESERVED5[4];  
  volatile uint32_t OFR1;          
  volatile uint32_t OFR2;          
  volatile uint32_t OFR3;          
  volatile uint32_t OFR4;          
       uint32_t RESERVED6[4];  
  volatile uint32_t JDR1;          
  volatile uint32_t JDR2;          
  volatile uint32_t JDR3;          
  volatile uint32_t JDR4;          
       uint32_t RESERVED7[4];  
  volatile uint32_t AWD2CR;        
  volatile uint32_t AWD3CR;        
       uint32_t RESERVED8;     
       uint32_t RESERVED9;     
  volatile uint32_t DIFSEL;        
  volatile uint32_t CALFACT;       

} ADC_TypeDef;

typedef struct
{
  uint32_t      RESERVED1;     
  uint32_t      RESERVED2;     
  volatile uint32_t CCR;           
  uint32_t      RESERVED3;     
} ADC_Common_TypeDef;




 

typedef struct
{
  volatile uint32_t TIR;   
  volatile uint32_t TDTR;  
  volatile uint32_t TDLR;  
  volatile uint32_t TDHR;  
} CAN_TxMailBox_TypeDef;



 

typedef struct
{
  volatile uint32_t RIR;   
  volatile uint32_t RDTR;  
  volatile uint32_t RDLR;  
  volatile uint32_t RDHR;  
} CAN_FIFOMailBox_TypeDef;



 

typedef struct
{
  volatile uint32_t FR1;  
  volatile uint32_t FR2;  
} CAN_FilterRegister_TypeDef;



 

typedef struct
{
  volatile uint32_t              MCR;                  
  volatile uint32_t              MSR;                  
  volatile uint32_t              TSR;                  
  volatile uint32_t              RF0R;                 
  volatile uint32_t              RF1R;                 
  volatile uint32_t              IER;                  
  volatile uint32_t              ESR;                  
  volatile uint32_t              BTR;                  
  uint32_t                   RESERVED0[88];        
  CAN_TxMailBox_TypeDef      sTxMailBox[3];        
  CAN_FIFOMailBox_TypeDef    sFIFOMailBox[2];      
  uint32_t                   RESERVED1[12];        
  volatile uint32_t              FMR;                  
  volatile uint32_t              FM1R;                 
  uint32_t                   RESERVED2;            
  volatile uint32_t              FS1R;                 
  uint32_t                   RESERVED3;            
  volatile uint32_t              FFA1R;                
  uint32_t                   RESERVED4;            
  volatile uint32_t              FA1R;                 
  uint32_t                   RESERVED5[8];         
  CAN_FilterRegister_TypeDef sFilterRegister[28];  
} CAN_TypeDef;




 

typedef struct
{
  volatile uint32_t CSR;          
} COMP_TypeDef;

typedef struct
{
  volatile uint32_t CSR;          
} COMP_Common_TypeDef;



 

typedef struct
{
  volatile uint32_t DR;           
  volatile uint8_t  IDR;          
  uint8_t       RESERVED0;    
  uint16_t      RESERVED1;    
  volatile uint32_t CR;           
  uint32_t      RESERVED2;    
  volatile uint32_t INIT;         
  volatile uint32_t POL;          
} CRC_TypeDef;



 
typedef struct
{
volatile uint32_t CR;             
volatile uint32_t CFGR;           
volatile uint32_t ISR;            
volatile uint32_t ICR;            
} CRS_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;           
  volatile uint32_t SWTRIGR;      
  volatile uint32_t DHR12R1;      
  volatile uint32_t DHR12L1;      
  volatile uint32_t DHR8R1;       
  volatile uint32_t DHR12R2;      
  volatile uint32_t DHR12L2;      
  volatile uint32_t DHR8R2;       
  volatile uint32_t DHR12RD;      
  volatile uint32_t DHR12LD;      
  volatile uint32_t DHR8RD;       
  volatile uint32_t DOR1;         
  volatile uint32_t DOR2;         
  volatile uint32_t SR;           
  volatile uint32_t CCR;          
  volatile uint32_t MCR;          
  volatile uint32_t SHSR1;        
  volatile uint32_t SHSR2;        
  volatile uint32_t SHHR;         
  volatile uint32_t SHRR;         
} DAC_TypeDef;




 

typedef struct
{
  volatile uint32_t IDCODE;       
  volatile uint32_t CR;           
  volatile uint32_t APB1FZR1;     
  volatile uint32_t APB1FZR2;     
  volatile uint32_t APB2FZ;       
} DBGMCU_TypeDef;




 

typedef struct
{
  volatile uint32_t CCR;          
  volatile uint32_t CNDTR;        
  volatile uint32_t CPAR;         
  volatile uint32_t CMAR;         
} DMA_Channel_TypeDef;

typedef struct
{
  volatile uint32_t ISR;          
  volatile uint32_t IFCR;         
} DMA_TypeDef;

typedef struct
{
  volatile uint32_t CSELR;        
} DMA_Request_TypeDef;

 





 

typedef struct
{
  volatile uint32_t IMR1;         
  volatile uint32_t EMR1;         
  volatile uint32_t RTSR1;        
  volatile uint32_t FTSR1;        
  volatile uint32_t SWIER1;       
  volatile uint32_t PR1;          
  uint32_t      RESERVED1;    
  uint32_t      RESERVED2;    
  volatile uint32_t IMR2;         
  volatile uint32_t EMR2;         
  volatile uint32_t RTSR2;        
  volatile uint32_t FTSR2;        
  volatile uint32_t SWIER2;       
  volatile uint32_t PR2;          
} EXTI_TypeDef;




 

typedef struct
{
  volatile uint32_t CSSA;         
  volatile uint32_t CSL;          
  volatile uint32_t NVDSSA;       
  volatile uint32_t NVDSL;        
  volatile uint32_t VDSSA ;       
  volatile uint32_t VDSL ;        
  uint32_t      RESERVED1;    
  uint32_t      RESERVED2;    
  volatile uint32_t CR ;          
} FIREWALL_TypeDef;




 

typedef struct
{
  volatile uint32_t ACR;               
  volatile uint32_t PDKEYR;            
  volatile uint32_t KEYR;              
  volatile uint32_t OPTKEYR;           
  volatile uint32_t SR;                
  volatile uint32_t CR;                
  volatile uint32_t ECCR;              
  volatile uint32_t RESERVED1;         
  volatile uint32_t OPTR;              
  volatile uint32_t PCROP1SR;          
  volatile uint32_t PCROP1ER;          
  volatile uint32_t WRP1AR;            
  volatile uint32_t WRP1BR;            
} FLASH_TypeDef;





 

typedef struct
{
  volatile uint32_t MODER;        
  volatile uint32_t OTYPER;       
  volatile uint32_t OSPEEDR;      
  volatile uint32_t PUPDR;        
  volatile uint32_t IDR;          
  volatile uint32_t ODR;          
  volatile uint32_t BSRR;         
  volatile uint32_t LCKR;         
  volatile uint32_t AFR[2];       
  volatile uint32_t BRR;          

} GPIO_TypeDef;




 

typedef struct
{
  volatile uint32_t CR1;          
  volatile uint32_t CR2;          
  volatile uint32_t OAR1;         
  volatile uint32_t OAR2;         
  volatile uint32_t TIMINGR;      
  volatile uint32_t TIMEOUTR;     
  volatile uint32_t ISR;          
  volatile uint32_t ICR;          
  volatile uint32_t PECR;         
  volatile uint32_t RXDR;         
  volatile uint32_t TXDR;         
} I2C_TypeDef;



 

typedef struct
{
  volatile uint32_t KR;           
  volatile uint32_t PR;           
  volatile uint32_t RLR;          
  volatile uint32_t SR;           
  volatile uint32_t WINR;         
} IWDG_TypeDef;



 
typedef struct
{
  volatile uint32_t ISR;          
  volatile uint32_t ICR;          
  volatile uint32_t IER;          
  volatile uint32_t CFGR;         
  volatile uint32_t CR;           
  volatile uint32_t CMP;          
  volatile uint32_t ARR;          
  volatile uint32_t CNT;          
  volatile uint32_t OR;           
} LPTIM_TypeDef;



 

typedef struct
{
  volatile uint32_t CSR;          
  volatile uint32_t OTR;          
  volatile uint32_t LPOTR;        
} OPAMP_TypeDef;

typedef struct
{
  volatile uint32_t CSR;          
} OPAMP_Common_TypeDef;



 

typedef struct
{
  volatile uint32_t CR1;    
  volatile uint32_t CR2;    
  volatile uint32_t CR3;    
  volatile uint32_t CR4;    
  volatile uint32_t SR1;    
  volatile uint32_t SR2;    
  volatile uint32_t SCR;    
  uint32_t RESERVED;    
  volatile uint32_t PUCRA;  
  volatile uint32_t PDCRA;  
  volatile uint32_t PUCRB;  
  volatile uint32_t PDCRB;  
  volatile uint32_t PUCRC;  
  volatile uint32_t PDCRC;  
  volatile uint32_t PUCRD;  
  volatile uint32_t PDCRD;  
  volatile uint32_t PUCRE;  
  volatile uint32_t PDCRE;  
  uint32_t RESERVED1;   
  uint32_t RESERVED2;   
  uint32_t RESERVED3;   
  uint32_t RESERVED4;   
  volatile uint32_t PUCRH;  
  volatile uint32_t PDCRH;  
} PWR_TypeDef;




 

typedef struct
{
  volatile uint32_t CR;           
  volatile uint32_t DCR;          
  volatile uint32_t SR;           
  volatile uint32_t FCR;          
  volatile uint32_t DLR;          
  volatile uint32_t CCR;          
  volatile uint32_t AR;           
  volatile uint32_t ABR;          
  volatile uint32_t DR;           
  volatile uint32_t PSMKR;        
  volatile uint32_t PSMAR;        
  volatile uint32_t PIR;          
  volatile uint32_t LPTR;         
} QUADSPI_TypeDef;




 

typedef struct
{
  volatile uint32_t CR;           
  volatile uint32_t ICSCR;        
  volatile uint32_t CFGR;         
  volatile uint32_t PLLCFGR;      
  volatile uint32_t PLLSAI1CFGR;  
  uint32_t      RESERVED;     
  volatile uint32_t CIER;         
  volatile uint32_t CIFR;         
  volatile uint32_t CICR;         
  uint32_t      RESERVED0;    
  volatile uint32_t AHB1RSTR;     
  volatile uint32_t AHB2RSTR;     
  volatile uint32_t AHB3RSTR;     
  uint32_t      RESERVED1;    
  volatile uint32_t APB1RSTR1;    
  volatile uint32_t APB1RSTR2;    
  volatile uint32_t APB2RSTR;     
  uint32_t      RESERVED2;    
  volatile uint32_t AHB1ENR;      
  volatile uint32_t AHB2ENR;      
  volatile uint32_t AHB3ENR;      
  uint32_t      RESERVED3;    
  volatile uint32_t APB1ENR1;     
  volatile uint32_t APB1ENR2;     
  volatile uint32_t APB2ENR;      
  uint32_t      RESERVED4;    
  volatile uint32_t AHB1SMENR;    
  volatile uint32_t AHB2SMENR;    
  volatile uint32_t AHB3SMENR;    
  uint32_t      RESERVED5;    
  volatile uint32_t APB1SMENR1;   
  volatile uint32_t APB1SMENR2;   
  volatile uint32_t APB2SMENR;    
  uint32_t      RESERVED6;    
  volatile uint32_t CCIPR;        
  uint32_t      RESERVED7;    
  volatile uint32_t BDCR;         
  volatile uint32_t CSR;          
  volatile uint32_t CRRCR;        
} RCC_TypeDef;



 

typedef struct
{
  volatile uint32_t TR;           
  volatile uint32_t DR;           
  volatile uint32_t CR;           
  volatile uint32_t ISR;          
  volatile uint32_t PRER;         
  volatile uint32_t WUTR;         
       uint32_t reserved;     
  volatile uint32_t ALRMAR;       
  volatile uint32_t ALRMBR;       
  volatile uint32_t WPR;          
  volatile uint32_t SSR;          
  volatile uint32_t SHIFTR;       
  volatile uint32_t TSTR;         
  volatile uint32_t TSDR;         
  volatile uint32_t TSSSR;        
  volatile uint32_t CALR;         
  volatile uint32_t TAMPCR;       
  volatile uint32_t ALRMASSR;     
  volatile uint32_t ALRMBSSR;     
  volatile uint32_t OR;           
  volatile uint32_t BKP0R;        
  volatile uint32_t BKP1R;        
  volatile uint32_t BKP2R;        
  volatile uint32_t BKP3R;        
  volatile uint32_t BKP4R;        
  volatile uint32_t BKP5R;        
  volatile uint32_t BKP6R;        
  volatile uint32_t BKP7R;        
  volatile uint32_t BKP8R;        
  volatile uint32_t BKP9R;        
  volatile uint32_t BKP10R;       
  volatile uint32_t BKP11R;       
  volatile uint32_t BKP12R;       
  volatile uint32_t BKP13R;       
  volatile uint32_t BKP14R;       
  volatile uint32_t BKP15R;       
  volatile uint32_t BKP16R;       
  volatile uint32_t BKP17R;       
  volatile uint32_t BKP18R;       
  volatile uint32_t BKP19R;       
  volatile uint32_t BKP20R;       
  volatile uint32_t BKP21R;       
  volatile uint32_t BKP22R;       
  volatile uint32_t BKP23R;       
  volatile uint32_t BKP24R;       
  volatile uint32_t BKP25R;       
  volatile uint32_t BKP26R;       
  volatile uint32_t BKP27R;       
  volatile uint32_t BKP28R;       
  volatile uint32_t BKP29R;       
  volatile uint32_t BKP30R;       
  volatile uint32_t BKP31R;       
} RTC_TypeDef;



 

typedef struct
{
  volatile uint32_t GCR;          
} SAI_TypeDef;

typedef struct
{
  volatile uint32_t CR1;          
  volatile uint32_t CR2;          
  volatile uint32_t FRCR;         
  volatile uint32_t SLOTR;        
  volatile uint32_t IMR;          
  volatile uint32_t SR;           
  volatile uint32_t CLRFR;        
  volatile uint32_t DR;           
} SAI_Block_TypeDef;




 

typedef struct
{
  volatile uint32_t POWER;           
  volatile uint32_t CLKCR;           
  volatile uint32_t ARG;             
  volatile uint32_t CMD;             
  volatile const uint32_t  RESPCMD;         
  volatile const uint32_t  RESP1;           
  volatile const uint32_t  RESP2;           
  volatile const uint32_t  RESP3;           
  volatile const uint32_t  RESP4;           
  volatile uint32_t DTIMER;          
  volatile uint32_t DLEN;            
  volatile uint32_t DCTRL;           
  volatile const uint32_t  DCOUNT;          
  volatile const uint32_t  STA;             
  volatile uint32_t ICR;             
  volatile uint32_t MASK;            
  uint32_t      RESERVED0[2];    
  volatile const uint32_t  FIFOCNT;         
  uint32_t      RESERVED1[13];   
  volatile uint32_t FIFO;            
} SDMMC_TypeDef;




 

typedef struct
{
  volatile uint32_t CR1;          
  volatile uint32_t CR2;          
  volatile uint32_t SR;           
  volatile uint32_t DR;           
  volatile uint32_t CRCPR;        
  volatile uint32_t RXCRCR;       
  volatile uint32_t TXCRCR;       
} SPI_TypeDef;




 

typedef struct
{
  volatile uint32_t CR;           
  volatile uint32_t BRR;          
    uint32_t  RESERVED1;      
  volatile uint32_t ISR;          
  volatile uint32_t ICR;          
  volatile uint32_t IER;          
  volatile uint32_t RFL;          
  volatile uint32_t TDR;          
  volatile uint32_t RDR;          
  volatile uint32_t OR;           
} SWPMI_TypeDef;




 

typedef struct
{
  volatile uint32_t MEMRMP;       
  volatile uint32_t CFGR1;        
  volatile uint32_t EXTICR[4];    
  volatile uint32_t SCSR;         
  volatile uint32_t CFGR2;        
  volatile uint32_t SWPR;         
  volatile uint32_t SKR;          
} SYSCFG_TypeDef;




 

typedef struct
{
  volatile uint32_t CR1;          
  volatile uint32_t CR2;          
  volatile uint32_t SMCR;         
  volatile uint32_t DIER;         
  volatile uint32_t SR;           
  volatile uint32_t EGR;          
  volatile uint32_t CCMR1;        
  volatile uint32_t CCMR2;        
  volatile uint32_t CCER;         
  volatile uint32_t CNT;          
  volatile uint32_t PSC;          
  volatile uint32_t ARR;          
  volatile uint32_t RCR;          
  volatile uint32_t CCR1;         
  volatile uint32_t CCR2;         
  volatile uint32_t CCR3;         
  volatile uint32_t CCR4;         
  volatile uint32_t BDTR;         
  volatile uint32_t DCR;          
  volatile uint32_t DMAR;         
  volatile uint32_t OR1;          
  volatile uint32_t CCMR3;        
  volatile uint32_t CCR5;         
  volatile uint32_t CCR6;         
  volatile uint32_t OR2;          
  volatile uint32_t OR3;          
} TIM_TypeDef;




 

typedef struct
{
  volatile uint32_t CR;             
  volatile uint32_t IER;            
  volatile uint32_t ICR;            
  volatile uint32_t ISR;            
  volatile uint32_t IOHCR;          
  uint32_t      RESERVED1;      
  volatile uint32_t IOASCR;         
  uint32_t      RESERVED2;      
  volatile uint32_t IOSCR;          
  uint32_t      RESERVED3;      
  volatile uint32_t IOCCR;          
  uint32_t      RESERVED4;      
  volatile uint32_t IOGCSR;         
  volatile uint32_t IOGXCR[7];      
} TSC_TypeDef;



 

typedef struct
{
  volatile uint32_t CR1;          
  volatile uint32_t CR2;          
  volatile uint32_t CR3;          
  volatile uint32_t BRR;          
  volatile uint16_t GTPR;         
  uint16_t  RESERVED2;        
  volatile uint32_t RTOR;         
  volatile uint16_t RQR;          
  uint16_t  RESERVED3;        
  volatile uint32_t ISR;          
  volatile uint32_t ICR;          
  volatile uint16_t RDR;          
  uint16_t  RESERVED4;        
  volatile uint16_t TDR;          
  uint16_t  RESERVED5;        
} USART_TypeDef;



 

typedef struct
{
  volatile uint32_t CSR;          
  volatile uint32_t CCR;          
} VREFBUF_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;           
  volatile uint32_t CFR;          
  volatile uint32_t SR;           
} WWDG_TypeDef;



 

typedef struct
{
  volatile uint32_t CR;   
  volatile uint32_t SR;   
  volatile uint32_t DR;   
} RNG_TypeDef;



 



 
#line 925 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"





 











 






 
#line 974 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"


 
#line 992 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 1000 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"


#line 1010 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"


#line 1020 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"


 
#line 1029 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"










 








 



 
#line 1079 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1102 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1112 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"


#line 1122 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"


#line 1132 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"









 



 



 




 



 

 
 
 

 
 
 
 
 



 
 

 
#line 1209 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 1244 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 1257 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 1289 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 1297 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"











#line 1315 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"







#line 1331 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"





#line 1342 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1361 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1370 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"





 
#line 1382 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1389 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1397 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1404 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 1412 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1419 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1426 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1433 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1440 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1447 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1454 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1461 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1468 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1475 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 1483 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1490 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1497 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1504 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1511 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1518 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1525 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1532 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1539 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 1556 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1572 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 1585 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1597 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 1610 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1622 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 1631 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1640 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1649 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1658 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1667 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 1677 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1686 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1695 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1704 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1713 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 1723 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1732 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1741 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1750 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1759 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 1769 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1778 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 1799 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 






#line 1814 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"







#line 1829 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1838 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1847 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1856 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 1873 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1882 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"





 
#line 1903 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1912 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"





 
#line 1933 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1942 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"





 
#line 1963 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 1972 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"





 
#line 1997 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2018 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2039 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2060 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2084 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2108 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2132 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2144 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 2155 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
 






#line 2171 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 2181 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
 
 
 
 
 
 
#line 2216 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2245 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2295 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 2308 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 2321 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2335 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2349 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2393 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2404 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 2411 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 2418 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2447 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
 
#line 2465 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2476 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2490 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2504 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2521 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2532 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2546 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2560 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2577 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2588 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2602 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2616 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2630 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2641 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2655 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2669 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2683 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2694 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2708 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2722 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
 




 
#line 2775 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2822 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2869 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 2916 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 3014 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 3112 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 3210 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 3308 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 3406 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 3504 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 3602 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 3700 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 3798 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 3896 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 3994 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 4092 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 4190 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 4288 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 4386 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 4484 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 4582 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 4680 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 4778 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 4876 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 4974 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 5072 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 5170 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 5268 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 5366 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 5464 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 5562 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 5660 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
 
 
 
 
 




 




 
#line 5693 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 




 
 
 
 

 
#line 5740 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 5748 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 5755 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"











 
#line 5794 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 5808 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
 
 
 
 


 


 
#line 5826 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 5833 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"







#line 5847 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 5857 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 5864 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 5871 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"







#line 5885 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 5895 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 5903 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 




 




 




 




 




 
#line 5941 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 5949 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 5957 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 




 
#line 5978 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 5988 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 5996 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 6004 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 6011 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 




 
#line 6029 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 6037 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
 
 
 
 

 
#line 6129 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 6215 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 6241 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"























 




 




 





 
#line 6302 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
 
 
 
 
 
#line 6402 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 6494 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 6562 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 6630 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 6698 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 6766 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 6786 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 6806 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 6814 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 6822 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 6830 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 6838 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"


 
 
 
 
 
 
#line 6875 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 6916 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 6957 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 6974 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 7023 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 
#line 7036 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 7044 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 7052 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"




 
 
 
 
 
 
#line 7142 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 7192 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 7242 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 7260 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 7342 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 7392 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 7474 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 7524 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 7574 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 7592 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 7610 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 7660 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 7678 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 7696 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 7794 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 7828 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 7881 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 7939 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 7949 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 8007 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 8017 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 8067 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 8085 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"



 
 
 
 
 
 
#line 8157 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 8192 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 8203 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 8236 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 8253 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 8270 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 8323 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 8352 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 




 




 
 
 
 
 
 




 
#line 8385 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 
#line 8401 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 
 
 
 
 

 
#line 8432 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 8443 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
 
 
 
 

 

#line 8479 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"


 
 
#line 8492 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"
 
#line 8521 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 8550 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 





 
#line 8579 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 8605 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 8625 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 8648 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 8695 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 8739 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 8789 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 8836 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 8886 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 8936 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 8986 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 9036 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 9086 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 9136 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"


 
#line 9148 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 9159 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"


 
 
 
 
 


 






 
#line 9188 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 9205 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 9218 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 9231 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 9244 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
 
#line 9258 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 9271 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 9284 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 9294 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
 











 











 
#line 9328 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 9338 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 9346 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"







 
#line 9360 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"











 
#line 9379 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 9386 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"







 
#line 9400 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




#line 9415 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 9422 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 9433 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 9443 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"







#line 9458 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 9467 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 9479 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 9486 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 9495 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 9504 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 9513 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 9542 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 9574 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 9606 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 9623 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 9649 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 
#line 9704 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 9715 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 9741 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 9758 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 9784 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 
#line 9845 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 9856 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 9885 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 9905 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 9934 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 
#line 9995 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 10006 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 10032 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 












































































 
#line 10120 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"







#line 10133 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"







#line 10152 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 10160 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 10168 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 10196 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 10204 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 10218 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
 
 
 
 
 
#line 10231 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 10248 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
 
 
 
 


 






 



 
#line 10309 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 10353 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 10423 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 
#line 10484 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 10492 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 
#line 10567 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 10637 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 




 
#line 10655 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 10698 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 10728 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 
#line 10756 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 10828 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 10840 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 10852 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 10860 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"


 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 




 
 
 
 
 
 












 












#line 11059 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 11066 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"







#line 11088 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 11096 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 11104 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 11117 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"


#line 11128 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 11137 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"


 
#line 11151 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 11162 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 11172 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 11182 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"







#line 11196 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"





 
#line 11223 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 11246 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 11253 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 11276 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 
 
 
 
 
 






 
#line 11307 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"







#line 11320 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 










#line 11349 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 




 




 




 




 




 




 
#line 11398 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 11406 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 11419 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 
#line 11495 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 11533 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 11601 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 




 
 
 
 
 
 
#line 11627 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 11634 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 11665 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 11707 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 11746 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 




 




 




 
 
 
 
 
 
#line 11821 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 11835 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 11858 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 11872 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 
#line 11929 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 




 




 




 




 




 




 
 
 
 
 
 
#line 11977 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 12012 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 12026 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"



 
#line 12036 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"



 
#line 12046 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"



 








 
#line 12065 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 12079 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"


 








 








 








 






 
#line 12128 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"



 








 








 








 






 
#line 12178 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"



 








 








 








 






 
#line 12222 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 12239 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 12289 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 







 
 
 
 
 
 
#line 12319 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"





















 
#line 12350 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 12357 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 12388 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 12396 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 12405 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"





#line 12416 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"





#line 12428 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"







#line 12441 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 12488 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 12538 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"


 
#line 12568 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"


 






#line 12583 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 12591 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"











#line 12608 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 12616 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"





 






#line 12635 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"







#line 12649 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 






#line 12663 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 12671 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"











#line 12688 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 12696 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"





 






#line 12715 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"







#line 12729 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 12737 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 12745 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"





#line 12756 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 12764 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"





 
#line 12827 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 12835 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 




 




 




 




 




 




 
#line 12884 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 
#line 12902 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"







#line 12927 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 12934 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 12941 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 12951 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 12960 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 










 
#line 12996 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 13003 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 13023 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"


 
#line 13032 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"







 
#line 13046 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"


 










 
#line 13078 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 13086 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 13106 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"


 
 
 
 
 
 
#line 13135 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 13158 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 13181 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 






















#line 13211 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 13218 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"







#line 13243 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 13254 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 




 




 






 
 
 
 
 
 










#line 13299 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"





















#line 13326 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 13333 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"















 
 
 
 
 
 
#line 13360 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"



















#line 13394 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 13402 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"



















#line 13436 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"





 
#line 13448 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 13456 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 13464 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 13472 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
 
 
 
 
 
#line 13494 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 13501 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 13508 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 13515 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 13526 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 13534 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

#line 13542 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 13550 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 13558 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 13566 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 13652 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 13738 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 13824 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 13910 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 13954 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 
 
 
 
 



 


 
#line 14048 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 14108 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 14178 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 14186 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 14194 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 14202 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 14219 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 14290 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 14331 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 




 




 
 
 
 
 

 
#line 14375 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 
#line 14415 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 14438 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 14467 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 14475 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 




 
#line 14493 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
 
 
 
 
 
#line 14512 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 
 
 
 
 
 
#line 14534 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"





 
#line 14550 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"











 





 
 
 
 
 
 
#line 14579 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 14593 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"







 
#line 14634 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 




 
#line 14650 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"




 



 



 

 




 


 





 


 


 


 
#line 14702 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 14710 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
 


 
 


 




 


 




 


 


 


 



 


 




 




 


 



 


 
#line 14775 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 


 




 




 


 





 




 



 



 


 


 




 
#line 14829 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 





 





 
#line 14864 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 
#line 14877 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l431xx.h"

 





 




 



 




 




 


 




 



 



 



 



 



 






 




 



 





 




 


 




 


 


 




 




 




 





 





 





 




 





 




 




 


 


 




 


 
 
 
 
 
 
 

 






 














 

  

 

#line 130 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l4xx.h"
#line 177 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l4xx.h"



 



 
typedef enum
{
  RESET = 0,
  SET = !RESET
} FlagStatus, ITStatus;

typedef enum
{
  DISABLE = 0,
  ENABLE = !DISABLE
} FunctionalState;


typedef enum
{
  SUCCESS = 0,
  ERROR = !SUCCESS
} ErrorStatus;



 




 














 
 
#line 235 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l4xx.h"

 
#line 244 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l4xx.h"

 
#line 253 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l4xx.h"

 
#line 262 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l4xx.h"

 
#line 271 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l4xx.h"

 
#line 280 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l4xx.h"





 

#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal.h"

















 

 
#line 289 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l4xx.h"









 



 

#line 30 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_def.h"
#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

















 

 







 
 
 



 
#line 48 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 
#line 95 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 103 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"












 



 





 



 
#line 147 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"




#line 157 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 179 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"




 
 
#line 192 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 202 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 212 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"




 



 
#line 227 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 





 



 






 



 

#line 265 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"






#line 277 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"








 



 
#line 304 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"







#line 337 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"












#line 358 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 420 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"






 



 

#line 529 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 

#line 546 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 

#line 571 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 




 
#line 591 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 





 



 


















#line 641 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"





#line 652 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 659 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"









#line 675 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 





 



 
#line 701 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 710 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 721 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 833 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 850 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 
#line 873 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 





 



 






 



 















 
 







 



 








 



 














 



 










 



 







































 



 


#line 1030 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"






 



 

 
#line 1052 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

 












 



 




























#line 1108 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 




 















 




 
#line 1149 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 









#line 1179 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 



#line 1217 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1227 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1246 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"










#line 1273 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"







 



 




 



 

























 




 








 



 




 



 
#line 1357 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 

#line 1374 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1386 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1417 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 











 






 






#line 1461 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 







 




 





 



 

 



 



 



 








 




 




 



 
#line 1530 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

 





































 



 
#line 1597 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 
#line 1612 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 








#line 1640 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1651 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 

#line 1681 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1689 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"






#line 1705 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



#line 1780 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 





 



 



 



 
#line 1818 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 



 



 






 




 



 

 



 





 



 
#line 1879 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"









 




 
#line 1907 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1928 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1939 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1948 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1961 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 1970 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 







 



 
#line 2006 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 2021 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


#line 2054 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 
#line 2221 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"




 
 
 
 




 




 




 




 







 



 

#line 2268 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 

#line 2296 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 










 



 














 




 




 




 







 




 
#line 2374 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 




 
#line 2418 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 2432 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 




 








#line 2706 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 2720 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 2937 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 2951 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 2958 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 2979 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3127 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

 



#line 3152 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3173 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3290 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3299 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3316 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3331 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"






#line 3360 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

















#line 3386 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"





#line 3413 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"







#line 3428 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3461 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3479 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"












#line 3497 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3518 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3554 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"



 



 




 



 
#line 3577 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3605 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3620 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"






 



 













#line 3669 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3691 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"
 




#line 3702 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3714 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 

#line 3728 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"








 



 
#line 3749 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 







 



 













 




 









#line 3803 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 












#line 3829 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3838 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"

#line 3847 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"








 



 








#line 3880 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"




 



 

#line 3897 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"






 



 




 



 
#line 3931 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 







 



 
#line 3958 "../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy/stm32_hal_legacy.h"


 



 





 



 



 








#line 31 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_def.h"
#line 1 "D:\\Keil_C\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"
 






 

 
 
 





 





#line 34 "D:\\Keil_C\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"




  typedef signed int ptrdiff_t;



  



    typedef unsigned int size_t;    
#line 57 "D:\\Keil_C\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"



   



      typedef unsigned short wchar_t;  
#line 82 "D:\\Keil_C\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"



    




   




  typedef long double max_align_t;









#line 114 "D:\\Keil_C\\ARM\\ARMCC\\Bin\\..\\include\\stddef.h"



 

#line 32 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_def.h"

 



 
typedef enum
{
  HAL_OK       = 0x00,
  HAL_ERROR    = 0x01,
  HAL_BUSY     = 0x02,
  HAL_TIMEOUT  = 0x03
} HAL_StatusTypeDef;



 
typedef enum
{
  HAL_UNLOCKED = 0x00,
  HAL_LOCKED   = 0x01
} HAL_LockTypeDef;

 




























 


#line 102 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_def.h"








#line 125 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_def.h"


 
#line 154 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_def.h"



 









 


#line 186 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_def.h"



 



 


#line 203 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_def.h"






#line 28 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"



 



 

 


 



 
typedef struct
{
  uint32_t PLLState;   
 

  uint32_t PLLSource;  
 

  uint32_t PLLM;       

 

  uint32_t PLLN;       
 


  uint32_t PLLP;       
 


  uint32_t PLLQ;       
 

  uint32_t PLLR;       


 

}RCC_PLLInitTypeDef;



 
typedef struct
{
  uint32_t OscillatorType;       
 

  uint32_t HSEState;             
 

  uint32_t LSEState;             
 

  uint32_t HSIState;             
 

  uint32_t HSICalibrationValue;  



 

  uint32_t LSIState;             
 






  uint32_t MSIState;             
 

  uint32_t MSICalibrationValue;  
 

  uint32_t MSIClockRange;        
 

  uint32_t HSI48State;             
 

  RCC_PLLInitTypeDef PLL;         

}RCC_OscInitTypeDef;



 
typedef struct
{
  uint32_t ClockType;             
 

  uint32_t SYSCLKSource;          
 

  uint32_t AHBCLKDivider;         
 

  uint32_t APB1CLKDivider;        
 

  uint32_t APB2CLKDivider;        
 

}RCC_ClkInitTypeDef;



 

 


 



 




 



 
#line 174 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"


 



 





 



 
#line 198 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"


 



 










 



 




 
#line 236 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"



 






 




 




 
#line 266 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"



 





 




 
#line 316 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"


 




 






 



 






 



 






 



 
#line 364 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"


 




 





 


#line 399 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"



 
#line 415 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"


 



 






 



 






 



 






 



 
#line 464 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"


 



 







 



 






 



 




 



 
#line 514 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"


 



 







 



 
#line 550 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"


 










 
 
#line 575 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

 



 
#line 590 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"


 




 



 






 



 




 



 

 



 







 

#line 644 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 652 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 662 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 670 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 678 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 686 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 696 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 706 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"


























 







 

#line 749 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 757 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 765 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 775 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 785 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 795 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 805 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 813 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 823 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 833 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 841 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 851 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 861 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 871 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 881 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 889 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 899 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 909 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 919 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"




































































 







 

#line 1006 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1016 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1026 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1036 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"



















 







 

#line 1072 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1082 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1092 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1102 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1110 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1120 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1130 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1140 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1148 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1158 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1168 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1176 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1186 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1196 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1206 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1214 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1224 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1232 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1242 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1252 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1262 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1272 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1282 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1290 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1300 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1308 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1316 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1324 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1334 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1342 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"




































































































 







 

#line 1459 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1467 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1477 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1485 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1493 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1503 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1511 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"


#line 1520 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1528 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1538 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1548 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1558 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1568 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1578 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 1588 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"
















































 







 
















































 







 




































































































































 







 



































 







 








































































































































































































 







 






























































































 




 



















































 




 







































































































































 




 






































 




 





































































































































































































 




 































































































 








 




















































 








 
















































































































































 








 



































 








 








































































































































































































 








 




























































































 








 




















































 








 
















































































































































 








 




































 








 








































































































































































































 








 




























































































 



 






 






 



 








 






 
















 












 









 












 




















 













 




























 
















 


















 













 


























 
#line 4133 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"




















 
#line 4171 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"









 





























 










 









 















 













 









































 


#line 4316 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 4343 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"








 















 














 











 










 















 










 




























 






 




















 





















 






















 






















 






 





























 
#line 4607 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"



 



 

 


 
 
#line 4627 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"



 








 
#line 4650 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"


 



 

 


 







#line 4676 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"















































#line 4729 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 4742 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

#line 4755 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"






























#line 4805 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"














 

 
#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"















 

 







 
#line 28 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"



 



 

 



 




 
typedef struct
{

  uint32_t PLLSAI1Source;    
 





  uint32_t PLLSAI1M;         
 


  uint32_t PLLSAI1N;         
 

  uint32_t PLLSAI1P;         
 

  uint32_t PLLSAI1Q;         
 

  uint32_t PLLSAI1R;         
 

  uint32_t PLLSAI1ClockOut;  
 
}RCC_PLLSAI1InitTypeDef;


#line 115 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"



 
typedef struct
{
  uint32_t PeriphClockSelection;   
 


  RCC_PLLSAI1InitTypeDef PLLSAI1;  
 
#line 134 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

  uint32_t Usart1ClockSelection;   
 

  uint32_t Usart2ClockSelection;   
 



  uint32_t Usart3ClockSelection;   
 



#line 154 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 161 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

  uint32_t Lpuart1ClockSelection;  
 

  uint32_t I2c1ClockSelection;     
 



  uint32_t I2c2ClockSelection;     
 



  uint32_t I2c3ClockSelection;     
 

#line 184 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

  uint32_t Lptim1ClockSelection;   
 

  uint32_t Lptim2ClockSelection;   
 


  uint32_t Sai1ClockSelection;     
 


#line 202 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 209 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"



  uint32_t Sdmmc1ClockSelection;   
 



  uint32_t RngClockSelection;      
 


  uint32_t AdcClockSelection;      
 




  uint32_t Swpmi1ClockSelection;   
 



#line 244 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 251 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 258 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 265 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

  uint32_t RTCClockSelection;      
 
}RCC_PeriphCLKInitTypeDef;





 
typedef struct
{
  uint32_t Prescaler;             
 

  uint32_t Source;                
 

  uint32_t Polarity;              
 

  uint32_t ReloadValue;           

 

  uint32_t ErrorLimitValue;       
 

  uint32_t HSI48CalibrationValue; 

 

}RCC_CRSInitTypeDef;



 
typedef struct
{
  uint32_t ReloadValue;           
 

  uint32_t HSI48CalibrationValue; 
 

  uint32_t FreqErrorCapture;      

 

  uint32_t FreqErrorDirection;    


 

}RCC_CRSSynchroInfoTypeDef;




 

 


 



 




 



 
#line 398 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"


 




 






 



 






 




 






 


#line 450 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 463 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"



 






 



 





 




 





 




 





 

#line 518 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"




 
#line 539 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"


 


#line 563 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"



 






 



 






 




 
#line 601 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"


 




 
#line 619 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"


 

#line 641 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"



 
#line 657 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"


 




 




 


#line 698 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 711 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 722 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 734 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"



 



 





 
#line 755 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"


 



 





 



 
#line 780 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"


 



 




 



 




 



 



 



 
#line 822 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"


 



 




 



 
#line 845 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"



 



 
#line 860 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"



 





 

 


 



































 
#line 940 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"



#line 951 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 964 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

















 



#line 1003 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"













 





#line 1028 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"












 














 







 

















 















 




#line 1362 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"























 
#line 1393 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"













 








#line 1454 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"









 








 












 








 












 








 


#line 1542 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"











 









 











 









 













 









 




#line 1639 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 1665 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"










 









 











 









 











 









 


































 
#line 1783 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"




















 
#line 1811 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"



















 














 


#line 1885 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"













 











 
#line 1922 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"









 







 




#line 1995 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 2020 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 2041 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 2064 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"




 




 




 




 




 




 




#line 2126 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"





 





 





 





 






 






 






 





 





 









 









 





 





 














 











 










 












 
 


#line 2279 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"













 















 

 


#line 2323 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"





 





 




 





 






 





 











 




 



#line 2410 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"



 

 


 



 

HAL_StatusTypeDef HAL_RCCEx_PeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
void              HAL_RCCEx_GetPeriphCLKConfig(RCC_PeriphCLKInitTypeDef  *PeriphClkInit);
uint32_t          HAL_RCCEx_GetPeriphCLKFreq(uint32_t PeriphClk);



 



 


HAL_StatusTypeDef HAL_RCCEx_EnablePLLSAI1(RCC_PLLSAI1InitTypeDef  *PLLSAI1Init);
HAL_StatusTypeDef HAL_RCCEx_DisablePLLSAI1(void);



#line 2448 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

void              HAL_RCCEx_WakeUpStopCLKConfig(uint32_t WakeUpClk);
void              HAL_RCCEx_StandbyMSIRangeConfig(uint32_t MSIRange);
void              HAL_RCCEx_EnableLSECSS(void);
void              HAL_RCCEx_DisableLSECSS(void);
void              HAL_RCCEx_EnableLSECSS_IT(void);
void              HAL_RCCEx_LSECSS_IRQHandler(void);
void              HAL_RCCEx_LSECSS_Callback(void);
void              HAL_RCCEx_EnableLSCO(uint32_t LSCOSource);
void              HAL_RCCEx_DisableLSCO(void);
void              HAL_RCCEx_EnableMSIPLLMode(void);
void              HAL_RCCEx_DisableMSIPLLMode(void);






 





 

void              HAL_RCCEx_CRSConfig(RCC_CRSInitTypeDef *pInit);
void              HAL_RCCEx_CRSSoftwareSynchronizationGenerate(void);
void              HAL_RCCEx_CRSGetSynchronizationInfo(RCC_CRSSynchroInfoTypeDef *pSynchroInfo);
uint32_t          HAL_RCCEx_CRSWaitSynchronization(uint32_t Timeout);
void              HAL_RCCEx_CRS_IRQHandler(void);
void              HAL_RCCEx_CRS_SyncOkCallback(void);
void              HAL_RCCEx_CRS_SyncWarnCallback(void);
void              HAL_RCCEx_CRS_ExpectedSyncCallback(void);
void              HAL_RCCEx_CRS_ErrorCallback(uint32_t Error);



 





 

 


 
 
#line 2629 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"



 

 


 





























#line 2676 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 2686 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"


























#line 2720 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 2739 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"








#line 2765 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"













#line 2789 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 2805 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"



#line 2820 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 2830 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 2857 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 2867 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 2878 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"











#line 2905 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 2915 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 2923 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"

#line 2932 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"































#line 2994 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc_ex.h"




































 



 



 







#line 4823 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"

 


 




 

 
HAL_StatusTypeDef HAL_RCC_DeInit(void);
HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FLatency);



 



 

 
void              HAL_RCC_MCOConfig(uint32_t RCC_MCOx, uint32_t RCC_MCOSource, uint32_t RCC_MCODiv);
void              HAL_RCC_EnableCSS(void);
uint32_t          HAL_RCC_GetSysClockFreq(void);
uint32_t          HAL_RCC_GetHCLKFreq(void);
uint32_t          HAL_RCC_GetPCLK1Freq(void);
uint32_t          HAL_RCC_GetPCLK2Freq(void);
void              HAL_RCC_GetOscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
void              HAL_RCC_GetClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t *pFLatency);
 
void              HAL_RCC_NMI_IRQHandler(void);
 
void              HAL_RCC_CSSCallback(void);

uint32_t          HAL_RCC_GetResetSource(void);


 



 



 



 







#line 259 "../Core/Inc/stm32l4xx_hal_conf.h"


#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio.h"
















 

 







 
#line 29 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio.h"



 



 

 



 


 
typedef struct
{
  uint32_t Pin;        
 

  uint32_t Mode;       
 

  uint32_t Pull;       
 

  uint32_t Speed;      
 

  uint32_t Alternate;  
 
} GPIO_InitTypeDef;



 
typedef enum
{
  GPIO_PIN_RESET = 0U,
  GPIO_PIN_SET
} GPIO_PinState;


 

 


 


 
#line 100 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio.h"




 









 
#line 128 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio.h"


 




 






 




 





 



 

 


 






 







 







 







 







 




 

 


 
#line 230 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio.h"



 



 





#line 256 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio.h"











 

 
#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio_ex.h"
















 

 







 
#line 29 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio_ex.h"



 




 

 
 


 



 

#line 142 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio_ex.h"


 


 
#line 155 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio_ex.h"



 







 





 






 






 





 





 






 




 





 





#line 228 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio_ex.h"



 







 




 







 






#line 379 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio_ex.h"

#line 509 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio_ex.h"

#line 649 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio_ex.h"

#line 800 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio_ex.h"

#line 945 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio_ex.h"



 



 

 


 



 
#line 970 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio_ex.h"











#line 988 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio_ex.h"

#line 998 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio_ex.h"

#line 1010 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio_ex.h"

#line 1023 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio_ex.h"

#line 1036 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio_ex.h"



 



 

 


 



 







#line 271 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio.h"

 


 




 

 
void              HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void              HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin);



 



 

 
GPIO_PinState     HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void              HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void              HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
HAL_StatusTypeDef HAL_GPIO_LockPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void              HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin);
void              HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);



 



 



 



 







#line 263 "../Core/Inc/stm32l4xx_hal_conf.h"


#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_dma.h"
















 

 







 
#line 29 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_dma.h"



 



 

 


 



 
typedef struct
{
  uint32_t Request;                   
 

  uint32_t Direction;                 

 

  uint32_t PeriphInc;                 
 

  uint32_t MemInc;                    
 

  uint32_t PeriphDataAlignment;       
 

  uint32_t MemDataAlignment;          
 

  uint32_t Mode;                      


 

  uint32_t Priority;                  
 
} DMA_InitTypeDef;



 
typedef enum
{
  HAL_DMA_STATE_RESET             = 0x00U,   
  HAL_DMA_STATE_READY             = 0x01U,   
  HAL_DMA_STATE_BUSY              = 0x02U,   
  HAL_DMA_STATE_TIMEOUT           = 0x03U,   
}HAL_DMA_StateTypeDef;



 
typedef enum
{
  HAL_DMA_FULL_TRANSFER      = 0x00U,     
  HAL_DMA_HALF_TRANSFER      = 0x01U      
}HAL_DMA_LevelCompleteTypeDef;




 
typedef enum
{
  HAL_DMA_XFER_CPLT_CB_ID          = 0x00U,     
  HAL_DMA_XFER_HALFCPLT_CB_ID      = 0x01U,     
  HAL_DMA_XFER_ERROR_CB_ID         = 0x02U,     
  HAL_DMA_XFER_ABORT_CB_ID         = 0x03U,     
  HAL_DMA_XFER_ALL_CB_ID           = 0x04U      
}HAL_DMA_CallbackIDTypeDef;



 
typedef struct __DMA_HandleTypeDef
{
  DMA_Channel_TypeDef    *Instance;                                                      

  DMA_InitTypeDef       Init;                                                            

  HAL_LockTypeDef       Lock;                                                            

  volatile HAL_DMA_StateTypeDef  State;                                                      

  void                  *Parent;                                                         

  void                  (* XferCpltCallback)(struct __DMA_HandleTypeDef * hdma);         

  void                  (* XferHalfCpltCallback)(struct __DMA_HandleTypeDef * hdma);     

  void                  (* XferErrorCallback)(struct __DMA_HandleTypeDef * hdma);        

  void                  (* XferAbortCallback)(struct __DMA_HandleTypeDef * hdma);        

  volatile uint32_t         ErrorCode;                                                       

  DMA_TypeDef           *DmaBaseAddress;                                                 

  uint32_t              ChannelIndex;                                                    

#line 152 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_dma.h"

}DMA_HandleTypeDef;


 

 



 



 
#line 174 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_dma.h"



 



 


#line 192 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_dma.h"



#line 431 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_dma.h"



 



 





 



 




 



 




 



 





 



 





 



 




 



 






 




 





 



 
#line 546 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_dma.h"


 



 

 


 




 






 






 



 





 

#line 602 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_dma.h"





 
#line 622 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_dma.h"





 
#line 642 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_dma.h"





 
#line 662 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_dma.h"












 














 












 











 











 






 




 






 



 



 
 
HAL_StatusTypeDef HAL_DMA_Init(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_DeInit (DMA_HandleTypeDef *hdma);


 



 
 
HAL_StatusTypeDef HAL_DMA_Start (DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMA_Start_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
HAL_StatusTypeDef HAL_DMA_Abort(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_Abort_IT(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_PollForTransfer(DMA_HandleTypeDef *hdma, HAL_DMA_LevelCompleteTypeDef CompleteLevel, uint32_t Timeout);
void HAL_DMA_IRQHandler(DMA_HandleTypeDef *hdma);
HAL_StatusTypeDef HAL_DMA_RegisterCallback(DMA_HandleTypeDef *hdma, HAL_DMA_CallbackIDTypeDef CallbackID, void (* pCallback)( DMA_HandleTypeDef * _hdma));
HAL_StatusTypeDef HAL_DMA_UnRegisterCallback(DMA_HandleTypeDef *hdma, HAL_DMA_CallbackIDTypeDef CallbackID);



 



 
 
HAL_DMA_StateTypeDef HAL_DMA_GetState(DMA_HandleTypeDef *hdma);
uint32_t             HAL_DMA_GetError(DMA_HandleTypeDef *hdma);


 



 

 


 















#line 820 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_dma.h"

























 

 



 



 





#line 267 "../Core/Inc/stm32l4xx_hal_conf.h"






#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_cortex.h"
















 

 







 
#line 29 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_cortex.h"



 




 

 


 





 
typedef struct
{
  uint8_t                Enable;                
 
  uint8_t                Number;                
 
  uint32_t               BaseAddress;            
  uint8_t                Size;                  
 
  uint8_t                SubRegionDisable;      
 
  uint8_t                TypeExtField;          
 
  uint8_t                AccessPermission;      
 
  uint8_t                DisableExec;           
 
  uint8_t                IsShareable;           
 
  uint8_t                IsCacheable;           
 
  uint8_t                IsBufferable;          
 
}MPU_Region_InitTypeDef;


 




 

 



 



 
#line 101 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_cortex.h"


 



 





 




 






 



 




 



 




 



 




 



 




 



 




 



 






 



 
#line 214 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_cortex.h"


 



 
#line 227 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_cortex.h"


 



 
#line 242 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_cortex.h"


 




 

 


 



 

 


 




 
 
void HAL_NVIC_SetPriorityGrouping(uint32_t PriorityGroup);
void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority);
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn);
void HAL_NVIC_DisableIRQ(IRQn_Type IRQn);
void HAL_NVIC_SystemReset(void);
uint32_t HAL_SYSTICK_Config(uint32_t TicksNumb);



 




 
 
uint32_t HAL_NVIC_GetPriorityGrouping(void);
void HAL_NVIC_GetPriority(IRQn_Type IRQn, uint32_t PriorityGroup, uint32_t* pPreemptPriority, uint32_t* pSubPriority);
uint32_t HAL_NVIC_GetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_SetPendingIRQ(IRQn_Type IRQn);
void HAL_NVIC_ClearPendingIRQ(IRQn_Type IRQn);
uint32_t HAL_NVIC_GetActive(IRQn_Type IRQn);
void HAL_SYSTICK_CLKSourceConfig(uint32_t CLKSource);
void HAL_SYSTICK_IRQHandler(void);
void HAL_SYSTICK_Callback(void);


void HAL_MPU_Enable(uint32_t MPU_Control);
void HAL_MPU_Disable(void);
void HAL_MPU_ConfigRegion(MPU_Region_InitTypeDef *MPU_Init);



 



 

  
 
 
 


 




































#line 358 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_cortex.h"

#line 367 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_cortex.h"

#line 396 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_cortex.h"






 

 



 



 








#line 275 "../Core/Inc/stm32l4xx_hal_conf.h"


#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"
















 

 







 
#line 29 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"

 
#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"
















 

 







 
#line 29 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"



 





 

 
 

 


 

 
 
 
 

 
 










 
 
#line 83 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"



 
 
 
 

 
 










 
 







 
 
 
 


 
 
 





 
 
 





 





 
 
 
 


 
 
 





 
 
 





 








 
 
 
 
 
 
 
 





 


 




 
 








 
 
#line 224 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"

 
 
#line 246 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"

 
 
#line 268 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"


 
 
 
 
 
 
#line 283 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"

 
 
 
 
 
 
 
 

 




 
 











 
#line 320 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"

 
 
#line 329 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"


 







 



 
 


 
#line 357 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"



 


 


 








 





 


 
#line 581 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"

 


 




 
#line 626 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"


 




 
#line 645 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"


 



 
 
 
 






 



 
#line 681 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"


 



 
 
 
 
 
 






 



 






 



 




 



 




 



 






 



 




 



 





 



 
#line 796 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"


 



 
#line 820 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"


 



 





 



 




 



 





 

#line 863 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"

#line 874 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"



 




 



 
#line 903 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"


 



 
#line 919 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"


 



 
#line 942 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"


 



 
#line 966 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"


 



 





 



 




 



 





 



 






 



 




 



 






 



 
#line 1041 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"


 



 





 



 





 



 
#line 1161 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"


 



 





 



 







 



 




 



 
#line 1207 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"


 



 
#line 1223 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"


 

#line 1285 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"



 
#line 1296 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"

#line 1304 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"

#line 1314 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"



 








 

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

 
 
 
 


 
 
 
 


 
 
 
 



 
 
 
 
 
 
 




 



 


 


 



 







 







 



 



 

















































 
#line 1475 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"

















































 
#line 1539 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"


























































 










































































 




































 
#line 1765 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"
























































































































































 
#line 1927 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"




















 





















 














 















 



#line 2021 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"

#line 2047 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"










 
#line 2068 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"

















 
#line 2099 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"













 




















 
#line 2141 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"
















 
#line 2164 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"

 


























 
#line 2200 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"













































 
#line 2259 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"












































 
#line 2320 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"



 



 


 


 



 
 
 
 






























 
#line 2391 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"
static __inline uint32_t LL_ADC_DMA_GetRegAddr(ADC_TypeDef *ADCx, uint32_t Register)
{
   
  (void)(Register);

   
  return (uint32_t) &(ADCx->DR);
}




 



 


































 
static __inline void LL_ADC_SetCommonClock(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t CommonClock)
{
  (((ADCxy_COMMON->CCR)) = ((((((ADCxy_COMMON->CCR))) & (~((0x3UL << (16U)) | (0xFUL << (18U))))) | (CommonClock))));
}























 
static __inline uint32_t LL_ADC_GetCommonClock(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (uint32_t)(((ADCxy_COMMON->CCR) & ((0x3UL << (16U)) | (0xFUL << (18U)))));
}
































 
static __inline void LL_ADC_SetCommonPathInternalCh(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t PathInternal)
{
  (((ADCxy_COMMON->CCR)) = ((((((ADCxy_COMMON->CCR))) & (~((0x1UL << (22U)) | (0x1UL << (23U)) | (0x1UL << (24U))))) | (PathInternal))));
}































 
static __inline void LL_ADC_SetCommonPathInternalChAdd(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t PathInternal)
{
  ((ADCxy_COMMON->CCR) |= (PathInternal));
}



















 
static __inline void LL_ADC_SetCommonPathInternalChRem(ADC_Common_TypeDef *ADCxy_COMMON, uint32_t PathInternal)
{
  ((ADCxy_COMMON->CCR) &= ~(PathInternal));
}

















 
static __inline uint32_t LL_ADC_GetCommonPathInternalCh(ADC_Common_TypeDef *ADCxy_COMMON)
{
  return (uint32_t)(((ADCxy_COMMON->CCR) & ((0x1UL << (22U)) | (0x1UL << (23U)) | (0x1UL << (24U)))));
}



 



 































 
static __inline void LL_ADC_SetCalibrationFactor(ADC_TypeDef *ADCx, uint32_t SingleDiff, uint32_t CalibrationFactor)
{
  (((ADCx->CALFACT)) = ((((((ADCx->CALFACT))) & (~(SingleDiff & ((0x7FUL << (16U)) | (0x7FUL << (0U)))))) | (CalibrationFactor << (((SingleDiff & (0x00010000UL)) >> ((16UL) - 4UL)) & ~(SingleDiff & (0x7FUL << (0U))))))));


}
















 
static __inline uint32_t LL_ADC_GetCalibrationFactor(ADC_TypeDef *ADCx, uint32_t SingleDiff)
{
   
   
   
   
  return (uint32_t)(((ADCx->CALFACT) & ((SingleDiff & ((0x7FUL << (16U)) | (0x7FUL << (0U)))))) >> ((SingleDiff & (0x00010000UL)) >>

                                                                                  ((16UL) - 4UL)));
}

















 
static __inline void LL_ADC_SetResolution(ADC_TypeDef *ADCx, uint32_t Resolution)
{
  (((ADCx->CFGR)) = ((((((ADCx->CFGR))) & (~((0x3UL << (3U))))) | (Resolution))));
}












 
static __inline uint32_t LL_ADC_GetResolution(ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CFGR) & ((0x3UL << (3U)))));
}















 
static __inline void LL_ADC_SetDataAlignment(ADC_TypeDef *ADCx, uint32_t DataAlignment)
{
  (((ADCx->CFGR)) = ((((((ADCx->CFGR))) & (~((0x1UL << (5U))))) | (DataAlignment))));
}










 
static __inline uint32_t LL_ADC_GetDataAlignment(ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CFGR) & ((0x1UL << (5U)))));
}



















































 
static __inline void LL_ADC_SetLowPowerMode(ADC_TypeDef *ADCx, uint32_t LowPowerMode)
{
  (((ADCx->CFGR)) = ((((((ADCx->CFGR))) & (~((0x1UL << (14U))))) | (LowPowerMode))));
}














































 
static __inline uint32_t LL_ADC_GetLowPowerMode(ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CFGR) & ((0x1UL << (14U)))));
}
















































































 
static __inline void LL_ADC_SetOffset(ADC_TypeDef *ADCx, uint32_t Offsety, uint32_t Channel, uint32_t OffsetLevel)
{
  volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->OFR1)) + ((Offsety) << 2UL))));

  (((*preg)) = ((((((*preg))) & (~((0x1UL << (31U)) | (0x1FUL << (26U)) | (0xFFFUL << (0U))))) | ((0x1UL << (31U)) | (Channel & ((0x1FUL << (26U)))) | OffsetLevel))));


}






































































 
static __inline uint32_t LL_ADC_GetOffsetChannel(ADC_TypeDef *ADCx, uint32_t Offsety)
{
  const volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->OFR1)) + ((Offsety) << 2UL))));

  return (uint32_t) ((*preg) & ((0x1FUL << (26U))));
}



















 
static __inline uint32_t LL_ADC_GetOffsetLevel(ADC_TypeDef *ADCx, uint32_t Offsety)
{
  const volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->OFR1)) + ((Offsety) << 2UL))));

  return (uint32_t) ((*preg) & ((0xFFFUL << (0U))));
}


























 
static __inline void LL_ADC_SetOffsetState(ADC_TypeDef *ADCx, uint32_t Offsety, uint32_t OffsetState)
{
  volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->OFR1)) + ((Offsety) << 2UL))));

  (((*preg)) = ((((((*preg))) & (~((0x1UL << (31U))))) | (OffsetState))));


}

















 
static __inline uint32_t LL_ADC_GetOffsetState(ADC_TypeDef *ADCx, uint32_t Offsety)
{
  const volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->OFR1)) + ((Offsety) << 2UL))));

  return (uint32_t) ((*preg) & ((0x1UL << (31U))));
}

#line 3134 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"



 



 







































 
static __inline void LL_ADC_REG_SetTriggerSource(ADC_TypeDef *ADCx, uint32_t TriggerSource)
{
  (((ADCx->CFGR)) = ((((((ADCx->CFGR))) & (~((0x3UL << (10U)) | (0xFUL << (6U))))) | (TriggerSource))));
}


































 
static __inline uint32_t LL_ADC_REG_GetTriggerSource(ADC_TypeDef *ADCx)
{
  volatile uint32_t TriggerSource = ((ADCx->CFGR) & ((0xFUL << (6U)) | (0x3UL << (10U))));

   
   
  uint32_t ShiftExten = ((TriggerSource & (0x3UL << (10U))) >> ((10UL) - 2UL));

   
   
  return ((TriggerSource
           & (((((0x00000000UL) & (0xFUL << (6U))) << (4U * 0UL)) | (((0xFUL << (6U))) << (4U * 1UL)) | (((0xFUL << (6U))) << (4U * 2UL)) | (((0xFUL << (6U))) << (4U * 3UL)) ) >> ShiftExten) & (0xFUL << (6U)))
          | ((((((0x00000000UL) & (0x3UL << (10U))) << (4U * 0UL)) | ((((0x1UL << (10U)))) << (4U * 1UL)) | ((((0x1UL << (10U)))) << (4U * 2UL)) | ((((0x1UL << (10U)))) << (4U * 3UL)) ) >> ShiftExten) & (0x3UL << (10U)))
         );
}











 
static __inline uint32_t LL_ADC_REG_IsTriggerSourceSWStart(ADC_TypeDef *ADCx)
{
  return ((((ADCx->CFGR) & ((0x3UL << (10U)))) == ((0x00000000UL) & (0x3UL << (10U)))) ? 1UL : 0UL);
}















 
static __inline void LL_ADC_REG_SetTriggerEdge(ADC_TypeDef *ADCx, uint32_t ExternalTriggerEdge)
{
  (((ADCx->CFGR)) = ((((((ADCx->CFGR))) & (~((0x3UL << (10U))))) | (ExternalTriggerEdge))));
}










 
static __inline uint32_t LL_ADC_REG_GetTriggerEdge(ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CFGR) & ((0x3UL << (10U)))));
}






















































 
static __inline void LL_ADC_REG_SetSequencerLength(ADC_TypeDef *ADCx, uint32_t SequencerNbRanks)
{
  (((ADCx->SQR1)) = ((((((ADCx->SQR1))) & (~((0xFUL << (0U))))) | (SequencerNbRanks))));
}

















































 
static __inline uint32_t LL_ADC_REG_GetSequencerLength(ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->SQR1) & ((0xFUL << (0U)))));
}



























 
static __inline void LL_ADC_REG_SetSequencerDiscont(ADC_TypeDef *ADCx, uint32_t SeqDiscont)
{
  (((ADCx->CFGR)) = ((((((ADCx->CFGR))) & (~((0x1UL << (16U)) | (0x7UL << (17U))))) | (SeqDiscont))));
}


















 
static __inline uint32_t LL_ADC_REG_GetSequencerDiscont(ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CFGR) & ((0x1UL << (16U)) | (0x7UL << (17U)))));
}






























































































 
static __inline void LL_ADC_REG_SetSequencerRanks(ADC_TypeDef *ADCx, uint32_t Rank, uint32_t Channel)
{
   
   
   
   
  volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->SQR1)) + ((((Rank & ((0x00000000UL) | (0x00000100UL) | (0x00000200UL) | (0x00000300UL))) >> (8UL))) << 2UL))));

  (((*preg)) = ((((((*preg))) & (~(((0x1FUL << (0U))) << (Rank & (((0x1FUL << (0U)))))))) | (((Channel & ((0x1FUL << (26U)))) >> (26UL)) << (Rank & (((0x1FUL << (0U)))))))));


}
































































































 
static __inline uint32_t LL_ADC_REG_GetSequencerRanks(ADC_TypeDef *ADCx, uint32_t Rank)
{
  const volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->SQR1)) + ((((Rank & ((0x00000000UL) | (0x00000100UL) | (0x00000200UL) | (0x00000300UL))) >> (8UL))) << 2UL))));

  return (uint32_t)((((*preg) & (((0x1FUL << (0U))) << (Rank & (((0x1FUL << (0U)))))))

                     >> (Rank & (((0x1FUL << (0U)))))) << (26UL)
                   );
}



















 
static __inline void LL_ADC_REG_SetContinuousMode(ADC_TypeDef *ADCx, uint32_t Continuous)
{
  (((ADCx->CFGR)) = ((((((ADCx->CFGR))) & (~((0x1UL << (13U))))) | (Continuous))));
}












 
static __inline uint32_t LL_ADC_REG_GetContinuousMode(ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CFGR) & ((0x1UL << (13U)))));
}



































 
static __inline void LL_ADC_REG_SetDMATransfer(ADC_TypeDef *ADCx, uint32_t DMATransfer)
{
  (((ADCx->CFGR)) = ((((((ADCx->CFGR))) & (~((0x1UL << (0U)) | (0x1UL << (1U))))) | (DMATransfer))));
}






























 
static __inline uint32_t LL_ADC_REG_GetDMATransfer(ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CFGR) & ((0x1UL << (0U)) | (0x1UL << (1U)))));
}

#line 3821 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"




















 
static __inline void LL_ADC_REG_SetOverrun(ADC_TypeDef *ADCx, uint32_t Overrun)
{
  (((ADCx->CFGR)) = ((((((ADCx->CFGR))) & (~((0x1UL << (12U))))) | (Overrun))));
}









 
static __inline uint32_t LL_ADC_REG_GetOverrun(ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CFGR) & ((0x1UL << (12U)))));
}



 



 







































 
static __inline void LL_ADC_INJ_SetTriggerSource(ADC_TypeDef *ADCx, uint32_t TriggerSource)
{
  (((ADCx->JSQR)) = ((((((ADCx->JSQR))) & (~((0xFUL << (2U)) | (0x3UL << (6U))))) | (TriggerSource))));
}


































 
static __inline uint32_t LL_ADC_INJ_GetTriggerSource(ADC_TypeDef *ADCx)
{
  volatile uint32_t TriggerSource = ((ADCx->JSQR) & ((0xFUL << (2U)) | (0x3UL << (6U))));

   
   
  uint32_t ShiftJexten = ((TriggerSource & (0x3UL << (6U))) >> (( 6UL) - 2UL));

   
   
  return ((TriggerSource
           & (((((0x00000000UL) & (0xFUL << (2U))) << (4U * 0UL)) | (((0xFUL << (2U))) << (4U * 1UL)) | (((0xFUL << (2U))) << (4U * 2UL)) | (((0xFUL << (2U))) << (4U * 3UL)) ) >> ShiftJexten) & (0xFUL << (2U)))
          | ((((((0x00000000UL) & (0x3UL << (6U))) << (4U * 0UL)) | ((((0x1UL << (6U)))) << (4U * 1UL)) | ((((0x1UL << (6U)))) << (4U * 2UL)) | ((((0x1UL << (6U)))) << (4U * 3UL)) ) >> ShiftJexten) & (0x3UL << (6U)))
         );
}











 
static __inline uint32_t LL_ADC_INJ_IsTriggerSourceSWStart(ADC_TypeDef *ADCx)
{
  return ((((ADCx->JSQR) & ((0x3UL << (6U)))) == ((0x00000000UL) & (0x3UL << (6U)))) ? 1UL : 0UL);
}















 
static __inline void LL_ADC_INJ_SetTriggerEdge(ADC_TypeDef *ADCx, uint32_t ExternalTriggerEdge)
{
  (((ADCx->JSQR)) = ((((((ADCx->JSQR))) & (~((0x3UL << (6U))))) | (ExternalTriggerEdge))));
}










 
static __inline uint32_t LL_ADC_INJ_GetTriggerEdge(ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->JSQR) & ((0x3UL << (6U)))));
}





















 
static __inline void LL_ADC_INJ_SetSequencerLength(ADC_TypeDef *ADCx, uint32_t SequencerNbRanks)
{
  (((ADCx->JSQR)) = ((((((ADCx->JSQR))) & (~((0x3UL << (0U))))) | (SequencerNbRanks))));
}
















 
static __inline uint32_t LL_ADC_INJ_GetSequencerLength(ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->JSQR) & ((0x3UL << (0U)))));
}













 
static __inline void LL_ADC_INJ_SetSequencerDiscont(ADC_TypeDef *ADCx, uint32_t SeqDiscont)
{
  (((ADCx->CFGR)) = ((((((ADCx->CFGR))) & (~((0x1UL << (20U))))) | (SeqDiscont))));
}










 
static __inline uint32_t LL_ADC_INJ_GetSequencerDiscont(ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CFGR) & ((0x1UL << (20U)))));
}

































































 
static __inline void LL_ADC_INJ_SetSequencerRanks(ADC_TypeDef *ADCx, uint32_t Rank, uint32_t Channel)
{
   
   
   
   
  (((ADCx->JSQR)) = ((((((ADCx->JSQR))) & (~((((0x1FUL << (26U))) >> (26UL)) << (Rank & (((0x1FUL << (0U)))))))) | (((Channel & ((0x1FUL << (26U)))) >> (26UL)) << (Rank & (((0x1FUL << (0U)))))))));


}




































































 
static __inline uint32_t LL_ADC_INJ_GetSequencerRanks(ADC_TypeDef *ADCx, uint32_t Rank)
{
  return (uint32_t)((((ADCx->JSQR) & ((((0x1FUL << (26U))) >> (26UL)) << (Rank & (((0x1FUL << (0U)))))))

                     >> (Rank & (((0x1FUL << (0U)))))) << (26UL)
                   );
}






























 
static __inline void LL_ADC_INJ_SetTrigAuto(ADC_TypeDef *ADCx, uint32_t TrigAuto)
{
  (((ADCx->CFGR)) = ((((((ADCx->CFGR))) & (~((0x1UL << (25U))))) | (TrigAuto))));
}









 
static __inline uint32_t LL_ADC_INJ_GetTrigAuto(ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CFGR) & ((0x1UL << (25U)))));
}









































 
static __inline void LL_ADC_INJ_SetQueueMode(ADC_TypeDef *ADCx, uint32_t QueueMode)
{
  (((ADCx->CFGR)) = ((((((ADCx->CFGR))) & (~((0x1UL << (21U)) | (0x1UL << (31U))))) | (QueueMode))));
}










 
static __inline uint32_t LL_ADC_INJ_GetQueueMode(ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CFGR) & ((0x1UL << (21U)) | (0x1UL << (31U)))));
}



























































































































































































































 
static __inline void LL_ADC_INJ_ConfigQueueContext(ADC_TypeDef *ADCx,
                                                   uint32_t TriggerSource,
                                                   uint32_t ExternalTriggerEdge,
                                                   uint32_t SequencerNbRanks,
                                                   uint32_t Rank1_Channel,
                                                   uint32_t Rank2_Channel,
                                                   uint32_t Rank3_Channel,
                                                   uint32_t Rank4_Channel)
{
   
   
   
   
   
   
  uint32_t is_trigger_not_sw = (uint32_t)((TriggerSource != (0x00000000UL)) ? 1UL : 0UL);
  (((ADCx->JSQR)) = ((((((ADCx->JSQR))) & (~((0xFUL << (2U)) | (0x3UL << (6U)) | (0x1FUL << (26U)) | (0x1FUL << (20U)) | (0x1FUL << (14U)) | (0x1FUL << (8U)) | (0x3UL << (0U))))) | ((TriggerSource & (0xFUL << (2U))) | (ExternalTriggerEdge * (is_trigger_not_sw)) | (((Rank4_Channel & ((0x1FUL << (26U)))) >> (26UL)) << (((0x00000300UL) | (26UL)) & (((0x1FUL << (0U)))))) | (((Rank3_Channel & ((0x1FUL << (26U)))) >> (26UL)) << (((0x00000200UL) | (20UL)) & (((0x1FUL << (0U)))))) | (((Rank2_Channel & ((0x1FUL << (26U)))) >> (26UL)) << (((0x00000100UL) | (14UL)) & (((0x1FUL << (0U)))))) | (((Rank1_Channel & ((0x1FUL << (26U)))) >> (26UL)) << (((0x00000000UL) | ( 8UL)) & (((0x1FUL << (0U)))))) | SequencerNbRanks))));
#line 4607 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"
}



 



 



































































































 
static __inline void LL_ADC_SetChannelSamplingTime(ADC_TypeDef *ADCx, uint32_t Channel, uint32_t SamplingTime)
{
   
   
   
   
  volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->SMPR1)) + ((((Channel & ((0x00000000UL) | (0x02000000UL))) >> (25UL))) << 2UL))));

  (((*preg)) = ((((((*preg))) & (~((0x7UL << (0U)) << ((Channel & (0x01F00000UL)) >> (20UL))))) | (SamplingTime << ((Channel & (0x01F00000UL)) >> (20UL))))));


}



















































































 
static __inline uint32_t LL_ADC_GetChannelSamplingTime(ADC_TypeDef *ADCx, uint32_t Channel)
{
  const volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->SMPR1)) + ((((Channel & ((0x00000000UL) | (0x02000000UL))) >> (25UL))) << 2UL))));

  return (uint32_t)(((*preg) & ((0x7UL << (0U)) << ((Channel & (0x01F00000UL)) >> (20UL))))

                    >> ((Channel & (0x01F00000UL)) >> (20UL))
                   );
}
















































 
static __inline void LL_ADC_SetChannelSingleDiff(ADC_TypeDef *ADCx, uint32_t Channel, uint32_t SingleDiff)
{
   
   
   
  (((ADCx->DIFSEL)) = ((((((ADCx->DIFSEL))) & (~(Channel & (((0x7FFFFUL << (0U))))))) | ((Channel & (((0x7FFFFUL << (0U))))) & ((0x7FFFFUL << (0U)) >> (SingleDiff & ((0x10UL << (0U)) | (0x08UL << (0U)))))))));


}








































 
static __inline uint32_t LL_ADC_GetChannelSingleDiff(ADC_TypeDef *ADCx, uint32_t Channel)
{
  return (uint32_t)(((ADCx->DIFSEL) & ((Channel & (((0x7FFFFUL << (0U))))))));
}



 



 
















































































































































 
static __inline void LL_ADC_SetAnalogWDMonitChannels(ADC_TypeDef *ADCx, uint32_t AWDy, uint32_t AWDChannelGroup)
{
   
   
   
   
  volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->CFGR)) + ((((AWDy & ((0x00000000UL) | (0x00100000UL) | (0x00200000UL))) >> (20UL)) + ((AWDy & ((0x00001UL << (0U)))) * (0x00000024UL))) << 2UL))));


  (((*preg)) = ((((((*preg))) & (~((AWDy & (((0x1FUL << (26U)) | (0x1UL << (24U)) | (0x1UL << (23U)) | (0x1UL << (22U))) | ((0x7FFFFUL << (0U)))))))) | (AWDChannelGroup & AWDy))));


}


























































































































 
static __inline uint32_t LL_ADC_GetAnalogWDMonitChannels(ADC_TypeDef *ADCx, uint32_t AWDy)
{
  const volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->CFGR)) + ((((AWDy & ((0x00000000UL) | (0x00100000UL) | (0x00200000UL))) >> (20UL)) + ((AWDy & ((0x00001UL << (0U)))) * (0x00000024UL))) << 2UL))));


  uint32_t AnalogWDMonitChannels = (((*preg) & (AWDy)) & (((0x1FUL << (26U)) | (0x1UL << (24U)) | (0x1UL << (23U)) | (0x1UL << (22U))) | ((0x7FFFFUL << (0U)))));

   
   
   
   
  if (AnalogWDMonitChannels != 0UL)
  {
    if (AWDy == (((0x1FUL << (26U)) | (0x1UL << (24U)) | (0x1UL << (23U)) | (0x1UL << (22U))) | (0x00000000UL)))
    {
      if ((AnalogWDMonitChannels & (0x1UL << (22U))) == 0UL)
      {
         
        AnalogWDMonitChannels = ((AnalogWDMonitChannels
                                  | (((0x7FFFFUL << (0U))))
                                 )
                                 & (~((0x1FUL << (26U))))
                                );
      }
      else
      {
         
        AnalogWDMonitChannels = (AnalogWDMonitChannels
                                 | ((0x00001UL << (0U)) << (AnalogWDMonitChannels >> (26U)))
                                );
      }
    }
    else
    {
      if ((AnalogWDMonitChannels & ((0x7FFFFUL << (0U)))) == ((0x7FFFFUL << (0U))))
      {
         
        AnalogWDMonitChannels = (((0x7FFFFUL << (0U)))
                                 | (((0x1UL << (24U)) | (0x1UL << (23U))))
                                );
      }
      else
      {
         
         
        AnalogWDMonitChannels = (AnalogWDMonitChannels
                                 | ((0x1UL << (24U)) | (0x1UL << (23U)) | (0x1UL << (22U)))
                                 | (((((AnalogWDMonitChannels) & ((0x7FFFFUL << (0U)))) == 0UL) ? ( ((AnalogWDMonitChannels) & ((0x1FUL << (26U)))) >> (26UL) ) : ( (uint32_t)(__clz(__rbit((AnalogWDMonitChannels)))) ) ) << (26U))
                                );
      }
    }
  }

  return AnalogWDMonitChannels;
}




















































 
static __inline void LL_ADC_ConfigAnalogWDThresholds(ADC_TypeDef *ADCx, uint32_t AWDy, uint32_t AWDThresholdHighValue,
                                                     uint32_t AWDThresholdLowValue)
{
   
   
   
   
   
  volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->TR1)) + ((((AWDy & (((0x00000000UL)) | ((0x00100000UL)) | ((0x00200000UL)))) >> ((20UL)))) << 2UL))));

  (((*preg)) = ((((((*preg))) & (~((0xFFFUL << (16U)) | (0xFFFUL << (0U))))) | ((AWDThresholdHighValue << (16UL)) | AWDThresholdLowValue))));


}






















































 
static __inline void LL_ADC_SetAnalogWDThresholds(ADC_TypeDef *ADCx, uint32_t AWDy, uint32_t AWDThresholdsHighLow,
                                                  uint32_t AWDThresholdValue)
{
   
   
   
   
   
  volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->TR1)) + ((((AWDy & (((0x00000000UL)) | ((0x00100000UL)) | ((0x00200000UL)))) >> ((20UL)))) << 2UL))));


  (((*preg)) = ((((((*preg))) & (~(AWDThresholdsHighLow))) | (AWDThresholdValue << ((AWDThresholdsHighLow & (0x00010000UL)) >> ((16UL) - 4UL))))));


}




























 
static __inline uint32_t LL_ADC_GetAnalogWDThresholds(ADC_TypeDef *ADCx, uint32_t AWDy, uint32_t AWDThresholdsHighLow)
{
  const volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->TR1)) + ((((AWDy & (((0x00000000UL)) | ((0x00100000UL)) | ((0x00200000UL)))) >> ((20UL)))) << 2UL))));


  return (uint32_t)(((*preg) & ((AWDThresholdsHighLow | (0xFFFUL << (0U)))))

                    >> (((AWDThresholdsHighLow & (0x00010000UL)) >> ((16UL) - 4UL))
                        & ~(AWDThresholdsHighLow & (0xFFFUL << (0U)))));
}



 



 

























 
static __inline void LL_ADC_SetOverSamplingScope(ADC_TypeDef *ADCx, uint32_t OvsScope)
{
  (((ADCx->CFGR2)) = ((((((ADCx->CFGR2))) & (~((0x1UL << (0U)) | (0x1UL << (1U)) | (0x1UL << (10U))))) | (OvsScope))));
}




















 
static __inline uint32_t LL_ADC_GetOverSamplingScope(ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CFGR2) & ((0x1UL << (0U)) | (0x1UL << (1U)) | (0x1UL << (10U)))));
}






















 
static __inline void LL_ADC_SetOverSamplingDiscont(ADC_TypeDef *ADCx, uint32_t OverSamplingDiscont)
{
  (((ADCx->CFGR2)) = ((((((ADCx->CFGR2))) & (~((0x1UL << (9U))))) | (OverSamplingDiscont))));
}














 
static __inline uint32_t LL_ADC_GetOverSamplingDiscont(ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CFGR2) & ((0x1UL << (9U)))));
}


































 
static __inline void LL_ADC_ConfigOverSamplingRatioShift(ADC_TypeDef *ADCx, uint32_t Ratio, uint32_t Shift)
{
  (((ADCx->CFGR2)) = ((((((ADCx->CFGR2))) & (~(((0xFUL << (5U)) | (0x7UL << (2U)))))) | ((Shift | Ratio)))));
}















 
static __inline uint32_t LL_ADC_GetOverSamplingRatio(ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CFGR2) & ((0x7UL << (2U)))));
}
















 
static __inline uint32_t LL_ADC_GetOverSamplingShift(ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->CFGR2) & ((0xFUL << (5U)))));
}



 



 

#line 5863 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"



 


 
 
 
static __inline void LL_ADC_REG_SetTrigSource(ADC_TypeDef *ADCx, uint32_t TriggerSource)
{
  LL_ADC_REG_SetTriggerSource(ADCx, TriggerSource);
}
static __inline void LL_ADC_INJ_SetTrigSource(ADC_TypeDef *ADCx, uint32_t TriggerSource)
{
  LL_ADC_INJ_SetTriggerSource(ADCx, TriggerSource);
}



 



 













 
static __inline void LL_ADC_EnableDeepPowerDown(ADC_TypeDef *ADCx)
{
   
   
   
  (((ADCx->CR)) = ((((((ADCx->CR))) & (~(((0x1UL << (31U)) | (0x1UL << (5U)) | (0x1UL << (4U)) | (0x1UL << (3U)) | (0x1UL << (2U)) | (0x1UL << (1U)) | (0x1UL << (0U)))))) | ((0x1UL << (29U))))));


}













 
static __inline void LL_ADC_DisableDeepPowerDown(ADC_TypeDef *ADCx)
{
   
   
   
  ((ADCx->CR) &= ~(((0x1UL << (29U)) | ((0x1UL << (31U)) | (0x1UL << (5U)) | (0x1UL << (4U)) | (0x1UL << (3U)) | (0x1UL << (2U)) | (0x1UL << (1U)) | (0x1UL << (0U))))));
}






 
static __inline uint32_t LL_ADC_IsDeepPowerDownEnabled(ADC_TypeDef *ADCx)
{
  return ((((ADCx->CR) & ((0x1UL << (29U)))) == ((0x1UL << (29U)))) ? 1UL : 0UL);
}














 
static __inline void LL_ADC_EnableInternalRegulator(ADC_TypeDef *ADCx)
{
   
   
   
  (((ADCx->CR)) = ((((((ADCx->CR))) & (~(((0x1UL << (31U)) | (0x1UL << (5U)) | (0x1UL << (4U)) | (0x1UL << (3U)) | (0x1UL << (2U)) | (0x1UL << (1U)) | (0x1UL << (0U)))))) | ((0x1UL << (28U))))));


}









 
static __inline void LL_ADC_DisableInternalRegulator(ADC_TypeDef *ADCx)
{
  ((ADCx->CR) &= ~(((0x1UL << (28U)) | ((0x1UL << (31U)) | (0x1UL << (5U)) | (0x1UL << (4U)) | (0x1UL << (3U)) | (0x1UL << (2U)) | (0x1UL << (1U)) | (0x1UL << (0U))))));
}






 
static __inline uint32_t LL_ADC_IsInternalRegulatorEnabled(ADC_TypeDef *ADCx)
{
  return ((((ADCx->CR) & ((0x1UL << (28U)))) == ((0x1UL << (28U)))) ? 1UL : 0UL);
}
















 
static __inline void LL_ADC_Enable(ADC_TypeDef *ADCx)
{
   
   
   
  (((ADCx->CR)) = ((((((ADCx->CR))) & (~(((0x1UL << (31U)) | (0x1UL << (5U)) | (0x1UL << (4U)) | (0x1UL << (3U)) | (0x1UL << (2U)) | (0x1UL << (1U)) | (0x1UL << (0U)))))) | ((0x1UL << (0U))))));


}










 
static __inline void LL_ADC_Disable(ADC_TypeDef *ADCx)
{
   
   
   
  (((ADCx->CR)) = ((((((ADCx->CR))) & (~(((0x1UL << (31U)) | (0x1UL << (5U)) | (0x1UL << (4U)) | (0x1UL << (3U)) | (0x1UL << (2U)) | (0x1UL << (1U)) | (0x1UL << (0U)))))) | ((0x1UL << (1U))))));


}









 
static __inline uint32_t LL_ADC_IsEnabled(ADC_TypeDef *ADCx)
{
  return ((((ADCx->CR) & ((0x1UL << (0U)))) == ((0x1UL << (0U)))) ? 1UL : 0UL);
}






 
static __inline uint32_t LL_ADC_IsDisableOngoing(ADC_TypeDef *ADCx)
{
  return ((((ADCx->CR) & ((0x1UL << (1U)))) == ((0x1UL << (1U)))) ? 1UL : 0UL);
}























 
static __inline void LL_ADC_StartCalibration(ADC_TypeDef *ADCx, uint32_t SingleDiff)
{
   
   
   
  (((ADCx->CR)) = ((((((ADCx->CR))) & (~((0x1UL << (30U)) | ((0x1UL << (31U)) | (0x1UL << (5U)) | (0x1UL << (4U)) | (0x1UL << (3U)) | (0x1UL << (2U)) | (0x1UL << (1U)) | (0x1UL << (0U)))))) | ((0x1UL << (31U)) | (SingleDiff & ((0x1UL << (30U))))))));


}






 
static __inline uint32_t LL_ADC_IsCalibrationOnGoing(ADC_TypeDef *ADCx)
{
  return ((((ADCx->CR) & ((0x1UL << (31U)))) == ((0x1UL << (31U)))) ? 1UL : 0UL);
}



 



 


















 
static __inline void LL_ADC_REG_StartConversion(ADC_TypeDef *ADCx)
{
   
   
   
  (((ADCx->CR)) = ((((((ADCx->CR))) & (~(((0x1UL << (31U)) | (0x1UL << (5U)) | (0x1UL << (4U)) | (0x1UL << (3U)) | (0x1UL << (2U)) | (0x1UL << (1U)) | (0x1UL << (0U)))))) | ((0x1UL << (2U))))));


}










 
static __inline void LL_ADC_REG_StopConversion(ADC_TypeDef *ADCx)
{
   
   
   
  (((ADCx->CR)) = ((((((ADCx->CR))) & (~(((0x1UL << (31U)) | (0x1UL << (5U)) | (0x1UL << (4U)) | (0x1UL << (3U)) | (0x1UL << (2U)) | (0x1UL << (1U)) | (0x1UL << (0U)))))) | ((0x1UL << (4U))))));


}






 
static __inline uint32_t LL_ADC_REG_IsConversionOngoing(ADC_TypeDef *ADCx)
{
  return ((((ADCx->CR) & ((0x1UL << (2U)))) == ((0x1UL << (2U)))) ? 1UL : 0UL);
}






 
static __inline uint32_t LL_ADC_REG_IsStopConversionOngoing(ADC_TypeDef *ADCx)
{
  return ((((ADCx->CR) & ((0x1UL << (4U)))) == ((0x1UL << (4U)))) ? 1UL : 0UL);
}









 
static __inline uint32_t LL_ADC_REG_ReadConversionData32(ADC_TypeDef *ADCx)
{
  return (uint32_t)(((ADCx->DR) & ((0xFFFFUL << (0U)))));
}










 
static __inline uint16_t LL_ADC_REG_ReadConversionData12(ADC_TypeDef *ADCx)
{
  return (uint16_t)(((ADCx->DR) & ((0xFFFFUL << (0U)))));
}










 
static __inline uint16_t LL_ADC_REG_ReadConversionData10(ADC_TypeDef *ADCx)
{
  return (uint16_t)(((ADCx->DR) & ((0xFFFFUL << (0U)))));
}










 
static __inline uint8_t LL_ADC_REG_ReadConversionData8(ADC_TypeDef *ADCx)
{
  return (uint8_t)(((ADCx->DR) & ((0xFFFFUL << (0U)))));
}










 
static __inline uint8_t LL_ADC_REG_ReadConversionData6(ADC_TypeDef *ADCx)
{
  return (uint8_t)(((ADCx->DR) & ((0xFFFFUL << (0U)))));
}

#line 6290 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"



 



 


















 
static __inline void LL_ADC_INJ_StartConversion(ADC_TypeDef *ADCx)
{
   
   
   
  (((ADCx->CR)) = ((((((ADCx->CR))) & (~(((0x1UL << (31U)) | (0x1UL << (5U)) | (0x1UL << (4U)) | (0x1UL << (3U)) | (0x1UL << (2U)) | (0x1UL << (1U)) | (0x1UL << (0U)))))) | ((0x1UL << (3U))))));


}










 
static __inline void LL_ADC_INJ_StopConversion(ADC_TypeDef *ADCx)
{
   
   
   
  (((ADCx->CR)) = ((((((ADCx->CR))) & (~(((0x1UL << (31U)) | (0x1UL << (5U)) | (0x1UL << (4U)) | (0x1UL << (3U)) | (0x1UL << (2U)) | (0x1UL << (1U)) | (0x1UL << (0U)))))) | ((0x1UL << (5U))))));


}






 
static __inline uint32_t LL_ADC_INJ_IsConversionOngoing(ADC_TypeDef *ADCx)
{
  return ((((ADCx->CR) & ((0x1UL << (3U)))) == ((0x1UL << (3U)))) ? 1UL : 0UL);
}






 
static __inline uint32_t LL_ADC_INJ_IsStopConversionOngoing(ADC_TypeDef *ADCx)
{
  return ((((ADCx->CR) & ((0x1UL << (5U)))) == ((0x1UL << (5U)))) ? 1UL : 0UL);
}

















 
static __inline uint32_t LL_ADC_INJ_ReadConversionData32(ADC_TypeDef *ADCx, uint32_t Rank)
{
  const volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->JDR1)) + ((((Rank & ((0x00000000UL) | (0x00000100UL) | (0x00000200UL) | (0x00000300UL))) >> (8UL))) << 2UL))));

  return (uint32_t)(((*preg) & ((0xFFFFUL << (0U))))

                   );
}


















 
static __inline uint16_t LL_ADC_INJ_ReadConversionData12(ADC_TypeDef *ADCx, uint32_t Rank)
{
  const volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->JDR1)) + ((((Rank & ((0x00000000UL) | (0x00000100UL) | (0x00000200UL) | (0x00000300UL))) >> (8UL))) << 2UL))));

  return (uint16_t)(((*preg) & ((0xFFFFUL << (0U))))

                   );
}


















 
static __inline uint16_t LL_ADC_INJ_ReadConversionData10(ADC_TypeDef *ADCx, uint32_t Rank)
{
  const volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->JDR1)) + ((((Rank & ((0x00000000UL) | (0x00000100UL) | (0x00000200UL) | (0x00000300UL))) >> (8UL))) << 2UL))));

  return (uint16_t)(((*preg) & ((0xFFFFUL << (0U))))

                   );
}


















 
static __inline uint8_t LL_ADC_INJ_ReadConversionData8(ADC_TypeDef *ADCx, uint32_t Rank)
{
  const volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->JDR1)) + ((((Rank & ((0x00000000UL) | (0x00000100UL) | (0x00000200UL) | (0x00000300UL))) >> (8UL))) << 2UL))));

  return (uint8_t)(((*preg) & ((0xFFFFUL << (0U))))

                  );
}


















 
static __inline uint8_t LL_ADC_INJ_ReadConversionData6(ADC_TypeDef *ADCx, uint32_t Rank)
{
  const volatile uint32_t *preg = ((volatile uint32_t *)((uint32_t) ((uint32_t)(&(ADCx->JDR1)) + ((((Rank & ((0x00000000UL) | (0x00000100UL) | (0x00000200UL) | (0x00000300UL))) >> (8UL))) << 2UL))));

  return (uint8_t)(((*preg) & ((0xFFFFUL << (0U))))

                  );
}



 



 









 
static __inline uint32_t LL_ADC_IsActiveFlag_ADRDY(ADC_TypeDef *ADCx)
{
  return ((((ADCx->ISR) & ((0x1UL << (0U)))) == ((0x1UL << (0U)))) ? 1UL : 0UL);
}






 
static __inline uint32_t LL_ADC_IsActiveFlag_EOC(ADC_TypeDef *ADCx)
{
  return ((((ADCx->ISR) & ((0x1UL << (2U)))) == ((0x1UL << (2U)))) ? 1UL : 0UL);
}






 
static __inline uint32_t LL_ADC_IsActiveFlag_EOS(ADC_TypeDef *ADCx)
{
  return ((((ADCx->ISR) & ((0x1UL << (3U)))) == ((0x1UL << (3U)))) ? 1UL : 0UL);
}






 
static __inline uint32_t LL_ADC_IsActiveFlag_OVR(ADC_TypeDef *ADCx)
{
  return ((((ADCx->ISR) & ((0x1UL << (4U)))) == ((0x1UL << (4U)))) ? 1UL : 0UL);
}






 
static __inline uint32_t LL_ADC_IsActiveFlag_EOSMP(ADC_TypeDef *ADCx)
{
  return ((((ADCx->ISR) & ((0x1UL << (1U)))) == ((0x1UL << (1U)))) ? 1UL : 0UL);
}






 
static __inline uint32_t LL_ADC_IsActiveFlag_JEOC(ADC_TypeDef *ADCx)
{
  return ((((ADCx->ISR) & ((0x1UL << (5U)))) == ((0x1UL << (5U)))) ? 1UL : 0UL);
}






 
static __inline uint32_t LL_ADC_IsActiveFlag_JEOS(ADC_TypeDef *ADCx)
{
  return ((((ADCx->ISR) & ((0x1UL << (6U)))) == ((0x1UL << (6U)))) ? 1UL : 0UL);
}






 
static __inline uint32_t LL_ADC_IsActiveFlag_JQOVF(ADC_TypeDef *ADCx)
{
  return ((((ADCx->ISR) & ((0x1UL << (10U)))) == ((0x1UL << (10U)))) ? 1UL : 0UL);
}






 
static __inline uint32_t LL_ADC_IsActiveFlag_AWD1(ADC_TypeDef *ADCx)
{
  return ((((ADCx->ISR) & ((0x1UL << (7U)))) == ((0x1UL << (7U)))) ? 1UL : 0UL);
}






 
static __inline uint32_t LL_ADC_IsActiveFlag_AWD2(ADC_TypeDef *ADCx)
{
  return ((((ADCx->ISR) & ((0x1UL << (8U)))) == ((0x1UL << (8U)))) ? 1UL : 0UL);
}






 
static __inline uint32_t LL_ADC_IsActiveFlag_AWD3(ADC_TypeDef *ADCx)
{
  return ((((ADCx->ISR) & ((0x1UL << (9U)))) == ((0x1UL << (9U)))) ? 1UL : 0UL);
}









 
static __inline void LL_ADC_ClearFlag_ADRDY(ADC_TypeDef *ADCx)
{
  ((ADCx->ISR) = ((0x1UL << (0U))));
}






 
static __inline void LL_ADC_ClearFlag_EOC(ADC_TypeDef *ADCx)
{
  ((ADCx->ISR) = ((0x1UL << (2U))));
}






 
static __inline void LL_ADC_ClearFlag_EOS(ADC_TypeDef *ADCx)
{
  ((ADCx->ISR) = ((0x1UL << (3U))));
}






 
static __inline void LL_ADC_ClearFlag_OVR(ADC_TypeDef *ADCx)
{
  ((ADCx->ISR) = ((0x1UL << (4U))));
}






 
static __inline void LL_ADC_ClearFlag_EOSMP(ADC_TypeDef *ADCx)
{
  ((ADCx->ISR) = ((0x1UL << (1U))));
}






 
static __inline void LL_ADC_ClearFlag_JEOC(ADC_TypeDef *ADCx)
{
  ((ADCx->ISR) = ((0x1UL << (5U))));
}






 
static __inline void LL_ADC_ClearFlag_JEOS(ADC_TypeDef *ADCx)
{
  ((ADCx->ISR) = ((0x1UL << (6U))));
}






 
static __inline void LL_ADC_ClearFlag_JQOVF(ADC_TypeDef *ADCx)
{
  ((ADCx->ISR) = ((0x1UL << (10U))));
}






 
static __inline void LL_ADC_ClearFlag_AWD1(ADC_TypeDef *ADCx)
{
  ((ADCx->ISR) = ((0x1UL << (7U))));
}






 
static __inline void LL_ADC_ClearFlag_AWD2(ADC_TypeDef *ADCx)
{
  ((ADCx->ISR) = ((0x1UL << (8U))));
}






 
static __inline void LL_ADC_ClearFlag_AWD3(ADC_TypeDef *ADCx)
{
  ((ADCx->ISR) = ((0x1UL << (9U))));
}

#line 7024 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"



 



 






 
static __inline void LL_ADC_EnableIT_ADRDY(ADC_TypeDef *ADCx)
{
  ((ADCx->IER) |= ((0x1UL << (0U))));
}






 
static __inline void LL_ADC_EnableIT_EOC(ADC_TypeDef *ADCx)
{
  ((ADCx->IER) |= ((0x1UL << (2U))));
}






 
static __inline void LL_ADC_EnableIT_EOS(ADC_TypeDef *ADCx)
{
  ((ADCx->IER) |= ((0x1UL << (3U))));
}






 
static __inline void LL_ADC_EnableIT_OVR(ADC_TypeDef *ADCx)
{
  ((ADCx->IER) |= ((0x1UL << (4U))));
}






 
static __inline void LL_ADC_EnableIT_EOSMP(ADC_TypeDef *ADCx)
{
  ((ADCx->IER) |= ((0x1UL << (1U))));
}






 
static __inline void LL_ADC_EnableIT_JEOC(ADC_TypeDef *ADCx)
{
  ((ADCx->IER) |= ((0x1UL << (5U))));
}






 
static __inline void LL_ADC_EnableIT_JEOS(ADC_TypeDef *ADCx)
{
  ((ADCx->IER) |= ((0x1UL << (6U))));
}






 
static __inline void LL_ADC_EnableIT_JQOVF(ADC_TypeDef *ADCx)
{
  ((ADCx->IER) |= ((0x1UL << (10U))));
}






 
static __inline void LL_ADC_EnableIT_AWD1(ADC_TypeDef *ADCx)
{
  ((ADCx->IER) |= ((0x1UL << (7U))));
}






 
static __inline void LL_ADC_EnableIT_AWD2(ADC_TypeDef *ADCx)
{
  ((ADCx->IER) |= ((0x1UL << (8U))));
}






 
static __inline void LL_ADC_EnableIT_AWD3(ADC_TypeDef *ADCx)
{
  ((ADCx->IER) |= ((0x1UL << (9U))));
}






 
static __inline void LL_ADC_DisableIT_ADRDY(ADC_TypeDef *ADCx)
{
  ((ADCx->IER) &= ~((0x1UL << (0U))));
}






 
static __inline void LL_ADC_DisableIT_EOC(ADC_TypeDef *ADCx)
{
  ((ADCx->IER) &= ~((0x1UL << (2U))));
}






 
static __inline void LL_ADC_DisableIT_EOS(ADC_TypeDef *ADCx)
{
  ((ADCx->IER) &= ~((0x1UL << (3U))));
}






 
static __inline void LL_ADC_DisableIT_OVR(ADC_TypeDef *ADCx)
{
  ((ADCx->IER) &= ~((0x1UL << (4U))));
}






 
static __inline void LL_ADC_DisableIT_EOSMP(ADC_TypeDef *ADCx)
{
  ((ADCx->IER) &= ~((0x1UL << (1U))));
}






 
static __inline void LL_ADC_DisableIT_JEOC(ADC_TypeDef *ADCx)
{
  ((ADCx->IER) &= ~((0x1UL << (5U))));
}






 
static __inline void LL_ADC_DisableIT_JEOS(ADC_TypeDef *ADCx)
{
  ((ADCx->IER) &= ~((0x1UL << (6U))));
}






 
static __inline void LL_ADC_DisableIT_JQOVF(ADC_TypeDef *ADCx)
{
  ((ADCx->IER) &= ~((0x1UL << (10U))));
}






 
static __inline void LL_ADC_DisableIT_AWD1(ADC_TypeDef *ADCx)
{
  ((ADCx->IER) &= ~((0x1UL << (7U))));
}






 
static __inline void LL_ADC_DisableIT_AWD2(ADC_TypeDef *ADCx)
{
  ((ADCx->IER) &= ~((0x1UL << (8U))));
}






 
static __inline void LL_ADC_DisableIT_AWD3(ADC_TypeDef *ADCx)
{
  ((ADCx->IER) &= ~((0x1UL << (9U))));
}







 
static __inline uint32_t LL_ADC_IsEnabledIT_ADRDY(ADC_TypeDef *ADCx)
{
  return ((((ADCx->IER) & ((0x1UL << (0U)))) == ((0x1UL << (0U)))) ? 1UL : 0UL);
}







 
static __inline uint32_t LL_ADC_IsEnabledIT_EOC(ADC_TypeDef *ADCx)
{
  return ((((ADCx->IER) & ((0x1UL << (2U)))) == ((0x1UL << (2U)))) ? 1UL : 0UL);
}







 
static __inline uint32_t LL_ADC_IsEnabledIT_EOS(ADC_TypeDef *ADCx)
{
  return ((((ADCx->IER) & ((0x1UL << (3U)))) == ((0x1UL << (3U)))) ? 1UL : 0UL);
}







 
static __inline uint32_t LL_ADC_IsEnabledIT_OVR(ADC_TypeDef *ADCx)
{
  return ((((ADCx->IER) & ((0x1UL << (4U)))) == ((0x1UL << (4U)))) ? 1UL : 0UL);
}







 
static __inline uint32_t LL_ADC_IsEnabledIT_EOSMP(ADC_TypeDef *ADCx)
{
  return ((((ADCx->IER) & ((0x1UL << (1U)))) == ((0x1UL << (1U)))) ? 1UL : 0UL);
}







 
static __inline uint32_t LL_ADC_IsEnabledIT_JEOC(ADC_TypeDef *ADCx)
{
  return ((((ADCx->IER) & ((0x1UL << (5U)))) == ((0x1UL << (5U)))) ? 1UL : 0UL);
}







 
static __inline uint32_t LL_ADC_IsEnabledIT_JEOS(ADC_TypeDef *ADCx)
{
  return ((((ADCx->IER) & ((0x1UL << (6U)))) == ((0x1UL << (6U)))) ? 1UL : 0UL);
}







 
static __inline uint32_t LL_ADC_IsEnabledIT_JQOVF(ADC_TypeDef *ADCx)
{
  return ((((ADCx->IER) & ((0x1UL << (10U)))) == ((0x1UL << (10U)))) ? 1UL : 0UL);
}







 
static __inline uint32_t LL_ADC_IsEnabledIT_AWD1(ADC_TypeDef *ADCx)
{
  return ((((ADCx->IER) & ((0x1UL << (7U)))) == ((0x1UL << (7U)))) ? 1UL : 0UL);
}







 
static __inline uint32_t LL_ADC_IsEnabledIT_AWD2(ADC_TypeDef *ADCx)
{
  return ((((ADCx->IER) & ((0x1UL << (8U)))) == ((0x1UL << (8U)))) ? 1UL : 0UL);
}







 
static __inline uint32_t LL_ADC_IsEnabledIT_AWD3(ADC_TypeDef *ADCx)
{
  return ((((ADCx->IER) & ((0x1UL << (9U)))) == ((0x1UL << (9U)))) ? 1UL : 0UL);
}



 

#line 7441 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_adc.h"



 



 





 





#line 32 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"



 



 

 


 



 
typedef struct
{
  uint32_t Ratio;                         
 

  uint32_t RightBitShift;                 
 

  uint32_t TriggeredMode;                 
 

  uint32_t OversamplingStopReset;         





 

} ADC_OversamplingTypeDef;
















 
typedef struct
{
  uint32_t ClockPrescaler;        








 

  uint32_t Resolution;            
 

  uint32_t DataAlign;             

 

  uint32_t ScanConvMode;          





 

  uint32_t EOCSelection;          
 

  FunctionalState LowPowerAutoWait; 









 

  FunctionalState ContinuousConvMode; 

 

  uint32_t NbrOfConversion;       



 

  FunctionalState DiscontinuousConvMode; 



 

  uint32_t NbrOfDiscConversion;   

 

  uint32_t ExternalTrigConv;      


 

  uint32_t ExternalTrigConvEdge;  

 

  FunctionalState DMAContinuousRequests; 


 

  uint32_t Overrun;               








 

  FunctionalState OversamplingMode;       

 

  ADC_OversamplingTypeDef Oversampling;   
 

#line 187 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"
} ADC_InitTypeDef;











 
typedef struct
{
  uint32_t Channel;                

 

  uint32_t Rank;                   


 

  uint32_t SamplingTime;           








 

  uint32_t SingleDiff;             









 

  uint32_t OffsetNumber;           

 

  uint32_t Offset;                 




 

} ADC_ChannelConfTypeDef;






 
typedef struct
{
  uint32_t WatchdogNumber;    


 

  uint32_t WatchdogMode;      


 

  uint32_t Channel;           


 

  FunctionalState ITMode;     
 

  uint32_t HighThreshold;     







 

  uint32_t LowThreshold;      







 
} ADC_AnalogWDGConfTypeDef;




 
typedef struct
{
  uint32_t ContextQueue;                 

 

  uint32_t ChannelCount;                  
} ADC_InjectionConfigTypeDef;



 








 
 





 




 






 





 




 




 



 



typedef struct

{
  ADC_TypeDef                   *Instance;               
  ADC_InitTypeDef               Init;                    
  DMA_HandleTypeDef             *DMA_Handle;             
  HAL_LockTypeDef               Lock;                    
  volatile uint32_t                 State;                   
  volatile uint32_t                 ErrorCode;               
  ADC_InjectionConfigTypeDef    InjectionConfig ;        
#line 384 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"
} ADC_HandleTypeDef;

#line 411 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"



 


 



 



 
#line 435 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"


 



 




#line 458 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"


 



 






 



 




 



 




 



 
 
#line 512 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"


 



 






 



 




 



 




 



 
#line 564 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"


 



 
#line 582 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"


 



 
 
 
#line 624 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"


 



 





 



 
#line 648 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"


 



 
#line 663 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"


 



 
#line 679 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"


 



 




 



 




 



 
#line 710 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"


 




 
#line 729 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"





 



 
#line 750 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"







 






 



 

 



 
 
 





 







 






 









 









 







 







 







 







 
#line 865 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"





 









 







 







 







 










 
#line 933 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"





 







 







 
#line 975 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"





 
#line 997 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"



 


 



 

 
 
 
 
 
 
 


 
 
 




 

 



 
 
 



 




 
#line 1054 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"


















 




















 



















 




















 




















 
 





 



 

















































 



















































 




























































 










































































 




































 



#line 1462 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"










 



















 















 




















 
#line 1536 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"
















 
#line 1559 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"

























 

















































 
#line 1641 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"












































 
#line 1698 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"



 



 

 
#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"
















 

 







 
#line 29 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"



 



 

 


 



 
typedef struct
{
  uint32_t Ratio;                         
 

  uint32_t RightBitShift;                 
 
} ADC_InjOversamplingTypeDef;
















 
typedef struct
{
  uint32_t InjectedChannel;               

 

  uint32_t InjectedRank;                  


 

  uint32_t InjectedSamplingTime;          








 

  uint32_t InjectedSingleDiff;            









 

  uint32_t InjectedOffsetNumber;          

 

  uint32_t InjectedOffset;                




 

  uint32_t InjectedNbrOfConversion;       



 

  FunctionalState InjectedDiscontinuousConvMode; 







 

  FunctionalState AutoInjectedConv;       






 

  FunctionalState QueueInjectedContext;   








 

  uint32_t ExternalTrigInjecConv;         



 

  uint32_t ExternalTrigInjecConvEdge;     



 

  FunctionalState InjecOversamplingMode;         

 

  ADC_InjOversamplingTypeDef  InjecOversampling; 

 
} ADC_InjectionConfTypeDef;

#line 195 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"



 

 



 



 
 
#line 227 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"


 



 






 



 




 



 







 



 






 

#line 320 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"



 





 



 
#line 349 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"


 



 
#line 367 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"


 



 

 







 

#line 395 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"



 

 

#line 428 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"

 



 
 
 






 







 








 








 
#line 482 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"






 







 






 






 






 






 






 






 






 






 






 







 






 


#line 585 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"












 














 













 










 
#line 656 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"



#line 670 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"






 

 
#line 685 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"





 

 
#line 699 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"





 
 






 






 








 
#line 896 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"






 
#line 953 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"





 







 










 










 
#line 1006 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"





 





#line 1059 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"





 








 
#line 1081 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"





 








 
#line 1102 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"





 
#line 1116 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"





 
#line 1131 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"





 







 










 
#line 1162 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"








 








 


 


 



 
 

 
HAL_StatusTypeDef       HAL_ADCEx_Calibration_Start(ADC_HandleTypeDef *hadc, uint32_t SingleDiff);
uint32_t                HAL_ADCEx_Calibration_GetValue(ADC_HandleTypeDef *hadc, uint32_t SingleDiff);
HAL_StatusTypeDef       HAL_ADCEx_Calibration_SetValue(ADC_HandleTypeDef *hadc, uint32_t SingleDiff,
                                                       uint32_t CalibrationFactor);

 
HAL_StatusTypeDef       HAL_ADCEx_InjectedStart(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedStop(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedPollForConversion(ADC_HandleTypeDef *hadc, uint32_t Timeout);

 
HAL_StatusTypeDef       HAL_ADCEx_InjectedStart_IT(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedStop_IT(ADC_HandleTypeDef *hadc);

#line 1213 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc_ex.h"

 
uint32_t                HAL_ADCEx_InjectedGetValue(ADC_HandleTypeDef *hadc, uint32_t InjectedRank);

 
void                    HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc);
void                    HAL_ADCEx_InjectedQueueOverflowCallback(ADC_HandleTypeDef *hadc);
void                    HAL_ADCEx_LevelOutOfWindow2Callback(ADC_HandleTypeDef *hadc);
void                    HAL_ADCEx_LevelOutOfWindow3Callback(ADC_HandleTypeDef *hadc);
void                    HAL_ADCEx_EndOfSamplingCallback(ADC_HandleTypeDef *hadc);

 
HAL_StatusTypeDef HAL_ADCEx_RegularStop(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADCEx_RegularStop_IT(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADCEx_RegularStop_DMA(ADC_HandleTypeDef *hadc);






 



 
 
HAL_StatusTypeDef       HAL_ADCEx_InjectedConfigChannel(ADC_HandleTypeDef *hadc,
                                                        ADC_InjectionConfTypeDef *sConfigInjected);



HAL_StatusTypeDef       HAL_ADCEx_EnableInjectedQueue(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADCEx_DisableInjectedQueue(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADCEx_DisableVoltageRegulator(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADCEx_EnterADCDeepPowerDownMode(ADC_HandleTypeDef *hadc);



 



 



 



 





#line 1709 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"

 


 




 
 
HAL_StatusTypeDef       HAL_ADC_Init(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADC_DeInit(ADC_HandleTypeDef *hadc);
void                    HAL_ADC_MspInit(ADC_HandleTypeDef *hadc);
void                    HAL_ADC_MspDeInit(ADC_HandleTypeDef *hadc);

#line 1731 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_adc.h"


 




 
 

 
HAL_StatusTypeDef       HAL_ADC_Start(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADC_Stop(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADC_PollForConversion(ADC_HandleTypeDef *hadc, uint32_t Timeout);
HAL_StatusTypeDef       HAL_ADC_PollForEvent(ADC_HandleTypeDef *hadc, uint32_t EventType, uint32_t Timeout);

 
HAL_StatusTypeDef       HAL_ADC_Start_IT(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADC_Stop_IT(ADC_HandleTypeDef *hadc);

 
HAL_StatusTypeDef       HAL_ADC_Start_DMA(ADC_HandleTypeDef *hadc, uint32_t *pData, uint32_t Length);
HAL_StatusTypeDef       HAL_ADC_Stop_DMA(ADC_HandleTypeDef *hadc);

 
uint32_t                HAL_ADC_GetValue(ADC_HandleTypeDef *hadc);

 
void                    HAL_ADC_IRQHandler(ADC_HandleTypeDef *hadc);
void                    HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);
void                    HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc);
void                    HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef *hadc);
void                    HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc);


 




 
 
HAL_StatusTypeDef       HAL_ADC_ConfigChannel(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig);
HAL_StatusTypeDef       HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef *hadc, ADC_AnalogWDGConfTypeDef *AnalogWDGConfig);



 

 


 
uint32_t                HAL_ADC_GetState(ADC_HandleTypeDef *hadc);
uint32_t                HAL_ADC_GetError(ADC_HandleTypeDef *hadc);



 



 

 


 
HAL_StatusTypeDef ADC_ConversionStop(ADC_HandleTypeDef *hadc, uint32_t ConversionGroup);
HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef ADC_Disable(ADC_HandleTypeDef *hadc);
void ADC_DMAConvCplt(DMA_HandleTypeDef *hdma);
void ADC_DMAHalfConvCplt(DMA_HandleTypeDef *hdma);
void ADC_DMAError(DMA_HandleTypeDef *hdma);



 



 



 






#line 279 "../Core/Inc/stm32l4xx_hal_conf.h"






































#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_exti.h"
















 

 







 
#line 29 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_exti.h"



 




 

 



 
typedef enum
{
  HAL_EXTI_COMMON_CB_ID          = 0x00U,
  HAL_EXTI_RISING_CB_ID          = 0x01U,
  HAL_EXTI_FALLING_CB_ID         = 0x02U,
} EXTI_CallbackIDTypeDef;




 
typedef struct
{
  uint32_t Line;                     
  void (* PendingCallback)(void);    
} EXTI_HandleTypeDef;



 
typedef struct
{
  uint32_t Line;      
 
  uint32_t Mode;      
 
  uint32_t Trigger;   
 
  uint32_t GPIOSel;   

 
} EXTI_ConfigTypeDef;



 

 


 



 
#line 134 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_exti.h"



#line 178 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_exti.h"



#line 226 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_exti.h"

#line 272 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_exti.h"

#line 318 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_exti.h"

#line 364 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_exti.h"

#line 410 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_exti.h"

#line 456 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_exti.h"

#line 502 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_exti.h"

#line 548 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_exti.h"

#line 594 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_exti.h"



 



 





 



 






 




 
#line 633 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_exti.h"


 



 

 


 



 

 


 


 
#line 663 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_exti.h"



 






 








 




 




 




 

 


 
#line 709 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_exti.h"










#line 728 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_exti.h"



#line 737 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_exti.h"



#line 748 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_exti.h"

#line 759 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_exti.h"

#line 772 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_exti.h"

#line 786 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_exti.h"

#line 800 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_exti.h"




 


 



 




 
 
HAL_StatusTypeDef HAL_EXTI_SetConfigLine(EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig);
HAL_StatusTypeDef HAL_EXTI_GetConfigLine(EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig);
HAL_StatusTypeDef HAL_EXTI_ClearConfigLine(EXTI_HandleTypeDef *hexti);
HAL_StatusTypeDef HAL_EXTI_RegisterCallback(EXTI_HandleTypeDef *hexti, EXTI_CallbackIDTypeDef CallbackID, void (*pPendingCbfn)(void));
HAL_StatusTypeDef HAL_EXTI_GetHandle(EXTI_HandleTypeDef *hexti, uint32_t ExtiLine);


 




 
 
void              HAL_EXTI_IRQHandler(EXTI_HandleTypeDef *hexti);
uint32_t          HAL_EXTI_GetPending(EXTI_HandleTypeDef *hexti, uint32_t Edge);
void              HAL_EXTI_ClearPending(EXTI_HandleTypeDef *hexti, uint32_t Edge);
void              HAL_EXTI_GenerateSWI(EXTI_HandleTypeDef *hexti);



 



 



 



 







#line 319 "../Core/Inc/stm32l4xx_hal_conf.h"










#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash.h"















 

 







 
#line 28 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash.h"



 



 

 


 



 
typedef struct
{
  uint32_t TypeErase;   
 
  uint32_t Banks;       

 
  uint32_t Page;        

 
  uint32_t NbPages;     
 
} FLASH_EraseInitTypeDef;



 
typedef struct
{
  uint32_t OptionType;     
 
  uint32_t WRPArea;        

 
  uint32_t WRPStartOffset; 

 
  uint32_t WRPEndOffset;   
 
  uint32_t RDPLevel;       
 
  uint32_t USERType;       
 
  uint32_t USERConfig;     







 
  uint32_t PCROPConfig;    

 
  uint32_t PCROPStartAddr; 

 
  uint32_t PCROPEndAddr;   
 
} FLASH_OBProgramInitTypeDef;



 
typedef enum
{
  FLASH_PROC_NONE = 0,
  FLASH_PROC_PAGE_ERASE,
  FLASH_PROC_MASS_ERASE,
  FLASH_PROC_PROGRAM,
  FLASH_PROC_PROGRAM_LAST
} FLASH_ProcedureTypeDef;



 
typedef enum
{
  FLASH_CACHE_DISABLED = 0,
  FLASH_CACHE_ICACHE_ENABLED,
  FLASH_CACHE_DCACHE_ENABLED,
  FLASH_CACHE_ICACHE_DCACHE_ENABLED
} FLASH_CacheTypeDef;



 
typedef struct
{
  HAL_LockTypeDef             Lock;               
  volatile uint32_t               ErrorCode;          
  volatile FLASH_ProcedureTypeDef ProcedureOnGoing;   
  volatile uint32_t               Address;            
  volatile uint32_t               Bank;               
  volatile uint32_t               Page;               
  volatile uint32_t               NbPagesToErase;     
  volatile FLASH_CacheTypeDef     CacheToReactivate;  
}FLASH_ProcessTypeDef;



 

 


 



 
#line 166 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash.h"


 



 




 



 
#line 191 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash.h"


 




 







 



 






 



 
#line 230 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash.h"


 



 






 



 
#line 279 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash.h"


 



 







 



 




 



 




 



 




 



 




 



 




 



 




 



 




 

#line 389 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash.h"

#line 397 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash.h"


 


 




 



 




 



 




 







 




 



 




 




 






 



 
#line 482 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash.h"


 



 













 



 
#line 543 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash.h"







 




 






 

 



 











 











 





 





 





 





 





 





 






 








 








 









 








 





 




 




 










 













 
























 























 





 

 
#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash_ex.h"















 

 







 
#line 28 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash_ex.h"



 



 

 

 
#line 57 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash_ex.h"

 

 


 

 


 
HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *PageError);
HAL_StatusTypeDef HAL_FLASHEx_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit);
HAL_StatusTypeDef HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit);
void              HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit);


 

#line 86 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash_ex.h"



 

 


 
void FLASH_PageErase(uint32_t Page, uint32_t Banks);
void FLASH_FlushCaches(void);


 

 


 





 



 



 







#line 772 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash.h"
#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash_ramfunc.h"















 

 







 
#line 28 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash_ramfunc.h"



 



 

 
 
 


 



 
 
  HAL_StatusTypeDef HAL_FLASHEx_EnableRunPowerDown(void);
  HAL_StatusTypeDef HAL_FLASHEx_DisableRunPowerDown(void);





 



 



 



 







#line 773 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash.h"

 


 

 


 
HAL_StatusTypeDef  HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint64_t Data);
HAL_StatusTypeDef  HAL_FLASH_Program_IT(uint32_t TypeProgram, uint32_t Address, uint64_t Data);
 
void               HAL_FLASH_IRQHandler(void);
 
void               HAL_FLASH_EndOfOperationCallback(uint32_t ReturnValue);
void               HAL_FLASH_OperationErrorCallback(uint32_t ReturnValue);


 

 


 
HAL_StatusTypeDef  HAL_FLASH_Unlock(void);
HAL_StatusTypeDef  HAL_FLASH_Lock(void);
 
HAL_StatusTypeDef  HAL_FLASH_OB_Unlock(void);
HAL_StatusTypeDef  HAL_FLASH_OB_Lock(void);
HAL_StatusTypeDef  HAL_FLASH_OB_Launch(void);


 

 


 
uint32_t HAL_FLASH_GetError(void);


 



 

 


 
extern FLASH_ProcessTypeDef pFlash;


 

 


 
HAL_StatusTypeDef FLASH_WaitForLastOperation(uint32_t Timeout);


 

 


 
#line 850 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash.h"

#line 857 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash.h"




 

 


 




#line 882 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash.h"








#line 899 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash.h"





#line 920 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash.h"



#line 931 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash.h"





#line 943 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash.h"



















#line 969 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash.h"






















#line 1007 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_flash.h"


 



 



 



 







#line 331 "../Core/Inc/stm32l4xx_hal_conf.h"


































































#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr.h"
















 

 







 
#line 29 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr.h"



 



 

 



 



 
typedef struct
{
  uint32_t PVDLevel;   
 

  uint32_t Mode;      
 
}PWR_PVDTypeDef;




 

 



 




 
#line 79 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr.h"


 



 
#line 93 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr.h"


 






 




 



 




 



 




 




 



 



 



 



 

 


 









































 





















 






 





 





 





 





 





 





 






 






 









 









 





 





 




 


 


 






#line 329 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr.h"










 

 
#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"
















 

 







 
#line 29 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"



 



 


 



 




 
typedef struct
{
  uint32_t PVMType;   






 

  uint32_t Mode;      
 
}PWR_PVMTypeDef;



 

 



 



 



 




 
#line 101 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"


 



 
#line 116 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"


 



 
#line 130 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"


 





 







 




 




 



 




 



 
#line 186 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"


 



 
#line 212 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"


 



 
#line 227 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"


 



 
#line 242 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"


 










 
#line 267 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"

#line 280 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"


 



 
#line 294 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"


 



 

 


 

#line 397 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"


#line 489 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"





 





 





 





 





 





 





 






 






 









 









 





 





 








 





 





 





 





 





 





 






 






 









 









 





 





 


















 
#line 694 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"



 

 


 

#line 719 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"

#line 733 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"

#line 742 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"

#line 750 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"

#line 759 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"











#line 811 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"

#line 820 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"



 




 



 


 
uint32_t HAL_PWREx_GetVoltageRange(void);
HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling);
void HAL_PWREx_EnableBatteryCharging(uint32_t ResistorSelection);
void HAL_PWREx_DisableBatteryCharging(void);
#line 848 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"
void HAL_PWREx_EnableInternalWakeUpLine(void);
void HAL_PWREx_DisableInternalWakeUpLine(void);
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber);
void HAL_PWREx_EnablePullUpPullDownConfig(void);
void HAL_PWREx_DisablePullUpPullDownConfig(void);
void HAL_PWREx_EnableSRAM2ContentRetention(void);
void HAL_PWREx_DisableSRAM2ContentRetention(void);
HAL_StatusTypeDef HAL_PWREx_SetSRAM2ContentRetention(uint32_t SRAM2Size);
#line 875 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"
void HAL_PWREx_EnablePVM3(void);
void HAL_PWREx_DisablePVM3(void);
void HAL_PWREx_EnablePVM4(void);
void HAL_PWREx_DisablePVM4(void);
HAL_StatusTypeDef HAL_PWREx_ConfigPVM(PWR_PVMTypeDef *sConfigPVM);
#line 888 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"


 
void HAL_PWREx_EnableLowPowerRunMode(void);
HAL_StatusTypeDef HAL_PWREx_DisableLowPowerRunMode(void);
void HAL_PWREx_EnterSTOP0Mode(uint8_t STOPEntry);
void HAL_PWREx_EnterSTOP1Mode(uint8_t STOPEntry);
void HAL_PWREx_EnterSTOP2Mode(uint8_t STOPEntry);
void HAL_PWREx_EnterSHUTDOWNMode(void);

void HAL_PWREx_PVD_PVM_IRQHandler(void);
#line 905 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"
void HAL_PWREx_PVM3Callback(void);
void HAL_PWREx_PVM4Callback(void);



 



 



 



 






#line 343 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr.h"

 



 



 

 
void HAL_PWR_DeInit(void);
void HAL_PWR_EnableBkUpAccess(void);
void HAL_PWR_DisableBkUpAccess(void);



 



 

 
HAL_StatusTypeDef HAL_PWR_ConfigPVD(PWR_PVDTypeDef *sConfigPVD);
void HAL_PWR_EnablePVD(void);
void HAL_PWR_DisablePVD(void);


 
void HAL_PWR_EnableWakeUpPin(uint32_t WakeUpPinPolarity);
void HAL_PWR_DisableWakeUpPin(uint32_t WakeUpPinx);

 
void HAL_PWR_EnterSLEEPMode(uint32_t Regulator, uint8_t SLEEPEntry);
void HAL_PWR_EnterSTOPMode(uint32_t Regulator, uint8_t STOPEntry);
void HAL_PWR_EnterSTANDBYMode(void);

void HAL_PWR_EnableSleepOnExit(void);
void HAL_PWR_DisableSleepOnExit(void);
void HAL_PWR_EnableSEVOnPend(void);
void HAL_PWR_DisableSEVOnPend(void);

void HAL_PWR_PVDCallback(void);




 



 



 



 






#line 399 "../Core/Inc/stm32l4xx_hal_conf.h"






























#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_spi.h"
















 

 







 
#line 29 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_spi.h"



 



 

 


 



 
typedef struct
{
  uint32_t Mode;                
 

  uint32_t Direction;           
 

  uint32_t DataSize;            
 

  uint32_t CLKPolarity;         
 

  uint32_t CLKPhase;            
 

  uint32_t NSS;                 

 

  uint32_t BaudRatePrescaler;   



 

  uint32_t FirstBit;            
 

  uint32_t TIMode;              
 

  uint32_t CRCCalculation;      
 

  uint32_t CRCPolynomial;       
 

  uint32_t CRCLength;           

 

  uint32_t NSSPMode;            




 
} SPI_InitTypeDef;



 
typedef enum
{
  HAL_SPI_STATE_RESET      = 0x00U,     
  HAL_SPI_STATE_READY      = 0x01U,     
  HAL_SPI_STATE_BUSY       = 0x02U,     
  HAL_SPI_STATE_BUSY_TX    = 0x03U,     
  HAL_SPI_STATE_BUSY_RX    = 0x04U,     
  HAL_SPI_STATE_BUSY_TX_RX = 0x05U,     
  HAL_SPI_STATE_ERROR      = 0x06U,     
  HAL_SPI_STATE_ABORT      = 0x07U      
} HAL_SPI_StateTypeDef;



 
typedef struct __SPI_HandleTypeDef
{
  SPI_TypeDef                *Instance;       

  SPI_InitTypeDef            Init;            

  uint8_t                    *pTxBuffPtr;     

  uint16_t                   TxXferSize;      

  volatile uint16_t              TxXferCount;     

  uint8_t                    *pRxBuffPtr;     

  uint16_t                   RxXferSize;      

  volatile uint16_t              RxXferCount;     

  uint32_t                   CRCSize;         

  void (*RxISR)(struct __SPI_HandleTypeDef *hspi);    

  void (*TxISR)(struct __SPI_HandleTypeDef *hspi);    

  DMA_HandleTypeDef          *hdmatx;         

  DMA_HandleTypeDef          *hdmarx;         

  HAL_LockTypeDef            Lock;            

  volatile HAL_SPI_StateTypeDef  State;           

  volatile uint32_t              ErrorCode;       

#line 162 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_spi.h"
} SPI_HandleTypeDef;

#line 189 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_spi.h"


 

 


 



 
#line 212 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_spi.h"


 



 




 



 





 



 
#line 251 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_spi.h"


 



 




 



 




 



 





 



 




 



 
#line 303 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_spi.h"


 



 




 



 




 



 




 







 





 








 





 



 





 



 
#line 387 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_spi.h"


 



 







 



 






 



 

 


 





 
#line 437 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_spi.h"










 











 











 


















 






 






 
#line 512 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_spi.h"





 
#line 525 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_spi.h"





 
#line 537 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_spi.h"





 






 




 

 


 





 






 






 

















 











 







 







 







 





 







 
#line 661 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_spi.h"





 







 







 








 







 
#line 708 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_spi.h"





 







 







 







 








 







 




 

 
#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_spi_ex.h"
















 

 







 
#line 29 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_spi_ex.h"



 



 

 
 
 
 


 

 
 


 
HAL_StatusTypeDef HAL_SPIEx_FlushRxFifo(SPI_HandleTypeDef *hspi);


 



 



 



 







#line 763 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_spi.h"

 


 



 
 
HAL_StatusTypeDef HAL_SPI_Init(SPI_HandleTypeDef *hspi);
HAL_StatusTypeDef HAL_SPI_DeInit(SPI_HandleTypeDef *hspi);
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi);
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi);

 







 



 
 
HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_SPI_Receive(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_SPI_TransmitReceive(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size,
                                          uint32_t Timeout);
HAL_StatusTypeDef HAL_SPI_Transmit_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_SPI_Receive_IT(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_SPI_TransmitReceive_IT(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData,
                                             uint16_t Size);
HAL_StatusTypeDef HAL_SPI_Transmit_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_SPI_Receive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_SPI_TransmitReceive_DMA(SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData,
                                              uint16_t Size);
HAL_StatusTypeDef HAL_SPI_DMAPause(SPI_HandleTypeDef *hspi);
HAL_StatusTypeDef HAL_SPI_DMAResume(SPI_HandleTypeDef *hspi);
HAL_StatusTypeDef HAL_SPI_DMAStop(SPI_HandleTypeDef *hspi);
 
HAL_StatusTypeDef HAL_SPI_Abort(SPI_HandleTypeDef *hspi);
HAL_StatusTypeDef HAL_SPI_Abort_IT(SPI_HandleTypeDef *hspi);

void HAL_SPI_IRQHandler(SPI_HandleTypeDef *hspi);
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_TxHalfCpltCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_RxHalfCpltCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_TxRxHalfCpltCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi);
void HAL_SPI_AbortCpltCallback(SPI_HandleTypeDef *hspi);


 



 
 
HAL_SPI_StateTypeDef HAL_SPI_GetState(SPI_HandleTypeDef *hspi);
uint32_t             HAL_SPI_GetError(SPI_HandleTypeDef *hspi);


 



 



 



 







#line 431 "../Core/Inc/stm32l4xx_hal_conf.h"










#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"
















 

 







 
#line 29 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"



 



 

 


 



 
typedef struct
{
  uint32_t Prescaler;         
 

  uint32_t CounterMode;       
 

  uint32_t Period;            

 

  uint32_t ClockDivision;     
 

  uint32_t RepetitionCounter;  








 

  uint32_t AutoReloadPreload;  
 
} TIM_Base_InitTypeDef;



 
typedef struct
{
  uint32_t OCMode;        
 

  uint32_t Pulse;         
 

  uint32_t OCPolarity;    
 

  uint32_t OCNPolarity;   

 

  uint32_t OCFastMode;    

 


  uint32_t OCIdleState;   

 

  uint32_t OCNIdleState;  

 
} TIM_OC_InitTypeDef;



 
typedef struct
{
  uint32_t OCMode;        
 

  uint32_t Pulse;         
 

  uint32_t OCPolarity;    
 

  uint32_t OCNPolarity;   

 

  uint32_t OCIdleState;   

 

  uint32_t OCNIdleState;  

 

  uint32_t ICPolarity;    
 

  uint32_t ICSelection;   
 

  uint32_t ICFilter;      
 
} TIM_OnePulse_InitTypeDef;



 
typedef struct
{
  uint32_t  ICPolarity;  
 

  uint32_t ICSelection;  
 

  uint32_t ICPrescaler;  
 

  uint32_t ICFilter;     
 
} TIM_IC_InitTypeDef;



 
typedef struct
{
  uint32_t EncoderMode;   
 

  uint32_t IC1Polarity;   
 

  uint32_t IC1Selection;  
 

  uint32_t IC1Prescaler;  
 

  uint32_t IC1Filter;     
 

  uint32_t IC2Polarity;   
 

  uint32_t IC2Selection;  
 

  uint32_t IC2Prescaler;  
 

  uint32_t IC2Filter;     
 
} TIM_Encoder_InitTypeDef;



 
typedef struct
{
  uint32_t ClockSource;     
 
  uint32_t ClockPolarity;   
 
  uint32_t ClockPrescaler;  
 
  uint32_t ClockFilter;     
 
} TIM_ClockConfigTypeDef;



 
typedef struct
{
  uint32_t ClearInputState;      
 
  uint32_t ClearInputSource;     
 
  uint32_t ClearInputPolarity;   
 
  uint32_t ClearInputPrescaler;  

 
  uint32_t ClearInputFilter;     
 
} TIM_ClearInputConfigTypeDef;





 
typedef struct
{
  uint32_t  MasterOutputTrigger;   
 
  uint32_t  MasterOutputTrigger2;  
 
  uint32_t  MasterSlaveMode;       





 
} TIM_MasterConfigTypeDef;



 
typedef struct
{
  uint32_t  SlaveMode;         
 
  uint32_t  InputTrigger;      
 
  uint32_t  TriggerPolarity;   
 
  uint32_t  TriggerPrescaler;  
 
  uint32_t  TriggerFilter;     
 

} TIM_SlaveConfigTypeDef;





 
typedef struct
{
  uint32_t OffStateRunMode;       

  uint32_t OffStateIDLEMode;      

  uint32_t LockLevel;             

  uint32_t DeadTime;              

  uint32_t BreakState;            

  uint32_t BreakPolarity;         

  uint32_t BreakFilter;           

  uint32_t Break2State;           

  uint32_t Break2Polarity;        

  uint32_t Break2Filter;          

  uint32_t AutomaticOutput;       

} TIM_BreakDeadTimeConfigTypeDef;



 
typedef enum
{
  HAL_TIM_STATE_RESET             = 0x00U,     
  HAL_TIM_STATE_READY             = 0x01U,     
  HAL_TIM_STATE_BUSY              = 0x02U,     
  HAL_TIM_STATE_TIMEOUT           = 0x03U,     
  HAL_TIM_STATE_ERROR             = 0x04U      
} HAL_TIM_StateTypeDef;



 
typedef enum
{
  HAL_TIM_CHANNEL_STATE_RESET             = 0x00U,     
  HAL_TIM_CHANNEL_STATE_READY             = 0x01U,     
  HAL_TIM_CHANNEL_STATE_BUSY              = 0x02U,     
} HAL_TIM_ChannelStateTypeDef;



 
typedef enum
{
  HAL_DMA_BURST_STATE_RESET             = 0x00U,     
  HAL_DMA_BURST_STATE_READY             = 0x01U,     
  HAL_DMA_BURST_STATE_BUSY              = 0x02U,     
} HAL_TIM_DMABurstStateTypeDef;



 
typedef enum
{
  HAL_TIM_ACTIVE_CHANNEL_1        = 0x01U,     
  HAL_TIM_ACTIVE_CHANNEL_2        = 0x02U,     
  HAL_TIM_ACTIVE_CHANNEL_3        = 0x04U,     
  HAL_TIM_ACTIVE_CHANNEL_4        = 0x08U,     
  HAL_TIM_ACTIVE_CHANNEL_5        = 0x10U,     
  HAL_TIM_ACTIVE_CHANNEL_6        = 0x20U,     
  HAL_TIM_ACTIVE_CHANNEL_CLEARED  = 0x00U      
} HAL_TIM_ActiveChannel;



 



typedef struct

{
  TIM_TypeDef                        *Instance;          
  TIM_Base_InitTypeDef               Init;               
  HAL_TIM_ActiveChannel              Channel;            
  DMA_HandleTypeDef                  *hdma[7];          
 
  HAL_LockTypeDef                    Lock;               
  volatile HAL_TIM_StateTypeDef          State;              
  volatile HAL_TIM_ChannelStateTypeDef   ChannelState[6];    
  volatile HAL_TIM_ChannelStateTypeDef   ChannelNState[4];   
  volatile HAL_TIM_DMABurstStateTypeDef  DMABurstState;      

#line 393 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"
} TIM_HandleTypeDef;

#line 438 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"



 
 

 


 



 





 



 
#line 488 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"


 



 
#line 504 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"


 



 





 



 




 



 






 



 







 



 




 



 





 



 




 



 





 



 




 



 




 



 




 



 




 



 




 



 




 



 





 



 




 



 





 



 






 



 




 



 





 



 
#line 712 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"


 



 




 



 
#line 735 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"


 



 




 



 
#line 767 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"


 



 
#line 781 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"


 



 
#line 798 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"


 



 







 



 






 



 




 



 






 



 




 



 




 


 






 



 




 



 




 



 




 



 




 



 




 



 






 



 
#line 940 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"


 



 
#line 963 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"


 



 




 



 
#line 985 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"


 



 
#line 1006 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"


 



 
#line 1022 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"


 



 







 



 






 



 




 



 
#line 1079 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"


 



 
#line 1093 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"


 



 






 



 






 



 
 

 


 




 
#line 1178 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"





 






 






 
#line 1208 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"







 
#line 1226 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"






 















 















 














 














 























 























 
















 
















 









 







 







 








 







 










 






 







 










 











 
#line 1475 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"








 



















 




















 



















 
#line 1552 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"













 
#line 1573 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"













 
#line 1594 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"













 
#line 1615 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"

















 
#line 1640 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"

















 
#line 1665 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"








 












 
















 













 





 
 

 


 

 




 
 

 


 




#line 1771 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"



























































#line 1837 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"











#line 1858 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"























































#line 1921 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"

#line 1939 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"




#line 1949 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"

#line 1956 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"

#line 1965 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"

#line 1974 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"























#line 2015 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"







































#line 2061 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"

#line 2069 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"

#line 2084 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"













#line 2107 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"



 
 

 
#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim_ex.h"
















 

 







 
#line 29 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim_ex.h"



 



 

 


 



 

typedef struct
{
  uint32_t IC1Polarity;         
 

  uint32_t IC1Prescaler;        
 

  uint32_t IC1Filter;           
 

  uint32_t Commutation_Delay;   
 
} TIM_HallSensor_InitTypeDef;



 
typedef struct
{
  uint32_t Source;         
 
  uint32_t Enable;         
 
  uint32_t Polarity;       

 
} TIMEx_BreakInputConfigTypeDef;



 
 

 


 



 
#line 106 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim_ex.h"

#line 131 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim_ex.h"

#line 140 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim_ex.h"

#line 159 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim_ex.h"

#line 170 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim_ex.h"

#line 180 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim_ex.h"

#line 187 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim_ex.h"


 



 




 



 
#line 209 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim_ex.h"


 



 




 



 




 



 
 

 


 



 
 

 


 





#line 265 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim_ex.h"









 
 

 


 




 
 
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Init(TIM_HandleTypeDef *htim, const TIM_HallSensor_InitTypeDef *sConfig);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_DeInit(TIM_HandleTypeDef *htim);

void HAL_TIMEx_HallSensor_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIMEx_HallSensor_MspDeInit(TIM_HandleTypeDef *htim);

 
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Start(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Stop(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Start_IT(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Stop_IT(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Start_DMA(TIM_HandleTypeDef *htim, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIMEx_HallSensor_Stop_DMA(TIM_HandleTypeDef *htim);


 




 
 
 
HAL_StatusTypeDef HAL_TIMEx_OCN_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_OCN_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

 
HAL_StatusTypeDef HAL_TIMEx_OCN_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_OCN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);

 
HAL_StatusTypeDef HAL_TIMEx_OCN_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, const uint32_t *pData,
                                          uint16_t Length);
HAL_StatusTypeDef HAL_TIMEx_OCN_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
 
HAL_StatusTypeDef HAL_TIMEx_PWMN_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_PWMN_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);

 
HAL_StatusTypeDef HAL_TIMEx_PWMN_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIMEx_PWMN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIMEx_PWMN_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, const uint32_t *pData,
                                           uint16_t Length);
HAL_StatusTypeDef HAL_TIMEx_PWMN_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
 
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Start(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Stop(TIM_HandleTypeDef *htim, uint32_t OutputChannel);

 
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Start_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIMEx_OnePulseN_Stop_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);


 




 
 
HAL_StatusTypeDef HAL_TIMEx_ConfigCommutEvent(TIM_HandleTypeDef *htim, uint32_t  InputTrigger,
                                              uint32_t  CommutationSource);
HAL_StatusTypeDef HAL_TIMEx_ConfigCommutEvent_IT(TIM_HandleTypeDef *htim, uint32_t  InputTrigger,
                                                 uint32_t  CommutationSource);
HAL_StatusTypeDef HAL_TIMEx_ConfigCommutEvent_DMA(TIM_HandleTypeDef *htim, uint32_t  InputTrigger,
                                                  uint32_t  CommutationSource);
HAL_StatusTypeDef HAL_TIMEx_MasterConfigSynchronization(TIM_HandleTypeDef *htim,
                                                        const TIM_MasterConfigTypeDef *sMasterConfig);
HAL_StatusTypeDef HAL_TIMEx_ConfigBreakDeadTime(TIM_HandleTypeDef *htim,
                                                const TIM_BreakDeadTimeConfigTypeDef *sBreakDeadTimeConfig);
HAL_StatusTypeDef HAL_TIMEx_ConfigBreakInput(TIM_HandleTypeDef *htim, uint32_t BreakInput,
                                             const TIMEx_BreakInputConfigTypeDef *sBreakInputConfig);
HAL_StatusTypeDef HAL_TIMEx_GroupChannel5(TIM_HandleTypeDef *htim, uint32_t Channels);
HAL_StatusTypeDef HAL_TIMEx_RemapConfig(TIM_HandleTypeDef *htim, uint32_t Remap);


 




 
 
void HAL_TIMEx_CommutCallback(TIM_HandleTypeDef *htim);
void HAL_TIMEx_CommutHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIMEx_BreakCallback(TIM_HandleTypeDef *htim);
void HAL_TIMEx_Break2Callback(TIM_HandleTypeDef *htim);


 




 
 
HAL_TIM_StateTypeDef HAL_TIMEx_HallSensor_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_ChannelStateTypeDef HAL_TIMEx_GetChannelNState(const TIM_HandleTypeDef *htim,  uint32_t ChannelN);


 



 
 

 


 
void TIMEx_DMACommutationCplt(DMA_HandleTypeDef *hdma);
void TIMEx_DMACommutationHalfCplt(DMA_HandleTypeDef *hdma);


 
 



 



 






#line 2115 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_tim.h"

 


 




 
 
HAL_StatusTypeDef HAL_TIM_Base_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_Base_Start(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_Stop(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_Base_Start_IT(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_Base_Start_DMA(TIM_HandleTypeDef *htim, const uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_Base_Stop_DMA(TIM_HandleTypeDef *htim);


 




 
 
HAL_StatusTypeDef HAL_TIM_OC_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_OC_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_OC_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OC_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_OC_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OC_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_OC_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, const uint32_t *pData,
                                       uint16_t Length);
HAL_StatusTypeDef HAL_TIM_OC_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
HAL_StatusTypeDef HAL_TIM_PWM_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_PWM_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_PWM_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_PWM_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, const uint32_t *pData,
                                        uint16_t Length);
HAL_StatusTypeDef HAL_TIM_PWM_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
HAL_StatusTypeDef HAL_TIM_IC_Init(TIM_HandleTypeDef *htim);
HAL_StatusTypeDef HAL_TIM_IC_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_IC_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_IC_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_IC_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_IC_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
HAL_StatusTypeDef HAL_TIM_OnePulse_Init(TIM_HandleTypeDef *htim, uint32_t OnePulseMode);
HAL_StatusTypeDef HAL_TIM_OnePulse_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OnePulse_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_OnePulse_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_OnePulse_Start(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIM_OnePulse_Stop(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
 
HAL_StatusTypeDef HAL_TIM_OnePulse_Start_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);
HAL_StatusTypeDef HAL_TIM_OnePulse_Stop_IT(TIM_HandleTypeDef *htim, uint32_t OutputChannel);


 




 
 
HAL_StatusTypeDef HAL_TIM_Encoder_Init(TIM_HandleTypeDef *htim,  TIM_Encoder_InitTypeDef *sConfig);
HAL_StatusTypeDef HAL_TIM_Encoder_DeInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim);
void HAL_TIM_Encoder_MspDeInit(TIM_HandleTypeDef *htim);
 
HAL_StatusTypeDef HAL_TIM_Encoder_Start(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_Encoder_Stop(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_Encoder_Start_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_Encoder_Stop_IT(TIM_HandleTypeDef *htim, uint32_t Channel);
 
HAL_StatusTypeDef HAL_TIM_Encoder_Start_DMA(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t *pData1,
                                            uint32_t *pData2, uint16_t Length);
HAL_StatusTypeDef HAL_TIM_Encoder_Stop_DMA(TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim);


 




 
 
HAL_StatusTypeDef HAL_TIM_OC_ConfigChannel(TIM_HandleTypeDef *htim, const TIM_OC_InitTypeDef *sConfig,
                                           uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_PWM_ConfigChannel(TIM_HandleTypeDef *htim, const TIM_OC_InitTypeDef *sConfig,
                                            uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_IC_ConfigChannel(TIM_HandleTypeDef *htim, const TIM_IC_InitTypeDef *sConfig,
                                           uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_OnePulse_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OnePulse_InitTypeDef *sConfig,
                                                 uint32_t OutputChannel,  uint32_t InputChannel);
HAL_StatusTypeDef HAL_TIM_ConfigOCrefClear(TIM_HandleTypeDef *htim,
                                           const TIM_ClearInputConfigTypeDef *sClearInputConfig,
                                           uint32_t Channel);
HAL_StatusTypeDef HAL_TIM_ConfigClockSource(TIM_HandleTypeDef *htim, const TIM_ClockConfigTypeDef *sClockSourceConfig);
HAL_StatusTypeDef HAL_TIM_ConfigTI1Input(TIM_HandleTypeDef *htim, uint32_t TI1_Selection);
HAL_StatusTypeDef HAL_TIM_SlaveConfigSynchro(TIM_HandleTypeDef *htim, const TIM_SlaveConfigTypeDef *sSlaveConfig);
HAL_StatusTypeDef HAL_TIM_SlaveConfigSynchro_IT(TIM_HandleTypeDef *htim, const TIM_SlaveConfigTypeDef *sSlaveConfig);
HAL_StatusTypeDef HAL_TIM_DMABurst_WriteStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                              uint32_t BurstRequestSrc, const uint32_t  *BurstBuffer, uint32_t  BurstLength);
HAL_StatusTypeDef HAL_TIM_DMABurst_MultiWriteStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                                   uint32_t BurstRequestSrc, const uint32_t *BurstBuffer,
                                                   uint32_t BurstLength,  uint32_t DataLength);
HAL_StatusTypeDef HAL_TIM_DMABurst_WriteStop(TIM_HandleTypeDef *htim, uint32_t BurstRequestSrc);
HAL_StatusTypeDef HAL_TIM_DMABurst_ReadStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                             uint32_t BurstRequestSrc, uint32_t  *BurstBuffer, uint32_t  BurstLength);
HAL_StatusTypeDef HAL_TIM_DMABurst_MultiReadStart(TIM_HandleTypeDef *htim, uint32_t BurstBaseAddress,
                                                  uint32_t BurstRequestSrc, uint32_t  *BurstBuffer,
                                                  uint32_t  BurstLength, uint32_t  DataLength);
HAL_StatusTypeDef HAL_TIM_DMABurst_ReadStop(TIM_HandleTypeDef *htim, uint32_t BurstRequestSrc);
HAL_StatusTypeDef HAL_TIM_GenerateEvent(TIM_HandleTypeDef *htim, uint32_t EventSource);
uint32_t HAL_TIM_ReadCapturedValue(const TIM_HandleTypeDef *htim, uint32_t Channel);


 




 
 
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PeriodElapsedHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_CaptureHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_TriggerCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_TriggerHalfCpltCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_ErrorCallback(TIM_HandleTypeDef *htim);

 








 




 
 
HAL_TIM_StateTypeDef HAL_TIM_Base_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_OC_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_PWM_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_IC_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_OnePulse_GetState(const TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef HAL_TIM_Encoder_GetState(const TIM_HandleTypeDef *htim);

 
HAL_TIM_ActiveChannel HAL_TIM_GetActiveChannel(const TIM_HandleTypeDef *htim);
HAL_TIM_ChannelStateTypeDef HAL_TIM_GetChannelState(const TIM_HandleTypeDef *htim,  uint32_t Channel);
HAL_TIM_DMABurstStateTypeDef HAL_TIM_DMABurstState(const TIM_HandleTypeDef *htim);


 



 
 

 


 
void TIM_Base_SetConfig(TIM_TypeDef *TIMx, const TIM_Base_InitTypeDef *Structure);
void TIM_TI1_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ICPolarity, uint32_t TIM_ICSelection, uint32_t TIM_ICFilter);
void TIM_OC2_SetConfig(TIM_TypeDef *TIMx, const TIM_OC_InitTypeDef *OC_Config);
void TIM_ETR_SetConfig(TIM_TypeDef *TIMx, uint32_t TIM_ExtTRGPrescaler,
                       uint32_t TIM_ExtTRGPolarity, uint32_t ExtTRGFilter);

void TIM_DMADelayPulseHalfCplt(DMA_HandleTypeDef *hdma);
void TIM_DMAError(DMA_HandleTypeDef *hdma);
void TIM_DMACaptureCplt(DMA_HandleTypeDef *hdma);
void TIM_DMACaptureHalfCplt(DMA_HandleTypeDef *hdma);
void TIM_CCxChannelCmd(TIM_TypeDef *TIMx, uint32_t Channel, uint32_t ChannelState);







 
 



 



 





#line 443 "../Core/Inc/stm32l4xx_hal_conf.h"






#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"
















 

 







 
#line 29 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"



 



 

 


 



 
typedef struct
{
  uint32_t BaudRate;                

















 

  uint32_t WordLength;              
 

  uint32_t StopBits;                
 

  uint32_t Parity;                  




 

  uint32_t Mode;                    
 

  uint32_t HwFlowCtl;               

 

  uint32_t OverSampling;            

 

  uint32_t OneBitSampling;          

 






} UART_InitTypeDef;



 
typedef struct
{
  uint32_t AdvFeatureInit;        


 

  uint32_t TxPinLevelInvert;      
 

  uint32_t RxPinLevelInvert;      
 

  uint32_t DataInvert;            

 

  uint32_t Swap;                  
 

  uint32_t OverrunDisable;        
 

  uint32_t DMADisableonRxError;   
 

  uint32_t AutoBaudRateEnable;    
 

  uint32_t AutoBaudRateMode;      

 

  uint32_t MSBFirst;              
 
} UART_AdvFeatureInitTypeDef;








































 
typedef uint32_t HAL_UART_StateTypeDef;



 
typedef enum
{
  UART_CLOCKSOURCE_PCLK1      = 0x00U,     
  UART_CLOCKSOURCE_PCLK2      = 0x01U,     
  UART_CLOCKSOURCE_HSI        = 0x02U,     
  UART_CLOCKSOURCE_SYSCLK     = 0x04U,     
  UART_CLOCKSOURCE_LSE        = 0x08U,     
  UART_CLOCKSOURCE_UNDEFINED  = 0x10U      
} UART_ClockSourceTypeDef;









 
typedef uint32_t HAL_UART_RxTypeTypeDef;



 
typedef struct __UART_HandleTypeDef
{
  USART_TypeDef            *Instance;                 

  UART_InitTypeDef         Init;                      

  UART_AdvFeatureInitTypeDef AdvancedInit;            

  const uint8_t            *pTxBuffPtr;               

  uint16_t                 TxXferSize;                

  volatile uint16_t            TxXferCount;               

  uint8_t                  *pRxBuffPtr;               

  uint16_t                 RxXferSize;                

  volatile uint16_t            RxXferCount;               

  uint16_t                 Mask;                      

#line 243 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"
  volatile HAL_UART_RxTypeTypeDef ReceptionType;          

  void (*RxISR)(struct __UART_HandleTypeDef *huart);  

  void (*TxISR)(struct __UART_HandleTypeDef *huart);  

  DMA_HandleTypeDef        *hdmatx;                   

  DMA_HandleTypeDef        *hdmarx;                   

  HAL_LockTypeDef           Lock;                     

  volatile HAL_UART_StateTypeDef    gState;              

 

  volatile HAL_UART_StateTypeDef    RxState;             
 

  volatile uint32_t                 ErrorCode;            

#line 283 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"

} UART_HandleTypeDef;

#line 319 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"



 

 


 



 
#line 349 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"


 



 
#line 363 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"






 



 






 



 





 



 






 



 





 



 




 



 




 



 




 

#line 461 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"


 
#line 472 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"


 



 




 



 




 



 




 



 




 



 




 



 




 



 




 



 







 



 
#line 563 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"


 



 




 



 




 



 




 



 




 



 




 



 




 



 




 



 






 



 




 



 




 



 



 



 






 



 




 



 




 



 




 



 



 



 



 





 
#line 763 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"


 


















 
#line 807 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"








 



 
#line 834 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"


 



 






 



 

 


 




 
#line 875 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"




 























 





 





 





 





 





 


#line 943 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"
































 
























 
#line 1010 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"























 
#line 1043 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"























 

























 
#line 1100 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"



















 












 





 





 





 





 














 


















 


















 


















 







 

 


 
#line 1290 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"





 






 






 






 








 









 





 






 









 







 








 










 






 







 







 







 









 







 






 







 







 







 







 







 







 










 
#line 1511 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"





 







 







 







 







 







 








 







 







 







 







 








 



#line 1629 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"



 

 
#line 1 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart_ex.h"
















 

 







 
#line 29 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart_ex.h"



 



 

 


 



 
typedef struct
{
  uint32_t WakeUpEvent;        


 

  uint16_t AddressLength;      
 

  uint8_t Address;              
} UART_WakeUpTypeDef;



 

 


 



 





 



 




 

#line 127 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart_ex.h"


 

 
 


 



 

 
HAL_StatusTypeDef HAL_RS485Ex_Init(UART_HandleTypeDef *huart, uint32_t Polarity, uint32_t AssertionTime,
                                   uint32_t DeassertionTime);



 



 

void HAL_UARTEx_WakeupCallback(UART_HandleTypeDef *huart);








 



 

 
HAL_StatusTypeDef HAL_UARTEx_StopModeWakeUpSourceConfig(UART_HandleTypeDef *huart, UART_WakeUpTypeDef WakeUpSelection);
HAL_StatusTypeDef HAL_UARTEx_EnableStopMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UARTEx_DisableStopMode(UART_HandleTypeDef *huart);


HAL_StatusTypeDef HAL_UARTEx_EnableClockStopMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UARTEx_DisableClockStopMode(UART_HandleTypeDef *huart);


HAL_StatusTypeDef HAL_MultiProcessorEx_AddressLength_Set(UART_HandleTypeDef *huart, uint32_t AddressLength);

#line 186 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart_ex.h"

HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint16_t *RxLen,
                                           uint32_t Timeout);
HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);




 



 

 


 





 
#line 630 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart_ex.h"









 
#line 680 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart_ex.h"





 








 



#line 724 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart_ex.h"


 

 



 



 







#line 1636 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"

 


 



 

 
HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_HalfDuplex_Init(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_LIN_Init(UART_HandleTypeDef *huart, uint32_t BreakDetectLength);
HAL_StatusTypeDef HAL_MultiProcessor_Init(UART_HandleTypeDef *huart, uint8_t Address, uint32_t WakeUpMethod);
HAL_StatusTypeDef HAL_UART_DeInit(UART_HandleTypeDef *huart);
void HAL_UART_MspInit(UART_HandleTypeDef *huart);
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart);

 
#line 1664 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"



 



 

 
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef HAL_UART_DMAPause(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DMAResume(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DMAStop(UART_HandleTypeDef *huart);
 
HAL_StatusTypeDef HAL_UART_Abort(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortTransmit(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortReceive(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_Abort_IT(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortTransmit_IT(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_AbortReceive_IT(UART_HandleTypeDef *huart);

void HAL_UART_IRQHandler(UART_HandleTypeDef *huart);
void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);
void HAL_UART_AbortCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_AbortTransmitCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_AbortReceiveCpltCallback(UART_HandleTypeDef *huart);

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);



 



 

 
void HAL_UART_ReceiverTimeout_Config(UART_HandleTypeDef *huart, uint32_t TimeoutValue);
HAL_StatusTypeDef HAL_UART_EnableReceiverTimeout(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_UART_DisableReceiverTimeout(UART_HandleTypeDef *huart);

HAL_StatusTypeDef HAL_LIN_SendBreak(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_MultiProcessor_EnableMuteMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_MultiProcessor_DisableMuteMode(UART_HandleTypeDef *huart);
void HAL_MultiProcessor_EnterMuteMode(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_HalfDuplex_EnableTransmitter(UART_HandleTypeDef *huart);
HAL_StatusTypeDef HAL_HalfDuplex_EnableReceiver(UART_HandleTypeDef *huart);



 



 

 
HAL_UART_StateTypeDef HAL_UART_GetState(const UART_HandleTypeDef *huart);
uint32_t              HAL_UART_GetError(const UART_HandleTypeDef *huart);



 



 

 


 



HAL_StatusTypeDef UART_SetConfig(UART_HandleTypeDef *huart);
HAL_StatusTypeDef UART_CheckIdleState(UART_HandleTypeDef *huart);
HAL_StatusTypeDef UART_WaitOnFlagUntilTimeout(UART_HandleTypeDef *huart, uint32_t Flag, FlagStatus Status,
                                              uint32_t Tickstart, uint32_t Timeout);
void              UART_AdvFeatureConfig(UART_HandleTypeDef *huart);
HAL_StatusTypeDef UART_Start_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef UART_Start_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);



 

 
#line 1775 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_uart.h"


 



 







#line 451 "../Core/Inc/stm32l4xx_hal_conf.h"










 
#line 477 "../Core/Inc/stm32l4xx_hal_conf.h"





#line 30 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal.h"



 



 

 


 



 
typedef enum
{
  HAL_TICK_FREQ_10HZ         = 100U,
  HAL_TICK_FREQ_100HZ        = 10U,
  HAL_TICK_FREQ_1KHZ         = 1U,
  HAL_TICK_FREQ_DEFAULT      = HAL_TICK_FREQ_1KHZ
} HAL_TickFreqTypeDef;


 



 

 



 



 



 



#line 84 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal.h"
        
        
        



#line 96 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal.h"



 



 
#line 110 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal.h"



 



 
#line 152 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal.h"



 

#line 198 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal.h"




 





 



 





 




 






 



 


 
#line 246 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal.h"



 



 



 

 


 



 


 
















































































































 



 


 



 



 


#line 410 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal.h"
        
        
        

#line 422 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal.h"


 


























 





 




#line 471 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal.h"



 






 




 











 





 





 





 








 



 








 










 



 

 


 



 

#line 570 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal.h"


















#line 605 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal.h"


 



 

 



 
extern volatile uint32_t uwTick;
extern uint32_t uwTickPrio;
extern HAL_TickFreqTypeDef uwTickFreq;


 

 



 



 

 
HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_DeInit(void);
void              HAL_MspInit(void);
void              HAL_MspDeInit(void);
HAL_StatusTypeDef HAL_InitTick (uint32_t TickPriority);



 



 

 
void               HAL_IncTick(void);
void               HAL_Delay(uint32_t Delay);
uint32_t           HAL_GetTick(void);
uint32_t           HAL_GetTickPrio(void);
HAL_StatusTypeDef  HAL_SetTickFreq(HAL_TickFreqTypeDef Freq);
HAL_TickFreqTypeDef HAL_GetTickFreq(void);
void               HAL_SuspendTick(void);
void               HAL_ResumeTick(void);
uint32_t           HAL_GetHalVersion(void);
uint32_t           HAL_GetREVID(void);
uint32_t           HAL_GetDEVID(void);
uint32_t           HAL_GetUIDw0(void);
uint32_t           HAL_GetUIDw1(void);
uint32_t           HAL_GetUIDw2(void);



 



 

 
void              HAL_DBGMCU_EnableDBGSleepMode(void);
void              HAL_DBGMCU_DisableDBGSleepMode(void);
void              HAL_DBGMCU_EnableDBGStopMode(void);
void              HAL_DBGMCU_DisableDBGStopMode(void);
void              HAL_DBGMCU_EnableDBGStandbyMode(void);
void              HAL_DBGMCU_DisableDBGStandbyMode(void);



 



 

 
void              HAL_SYSCFG_SRAM2Erase(void);
void              HAL_SYSCFG_EnableMemorySwappingBank(void);
void              HAL_SYSCFG_DisableMemorySwappingBank(void);


void              HAL_SYSCFG_VREFBUF_VoltageScalingConfig(uint32_t VoltageScaling);
void              HAL_SYSCFG_VREFBUF_HighImpedanceConfig(uint32_t Mode);
void              HAL_SYSCFG_VREFBUF_TrimmingConfig(uint32_t TrimmingValue);
HAL_StatusTypeDef HAL_SYSCFG_EnableVREFBUF(void);
void              HAL_SYSCFG_DisableVREFBUF(void);


void              HAL_SYSCFG_EnableIOAnalogSwitchBooster(void);
void              HAL_SYSCFG_DisableIOAnalogSwitchBooster(void);



 



 



 



 





#line 34 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc_ex.c"



 




 



 
 



 





 
 
 
 
 
 
 




 

 
 
 
 



 



























 











 
HAL_StatusTypeDef HAL_ADCEx_Calibration_Start(ADC_HandleTypeDef *hadc, uint32_t SingleDiff)
{
  HAL_StatusTypeDef tmp_hal_status;
  volatile uint32_t wait_loop_index = 0UL;

   
  ((void)0U);
  ((void)0U);

   
  do{ if((hadc)->Lock == HAL_LOCKED) { return HAL_BUSY; } else { (hadc)->Lock = HAL_LOCKED; } }while (0);

   

   
  tmp_hal_status = ADC_Disable(hadc);

   
  if (tmp_hal_status == HAL_OK)
  {
     
    (((hadc->State)) = ((((((hadc->State))) & (~((0x00000100UL) | (0x00001000UL)))) | ((0x00000002UL)))));



     
    LL_ADC_StartCalibration(hadc->Instance, SingleDiff);

     
    while (LL_ADC_IsCalibrationOnGoing(hadc->Instance) != 0UL)
    {
      wait_loop_index++;
      if (wait_loop_index >= (296960UL))
      {
         
        (((hadc->State)) = ((((((hadc->State))) & (~((0x00000002UL)))) | ((0x00000010UL)))));



         
        do{ (hadc)->Lock = HAL_UNLOCKED; }while (0);

        return HAL_ERROR;
      }
    }

     
    (((hadc->State)) = ((((((hadc->State))) & (~((0x00000002UL)))) | ((0x00000001UL)))));


  }
  else
  {
    ((hadc->State) |= ((0x00000010UL)));

     
     
  }

   
  do{ (hadc)->Lock = HAL_UNLOCKED; }while (0);

   
  return tmp_hal_status;
}








 
uint32_t HAL_ADCEx_Calibration_GetValue(ADC_HandleTypeDef *hadc, uint32_t SingleDiff)
{
   
  ((void)0U);
  ((void)0U);

   
  return LL_ADC_GetCalibrationFactor(hadc->Instance, SingleDiff);
}










 
HAL_StatusTypeDef HAL_ADCEx_Calibration_SetValue(ADC_HandleTypeDef *hadc, uint32_t SingleDiff,
                                                 uint32_t CalibrationFactor)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  uint32_t tmp_adc_is_conversion_on_going_regular;
  uint32_t tmp_adc_is_conversion_on_going_injected;

   
  ((void)0U);
  ((void)0U);
  ((void)0U);

   
  do{ if((hadc)->Lock == HAL_LOCKED) { return HAL_BUSY; } else { (hadc)->Lock = HAL_LOCKED; } }while (0);

   
   
  tmp_adc_is_conversion_on_going_regular = LL_ADC_REG_IsConversionOngoing(hadc->Instance);
  tmp_adc_is_conversion_on_going_injected = LL_ADC_INJ_IsConversionOngoing(hadc->Instance);

  if ((LL_ADC_IsEnabled(hadc->Instance) != 0UL)
      && (tmp_adc_is_conversion_on_going_regular == 0UL)
      && (tmp_adc_is_conversion_on_going_injected == 0UL)
     )
  {
     
    LL_ADC_SetCalibrationFactor(hadc->Instance, SingleDiff, CalibrationFactor);
  }
  else
  {
     
    ((hadc->State) |= ((0x00000020UL)));
     
    ((hadc->ErrorCode) |= ((0x01U)));

     
    tmp_hal_status = HAL_ERROR;
  }

   
  do{ (hadc)->Lock = HAL_UNLOCKED; }while (0);

   
  return tmp_hal_status;
}











 
HAL_StatusTypeDef HAL_ADCEx_InjectedStart(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status;
  uint32_t tmp_config_injected_queue;




   
  ((void)0U);

  if (LL_ADC_INJ_IsConversionOngoing(hadc->Instance) != 0UL)
  {
    return HAL_BUSY;
  }
  else
  {
    





 
    tmp_config_injected_queue = ((hadc->Instance ->CFGR) & ((0x1UL << (31U))));

    if ((((hadc->Instance ->JSQR) & ((0x3UL << (6U)))) == 0UL)
        && (tmp_config_injected_queue == 0UL)
       )
    {
      ((hadc->State) |= ((0x00000020UL)));
      return HAL_ERROR;
    }

     
    do{ if((hadc)->Lock == HAL_LOCKED) { return HAL_BUSY; } else { (hadc)->Lock = HAL_LOCKED; } }while (0);

     
    tmp_hal_status = ADC_Enable(hadc);

     
    if (tmp_hal_status == HAL_OK)
    {
       
      if ((hadc->State & (0x00000100UL)) != 0UL)
      {
         
        ((hadc->ErrorCode) &= ~((0x08U)));
      }
      else
      {
         
        ((hadc)->ErrorCode = (0x00U));
      }

       
       
       
      (((hadc->State)) = ((((((hadc->State))) & (~((0x00000001UL) | (0x00002000UL)))) | ((0x00001000UL)))));



#line 342 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc_ex.c"

       
       
      (((hadc)->Instance ->ISR) = (((0x1UL << (5U)) | (0x1UL << (6U)))));

       
       
       
      do{ (hadc)->Lock = HAL_UNLOCKED; }while (0);

       
       
       
       
       
       
       
       
       
       
       
       
#line 383 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc_ex.c"
      if (LL_ADC_INJ_GetTrigAuto(hadc->Instance) == (0x00000000UL))
      {
         
        LL_ADC_INJ_StartConversion(hadc->Instance);
      }


    }
    else
    {
       
      do{ (hadc)->Lock = HAL_UNLOCKED; }while (0);
    }

     
    return tmp_hal_status;
  }
}
















 
HAL_StatusTypeDef HAL_ADCEx_InjectedStop(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status;

   
  ((void)0U);

   
  do{ if((hadc)->Lock == HAL_LOCKED) { return HAL_BUSY; } else { (hadc)->Lock = HAL_LOCKED; } }while (0);

   
  tmp_hal_status = ADC_ConversionStop(hadc, ((0x00000002UL)));

   
   
  if (tmp_hal_status == HAL_OK)
  {
    if (LL_ADC_REG_IsConversionOngoing(hadc->Instance) == 0UL)
    {
       
      tmp_hal_status = ADC_Disable(hadc);

       
      if (tmp_hal_status == HAL_OK)
      {
         
        (((hadc->State)) = ((((((hadc->State))) & (~((0x00000100UL) | (0x00001000UL)))) | ((0x00000001UL)))));


      }
    }
     
     
    else
    {
       
      ((hadc->State) &= ~((0x00001000UL)));
    }
  }

   
  do{ (hadc)->Lock = HAL_UNLOCKED; }while (0);

   
  return tmp_hal_status;
}








 
HAL_StatusTypeDef HAL_ADCEx_InjectedPollForConversion(ADC_HandleTypeDef *hadc, uint32_t Timeout)
{
  uint32_t tickstart;
  uint32_t tmp_Flag_End;
  uint32_t tmp_adc_inj_is_trigger_source_sw_start;
  uint32_t tmp_adc_reg_is_trigger_source_sw_start;
  uint32_t tmp_cfgr;





   
  ((void)0U);

   
  if (hadc->Init.EOCSelection == ((0x1UL << (3U))))
  {
    tmp_Flag_End = (0x1UL << (6U));
  }
  else  
  {
    tmp_Flag_End = (0x1UL << (5U));
  }

   
  tickstart = HAL_GetTick();

   
  while ((hadc->Instance->ISR & tmp_Flag_End) == 0UL)
  {
     
    if (Timeout != 0xFFFFFFFFU)
    {
      if (((HAL_GetTick() - tickstart) > Timeout) || (Timeout == 0UL))
      {
         
        if ((hadc->Instance->ISR & tmp_Flag_End) == 0UL)
        {
           
          ((hadc->State) |= ((0x00000004UL)));

           
          do{ (hadc)->Lock = HAL_UNLOCKED; }while (0);

          return HAL_TIMEOUT;
        }
      }
    }
  }

   
  tmp_adc_inj_is_trigger_source_sw_start = LL_ADC_INJ_IsTriggerSourceSWStart(hadc->Instance);
  tmp_adc_reg_is_trigger_source_sw_start = LL_ADC_REG_IsTriggerSourceSWStart(hadc->Instance);
   
   
   
#line 545 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc_ex.c"
  tmp_cfgr = ((hadc->Instance ->CFGR));


   
  ((hadc->State) |= ((0x00002000UL)));

   
   
   
  if ((tmp_adc_inj_is_trigger_source_sw_start != 0UL)            ||
      ((((tmp_cfgr) & ((0x1UL << (25U)))) == 0UL)      &&
       ((tmp_adc_reg_is_trigger_source_sw_start != 0UL)  &&
        (((tmp_cfgr) & ((0x1UL << (13U)))) == 0UL))))
  {
     
    if (((((hadc)->Instance ->ISR) & ((0x1UL << (6U)))) == ((0x1UL << (6U)))))
    {
       
       
       
       
       
       
      if (((tmp_cfgr) & ((0x1UL << (21U)))) == 0UL)
      {
         
        ((hadc->State) &= ~((0x00001000UL)));

        if ((hadc->State & (0x00000100UL)) == 0UL)
        {
          ((hadc->State) |= ((0x00000001UL)));
        }
      }
    }
  }

   
  if (tmp_Flag_End == (0x1UL << (6U)))
  {
     
     
     
     
    if (((tmp_cfgr) & ((0x1UL << (14U)))) == 0UL)
    {
      (((hadc)->Instance ->ISR) = (((0x1UL << (5U)) | (0x1UL << (6U)))));
    }
  }
  else
  {
    (((hadc)->Instance ->ISR) = ((0x1UL << (5U))));
  }

   
  return HAL_OK;
}












 
HAL_StatusTypeDef HAL_ADCEx_InjectedStart_IT(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status;
  uint32_t tmp_config_injected_queue;




   
  ((void)0U);

  if (LL_ADC_INJ_IsConversionOngoing(hadc->Instance) != 0UL)
  {
    return HAL_BUSY;
  }
  else
  {
    





 
    tmp_config_injected_queue = ((hadc->Instance ->CFGR) & ((0x1UL << (31U))));

    if ((((hadc->Instance ->JSQR) & ((0x3UL << (6U)))) == 0UL)
        && (tmp_config_injected_queue == 0UL)
       )
    {
      ((hadc->State) |= ((0x00000020UL)));
      return HAL_ERROR;
    }

     
    do{ if((hadc)->Lock == HAL_LOCKED) { return HAL_BUSY; } else { (hadc)->Lock = HAL_LOCKED; } }while (0);

     
    tmp_hal_status = ADC_Enable(hadc);

     
    if (tmp_hal_status == HAL_OK)
    {
       
      if ((hadc->State & (0x00000100UL)) != 0UL)
      {
         
        ((hadc->ErrorCode) &= ~((0x08U)));
      }
      else
      {
         
        ((hadc)->ErrorCode = (0x00U));
      }

       
       
       
      (((hadc->State)) = ((((((hadc->State))) & (~((0x00000001UL) | (0x00002000UL)))) | ((0x00001000UL)))));



#line 687 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc_ex.c"

       
       
      (((hadc)->Instance ->ISR) = (((0x1UL << (5U)) | (0x1UL << (6U)))));

       
       
       
      do{ (hadc)->Lock = HAL_UNLOCKED; }while (0);

       
       
      if ((hadc->Instance->CFGR & (0x1UL << (21U))) != 0UL)
      {
        (((hadc)->Instance ->IER) |= ((0x1UL << (10U))));
      }

       
      switch (hadc->Init.EOCSelection)
      {
        case ((0x1UL << (3U))):
          (((hadc)->Instance ->IER) &= ~((0x1UL << (5U))));
          (((hadc)->Instance ->IER) |= ((0x1UL << (6U))));
          break;
         
        default:
          (((hadc)->Instance ->IER) &= ~((0x1UL << (6U))));
          (((hadc)->Instance ->IER) |= ((0x1UL << (5U))));
          break;
      }

       
       
       
       
       
       
       
       
       
       
       
       
#line 749 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc_ex.c"
      if (LL_ADC_INJ_GetTrigAuto(hadc->Instance) == (0x00000000UL))
      {
         
        LL_ADC_INJ_StartConversion(hadc->Instance);
      }


    }
    else
    {
       
      do{ (hadc)->Lock = HAL_UNLOCKED; }while (0);
    }

     
    return tmp_hal_status;
  }
}



















 
HAL_StatusTypeDef HAL_ADCEx_InjectedStop_IT(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status;

   
  ((void)0U);

   
  do{ if((hadc)->Lock == HAL_LOCKED) { return HAL_BUSY; } else { (hadc)->Lock = HAL_LOCKED; } }while (0);

   
  tmp_hal_status = ADC_ConversionStop(hadc, ((0x00000002UL)));

   
   
   
  if (tmp_hal_status == HAL_OK)
  {
     
    (((hadc)->Instance ->IER) &= ~(((0x1UL << (5U)) | (0x1UL << (6U)) | (0x1UL << (10U)))));

    if (LL_ADC_REG_IsConversionOngoing(hadc->Instance) == 0UL)
    {
       
      tmp_hal_status = ADC_Disable(hadc);

       
      if (tmp_hal_status == HAL_OK)
      {
         
        (((hadc->State)) = ((((((hadc->State))) & (~((0x00000100UL) | (0x00001000UL)))) | ((0x00000001UL)))));


      }
    }
     
     
    else
    {
       
      ((hadc->State) &= ~((0x00001000UL)));
    }
  }

   
  do{ (hadc)->Lock = HAL_UNLOCKED; }while (0);

   
  return tmp_hal_status;
}

#line 1115 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc_ex.c"




























 
uint32_t HAL_ADCEx_InjectedGetValue(ADC_HandleTypeDef *hadc, uint32_t InjectedRank)
{
  uint32_t tmp_jdr;

   
  ((void)0U);
  ((void)0U);

   
  switch (InjectedRank)
  {
    case (((0x00000300UL) | (26UL))):
      tmp_jdr = hadc->Instance->JDR4;
      break;
    case (((0x00000200UL) | (20UL))):
      tmp_jdr = hadc->Instance->JDR3;
      break;
    case (((0x00000100UL) | (14UL))):
      tmp_jdr = hadc->Instance->JDR2;
      break;
    case (((0x00000000UL) | ( 8UL))):
    default:
      tmp_jdr = hadc->Instance->JDR1;
      break;
  }

   
  return tmp_jdr;
}





 
__weak void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc)
{
   
  (void)hadc;

  

 
}









 
__weak void HAL_ADCEx_InjectedQueueOverflowCallback(ADC_HandleTypeDef *hadc)
{
   
  (void)hadc;

  

 
}





 
__weak void HAL_ADCEx_LevelOutOfWindow2Callback(ADC_HandleTypeDef *hadc)
{
   
  (void)hadc;

  

 
}





 
__weak void HAL_ADCEx_LevelOutOfWindow3Callback(ADC_HandleTypeDef *hadc)
{
   
  (void)hadc;

  

 
}






 
__weak void HAL_ADCEx_EndOfSamplingCallback(ADC_HandleTypeDef *hadc)
{
   
  (void)hadc;

  

 
}







 
HAL_StatusTypeDef HAL_ADCEx_RegularStop(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status;

   
  ((void)0U);

   
  do{ if((hadc)->Lock == HAL_LOCKED) { return HAL_BUSY; } else { (hadc)->Lock = HAL_LOCKED; } }while (0);

   
  tmp_hal_status = ADC_ConversionStop(hadc, ((0x00000001UL)));

  
 
  if (tmp_hal_status == HAL_OK)
  {
     
    ((hadc->State) &= ~((0x00000100UL)));

    if (LL_ADC_INJ_IsConversionOngoing(hadc->Instance) == 0UL)
    {
       
      tmp_hal_status = ADC_Disable(hadc);

       
      if (tmp_hal_status == HAL_OK)
      {
         
        (((hadc->State)) = ((((((hadc->State))) & (~((0x00001000UL)))) | ((0x00000001UL)))));


      }
    }
     
     
    else
    {
      ((hadc->State) |= ((0x00001000UL)));
    }
  }

   
  do{ (hadc)->Lock = HAL_UNLOCKED; }while (0);

   
  return tmp_hal_status;
}









 
HAL_StatusTypeDef HAL_ADCEx_RegularStop_IT(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status;

   
  ((void)0U);

   
  do{ if((hadc)->Lock == HAL_LOCKED) { return HAL_BUSY; } else { (hadc)->Lock = HAL_LOCKED; } }while (0);

   
  tmp_hal_status = ADC_ConversionStop(hadc, ((0x00000001UL)));

  
 
  if (tmp_hal_status == HAL_OK)
  {
     
    ((hadc->State) &= ~((0x00000100UL)));

     
    (((hadc)->Instance ->IER) &= ~(((0x1UL << (2U)) | (0x1UL << (3U)) | (0x1UL << (4U)))));

     
    if (LL_ADC_INJ_IsConversionOngoing(hadc->Instance) == 0UL)
    {
      tmp_hal_status = ADC_Disable(hadc);
       
      if (tmp_hal_status == HAL_OK)
      {
         
        (((hadc->State)) = ((((((hadc->State))) & (~((0x00001000UL)))) | ((0x00000001UL)))));


      }
    }
    else
    {
      ((hadc->State) |= ((0x00001000UL)));
    }
  }

   
  do{ (hadc)->Lock = HAL_UNLOCKED; }while (0);

   
  return tmp_hal_status;
}











 
HAL_StatusTypeDef HAL_ADCEx_RegularStop_DMA(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status;

   
  ((void)0U);

   
  do{ if((hadc)->Lock == HAL_LOCKED) { return HAL_BUSY; } else { (hadc)->Lock = HAL_LOCKED; } }while (0);

   
  tmp_hal_status = ADC_ConversionStop(hadc, ((0x00000001UL)));

  
 
  if (tmp_hal_status == HAL_OK)
  {
     
    ((hadc->State) &= ~((0x00000100UL)));

     
    ((hadc->Instance ->CFGR) &= ~((0x1UL << (0U))));

     
     
    tmp_hal_status = HAL_DMA_Abort(hadc->DMA_Handle);

     
    if (tmp_hal_status != HAL_OK)
    {
       
      ((hadc->State) |= ((0x00000040UL)));
    }

     
    (((hadc)->Instance ->IER) &= ~((0x1UL << (4U))));

     
     
     
    if (LL_ADC_INJ_IsConversionOngoing(hadc->Instance) == 0UL)
    {
      if (tmp_hal_status == HAL_OK)
      {
        tmp_hal_status = ADC_Disable(hadc);
      }
      else
      {
        (void)ADC_Disable(hadc);
      }

       
      if (tmp_hal_status == HAL_OK)
      {
         
        (((hadc->State)) = ((((((hadc->State))) & (~((0x00001000UL)))) | ((0x00000001UL)))));


      }
    }
    else
    {
      ((hadc->State) |= ((0x00001000UL)));
    }
  }

   
  do{ (hadc)->Lock = HAL_UNLOCKED; }while (0);

   
  return tmp_hal_status;
}

#line 1594 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc_ex.c"



 

















 


































 
HAL_StatusTypeDef HAL_ADCEx_InjectedConfigChannel(ADC_HandleTypeDef *hadc, ADC_InjectionConfTypeDef *sConfigInjected)
{
  HAL_StatusTypeDef tmp_hal_status = HAL_OK;
  uint32_t tmpOffsetShifted;
  uint32_t tmp_config_internal_channel;
  uint32_t tmp_adc_is_conversion_on_going_regular;
  uint32_t tmp_adc_is_conversion_on_going_injected;
  volatile uint32_t wait_loop_index = 0;

  uint32_t tmp_JSQR_ContextQueueBeingBuilt = 0U;

   
  ((void)0U);
  ((void)0U);
  ((void)0U);
  ((void)0U);
  ((void)0U);
  ((void)0U);
  ((void)0U);
  ((void)0U);
  ((void)0U);
  ((void)0U);

  if (hadc->Init.ScanConvMode != (0x00000000UL))
  {
    ((void)0U);
    ((void)0U);
    ((void)0U);
  }


  
 
  ((void)0U);

   
  ((void)0U);

   
  ((void)0U);

   
  if (sConfigInjected->InjectedSingleDiff != (((0x1UL << (30U)) | (0x7FUL << (16U)))))
  {
    ((void)0U);
  }
  else
  {
    ((void)0U);
  }

   
  do{ if((hadc)->Lock == HAL_LOCKED) { return HAL_BUSY; } else { (hadc)->Lock = HAL_LOCKED; } }while (0);

   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   

  if ((hadc->Init.ScanConvMode == (0x00000000UL))  ||
      (sConfigInjected->InjectedNbrOfConversion == 1U))
  {
     
     
     
     
     
     

    if (sConfigInjected->InjectedRank == (((0x00000000UL) | ( 8UL))))
    {
       
       
       
       
       
      if (sConfigInjected->ExternalTrigInjecConv != ((0x00000000UL)))
      {
        tmp_JSQR_ContextQueueBeingBuilt = (((((sConfigInjected->InjectedChannel) & ((0x1FUL << (26U)))) >> (26UL)) << (((((0x00000000UL) | ( 8UL)))) & (((0x1FUL << (0U))))))
                                           | (sConfigInjected->ExternalTrigInjecConv & (0xFUL << (2U)))
                                           | sConfigInjected->ExternalTrigInjecConvEdge
                                          );
      }
      else
      {
        tmp_JSQR_ContextQueueBeingBuilt = (((((sConfigInjected->InjectedChannel) & ((0x1FUL << (26U)))) >> (26UL)) << (((((0x00000000UL) | ( 8UL)))) & (((0x1FUL << (0U)))))));
      }

      (((hadc->Instance ->JSQR)) = ((((((hadc->Instance ->JSQR))) & (~((((0x3UL << (0U)) | (0xFUL << (2U)) | (0x3UL << (6U)) | (0x1FUL << (8U)) | (0x1FUL << (14U)) | (0x1FUL << (20U)) | (0x1FUL << (26U)) ))))) | (tmp_JSQR_ContextQueueBeingBuilt))));
       
      hadc->InjectionConfig.ContextQueue = tmp_JSQR_ContextQueueBeingBuilt;

    }
  }
  else
  {
     
     
     
     
     
     
     

     
     
    if (hadc->InjectionConfig.ChannelCount == 0U)
    {
       
       
      hadc->InjectionConfig.ChannelCount = sConfigInjected->InjectedNbrOfConversion;
      

 
      hadc->InjectionConfig.ContextQueue = 0x00000000U;

       
       
       
       

       
       
       
       
       
      if (sConfigInjected->ExternalTrigInjecConv != ((0x00000000UL)))
      {
        tmp_JSQR_ContextQueueBeingBuilt = ((sConfigInjected->InjectedNbrOfConversion - 1U)
                                           | (sConfigInjected->ExternalTrigInjecConv & (0xFUL << (2U)))
                                           | sConfigInjected->ExternalTrigInjecConvEdge
                                          );
      }
      else
      {
        tmp_JSQR_ContextQueueBeingBuilt = ((sConfigInjected->InjectedNbrOfConversion - 1U));
      }

    }

     
     
     
    tmp_JSQR_ContextQueueBeingBuilt &= ~(((((0x1FUL << (0U))) & ((0x1FUL << (26U)))) >> (26UL)) << ((sConfigInjected->InjectedRank) & (((0x1FUL << (0U))))));

     
    tmp_JSQR_ContextQueueBeingBuilt |= ((((sConfigInjected->InjectedChannel) & ((0x1FUL << (26U)))) >> (26UL)) << ((sConfigInjected->InjectedRank) & (((0x1FUL << (0U))))));

     
    hadc->InjectionConfig.ChannelCount--;

    

 
    hadc->InjectionConfig.ContextQueue |= tmp_JSQR_ContextQueueBeingBuilt;

    
 
    if (hadc->InjectionConfig.ChannelCount == 0U)
    {
      (((hadc->Instance ->JSQR)) = ((((((hadc->Instance ->JSQR))) & (~((((0x3UL << (0U)) | (0xFUL << (2U)) | (0x3UL << (6U)) | (0x1FUL << (8U)) | (0x1FUL << (14U)) | (0x1FUL << (20U)) | (0x1FUL << (26U)) ))))) | (hadc->InjectionConfig . ContextQueue))));
    }
  }

   
   
   
   
   
   
   
  if (LL_ADC_INJ_IsConversionOngoing(hadc->Instance) == 0UL)
  {
     
    if (sConfigInjected->AutoInjectedConv == DISABLE)
    {
      (((hadc->Instance ->CFGR)) = ((((((hadc->Instance ->CFGR))) & (~((0x1UL << (21U)) | (0x1UL << (20U))))) | ((((uint32_t)sConfigInjected->QueueInjectedContext) << (21U)) | (((uint32_t)sConfigInjected->InjectedDiscontinuousConvMode) << (20U))))));



    }
     
     
    else
    {
      (((hadc->Instance ->CFGR)) = ((((((hadc->Instance ->CFGR))) & (~((0x1UL << (21U)) | (0x1UL << (20U))))) | ((((uint32_t)sConfigInjected->QueueInjectedContext) << (21U))))));


    }

  }

   
   
   
   
   
   
   
  tmp_adc_is_conversion_on_going_regular = LL_ADC_REG_IsConversionOngoing(hadc->Instance);
  tmp_adc_is_conversion_on_going_injected = LL_ADC_INJ_IsConversionOngoing(hadc->Instance);

  if ((tmp_adc_is_conversion_on_going_regular == 0UL)
      && (tmp_adc_is_conversion_on_going_injected == 0UL)
     )
  {
     
     
    if ((sConfigInjected->ExternalTrigInjecConv == ((0x00000000UL)))
        || (sConfigInjected->ExternalTrigInjecConvEdge == (0x00000000UL)))
    {
      if (sConfigInjected->AutoInjectedConv == ENABLE)
      {
        ((hadc->Instance ->CFGR) |= ((0x1UL << (25U))));
      }
      else
      {
        ((hadc->Instance ->CFGR) &= ~((0x1UL << (25U))));
      }
    }
     
     
    else
    {
      if (sConfigInjected->AutoInjectedConv == ENABLE)
      {
         
        ((hadc->State) |= ((0x00000020UL)));

        tmp_hal_status = HAL_ERROR;
      }
      else
      {
        ((hadc->Instance ->CFGR) &= ~((0x1UL << (25U))));
      }
    }

    if (sConfigInjected->InjecOversamplingMode == ENABLE)
    {
      ((void)0U);
      ((void)0U);

       
      ((void)0U);

       
       
       

       
      (((hadc->Instance ->CFGR2)) = ((((((hadc->Instance ->CFGR2))) & (~((0x1UL << (1U)) | (0x7UL << (2U)) | (0xFUL << (5U))))) | ((0x1UL << (1U)) | sConfigInjected->InjecOversampling . Ratio | sConfigInjected->InjecOversampling . RightBitShift))));
#line 1925 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc_ex.c"
    }
    else
    {
       
      ((hadc->Instance ->CFGR2) &= ~((0x1UL << (1U))));
    }

#line 1951 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc_ex.c"
     
    LL_ADC_SetChannelSamplingTime(hadc->Instance, sConfigInjected->InjectedChannel, sConfigInjected->InjectedSamplingTime);


     

     
     
    tmpOffsetShifted = ((sConfigInjected->InjectedOffset) << ((((hadc)->Instance ->CFGR & (0x3UL << (3U))) >> 3UL) * 2UL));

    if (sConfigInjected->InjectedOffsetNumber != (((0x00000003UL)) + 1U))
    {
       
      LL_ADC_SetOffset(hadc->Instance, sConfigInjected->InjectedOffsetNumber, sConfigInjected->InjectedChannel,
                       tmpOffsetShifted);

    }
    else
    {
       
       
      if (((((LL_ADC_GetOffsetChannel(hadc->Instance, (0x00000000UL))) & ((0x7FFFFUL << (0U)))) == 0UL) ? ( ((LL_ADC_GetOffsetChannel(hadc->Instance, (0x00000000UL))) & ((0x1FUL << (26U)))) >> (26UL) ) : ( (uint32_t)(__clz(__rbit((LL_ADC_GetOffsetChannel(hadc->Instance, (0x00000000UL)))))) ) )
          == ((((sConfigInjected->InjectedChannel) & ((0x7FFFFUL << (0U)))) == 0UL) ? ( ((sConfigInjected->InjectedChannel) & ((0x1FUL << (26U)))) >> (26UL) ) : ( (uint32_t)(__clz(__rbit((sConfigInjected->InjectedChannel)))) ) ))
      {
        LL_ADC_SetOffsetState(hadc->Instance, (0x00000000UL), (0x00000000UL));
      }
      if (((((LL_ADC_GetOffsetChannel(hadc->Instance, (0x00000001UL))) & ((0x7FFFFUL << (0U)))) == 0UL) ? ( ((LL_ADC_GetOffsetChannel(hadc->Instance, (0x00000001UL))) & ((0x1FUL << (26U)))) >> (26UL) ) : ( (uint32_t)(__clz(__rbit((LL_ADC_GetOffsetChannel(hadc->Instance, (0x00000001UL)))))) ) )
          == ((((sConfigInjected->InjectedChannel) & ((0x7FFFFUL << (0U)))) == 0UL) ? ( ((sConfigInjected->InjectedChannel) & ((0x1FUL << (26U)))) >> (26UL) ) : ( (uint32_t)(__clz(__rbit((sConfigInjected->InjectedChannel)))) ) ))
      {
        LL_ADC_SetOffsetState(hadc->Instance, (0x00000001UL), (0x00000000UL));
      }
      if (((((LL_ADC_GetOffsetChannel(hadc->Instance, (0x00000002UL))) & ((0x7FFFFUL << (0U)))) == 0UL) ? ( ((LL_ADC_GetOffsetChannel(hadc->Instance, (0x00000002UL))) & ((0x1FUL << (26U)))) >> (26UL) ) : ( (uint32_t)(__clz(__rbit((LL_ADC_GetOffsetChannel(hadc->Instance, (0x00000002UL)))))) ) )
          == ((((sConfigInjected->InjectedChannel) & ((0x7FFFFUL << (0U)))) == 0UL) ? ( ((sConfigInjected->InjectedChannel) & ((0x1FUL << (26U)))) >> (26UL) ) : ( (uint32_t)(__clz(__rbit((sConfigInjected->InjectedChannel)))) ) ))
      {
        LL_ADC_SetOffsetState(hadc->Instance, (0x00000002UL), (0x00000000UL));
      }
      if (((((LL_ADC_GetOffsetChannel(hadc->Instance, (0x00000003UL))) & ((0x7FFFFUL << (0U)))) == 0UL) ? ( ((LL_ADC_GetOffsetChannel(hadc->Instance, (0x00000003UL))) & ((0x1FUL << (26U)))) >> (26UL) ) : ( (uint32_t)(__clz(__rbit((LL_ADC_GetOffsetChannel(hadc->Instance, (0x00000003UL)))))) ) )
          == ((((sConfigInjected->InjectedChannel) & ((0x7FFFFUL << (0U)))) == 0UL) ? ( ((sConfigInjected->InjectedChannel) & ((0x1FUL << (26U)))) >> (26UL) ) : ( (uint32_t)(__clz(__rbit((sConfigInjected->InjectedChannel)))) ) ))
      {
        LL_ADC_SetOffsetState(hadc->Instance, (0x00000003UL), (0x00000000UL));
      }
    }

  }

   
   
   
  if (LL_ADC_IsEnabled(hadc->Instance) == 0UL)
  {
     
    LL_ADC_SetChannelSingleDiff(hadc->Instance, sConfigInjected->InjectedChannel, sConfigInjected->InjectedSingleDiff);

     
     
    if (sConfigInjected->InjectedSingleDiff == (((0x1UL << (30U)) | (0x7FUL << (16U)))))
    {
       
      LL_ADC_SetChannelSamplingTime(hadc->Instance,
                                    (uint32_t)((((((((((uint32_t)sConfigInjected->InjectedChannel) & ((0x7FFFFUL << (0U)))) == 0UL) ? ( (((uint32_t)sConfigInjected->InjectedChannel) & ((0x1FUL << (26U)))) >> (26UL) ) : ( (uint32_t)(__clz(__rbit(((uint32_t)sConfigInjected->InjectedChannel)))) ) ) + 1UL) & 0x1FUL) <= 9UL) ? ( ((((((((uint32_t)sConfigInjected->InjectedChannel) & ((0x7FFFFUL << (0U)))) == 0UL) ? ( (((uint32_t)sConfigInjected->InjectedChannel) & ((0x1FUL << (26U)))) >> (26UL) ) : ( (uint32_t)(__clz(__rbit(((uint32_t)sConfigInjected->InjectedChannel)))) ) ) + 1UL) & 0x1FUL) << (26UL)) | ((0x00001UL << (0U)) << (((((((uint32_t)sConfigInjected->InjectedChannel) & ((0x7FFFFUL << (0U)))) == 0UL) ? ( (((uint32_t)sConfigInjected->InjectedChannel) & ((0x1FUL << (26U)))) >> (26UL) ) : ( (uint32_t)(__clz(__rbit(((uint32_t)sConfigInjected->InjectedChannel)))) ) ) + 1UL) & 0x1FUL)) | ((0x00000000UL) | (((3UL * (((((((uint32_t)sConfigInjected->InjectedChannel) & ((0x7FFFFUL << (0U)))) == 0UL) ? ( (((uint32_t)sConfigInjected->InjectedChannel) & ((0x1FUL << (26U)))) >> (26UL) ) : ( (uint32_t)(__clz(__rbit(((uint32_t)sConfigInjected->InjectedChannel)))) ) ) + 1UL) & 0x1FUL))) << (20UL))) ) : ( ((((((((uint32_t)sConfigInjected->InjectedChannel) & ((0x7FFFFUL << (0U)))) == 0UL) ? ( (((uint32_t)sConfigInjected->InjectedChannel) & ((0x1FUL << (26U)))) >> (26UL) ) : ( (uint32_t)(__clz(__rbit(((uint32_t)sConfigInjected->InjectedChannel)))) ) ) + 1UL) & 0x1FUL) << (26UL)) | ((0x00001UL << (0U)) << (((((((uint32_t)sConfigInjected->InjectedChannel) & ((0x7FFFFUL << (0U)))) == 0UL) ? ( (((uint32_t)sConfigInjected->InjectedChannel) & ((0x1FUL << (26U)))) >> (26UL) ) : ( (uint32_t)(__clz(__rbit(((uint32_t)sConfigInjected->InjectedChannel)))) ) ) + 1UL) & 0x1FUL)) | ((0x02000000UL) | (((3UL * ((((((((uint32_t)sConfigInjected->InjectedChannel) & ((0x7FFFFUL << (0U)))) == 0UL) ? ( (((uint32_t)sConfigInjected->InjectedChannel) & ((0x1FUL << (26U)))) >> (26UL) ) : ( (uint32_t)(__clz(__rbit(((uint32_t)sConfigInjected->InjectedChannel)))) ) ) + 1UL) & 0x1FUL) - 10UL))) << (20UL))) ) )), sConfigInjected->InjectedSamplingTime);

    }

  }

   
   
   
   
   

  if ((((sConfigInjected->InjectedChannel) & ((0x80000000UL) | (0x00080000UL))) != 0UL))
  {
    tmp_config_internal_channel = LL_ADC_GetCommonPathInternalCh((((ADC_Common_TypeDef *) (((0x40000000UL) + 0x08000000UL) + 0x08040300UL))));

     
     
    if ((sConfigInjected->InjectedChannel == (((((0x10UL << (26U)) | (0x01UL << (26U))) | ((0x02000000UL) | ((21UL) << (20UL))) | ((0x20000UL << (0U)))) | (0x80000000UL))))
        && ((tmp_config_internal_channel & ((0x1UL << (23U)))) == 0UL))
    {
      if ((((hadc)->Instance) == ((ADC_TypeDef *) (((0x40000000UL) + 0x08000000UL) + 0x08040000UL))))
      {
        LL_ADC_SetCommonPathInternalCh((((ADC_Common_TypeDef *) (((0x40000000UL) + 0x08000000UL) + 0x08040300UL))),
                                       ((0x1UL << (23U))) | tmp_config_internal_channel);

         
         
         
         
         
        wait_loop_index = (((120UL) / 10UL) * (((SystemCoreClock / (100000UL * 2UL)) + 1UL) + 1UL));
        while (wait_loop_index != 0UL)
        {
          wait_loop_index--;
        }
      }
    }
    else if ((sConfigInjected->InjectedChannel == (((((0x10UL << (26U)) | (0x02UL << (26U))) | ((0x02000000UL) | ((24UL) << (20UL))) | ((0x40000UL << (0U)))) | (0x80000000UL))))
             && ((tmp_config_internal_channel & ((0x1UL << (24U)))) == 0UL))
    {
      if ((((hadc)->Instance) == ((ADC_TypeDef *) (((0x40000000UL) + 0x08000000UL) + 0x08040000UL))))
      {
        LL_ADC_SetCommonPathInternalCh((((ADC_Common_TypeDef *) (((0x40000000UL) + 0x08000000UL) + 0x08040300UL))),
                                       ((0x1UL << (24U))) | tmp_config_internal_channel);
      }
    }
    else if ((sConfigInjected->InjectedChannel == ((((0x00000000UL) | ((0x00000000UL) | (( 0UL) << (20UL))) | ((0x00001UL << (0U))) ) | (0x80000000UL))))
             && ((tmp_config_internal_channel & ((0x1UL << (22U)))) == 0UL))
    {
      if ((((hadc)->Instance) == ((ADC_TypeDef *) (((0x40000000UL) + 0x08000000UL) + 0x08040000UL))))
      {
        LL_ADC_SetCommonPathInternalCh((((ADC_Common_TypeDef *) (((0x40000000UL) + 0x08000000UL) + 0x08040300UL))),
                                       ((0x1UL << (22U))) | tmp_config_internal_channel);
      }
    }
    else
    {
       
    }
  }

   
  do{ (hadc)->Lock = HAL_UNLOCKED; }while (0);

   
  return tmp_hal_status;
}

#line 2203 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_adc_ex.c"









 
HAL_StatusTypeDef HAL_ADCEx_EnableInjectedQueue(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status;
  uint32_t tmp_adc_is_conversion_on_going_regular;
  uint32_t tmp_adc_is_conversion_on_going_injected;

   
  ((void)0U);

  tmp_adc_is_conversion_on_going_regular = LL_ADC_REG_IsConversionOngoing(hadc->Instance);
  tmp_adc_is_conversion_on_going_injected = LL_ADC_INJ_IsConversionOngoing(hadc->Instance);

   
  if ((tmp_adc_is_conversion_on_going_regular == 0UL)
      && (tmp_adc_is_conversion_on_going_injected == 0UL)
     )
  {
    ((hadc->Instance ->CFGR) &= ~((0x1UL << (31U))));

     
    ((hadc->State) &= ~((0x00004000UL)));

    tmp_hal_status = HAL_OK;
  }
  else
  {
    tmp_hal_status = HAL_ERROR;
  }

  return tmp_hal_status;
}









 
HAL_StatusTypeDef HAL_ADCEx_DisableInjectedQueue(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status;
  uint32_t tmp_adc_is_conversion_on_going_regular;
  uint32_t tmp_adc_is_conversion_on_going_injected;

   
  ((void)0U);

  tmp_adc_is_conversion_on_going_regular = LL_ADC_REG_IsConversionOngoing(hadc->Instance);
  tmp_adc_is_conversion_on_going_injected = LL_ADC_INJ_IsConversionOngoing(hadc->Instance);

   
  if ((tmp_adc_is_conversion_on_going_regular == 0UL)
      && (tmp_adc_is_conversion_on_going_injected == 0UL)
     )
  {
    LL_ADC_INJ_SetQueueMode(hadc->Instance, ((0x1UL << (31U))));
    tmp_hal_status = HAL_OK;
  }
  else
  {
    tmp_hal_status = HAL_ERROR;
  }

  return tmp_hal_status;
}









 
HAL_StatusTypeDef HAL_ADCEx_DisableVoltageRegulator(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status;

   
  ((void)0U);

   
  if (LL_ADC_IsEnabled(hadc->Instance) == 0UL)
  {
    LL_ADC_DisableInternalRegulator(hadc->Instance);
    tmp_hal_status = HAL_OK;
  }
  else
  {
    tmp_hal_status = HAL_ERROR;
  }

  return tmp_hal_status;
}
















 
HAL_StatusTypeDef HAL_ADCEx_EnterADCDeepPowerDownMode(ADC_HandleTypeDef *hadc)
{
  HAL_StatusTypeDef tmp_hal_status;

   
  ((void)0U);

   
  if (LL_ADC_IsEnabled(hadc->Instance) == 0UL)
  {
    LL_ADC_EnableDeepPowerDown(hadc->Instance);
    tmp_hal_status = HAL_OK;
  }
  else
  {
    tmp_hal_status = HAL_ERROR;
  }

  return tmp_hal_status;
}



 



 




 



 
