#include "includes.h"

void LCD_ClearArea(uint16_t posX, uint16_t posY, uint16_t width, uint16_t height, uint16_t backColor)
{
    ST7735S_ClearArea(posX, posY, width, height, backColor);
}

void LCD_DisplayText(uint16_t posX,uint16_t posY,uint08_t *pString,uint08_t fontSize,uint16_t brushColor,uint16_t backColor, uint08_t divDot)
{
    uint08_t iconNum,i;
	uint08_t bufDat[128] = {0};

	for(i = 0; ; )
	{
        if(pString[i] == '\0')
        {
            return;
		}
		
        if(pString[i] >= 0xA1)
        {
            if(pString[i+1] == 0x00)
            {
                if(fontSize == FONTSIZE_16x16)
                {
                    LCD_ClearArea( posX, posY, 8, 16,backColor);  
                }
                else
                {
                    LCD_ClearArea( posX, posY, 6, 12,backColor);  
                }
                return;
            }
            
            if(fontSize == FONTSIZE_16x16)
            {
                Font_Read_16x16_CN(pString+i, bufDat);
                ST7735S_DisplayArea( posX, posY, 16, 16, bufDat, brushColor, backColor);
    			posX += 16;
            }
            else
            {
                Font_Read_12x12_CN(pString+i, bufDat);
                ST7735S_DisplayArea( posX, posY, 12, 12, bufDat, brushColor, backColor);
    			posX += 12;
            }
		    
			if(divDot)
            {
                LCD_ClearArea( posX, posY, divDot, fontSize,backColor);
                posX += divDot;
            }
			i += 2;
		}
		else
		{
            if( pString[i] >= 0x20 && pString[i] <= 0x7E )
            {
                if(fontSize == FONTSIZE_16x16)
                {
                    Font_Read_8x16_ASCII(pString+i, bufDat); 
                    ST7735S_DisplayArea( posX, posY, 8, 16, bufDat, brushColor, backColor);
    				posX += 8;
                }
                else
                {
                    Font_Read_6x12_ASCII(pString+i, bufDat); 
                    ST7735S_DisplayArea( posX, posY, 6, 12, bufDat, brushColor, backColor);
    				posX += 6;
                }

				if(divDot)
                {
                    LCD_ClearArea( posX, posY, divDot, fontSize, backColor);
                    posX += (divDot/2);
                }

			}
            /*
			else if(pString[i] == ICON_STR)
			{
			    i += 1;
			    //GT12֧��21X21�ĵ���ͼ��
			    {
			        iconNum = pString[i]-ICON_START;
			        if(iconNum < ICON_MAX_NUM)
			        {
                        memcpy(bufDat,iconMenuUse[iconNum],63);
			        }
			    }
                st7735s_DisplayArea( posX, posY, 21, 21, bufDat, back_Color, brush_Color);
                //21����
			    posX += 21;
			}
            */
			
			i += 1;
		}
	}
}

void LCD_DisplayText5X7(uint16_t posX, uint16_t posY, uint08_t *pString,uint16_t len, uint16_t brushColor, uint16_t backColor)
{
    uint08_t i = 0;
	uint08_t bufDat[5];

	for( i = 0; ; )
	{
        if(pString[i] == '\0' )
        {
            return;
		}
		
        Font_Read_5x7_ASCII(pString+i, bufDat);
        ST7735S_DisplayArea( posX, posY, 5, 8, bufDat,brushColor, backColor);
        
		posX += 6;
		i += 1;
	}
}

void LCD_DrawRectangle(uint16_t posX, uint16_t posY, uint16_t width, uint16_t height, uint16_t color )
{
    ST7735S_DrawRect(posX, posY, posX + width, posY + height, color);
}

void LCD_DisplayIcon(uint16_t posX,uint16_t posY,uint16_t width,uint16_t height,const uint08_t *pdat,uint16_t brushColor,uint16_t backColor)
{
    ST7735S_DisplayArea(posX, posY, width, height, pdat, brushColor, backColor);
}

void LCD_DisplayNum6X9(uint16_t posX,uint16_t posY,uint08_t *pString,uint16_t backColor)
{
    uint08_t picDisBuf[108+1] = {0};
    uint08_t i;
    uint08_t flagGradient = 0;

    if(backColor == COLOR_WORK_AREA)
    {
        flagGradient = 1;
    }
    
    for( i = 0; i < 3; )
    {
        if(pString[i] == '\0' )
        {
            return;
        }

        if(Font_Read_6x9_Number(pString+i, picDisBuf, flagGradient) == 1)
        {
            ST7735S_DisplayColorArea( posX, posY, 6, 9, picDisBuf);
        }
        else
        {
            ST7735S_ClearArea( posX, posY, 6, 9, backColor);
        }
        
		posX += 7;
		i++;
	}

}

void LCD_DisplayNum12x17(uint16_t posX,uint16_t posY,uint08_t *pString,uint16_t backColor)
{
    uint08_t picDisBuf[468+1] = {0};
    uint08_t i;
    uint08_t flagGradient = 0;
    uint08_t flagSymbol;

    if(backColor == COLOR_WORK_AREA)
    {
        flagGradient = 1;
    }
    
    for( i = 0; i < 8; )
    {
        if(pString[i] == '\0' )
        {
            return;
        }

        flagSymbol = Font_Read_12x17_Number(pString+i, picDisBuf, flagGradient);
        if(flagSymbol == 1)
        {
            ST7735S_DisplayColorArea( posX, posY, 12, 17, picDisBuf);
            posX += 12;
        }
        else if(flagSymbol == 2)
        {
            ST7735S_DisplayColorArea( posX, posY, 3, 17, picDisBuf);
            posX += 3;
        }
        else
        {
            ST7735S_ClearArea( posX, posY, 12, 17, backColor);
            posX += 12;
        }

        ST7735S_ClearArea( posX, posY, 3, 17, backColor);
        posX += 3;
		i++;
	}

}
