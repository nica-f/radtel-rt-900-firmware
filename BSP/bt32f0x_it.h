/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BT32F0X_IT_H
#define __BT32F0X_IT_H

/* Includes ------------------------------------------------------------------*/
#include "bt32f0x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);

#endif

/******************* (C) COPYRIGHT  MHSEMICONDUCTOR *****END OF FILE****/
