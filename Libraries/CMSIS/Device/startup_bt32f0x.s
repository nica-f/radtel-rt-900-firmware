.syntax unified
.cpu cortex-m0
.thumb

/* Vector Table Base Address (Set by Linker Script) */
.equ VTOR, 0x08000000  // Example, ensure this matches your linker script

/* Stack Configuration */
.equ Stack_Size, 0x00003000 /* Stack size (in Bytes) */
.section .stack, "aw", %nobits
.align 3
.global __StackTop
.global __StackLimit
__StackLimit:
.space Stack_Size
__StackTop:

/* Heap Configuration */
.equ Heap_Size, 0x00000000 /* Heap size (in Bytes) */
.section .heap, "aw", %nobits
.align 3
.global __HeapBase
.global __HeapLimit
__HeapBase:
.space Heap_Size
__HeapLimit:

/* Vector Table */
.section .isr_vector, "a", %progbits
.type __isr_vector, %object
.size __isr_vector, . - __isr_vector

.global __isr_vector
.global __Vectors         /* Keil compatibility */
.global __Vectors_End     /* Keil compatibility */
.global __Vectors_Size    /* Keil compatibility */

__isr_vector:
__Vectors:
    .word   __StackTop            /* Top of Stack */
    .word   Reset_Handler         /* Reset Handler */
    .word   NMI_Handler           /* NMI Handler */
    .word   HardFault_Handler     /* Hard Fault Handler */
    .word   0                     /* Reserved */
    .word   0                     /* Reserved */
    .word   0                     /* Reserved */
    .word   0                     /* Reserved */
    .word   0                     /* Reserved */
    .word   0                     /* Reserved */
    .word   0                     /* Reserved */
    .word   SVC_Handler           /* SVCall Handler */
    .word   0                     /* Reserved */
    .word   0                     /* Reserved */
    .word   PendSV_Handler        /* PendSV Handler */
    .word   SysTick_Handler       /* SysTick Handler */

    /* External Interrupts */
    .word   WWDG_IRQHandler                /* Window Watchdog */
    .word   PVD_IRQHandler                 /* PVD through EXTI Line detect */
    .word   RTC_IRQHandler                 /* RTC through EXTI Line */
    .word   FLASH_IRQHandler               /* FLASH */
    .word   RCC_IRQHandler                 /* RCC */
    .word   EXTI0_1_IRQHandler             /* EXTI Line 0 and 1 */
    .word   EXTI2_3_IRQHandler             /* EXTI Line 2 and 3 */
    .word   EXTI4_15_IRQHandler            /* EXTI Line 4 to 15 */
    .word   TS_IRQHandler                  /* TS */
    .word   DMA1_Channel1_IRQHandler       /* DMA1 Channel 1 */
    .word   DMA1_Channel2_3_IRQHandler     /* DMA1 Channel 2 and Channel 3 */
    .word   DMA1_Channel4_5_IRQHandler     /* DMA1 Channel 4 and Channel 5 */
    .word   ADC1_COMP_IRQHandler           /* ADC1, COMP1 and COMP2 */
    .word   TIM1_BRK_UP_TRG_COM_IRQHandler /* TIM1 Break, Update, Trigger and Commutation */
    .word   TIM1_CC_IRQHandler             /* TIM1 Capture Compare */
    .word   TIM2_IRQHandler                /* TIM2 */
    .word   TIM3_IRQHandler                /* TIM3 */
    .word   TIM6_IRQHandler                /* TIM6 */
    .word   TIM7_IRQHandler                /* TIM7 */
    .word   TIM14_IRQHandler               /* TIM14 */
    .word   TIM15_IRQHandler               /* TIM15 */
    .word   TIM16_IRQHandler               /* TIM16 */
    .word   TIM17_IRQHandler               /* TIM17 */
    .word   I2C1_IRQHandler                /* I2C1 */
    .word   I2C2_IRQHandler                /* I2C2 */
    .word   SPI1_IRQHandler                /* SPI1 */
    .word   SPI2_IRQHandler                /* SPI2 */
    .word   USART1_IRQHandler              /* USART1 */
    .word   USART2_IRQHandler              /* USART2 */
    .word   USART3_6IRQHandler             /* USART3_6 */
    .word   ALU_IRQHandler                 /* ALU */
    .word   0                              /* Reserved */
__Vectors_End:

.equ __Vectors_Size, __Vectors_End - __Vectors
.global __initial_sp /* For Keil compatibility, points to top of stack */
.equ __initial_sp, __StackTop

.text
.thumb
.thumb_func

/* Reset Handler */
.global Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
    ldr   r0, =SystemInit
    blx   r0
    /* Call main directly, bypassing __main C library init */
    ldr   r0, =main
    blx   r0
    /* If main returns, loop indefinitely */
LoopForever:
    b LoopForever
.size Reset_Handler, . - Reset_Handler

/* Default Exception Handlers (infinite loops) */
.weak NMI_Handler
.type NMI_Handler, %function
NMI_Handler:
    b .
.size NMI_Handler, . - NMI_Handler

.weak HardFault_Handler
.type HardFault_Handler, %function
HardFault_Handler:
    b .
.size HardFault_Handler, . - HardFault_Handler

.weak SVC_Handler
.type SVC_Handler, %function
SVC_Handler:
    b .
.size SVC_Handler, . - SVC_Handler

.weak PendSV_Handler
.type PendSV_Handler, %function
PendSV_Handler:
    b .
.size PendSV_Handler, . - PendSV_Handler

.weak SysTick_Handler
.type SysTick_Handler, %function
SysTick_Handler:
    b .
.size SysTick_Handler, . - SysTick_Handler

/* Default Interrupt Handlers */
.weak WWDG_IRQHandler
.weak PVD_IRQHandler
.weak RTC_IRQHandler
.weak FLASH_IRQHandler
.weak RCC_IRQHandler
.weak EXTI0_1_IRQHandler
.weak EXTI2_3_IRQHandler
.weak EXTI4_15_IRQHandler
.weak TS_IRQHandler
.weak DMA1_Channel1_IRQHandler
.weak DMA1_Channel2_3_IRQHandler
.weak DMA1_Channel4_5_IRQHandler
.weak ADC1_COMP_IRQHandler
.weak TIM1_BRK_UP_TRG_COM_IRQHandler
.weak TIM1_CC_IRQHandler
.weak TIM2_IRQHandler
.weak TIM3_IRQHandler
.weak TIM6_IRQHandler
.weak TIM7_IRQHandler
.weak TIM14_IRQHandler
.weak TIM15_IRQHandler
.weak TIM16_IRQHandler
.weak TIM17_IRQHandler
.weak I2C1_IRQHandler
.weak I2C2_IRQHandler
.weak SPI1_IRQHandler
.weak SPI2_IRQHandler
.weak USART1_IRQHandler
.weak USART2_IRQHandler
.weak USART3_6IRQHandler
.weak ALU_IRQHandler

.type Default_Handler, %function
Default_Handler:
WWDG_IRQHandler:
PVD_IRQHandler:
RTC_IRQHandler:
FLASH_IRQHandler:
RCC_IRQHandler:
EXTI0_1_IRQHandler:
EXTI2_3_IRQHandler:
EXTI4_15_IRQHandler:
TS_IRQHandler:
DMA1_Channel1_IRQHandler:
DMA1_Channel2_3_IRQHandler:
DMA1_Channel4_5_IRQHandler:
ADC1_COMP_IRQHandler:
TIM1_BRK_UP_TRG_COM_IRQHandler:
TIM1_CC_IRQHandler:
TIM2_IRQHandler:
TIM3_IRQHandler:
TIM6_IRQHandler:
TIM7_IRQHandler:
TIM14_IRQHandler:
TIM15_IRQHandler:
TIM16_IRQHandler:
TIM17_IRQHandler:
I2C1_IRQHandler:
I2C2_IRQHandler:
SPI1_IRQHandler:
SPI2_IRQHandler:
USART1_IRQHandler:
USART2_IRQHandler:
USART3_6IRQHandler:
ALU_IRQHandler:
    b .
.size Default_Handler, . - Default_Handler

/* User Stack and Heap initialization (MicroLIB or standard library) */
.section .text.init_stack_heap
.global __User_Initial_StackHeap
.type __User_Initial_StackHeap, %function
__User_Initial_StackHeap:
#ifdef __MICROLIB
    /* For microlib, __initial_sp, __heap_base, __heap_limit are exported directly */
    /* and the C library handles initialization. */
    bx lr
#else
    /* For standard library, provide __user_initial_stackheap */
    .global __use_two_region_memory
    ldr r0, =__HeapBase
    ldr r1, =__StackTop
    ldr r2, =__HeapLimit
    ldr r3, =__StackLimit  /* Keil uses Stack_Mem as bottom, GCC uses __StackLimit */
    bx lr
#endif
.size __User_Initial_StackHeap, . - __User_Initial_StackHeap

.end
