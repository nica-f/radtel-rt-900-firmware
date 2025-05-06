#include "includes.h"

#define STA_PWR_KEY                                 (GPIOA->IDR & GPIO_Pin_3)
#define POWER_OFF                                    GPIOB->BRR  = GPIO_Pin_3

extern void CheckPowerOff(void)
{
    if(STA_PWR_KEY)
    {
        DelayMs(50);
        if(STA_PWR_KEY)
        {
            RfOff();
            Rfic_Sleep();
            //��ʾ�ػ�����
            if(g_rfState == RF_TX)
            {
                DelayMs(200);
            }

            //�ر�˫�ز����л����ŵ�
            DualStandbyWorkOFF();
        
            //�������õ�����
            Flash_SaveRadioImfosData();

            if(g_ChannelVfoInfo.chVfoInfo[g_ChannelVfoInfo.switchAB].chVfoMode == CHAN_MODE)
            {
                //�����ŵ�����/�ŵ�����
                Flash_SaveChannelData(g_ChannelVfoInfo.channelNum[g_ChannelVfoInfo.switchAB],(U8 *)&g_ChannelVfoInfo.channelInfo[g_ChannelVfoInfo.switchAB].rxFreq,g_ChannelVfoInfo.chVfoInfo[g_ChannelVfoInfo.switchAB].channelName);
            }
            else
            {
                //����Ƶ��ģʽ����
                Flash_SaveVfoData(g_ChannelVfoInfo.switchAB);
            }
            
            //����ϵͳ��������
            Flash_SaveSystemRunData();
        
            //��ʱ100ms�ȴ�����д��
            DelayMs(100);
            POWER_OFF;

            //��ʱ��ȷ���ػ�
            DelayMs(500);
            //��λϵͳ,����ػ���������
            NVIC_SystemReset();
        }
    }
}

extern void LcdBackLightSwitch(ENUM_LED flag)
{
    if(flag == LED_OFF)
    {
        //g_sysRunPara.lcdBackSwtch = OFF;
        GPIOA->BRR = GPIO_Pin_12;
    }
    else
    { 
        //g_sysRunPara.lcdBackSwtch = ON;
        GPIOA->BSRR = GPIO_Pin_12;
    }
}

extern void LedTxSwitch(ENUM_LED flag)
{
    static U8 state;
    
    if(flag == LED_OFF)
    {
        GPIOA->BRR = GPIO_Pin_15;
        state = 0;
    }
    else if(flag == LED_ON)
    {
        GPIOA->BSRR = GPIO_Pin_15;
        state = 1;
    }
    else
    {
        if(state)
        {
            GPIOA->BRR = GPIO_Pin_15;
            state = 0;
        }
        else
        {
            GPIOA->BSRR = GPIO_Pin_15;
            state = 1;
        }
    }
}

extern void LedRxSwitch(ENUM_LED flag)
{
    static U8 state;
    
    if(flag == LED_OFF)
    {
        GPIOA->BRR = GPIO_Pin_14;
        state = 0;
    }
    else if(flag == LED_ON)
    {
        GPIOA->BSRR = GPIO_Pin_14;
        state = 1;
    }
    else
    {
        if(state)
        {
            GPIOA->BRR = GPIO_Pin_14;
            state = 0;
        }
        else
        {
            GPIOA->BSRR = GPIO_Pin_14;
            state = 1;
        }
    }
}

extern void LightSwitch(U8 flag)
{
    static U8 state;

    if(flag == LED_OFF)
    {
        GPIOF->BRR  = GPIO_Pin_6;
        state = 0;
    }
    else if(flag == LED_ON)
    {
        GPIOF->BSRR  = GPIO_Pin_6;
        state = 1;
    }
    else
    {
        if(state)
        {
            GPIOF->BRR  = GPIO_Pin_6;
            state = 0;
        }
        else
        {
            GPIOF->BSRR  = GPIO_Pin_6;
            state = 1;
        }
    }
}

extern void LightFlashTask(void)
{
    if(g_sysRunPara.ledState != 2)
    {
        return;
    }

    if(alarmDat.alarmStates == ON)
    {//����ģʽ��LEDҲ����˸
        return;
    }
    LightSwitch(LED_FLASH);
}


extern void LCD_BackLightSetOn(void)
{
    if(g_radioInform.autoBack < 5)
    {
        g_sysRunPara.lcdAutoLight = g_radioInform.autoBack * 50;
    }
    else if(g_radioInform.autoBack == 5)
    {
        g_sysRunPara.lcdAutoLight = 300;
    }
    else
    {
        g_sysRunPara.lcdAutoLight = (g_radioInform.autoBack - 5) * 600;
    }
    LcdBackLightSwitch(LED_ON); 
}

extern void LCD_CheckBackLight(void)
{
    if(g_radioInform.autoBack == 0)
    {//����
        return;
    }

    if(g_sysRunPara.sysRunMode == MODE_SEARCH || g_sysRunPara.sysRunMode == MODE_SCAN_QT)
    {
        return;
    }

    if(g_sysRunPara.lcdAutoLight == 0)
    {
        LcdBackLightSwitch(LED_OFF);
    }
}


void RF_PowerSet(U8 band,ENUM_RFPWR flag)
{
    if(flag == PWR_RXON)
    {
        switch(band)
        {
            case FREQ_BAND_350M:
            case FREQ_BAND_UHF:
                Rfic_GpioSetBit(RF_GPIO2,GPIOx_RFIC_L);
                Rfic_GpioSetBit(RF_GPIO1,GPIOx_RFIC_H);
                break;

            case FREQ_BAND_200M:
            case FREQ_BAND_VHF:
            default:
                Rfic_GpioSetBit(RF_GPIO1,GPIOx_RFIC_L);
                Rfic_GpioSetBit(RF_GPIO2,GPIOx_RFIC_H);
                break;
         }       	
    }
    else if(flag == PWR_TXON)
    {

        switch(band)
        {
            case FREQ_BAND_350M:
            case FREQ_BAND_UHF:
                Rfic_GpioSetBit(RF_GPIO4,GPIOx_RFIC_L);
                Rfic_GpioSetBit(RF_GPIO3,GPIOx_RFIC_H);
                break;

            case FREQ_BAND_200M:
            case FREQ_BAND_VHF:
                Rfic_GpioSetBit(RF_GPIO3,GPIOx_RFIC_L);
                Rfic_GpioSetBit(RF_GPIO4,GPIOx_RFIC_H);
                break;
            default:
                Rfic_GpioSetBit(RF_GPIO3,GPIOx_RFIC_L);
                Rfic_GpioSetBit(RF_GPIO4,GPIOx_RFIC_L);
                break;
         } 
    }
    else
    {
        Rfic_GpioSetBit(RF_GPIO1,GPIOx_RFIC_L);
        Rfic_GpioSetBit(RF_GPIO2,GPIOx_RFIC_L);
        Rfic_GpioSetBit(RF_GPIO3,GPIOx_RFIC_L);
        Rfic_GpioSetBit(RF_GPIO4,GPIOx_RFIC_L);		
    }
}

extern void SpeakerSwitch(ENUM_ONOFF flag)
{
    if(flag == ON)
    {
        GPIOF->BSRR = GPIO_Pin_7;
    }
    else
    {
        GPIOF->BRR = GPIO_Pin_7;
    }
}

