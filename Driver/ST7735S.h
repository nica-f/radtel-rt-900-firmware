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
//画笔颜色
#define WHITE           0xFFFF //白色
#define BLACK           0x0000 //黑色
#define BLUE            0x001F //蓝色
#define BRED            0XF81F
#define GRED            0XCDFC //灰色
#define GBLUE           0X07FF //吉蓝
#define RED             0xF800 //红色
#define MAGENTA         0xF81F //酒红
#define GREEN           0x07E0 //绿色
#define CYAN            0x7FFF //蓝绿
#define YELLOW          0xFFE0 //黄色
#define BROWN           0XBC40 //棕色
#define BRRED           0XFC07 //棕红色
#define GRAY            0X8430 //灰色
#define LIGHTGRAY       0XEF1C //浅灰色

#define BLUEBLACK       0X0109
#define SKYBLUE         0X341F
//GUI颜色

#define BLUE2           0x211F //蓝色
#define DARKBLUE        0X01CF //深蓝色
#define LIGHTBLUE       0X7D7C //浅蓝色
#define GRAYBLUE        0X5458 //灰蓝色
#define DARKGREEN       0x0679 //青绿色
#define PALEBLUE        0xCF1E //淡蓝色

//以上三色为PANEL的颜色

#define LIGHTGREEN      0X841F //浅绿色
#define LGRAY           0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE       0XA651 //浅灰蓝色(中间层颜色)
#define LIGHTBLUE_1     0XAEBF //浅蓝色
#define LBBLUE          0X2B12 //浅棕蓝色(选择条目的反色)

/*LCD显示方向定义*/
//#define FORWORD   /*LCD正向显示*/
#define BACKWORD  /*LCD倒向显示*/

#define ROW_OFFSET        0 
#define COLUMN_OFFSET     0


/*****************************************************************************/
/*配置液显示方向以及RGB模式*/
 #define LCD_DIR_DATA     0x60//0xA8       //正向横屏,RGB = 1;

#ifndef LCD_COLOUR_REV
    #define LCD_COLOUR_REV   0         //定义颜色反向标志 0正常显示不设置 
#endif

/* Exported macro ------------------------------------------------------------*/
/* Exported typedef ----------------------------------------------------------*/
typedef enum
{
  LCD_Switch_OFF                  = 0, /*关显示*/
  LCD_Switch_ON                   = 1, /*开显示*/
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
