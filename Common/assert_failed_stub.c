#include <stdint.h>
#include <stdio.h> // For printf, if used

/*
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
__attribute__((weak)) void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %ld\r\n", file, line); */
  /* Or send to a serial port, or blink an LED, etc. */
  
  /* Infinite loop */
  while (1)
  {
  }
}
