/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup bt32f0x_system
  * @{
  */  
  
/**
  * @brief Define to prevent recursive inclusion
  */
#ifndef __SYSTEM_BT32F0X_H
#define __SYSTEM_BT32F0X_H

#ifdef __cplusplus
 extern "C" {
#endif 

/** @addtogroup BT32F0X_System_Includes
  * @{
  */

/**
  * @}
  */


/** @addtogroup BT32F0X_System_Exported_types
  * @{
  */

extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */

/**
  * @}
  */

/** @addtogroup BT32F0X_System_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @addtogroup BT32F0X_System_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup BT32F0X_System_Exported_Functions
  * @{
  */
  
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_BT32F0X_H */

/**
  * @}
  */
  
/**
  * @}
  */  
