#include "includes.h"

extern void DisplayProgrom(void)
{
    LCD_ClearArea(0,0,LCD_WIDTH,LCD_HEIGHT,COLOR_BACKGROUND);
    LCD_DisplayIcon(68,44,ICON_PROG_WIDTH,ICON_PROG_HEIGHT,iconProgrom,COLOR_FOREGROUND, COLOR_BACKGROUND);
    LCD_DisplayText(40,80, "Program...", FONTSIZE_16x16,COLOR_FOREGROUND,COLOR_BACKGROUND,0);

    //开启按键背光灯
    LCD_BackLightSetOn();
}

extern void DisplayLockFlag(U8 flag)
{
    if(flag)
    {       
        LCD_DisplayIcon(109,3,ICON_LOCK_WIDTH,ICON_LOCK_HEIGHT,iconLock,COLOR_FOREGROUND, COLOR_BACKGROUND);
    }
    else
    {
        LCD_DisplayIcon(109,3,ICON_LOCK_WIDTH,ICON_LOCK_HEIGHT,iconLock,COLOR_NOT_WORK, COLOR_BACKGROUND);
    }
}

extern void DisplayMoniFlag(U8 flag)
{
    if(flag)
    {
        LCD_DisplayIcon(65,3,ICON_MONI_WIDTH,ICON_MONI_HEIGHT,iconMoni,COLOR_FOREGROUND,COLOR_BACKGROUND);
    }
    else
    {
        LCD_DisplayIcon(65,3,ICON_MONI_WIDTH,ICON_MONI_HEIGHT,iconMoni,COLOR_NOT_WORK,COLOR_BACKGROUND);
    }
}

extern void DisplayVoxFlag(U8 flag)
{
    if(flag)
    {
        LCD_DisplayIcon(6,3,ICON_VOX_WIDTH,ICON_VOX_HEIGHT,iconVox,COLOR_FOREGROUND,COLOR_BACKGROUND);
    }
    else
    {
        LCD_DisplayIcon(6,3,ICON_VOX_WIDTH,ICON_VOX_HEIGHT,iconVox,COLOR_NOT_WORK,COLOR_BACKGROUND);
    }
}

extern void DisplayDualRxFlag(U8 flag)
{
    if(flag)
    {
        LCD_DisplayIcon(38,3,ICON_DUAL_WIDTH,ICON_DUAL_HEIGHT,iconDual,COLOR_FOREGROUND,COLOR_BACKGROUND);
    }
    else
    {
        LCD_DisplayIcon(38,3,ICON_DUAL_WIDTH,ICON_DUAL_HEIGHT,iconDual,COLOR_NOT_WORK,COLOR_BACKGROUND);
    }
}

extern void DisplaySKeyTone(U8 flag)
{
    if(flag)
    {
        LCD_DisplayIcon(91,3,ICON_SKTONE_WIDTH,ICON_SKTONE_HEIGHT,iconSKTone,COLOR_FOREGROUND,COLOR_BACKGROUND);
    }
    else
    {
        LCD_DisplayIcon(91,3,ICON_SKTONE_WIDTH,ICON_SKTONE_HEIGHT,iconSKTone,COLOR_NOT_WORK,COLOR_BACKGROUND);
    }
}

extern void DisplayStateBar(void)
{
    LCD_ClearArea(0,0,160,16,COLOR_BACKGROUND);

    DisplayVoxFlag(g_radioInform.voxLevel);

    if(g_sysRunPara.sysRunMode == MODE_FM || g_sysRunPara.sysRunMode == MODE_MENU)
    {
        DisplayDualRxFlag(0);
    }
    else
    {
        DisplayDualRxFlag(g_radioInform.dualRxFlag);
    }

    DisplayMoniFlag(0);

    DisplaySKeyTone(g_radioInform.dtmfTone);

    DisplayLockFlag(g_radioInform.keyLock);

    DisplayBattaryFlag();
}

extern void TranStrToMiddle(String  *targeBuf,String *sourceBuf,U8 len)
{
    if (strlen(sourceBuf) >= len)
    {
        memcpy(targeBuf,sourceBuf,len);
    }else
    {
        memset(targeBuf,' ',len);
        memcpy(&targeBuf[(len-strlen(sourceBuf))/2],sourceBuf,strlen(sourceBuf));
    }
}

Boolean FillChannelName2Buf(U8 *src,String *dest)
{
    U8 i;
    String buf[13] = {0};

    if(src[0] == 0xFF || src[0] == 0x00)
    {//
       if(g_radioInform.language == LANG_CN)
       {
           sprintf(buf, "未命名 ");
       }
       else
       {
           sprintf(buf, "NO NAME");
       }
       return TRUE;
    }
    
    for(i=0;i<12;i++)
    {
        if(src[i] == 0xFF || src[i] == 0x00)
        {
            break;
        }
        buf[i] = src[i];
    }
    memset(dest,' ',12);
    memcpy(dest,buf,strlen(buf));
	dest[12] = '\0';

    return TRUE;
}

U16 GetWorkBackColour(U8 disAB)
{
    if(g_ChannelVfoInfo.switchAB == disAB)
    {
        return COLOR_WORK_AREA;
    }

    return COLOR_BACKGROUND;
}
extern void DisplayChannelNum(U8 isOperaMode, U16 currNum,U8 disAB)
{
    U8 buf[5] = {0},posY;
    U16 backColor = GetWorkBackColour(disAB);
    U8 posX = 132;

    if(disAB == 0 || isOperaMode == 1)
    {
         posY = 36;
         if(isOperaMode == 1)
         {
            backColor = COLOR_WORK_AREA;
         }
    }
    else
    {
        posY = 92;
    }

    LCD_ClearArea( posX, posY, 21, 9, backColor);
    if(0xFFFF == currNum)
    {
        sprintf((char *)buf,"VFO ");
        LCD_DisplayText5X7(posX, posY + 2, buf, 4, COLOR_CH_NUM, backColor);
        LCD_ClearArea( posX, posY + 14, 21, 9, backColor);
    }
    else
    {
        sprintf((char *)buf,"CH  ");
        LCD_DisplayText5X7(posX, posY, buf, 4, COLOR_CH_NUM, backColor);

        sprintf((char *)buf,"%03d",currNum+1);
        LCD_DisplayNum6X9(posX, posY + 14, buf, backColor);
    }
}

extern void DisplayCurFreq(U8 posX,U8 posY,U32 freq, U16 backColor)
{
    String freqBuf[12] = {0};
    U8 fontBuf[3] ={0};

    sprintf(freqBuf,"%03d.%05d",freq/100000,freq%100000);

    memcpy(fontBuf,&freqBuf[7],2);
    freqBuf[7] = 0;
    fontBuf[2] = 0;
    
    LCD_DisplayNum12x17(posX,posY,(U8 *)freqBuf,backColor);
    LCD_DisplayNum6X9(posX + 100,posY+8,fontBuf,backColor);
}

extern void DisplayUpdateChFlag(U8 locate, U8 disAB)
{
    U8 ctsType;
    U8 posY = 0;
    U16 backColor = GetWorkBackColour(disAB);

    if(disAB == 0 || locate == 1)
    {
        posY = 19;
    }
    else
    {
        posY = 75;
    }

    if(g_ChannelVfoInfo.chVfoInfo[disAB].txPower == 2)
    {
        LCD_DisplayIcon(45, posY,ICON_DTXPWR_WIDTH,ICON_DTXPWR_HEIGHT,iconPowerL, COLOR_FOREGROUND, backColor);
    }
    else if(g_ChannelVfoInfo.chVfoInfo[disAB].txPower == 1)
    {
        LCD_DisplayIcon(45, posY,ICON_DTXPWR_WIDTH,ICON_DTXPWR_HEIGHT,iconPowerM, COLOR_FOREGROUND, backColor);
    }
    else
    {
        LCD_DisplayIcon(45, posY,ICON_DTXPWR_WIDTH,ICON_DTXPWR_HEIGHT,iconPowerH, COLOR_FOREGROUND, backColor);
    }
    
    /*显示宽窄带标志*/
    if(g_ChannelVfoInfo.chVfoInfo[disAB].wideNarrow)
    {
        LCD_DisplayIcon(57, posY,ICON_NARROW_WIDTH,ICON_NARROW_HEIGHT,iconNarrow, COLOR_FOREGROUND, backColor);
    }
    else
    {
        LCD_ClearArea(57, posY,ICON_NARROW_WIDTH,ICON_NARROW_HEIGHT, backColor);
    }

    /*显示频差频率*/
	if(g_ChannelVfoInfo.chVfoInfo[disAB].freqDir == 1)
	{
		LCD_DisplayIcon(71,posY,ICON_ADDSUB_WIDTH,ICON_ADDSUB_HEIGHT,iconAdd,COLOR_FOREGROUND, backColor);
	}
	else if(g_ChannelVfoInfo.chVfoInfo[disAB].freqDir == 2)
	{
		LCD_DisplayIcon(71,posY,ICON_ADDSUB_WIDTH,ICON_ADDSUB_HEIGHT,iconSub,COLOR_FOREGROUND, backColor);
	}
	else
	{
		LCD_ClearArea(71,posY,ICON_ADDSUB_WIDTH,ICON_ADDSUB_HEIGHT, backColor);
	}

    /*显示倒频/脱网标志*/
    if(g_ChannelVfoInfo.chVfoInfo[disAB].reverseFlag == 1)
    {
        LCD_DisplayIcon(85,posY,ICON_REVERSE_WIDTH,ICON_REVERSE_HEIGHT,iconReverse,COLOR_FOREGROUND, backColor);
    }
    else if (g_ChannelVfoInfo.chVfoInfo[disAB].reverseFlag == 2)
    {
        LCD_DisplayIcon(85,posY,ICON_UNNET_WIDTH,ICON_UNNET_HEIGHT,iconUnNet,COLOR_FOREGROUND, backColor);
    }
    else
    {
        LCD_ClearArea(85,posY,ICON_REVERSE_WIDTH,ICON_REVERSE_HEIGHT, backColor);
    }
				
    /*显示AM标志*/
    if(g_ChannelVfoInfo.chVfoInfo[disAB].rx->frequency >= 10800000 && g_ChannelVfoInfo.chVfoInfo[disAB].rx->frequency < 13600000 )
    {
        LCD_DisplayIcon(115,posY,ICON_AM_WIDTH,ICON_AM_HEIGHT,iconAM,COLOR_FOREGROUND, backColor);
        
        //AM模式下 亚音频 跳频 倒频均无效
        LCD_ClearArea(21,posY,ICON_DCS_WIDTH,ICON_DCS_HEIGHT,backColor);
        LCD_ClearArea(97,posY,ICON_FHSS_WIDTH,ICON_FHSS_HEIGHT,backColor);
        return;
    }

    if(g_ChannelVfoInfo.chVfoInfo[disAB].fhssFlag == 1)
    {
        LCD_DisplayIcon(115,posY,ICON_FHSS_WIDTH,ICON_FHSS_HEIGHT,iconFhss,COLOR_FOREGROUND, backColor);
    }
    else
    {
        LCD_ClearArea(115,posY,ICON_AM_WIDTH,ICON_AM_HEIGHT,backColor);
    }

    /*显示亚音频类型*/
    if(g_rfState == RF_RX)
    {
        ctsType = g_ChannelVfoInfo.chVfoInfo[disAB].rx->dcsCtsType;
    }
    else
    {
        ctsType = g_ChannelVfoInfo.chVfoInfo[disAB].tx->dcsCtsType;
    }
				
	if(ctsType == SUBAUDIO_NONE)
	{
        LCD_ClearArea(21,posY,ICON_DCS_WIDTH,ICON_DCS_HEIGHT,backColor);
	}
	else if(ctsType == SUBAUDIO_CTS)
	{
        LCD_DisplayIcon(21,posY,ICON_DCS_WIDTH,ICON_DCS_HEIGHT,iconCtcss,COLOR_FOREGROUND, backColor);
	}
	else 
	{
        LCD_DisplayIcon(21,posY,ICON_DCS_WIDTH,ICON_DCS_HEIGHT,iconDcs,COLOR_FOREGROUND, backColor);
	}
		
	if(g_ChannelVfoInfo.chVfoInfo[disAB].scarmble & 0x03)
	{
        LCD_DisplayIcon(97,posY,ICON_SCR_WIDTH,ICON_SCR_HEIGHT,iconScr,COLOR_FOREGROUND, backColor);
	}
	else
	{
        LCD_ClearArea(97,posY,ICON_SCR_WIDTH,ICON_SCR_HEIGHT, backColor);
	}
}

const U8 linePosX[] = {27,35,43,51,59,67,75,83};
extern void DisplayTxPowerLv(U8 disAB, U8 level)
{
    U8 i,num;
    U16 foreColor;
    U16 posX,posY;
    
    if(disAB == 0)
    {
        posY = 61;
    }
    else
    {
        posY = 117;
    }

    ST7735S_DrawHorizonLine(19, posY + 2, 84, COLOR_FOREGROUND, 1);
    for(i = 0; i < 8; i++)
    {
        ST7735S_DrawVerticalLine(linePosX[i], posY, posY+2, COLOR_FOREGROUND, 1);
    }

    if(level >= 7)
    {// Power High
        num = 22;
        foreColor = COLOR_TXPWR_LEVEL_HIGH;
    }
    else if(level >= 5)
    {// Power Medium
        num = 16;
        foreColor = COLOR_TXPWR_LEVEL_MID;
    }
    else if(level == 0)
    {// Clear
        num = 0;
        foreColor = COLOR_TXPWR_LEVEL_0;
    }
    else
    {// Power Low
        num = 8;
        foreColor = COLOR_TXPWR_LEVEL_LOW;
    }

    posX = 19;
    for(i = 0; i < 22; i++)
    {
        if(i < num)
        {
            LCD_ClearArea(posX, posY + 6, 2, 3, foreColor);
        }
        else
        {
            LCD_ClearArea(posX, posY + 6, 2, 3, COLOR_TXPWR_LEVEL_0);
        }

        posX += 3;
    }
}

extern void DisplayRssiValue(U8 location, U8 disAB, U8 level)
{
    U8 num;
    U16 posY;

    if(disAB == 0 || location == 1)
    {
        posY = 63;
    }
    else
    {
        posY = 119;
    }

    LCD_DisplayText5X7(90, posY, "RSSI", 4, COLOR_FOREGROUND, GetWorkBackColour(disAB));

    num = (40*level) / 10;
    LCD_ClearArea(115+num, posY+3, (40-num), 4, COLOR_RSSI_0);
    LCD_ClearArea(115, posY+3, num, 4, COLOR_RSSI_1);
}

extern void DisplayChannelMsg(U8 location, U8 disMode,U8 disAB, U8 txOrRx)
{
    String nameBuf[16] = {0};
    const U8 *iconPtr;
    U8 posX,posY,namePosY;
    U8 flagABPosX,flagABPosY;
    U16 chNum;
    U16 backColor;
    U16 arrowColor = COLOR_ARROW_MAIN;
    
    backColor = GetWorkBackColour(disAB);
    if(backColor == COLOR_BACKGROUND)
    {
        arrowColor = COLOR_ARROW_AUX;
    }

    if(disAB == 0 || location == 1)
    {
        posX = 7;
        posY = 28;
        namePosY = 47;
        flagABPosX = 8;
        flagABPosY = 61;

        if(disAB == 1)
        {
            iconPtr = iconArrowB;
            chNum = g_ChannelVfoInfo.channelNum[1];
        }
        else
        {
            iconPtr = iconArrowA;
            chNum = g_ChannelVfoInfo.channelNum[0];
        }
    }
    else
    {
        posX = 7;
        posY = 84;
        namePosY = 103;
        flagABPosX = 8;
        flagABPosY = 117;

        iconPtr = iconArrowB;
        chNum = g_ChannelVfoInfo.channelNum[1];
    }
    LCD_ClearArea(flagABPosX-1,flagABPosY-1,ICON_ARROW_WIDTH+2,ICON_ARROW_HEIGHT+2, arrowColor);
    LCD_DisplayIcon(flagABPosX,flagABPosY,ICON_ARROW_WIDTH,ICON_ARROW_HEIGHT,iconPtr,COLOR_FOREGROUND, arrowColor);

    if(g_ChannelVfoInfo.chVfoInfo[disAB].chVfoMode == VFO_MODE)
    {
        if(g_radioInform.language == LANG_EN)
        {
            sprintf(nameBuf,"VFO Mode    ");
        }
        else
        {
            sprintf(nameBuf,"频率模式    ");
        }
        LCD_DisplayText(posX, namePosY,(U8 *)nameBuf,FONTSIZE_12x12,COLOR_CH_NAME,backColor,0);
    }
    else
    {
        if(disMode == CH_DISNAME || disMode == CH_DISFREQ)
        {//显示信道名称
            if(FillChannelName2Buf(g_ChannelVfoInfo.chVfoInfo[disAB].channelName,nameBuf) == TRUE)
            {
                LCD_DisplayText(posX, namePosY,(U8 *)nameBuf,FONTSIZE_12x12,COLOR_CH_NAME,backColor,0);
            }
        }
        else
        {
            sprintf(nameBuf, " CH-%03d", chNum+1);
            LCD_DisplayNum12x17(posX,posY,(U8 *)nameBuf,backColor);
        }
    }

    if(disMode != CH_DISCHNUM)
    {
        if(txOrRx == DIS_TX)
        {
            DisplayCurFreq(posX,posY,g_ChannelVfoInfo.chVfoInfo[disAB].tx->frequency,backColor);
        }
        else
        {
            DisplayCurFreq(posX,posY,g_ChannelVfoInfo.chVfoInfo[disAB].rx->frequency,backColor);
        }       
    }

    //显示信道标志
    DisplayUpdateChFlag(location, disAB);
}

extern void DisplayRadioHome(void)
{
    U16 backColor_A = GetWorkBackColour(0);
    U16 backColor_B = GetWorkBackColour(1);
    //清除A段背景
    LCD_ClearArea(0, 17, 160, 55, backColor_A);
    //清除B段背景
    LCD_ClearArea(0, 73, 160, 55, backColor_B);
    
    //显示A段信息
    if(g_ChannelVfoInfo.chVfoInfo[0].chVfoMode == CHAN_MODE)
    {
        DisplayChannelMsg(0,g_radioInform.channleDisA,0,DIS_RX);
        DisplayChannelNum(0,g_ChannelVfoInfo.channelNum[0],0);
    }
    else
    {
        DisplayChannelMsg(0,CH_DISFREQ,0,DIS_RX);
        DisplayChannelNum(0,0xFFFF,0); 
    }
    DisplayTxPowerLv(0, 0);
    DisplayRssiValue(0, 0, 0);

    //分界线
    ST7735S_DrawHorizonLine(0, 72, 160, COLOR_FOREGROUND, 1);

    //显示B段信息
    if(g_ChannelVfoInfo.chVfoInfo[1].chVfoMode == CHAN_MODE)
    {
        DisplayChannelMsg(0,g_radioInform.channleDisB,1,DIS_RX);
        DisplayChannelNum(0,g_ChannelVfoInfo.channelNum[1],1);
    }
    else
    {
        DisplayChannelMsg(0,CH_DISFREQ,1,DIS_RX);
        DisplayChannelNum(0,0xFFFF,1);
    } 
    DisplayTxPowerLv(1, 0);
    DisplayRssiValue(0, 1, 0);
}

extern void DisplayHomePage(void)
{
    //显示状态栏
    DisplayStateBar();

    //分界线
    ST7735S_DrawHorizonLine(0, 16, 160, COLOR_FOREGROUND, 1);

    //显示主界面
    DisplayRadioHome();
}

extern void DisplayInputChNum(void)
{
    U8 buf[11],i,flag,posY;

    buf[0] = '-';
    buf[1] = '-';
    buf[2] = '-';
    buf[3] = 0;

    flag = 0;
    for(i=0;i<g_inputbuf.len;i++)
    {
        if(g_inputbuf.buf[i] == '0' && flag == 0)
        {
            buf[i + 1] = ' ';
        }
        else
        {
            flag = 1;
            buf[i + 1] = g_inputbuf.buf[i];
        }
    }
    buf[3] = 0;

    if(g_ChannelVfoInfo.switchAB)
    {
        posY = 92;
    }
    else
    {
        posY = 36;
    }

    LCD_DisplayNum6X9(132, posY, buf, COLOR_WORK_AREA);
}

extern void DisplayInputVfoFreq(void)
{
    U8 i,j,posX,posY;
    U8 buf[10];
    U8 fontBuf[3];
	 
    memset(&buf[0],'-',7);
    buf[3] = '.';

    j = 0;
    for(i=0;i<g_inputbuf.len;i++)
    {
        if(i == 3)
        {
           j++;
        }
        buf[j++] = g_inputbuf.buf[i];
    }
    buf[7] = 0;
    
    memcpy(fontBuf,&buf[7],2);
    buf[7] = 0;	
    fontBuf[0] = '-';
    fontBuf[1] = '-';
    fontBuf[2] = 0;

    posX = 7;
    if(g_ChannelVfoInfo.switchAB)
    {
        posY = 84;
    }
    else
    {
        posY = 28;
    }

    LCD_DisplayNum12x17(posX,posY,(U8 *)buf,COLOR_WORK_AREA);
    LCD_DisplayNum6X9(posX + 100,posY+8,fontBuf,COLOR_WORK_AREA);
}

extern void DisplayRxMode(void)
{
    
}

extern void DisplayTxMode(void)
{
    if(g_CurrentVfo->txPower == 0)
    {
        DisplayTxPowerLv(g_ChannelVfoInfo.switchAB, 7);
    }
    else if (g_CurrentVfo->txPower == 1)
    {
        DisplayTxPowerLv(g_ChannelVfoInfo.switchAB, 5);
    }
    else
    {
        DisplayTxPowerLv(g_ChannelVfoInfo.switchAB, 0);
    }

    if(g_CurrentVfo->chVfoMode == CHAN_MODE)
    {
        if(g_ChannelVfoInfo.switchAB)
        {
            DisplayChannelMsg(0, g_radioInform.channleDisB,1,DIS_TX); 
        }
        else
        {
            DisplayChannelMsg(0, g_radioInform.channleDisA,0,DIS_TX); 
        }
    }
    else
    {
        if(g_ChannelVfoInfo.switchAB)
        {
            DisplayChannelMsg(0, CH_DISFREQ,1,DIS_TX); 
        }
        else
        {
            DisplayChannelMsg(0, CH_DISFREQ,0,DIS_TX); 
        }
    } 
}

U8 GetRxArea(void)
{
    U8 swab;

    if(dualStandby.dualRxFlag == ON)
    {
        if(g_ChannelVfoInfo.switchAB)
        {
            swab =  0;
        }
        else
        {
            swab =  1;
        }
    }
    else
    {
        swab = g_ChannelVfoInfo.switchAB;
    }

    return swab;
}

extern void DisplayResetRxFlag(void)
{

}

extern void DisplaySoftVersion(void)
{
    
}


