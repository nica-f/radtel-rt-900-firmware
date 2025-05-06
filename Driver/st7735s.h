#ifndef __ST7735S_H
#define __ST7735S_H

#include "includes.h"

/* Includes ------------------------------------------------------------------*/

/* Private defines -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Exported defines ----------------------------------------------------------*/
//������ɫ
#define WHITE           0xFFFF //��ɫ
#define BLACK           0x0000 //��ɫ
#define BLUE            0x001F //��ɫ
#define BRED            0XF81F
#define GRED            0XCDFC //��ɫ
#define GBLUE           0X07FF //����
#define RED             0xF800 //��ɫ
#define MAGENTA         0xF81F //�ƺ�
#define GREEN           0x07E0 //��ɫ
#define CYAN            0x7FFF //����
#define YELLOW          0xFFE0 //��ɫ
#define BROWN           0XBC40 //��ɫ
#define BRRED           0XFC07 //�غ�ɫ
#define GRAY            0X8430 //��ɫ
#define LIGHTGRAY       0XEF1C //ǳ��ɫ

#define BLUEBLACK       0X0109
#define SKYBLUE         0X341F
//GUI��ɫ

#define BLUE2           0x211F //��ɫ
#define DARKBLUE        0X01CF //����ɫ
#define LIGHTBLUE       0X7D7C //ǳ��ɫ
#define GRAYBLUE        0X5458 //����ɫ
#define DARKGREEN       0x0679 //����ɫ
#define PALEBLUE        0xCF1E //����ɫ

//������ɫΪPANEL����ɫ

#define LIGHTGREEN      0X841F //ǳ��ɫ
#define LGRAY           0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE       0XA651 //ǳ����ɫ(�м����ɫ)
#define LIGHTBLUE_1     0XAEBF //ǳ��ɫ
#define LBBLUE          0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

/*LCD��ʾ������*/
//#define FORWORD   /*LCD������ʾ*/
#define BACKWORD  /*LCD������ʾ*/

#define ROW_OFFSET        0 
#define COLUMN_OFFSET     0


/*****************************************************************************/
/*����Һ��ʾ�����Լ�RGBģʽ*/
 #define LCD_DIR_DATA     0x60//0xA8       //�������,RGB = 1;

#ifndef LCD_COLOUR_REV
    #define LCD_COLOUR_REV   0         //������ɫ�����־ 0������ʾ������ 
#endif

/* Exported macro ------------------------------------------------------------*/
/* Exported typedef ----------------------------------------------------------*/
typedef enum
{
  LCD_Switch_OFF                  = 0, /*����ʾ*/
  LCD_Switch_ON                   = 1, /*����ʾ*/
}LCD_SwitchMode_TypeDef;

/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
void ST7735S_Display_ON(void);
void ST7735S_Display_OFF(void);
void ST7735S_Cursor_Set(uint16_t Xpos, uint16_t Ypos);
void ST7735S_Init(void);
void ST7735S_Command_Write(uint8_t cmd);

void ST7735S_DrawPoint(uint16_t x, uint16_t y, uint16_t color);
void ST7735S_Window(uint16_t StartX, uint16_t StartY, uint16_t EndX, uint16_t EndY, uint16_t back_color);
void ST7735S_Clear(uint16_t back_color);
void ST7735S_Byte2Point(uint8_t dat, uint16_t back_color, uint16_t brush_color);

void ST7735S_GRAM_Write(void);
void WriteWord(uint16_t word);
void ST7735S_SetRamAddr(uint8_t xStart,uint8_t xEnd,uint8_t yStart,uint8_t yEnd);
void ST7735S_Data_Write(uint8_t dat);

void ST7735S_DisplayArea(uint16_t posX, uint16_t posY, uint16_t width,uint16_t height,const uint08_t *pdat,uint16_t brushColor, uint16_t backColor);
void ST7735S_DisplayColorArea(uint16_t posX, uint16_t posY, uint16_t width, uint16_t height, const uint08_t *pdat);
void ST7735S_ClearArea(uint16_t posX, uint16_t posY, uint16_t width,uint16_t height,uint16_t Color);
void ST7735S_DrawHorizonLine(uint16_t x0, uint16_t y,uint16_t x1,uint16_t Color,uint16_t wide);
void ST7735S_DrawVerticalLine(uint16_t x, uint16_t y0,uint16_t y1,uint16_t Color,uint16_t wide);
void ST7735S_DrawRect(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t Color);
void ST7735S_DrawRoundRectFill(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t Color);


/* ---------------------------------------------------------------------------*/
#endif

/*******************************************************************************
      END OF FILE
*******************************************************************************/
