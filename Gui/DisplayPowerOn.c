#include "includes.h"

extern void UI_DisplayPowerOn(void)
{
    U8 i;
    U8 posX,posY;
    U32 addr;
    U8 picDisBuf[2560+1] = {0};


    if(g_radioInform.OpFlag1.Bit.b0 == 0)
    {
        addr = FLASH_PON_MSG_ADDR;
        for(i=0;i<(LCD_HEIGHT/8);i++)
        {
            SpiFlash_ReadBytes(addr,picDisBuf,2560);
            ST7735S_DisplayColorArea(posX,posY,LCD_WIDTH, 8, picDisBuf);
            posY += 8;
            addr += 2560;
        }
    }
    else
    {
        DisplayBatteryVol(0);
    }

    LcdBackLightSwitch(LED_ON);
    //Delay 500ms
    DelayMs(500);
}

