
/* Includes ------------------------------------------------------------------*/
#include "includes.h"

/* Private defines -----------------------------------------------------------*/
#define ST7735S_RST_H                 GPIOA->BSRR = GPIO_Pin_8
#define ST7735S_RST_L                 GPIOA->BRR = GPIO_Pin_8

#define ST7735S_CS_H                  GPIOB->BSRR = GPIO_Pin_12 
#define ST7735S_CS_L                  GPIOB->BRR  = GPIO_Pin_12

#define ST7735S_RS_H                  GPIOB->BSRR = GPIO_Pin_14
#define ST7735S_RS_L                  GPIOB->BRR  = GPIO_Pin_14 


/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Exported defines ----------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported typedef ----------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/

/* Functions -----------------------------------------------------------------*/
#define LCD_USE_SPI         SPI2
/*******************************************************************************
* Function Name  : Delay
* Description    : OOK 配置
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void ST7735S_delay(long i)
{
    while(i--);
}

#define ST7735S_DELAY      __nop();__nop();__nop();

/*******************************************************************************
* Function Name  : ST7735S_Command_Write
* Description    : 命令写
* Input          : command -> 命令
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void ST7735S_Command_Write(uint08_t cmd)
{
    ST7735S_CS_L;
    ST7735S_RS_L;
    ST7735S_DELAY;

    while(RESET == SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE));
    SPI_SendData8(SPI2, cmd);
    while(SET == SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY));
   
    ST7735S_DELAY;
    ST7735S_CS_H;
}

/*******************************************************************************
* Function Name  : ST7735S_Data_Write
* Description    : 数据写
* Input          : data1 ->数据
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void ST7735S_Data_Write(uint08_t dat)
{
    ST7735S_CS_L;
    ST7735S_RS_H;
    ST7735S_DELAY;
 
    while(RESET == SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE));
    SPI_SendData8(SPI2, dat);
    while(SET == SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY));  

    ST7735S_DELAY;
    ST7735S_CS_H;
}
/*******************************************************************************
* Function Name  : ST7735S_GRAM_Write
* Description    : ST7735S GRAM写
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void ST7735S_GRAM_Write(void)
{
    ST7735S_Command_Write(0x2C);
}

/*******************************************************************************
* Function Name  : ST7735S_Display_On
* Description    : ST7735S开启显示
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void ST7735S_Display_ON(void)
{
    ST7735S_Command_Write(0x28); //Dislay Off
    ST7735S_Command_Write(0x10); //Sleep In
}

/*******************************************************************************
* Function Name  : ST7735S_Display_Off
* Description    : ST7735S关闭显示
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void ST7735S_Display_OFF(void)
{
    ST7735S_Command_Write(0x11); //Sleep Out
    ST7735S_Command_Write(0x29); //Dislay On
}

/*******************************************************************************
* Function Name  : ST7735S_Cursor_Set
* Description    : ST7735S光标设置
* Input          : Xpos,Ypos -> 坐标
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void ST7735S_Cursor_Set(uint16_t Xpos, uint16_t Ypos)
{
    Xpos += ROW_OFFSET;
    Ypos += COLUMN_OFFSET;

    /*Set Column Address*/
    ST7735S_Command_Write(0x2A);
    ST7735S_Data_Write(Xpos >> 8);
    ST7735S_Data_Write(Xpos);

    /*Set Page Address*/
    ST7735S_Command_Write(0x2B);
    ST7735S_Data_Write(Ypos >> 8);
    ST7735S_Data_Write(Ypos);
}

/*******************************************************************************
* Function Name  : ST7735S_Window_Set
* Description    : ST7735S 窗口设置
* Input          : Xpos,Ypos    -> 起始坐标
                   width,height -> 窗口大小(必须大于0)
* Output         : None
* Return         : None
* Attention      : 窗体大小:width*height
*******************************************************************************/
void ST7735S_Window_Set(uint16_t sx, uint16_t sy, uint16_t width, uint16_t height)
{
    uint16_t twidth,theight;

    sx += ROW_OFFSET;
    sy += COLUMN_OFFSET;

    twidth  = sx + width - 1;
    theight = sy + height - 1;

    /*Set Column Address*/
    ST7735S_Command_Write(0x2A);
    ST7735S_Data_Write(sx >> 8);
    ST7735S_Data_Write(sx);
    ST7735S_Data_Write(twidth >> 8);
    ST7735S_Data_Write(twidth);

    /*Set Page Address*/
    ST7735S_Command_Write(0x2B);
    ST7735S_Data_Write(sy >> 8);
    ST7735S_Data_Write(sy);
    ST7735S_Data_Write(theight >> 8);
    ST7735S_Data_Write(theight);
}

/*******************************************************************************
* Function Name  : ST7735S_DrawPoint
* Description    : 画点
* Input          : Xpos,Ypos -> 坐标
                   color     -> 颜色
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void ST7735S_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
    x += ROW_OFFSET;
    y += COLUMN_OFFSET;

    /*Set Column Address*/
    ST7735S_Command_Write(0x2A);
    ST7735S_Data_Write(x >> 8);
    ST7735S_Data_Write(x);
    ST7735S_Data_Write(x >> 8);
    ST7735S_Data_Write(x);

    /*Set Page Address*/
    ST7735S_Command_Write(0x2B);
    ST7735S_Data_Write(y >> 8);
    ST7735S_Data_Write(y);
    ST7735S_Data_Write(y >> 8);
    ST7735S_Data_Write(y);

    /*Set GRAM*/
    ST7735S_Command_Write(0x2C);
    ST7735S_Data_Write(color >> 8);
    ST7735S_Data_Write(color);
}
/*******************************************************************************
* Function Name  : ST7735S_Window
* Description    : ST7735S 初始化
* Input          : StartX, StartY ->
                   EndX,   EndY   ->
                   color          ->
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void ST7735S_Window(uint16_t StartX, uint16_t StartY, uint16_t EndX, uint16_t EndY, uint16_t back_color)
{
    uint16_t len;
    uint16_t i;
    uint16_t width,height;

    i = 0;

    width = EndX - StartX;
    height = EndY - StartY;
    len = width * height;

    if(EndX <= 0)
    {
        return;
    }

    ST7735S_Window_Set(StartX, StartY, width, height);

    /*设置光标位置*/
    ST7735S_Cursor_Set(StartX, StartY);

    /*开始写入GRAM*/
    ST7735S_GRAM_Write();

    for(i = 0; i < len; i++)
    {
        ST7735S_Data_Write(back_color>> 8);
        ST7735S_Data_Write(back_color);
    }
}

/*******************************************************************************
* Function Name  : ST7735S_Clear
* Description    : ST7735S 显示清除
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void ST7735S_Clear(uint16_t back_color)
{
    ST7735S_Window(0, 0, 160, 128, back_color);
}
/*******************************************************************************
* Function Name  : ST7735S_Configuration
* Description    : ST7735S初始化配置
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void ST7735S_Init(void)
{
    ST7735S_RST_H;
    DelayMs(1);
    ST7735S_RST_L;
    DelayMs(1);
    ST7735S_RST_H;
    
    DelayMs(120);
    ST7735S_Command_Write(0x11); //Sleep out
    DelayMs(120); //Delay 120ms
  
    /*----------------------------------- ST7735R Frame Rate -------------------*/
    /*帧数率控制(正常模式/全彩)*/
    ST7735S_Command_Write(0xB1);
    ST7735S_Data_Write(0x05);
    ST7735S_Data_Write(0x3A);
    ST7735S_Data_Write(0x3A);
    /*帧数率控制(待机/8色)*/
    ST7735S_Command_Write(0xB2);
    ST7735S_Data_Write(0x05);
    ST7735S_Data_Write(0x3A);
    ST7735S_Data_Write(0x3A);
    /*帧数率控制(部分模式/全彩)*/
    ST7735S_Command_Write(0xB3);
    ST7735S_Data_Write(0x05);
    ST7735S_Data_Write(0x3A);
    ST7735S_Data_Write(0x3A);
    ST7735S_Data_Write(0x05);
    ST7735S_Data_Write(0x3A);
    ST7735S_Data_Write(0x3A);
  
    /*----------------------------------- End ST7735R Frame Rate ---------------*/
    /*显示反反显控制*/
    ST7735S_Command_Write(0xB4); //Column inversion
    ST7735S_Data_Write(0x03);//0x07
  
    /*ST7735S_Command_Write(0xB6);
    ST7735S_Data_Write(0xb4);
    ST7735S_Data_Write(0xf0);*/
  
    /*----------------------------------- ST7735R Power Sequence ---------------*/
    ST7735S_Command_Write(0xC0);
    ST7735S_Data_Write(0x62);
    ST7735S_Data_Write(0x02);
    ST7735S_Data_Write(0x04);
  
    ST7735S_Command_Write(0xC1);
    ST7735S_Data_Write(0xC0);
  
    ST7735S_Command_Write(0xC2);
    ST7735S_Data_Write(0x0D);
    ST7735S_Data_Write(0x00);
  
    ST7735S_Command_Write(0xC3);
    ST7735S_Data_Write(0x8D);
    ST7735S_Data_Write(0X6A);
  
    ST7735S_Command_Write(0xC4);
    ST7735S_Data_Write(0x8D);
    ST7735S_Data_Write(0xEE);
  
    /*----------------------------------- End ST7735R Power Sequence------------*/
    ST7735S_Command_Write(0xC5); //VCOM
    ST7735S_Data_Write(0x12);//0x10
  
    /*----------------------------------- ST7735R Gamma Sequence ---------------*/
    ST7735S_Command_Write(0xe0);
    ST7735S_Data_Write(0x03);
    ST7735S_Data_Write(0x1b);
    ST7735S_Data_Write(0x12);//0x07
    ST7735S_Data_Write(0x11);
    ST7735S_Data_Write(0x3f);
    ST7735S_Data_Write(0x3A);
    ST7735S_Data_Write(0x32);
    ST7735S_Data_Write(0x34);
    ST7735S_Data_Write(0x2F);
    ST7735S_Data_Write(0x2B);
    ST7735S_Data_Write(0x30);
    ST7735S_Data_Write(0x3A);
    ST7735S_Data_Write(0x00);
    ST7735S_Data_Write(0x01);
    ST7735S_Data_Write(0x02);
    ST7735S_Data_Write(0x05);
  
    ST7735S_Command_Write(0xe1);
    ST7735S_Data_Write(0x03);
    ST7735S_Data_Write(0x1B);
    ST7735S_Data_Write(0x12);
    ST7735S_Data_Write(0x11);
    ST7735S_Data_Write(0x32);
    ST7735S_Data_Write(0x2F);
    ST7735S_Data_Write(0x2A);
    ST7735S_Data_Write(0x2F);
    ST7735S_Data_Write(0x2E);
    ST7735S_Data_Write(0x2C);
    ST7735S_Data_Write(0x35);
    ST7735S_Data_Write(0x3F);
    ST7735S_Data_Write(0x00);
    ST7735S_Data_Write(0x00);
    ST7735S_Data_Write(0x01);
    ST7735S_Data_Write(0x05);
  
    /*----------------------------------- End ST7735R Gamma Sequence -----------*/
    ST7735S_Command_Write(0xFC); //Enable Gate power save mode
    ST7735S_Data_Write(0x8C);
  
    ST7735S_Command_Write(0x36); //65k mode 
    ST7735S_Data_Write(LCD_DIR_DATA); 
    
  #if LCD_COLOUR_REV
    ST7735S_Command_Write(0x21); //显示颜色反向
  #endif

    ST7735S_Command_Write(0x3A); //16bit pixel
    ST7735S_Data_Write(0x05);

    ST7735S_Clear(0x0000);
    ST7735S_Command_Write(0x29); //Display on
    //ST7735S_Command_Write(0x2C); //
    //
}

/*******************************************************************************
* Function Name  : ST7735S_Switch_Set
* Description    : ST7735S显示开关
* Input          : None
* Output         : None
* Return         : None
* Attention      : None
*******************************************************************************/
void ST7735S_Switch_Set(LCD_SwitchMode_TypeDef LCD_Switch)
{
    if(LCD_Switch == LCD_Switch_ON)
    {
        /*开显示*/
        ST7735S_Command_Write(0xaf);
    }
    else
    {
        /*关显示*/
        ST7735S_Command_Write(0xae);
    }
}

/****************************************************************************
*    函数名:  ST7735S_Byte2Point
*    描  述:  本函数用于 用 1Byte的数据显示 8个点
*    注  意: 本函数仅内部使用
****************************************************************************/
void ST7735S_Byte2Point(uint08_t dat, uint16_t back_color, uint16_t brush_color)
{
    uint08_t i;

	for( i = 0; i < 8; i++ )
	{
        if( dat & 0x01 )
        {
            ST7735S_Data_Write( brush_color>>8 );
			ST7735S_Data_Write( brush_color );
		}
		else
		{
            ST7735S_Data_Write( back_color>>8 );
			ST7735S_Data_Write( back_color );
		}

		dat >>= 1;
	}
}
/*********************************************************************
* 函 数 名: WriteWord
* 功能描述: 底层函数，向ST7735S写入两字节数据
* 全局变量: 无
* 输入参数：word:需要写入的数据
* 输出参数:
* 返　　回:
* 调用函数: ST7735WriteData
* 说    明：2013.4.9 hht  v1.0
***********************************************************************/ 
void WriteWord(uint16_t word)
{  
    ST7735S_Data_Write(word>>8);
	ST7735S_Data_Write(word&0xff);
}

/*********************************************************************
* 函 数 名: ST7735SetRamAddr
* 功能描述: ST7735设置DRAN开始与结束地址
* 全局变量: 无
* 输入参数：x：横坐标(0-160) ,y：纵坐标(0-128), Color:颜色
* 输出参数:
* 返　　回:
* 调用函数: ST7735S_Command_Write,WriteWord
* 说    明：2013.4.9 hht  v1.0
***********************************************************************/ 
void ST7735S_SetRamAddr(uint08_t xStart,uint08_t xEnd,uint08_t yStart,uint08_t yEnd)
{
    xStart += ROW_OFFSET;
    yStart += COLUMN_OFFSET;
    xEnd += ROW_OFFSET -1;
    yEnd += COLUMN_OFFSET -1;
    ST7735S_Command_Write(0x2A);							//设置点横坐标范围
    WriteWord(xStart);
    WriteWord(xEnd);
	ST7735S_Command_Write(0x2B);							//设置纵坐标范围
	WriteWord(yStart);
	WriteWord(yEnd);
}

void ST7735S_DisplayArea(uint16_t posX, uint16_t posY, uint16_t width,uint16_t height,const uint08_t *pdat,uint16_t brushColor, uint16_t backColor)
{
    uint16_t i,j,k;
    uint16_t pos;

    if( width == 0 || height == 0)
	{
        return;
	}

	ST7735S_SetRamAddr(posX,posX+width,posY,posY+height);	

    k = 0x01;
    pos = 0;
    ST7735S_GRAM_Write();
    for (i=0;i< height;i++)
	{
		for (j=0;j<width;j++)
		{        
		    if(pdat[j + pos] & k)
		    {
                WriteWord(brushColor);
		    }
		    else
		    {
		        WriteWord(backColor);
		    }
		}

        if((i+1) % 8 == 0)
        {
            k = 0x01;
            pos += width; 
        }
        else
        {
            k <<= 1;
        }
	}
}


void ST7735S_DisplayColorArea(uint16_t posX, uint16_t posY, uint16_t width, uint16_t height, const uint08_t *pdat)
{
    uint16_t i,j;
    uint16_t pos;
    uint16_t color;

    if(width == 0 || height == 0)
    {
        return;
    }
    
    ST7735S_SetRamAddr(posX, posX+width, posY, posY+height);

    pos = 0;
    ST7735S_GRAM_Write();
    for(i = 0; i < height; i++)
    {
        for(j = 0; j < width; j++)
        {
            pos = (i * width + j) * 2;
            color = pdat[pos + 1];
            color <<= 8;
            color |= pdat[pos];

            WriteWord(color);
        }
    }
}

void ST7735S_ClearArea(uint16_t posX, uint16_t posY, uint16_t width,uint16_t height,uint16_t Color)
{
    uint16_t i,j;

    if( width == 0 || height == 0 )
	{
        return;
	}
	ST7735S_SetRamAddr(posX,posX+width,posY,posY+height);	

	ST7735S_GRAM_Write();
	for (i=0;i<height;i++)
	{
		for (j=0;j<width;j++)
		{        
			WriteWord(Color);
		}
	}
}

void ST7735S_DrawHorizonLine(uint16_t x0, uint16_t y,uint16_t x1,uint16_t Color,uint16_t wide)
{
  	uint16_t i,j;

    ST7735S_SetRamAddr(x0,x1,y,y+wide);	
	ST7735S_GRAM_Write();							//写颜色
	x1 = (x1 > x0 ) ? (x1 - x0) : (x0 - x1);
	for (i=0;i<=x1;i++)
	{
	    for(j=0;j<wide;j++)
	    {        
	        WriteWord( Color );
	    }
	}
}

void ST7735S_DrawVerticalLine(uint16_t x, uint16_t y0,uint16_t y1,uint16_t Color,uint16_t wide)
{
  	uint16_t i,j;

  	ST7735S_SetRamAddr(x,x+wide,y0,y1);
	
	ST7735S_GRAM_Write();
	y1 = (y1 > y0 ) ? (y1 - y0) : (y0 - y1);
	for (i=0;i<y1;i++)
	{
	    for(j=0;j<wide;j++)
	    {        
	        WriteWord( Color );
	    }
	}
}

void ST7735S_DrawRect(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t Color)
{
    //绘制矩形框
    ST7735S_DrawHorizonLine(x0,y0,x1,Color,1);
    ST7735S_DrawVerticalLine(x0,y0,y1,Color,1);
    ST7735S_DrawHorizonLine(x0,y1,x1,Color,1);
    ST7735S_DrawVerticalLine(x1,y0,y1+1,Color,1);
}

void ST7735S_DrawRoundRectFill(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t Color)
{
  	uint16_t i,j;
  	uint16_t height,width;

    if(((x1-x0) < 4) || ((y1-y0) < 4))
    {
        return;
    }

    j = 2;
    for(i=1;i<3;i++)
    {
        ST7735S_DrawVerticalLine(x0+i-1,y0+j,y1-j,Color,1);
        ST7735S_DrawVerticalLine(x1-i,y0+j,y1-j,Color,1);
        j--;
    } 
    
    width = x1 - x0 - 4;
    height = y1 - y0;
  	ST7735S_ClearArea(y0,x0+2,width,height,Color);
}



