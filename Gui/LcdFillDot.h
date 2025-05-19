#ifndef __LCDFILLDOT_H
    #define __LCDFILLDOT_H

#define LCD_WIDTH                             160
#define LCD_HEIGHT                            128

// RGB-565
#define COLOR_BACKGROUND                      0X0000
#define COLOR_WORK_AREA                       0X0188
#define COLOR_FOREGROUND                      0XFFFF
#define COLOR_NOT_WORK                        0X18E3
#define COLOR_CH_NUM                          0XFFFF
#define COLOR_CH_NAME                         0X059B
#define COLOR_ARROW_MAIN                      0xE0A3
#define COLOR_ARROW_AUX                       0XA514

#define COLOR_TXPWR_LEVEL_0                   0xA514
#define COLOR_TXPWR_LEVEL_HIGH                0X07E0
#define COLOR_TXPWR_LEVEL_MID                 0X07E0
#define COLOR_TXPWR_LEVEL_LOW                 0X07E0

#define COLOR_RSSI_0                          0xA514
#define COLOR_RSSI_1                          0xE9A3

extern void LCD_ClearArea(uint16_t posX, uint16_t posY, uint16_t width, uint16_t height, uint16_t backColor);
extern void LCD_DisplayText(uint16_t posX,uint16_t posY,uint08_t *pString,uint08_t fontSize,uint16_t brushColor,uint16_t backColor, uint08_t divDot);
extern void LCD_DisplayText5X7(uint16_t posX, uint16_t posY, uint08_t *pString,uint16_t len, uint16_t brushColor, uint16_t backColor);
extern void LCD_DrawRectangle(uint16_t posX, uint16_t posY, uint16_t width, uint16_t height, uint16_t color );
extern void LCD_DisplayIcon(uint16_t posX,uint16_t posY,uint16_t width,uint16_t height,const uint08_t *pdat,uint16_t brushColor,uint16_t backColor);
extern void LCD_DisplayNum6X9(uint16_t posX,uint16_t posY,uint08_t *pString,uint16_t backColor);
extern void LCD_DisplayNum12x17(uint16_t posX,uint16_t posY,uint08_t *pString,uint16_t backColor);


#endif
