#ifndef __BOARD_H
    #define __BOARD_H


/*************************************************************************************/
extern void GpioModeSwitch(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,uint8_t mode);
extern void uartSendChar( uint8_t ch );
extern uint8_t UserADC_GetValOfBatt(void);
extern uint8_t UserADC_GetValOfVox(void);
extern void Board_Init(void);

extern void USART1_Handler(void);
extern void DMA1Int_Handler(void);

extern void AmAgcValSet(uint8_t val);


#endif
