/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MH210x_CONF_H
#define __MH210x_CONF_H

/* Includes ------------------------------------------------------------------*/
/* Uncomment/Comment the line below to enable/disable peripheral header file inclusion */
#include "bt32f0x_adc.h"
#include "bt32f0x_crc.h"
#include "bt32f0x_comp.h"
#include "bt32f0x_dbgmcu.h"
#include "bt32f0x_dma.h"
#include "bt32f0x_exti.h"
#include "bt32f0x_flash.h"
#include "bt32f0x_gpio.h"
#include "bt32f0x_syscfg.h"
#include "bt32f0x_i2c.h"
#include "bt32f0x_iwdg.h"
#include "bt32f0x_pwr.h"
#include "bt32f0x_rcc.h"
#include "bt32f0x_rtc.h"
#include "bt32f0x_spi.h"
#include "bt32f0x_tim.h"
#include "bt32f0x_usart.h"
#include "bt32f0x_wwdg.h"
#include "bt32f0x_misc.h"  

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line below to expanse the "assert_param" macro in the 
   Standard Peripheral Library drivers code */
/* #define USE_FULL_ASSERT    1 */

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports 
  *         the name of the source file and the source line number of the call 
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif /* __mh210x_CONF_H */

/******************* (C) COPYRIGHT  MHSEMICONDUCTOR *****END OF FILE****/
