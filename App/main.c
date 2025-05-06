#include "includes.h"
#include "stdio.h"

void BeepPowerOn(void)
{
    Audio_PlayVoiceLock(vo_Welcome);
}

int main(void)
{   
    memcpy((void *)0x20000000, (void *)(0x08000000+0x3000), 0XBC);
    SYSCFG_MemoryRemapConfig(SYSCFG_MemoryRemap_SRAM);

    Board_Init();   
    ST7735S_Init(); 
    RadioConfig_Init();
    UI_DisplayPowerOn();
    Rfic_Init();
    ChannelCheckActiveAll();
    BeepPowerOn();
    BatteryInitLevel();
    RadioVfoInfo_Init();

    ResetTimeKeyLockAndPowerSave();
    ResetInputBuf();

    ProgromInit();
    LCD_BackLightSetOn();

    g_rfState = RF_RX;
    g_rfTxState = TX_READY;
    g_rfRxState = RX_READY;
    g_scanInfo.state = SCAN_IDLE;
    g_sysRunPara.sysRunMode = MODE_MAIN;
    g_keyScan.keyEvent = KEYID_NONE;
    
    while(1)
    {
        //Task_10ms
        if(g_10msFlag)
        {
            App_10msTask();
        }
        
        //Task_50ms
        if(g_50msFlag)
        {
            App_50msTask();
        }
        
        //Task_100ms
        if(g_100msFlag)
        {
            App_100msTask();
        }

        //Task_500ms
        if(g_500msFlag)
        {
            App_500msTask();
        }
        
        AppRunTask();
        AlarmTask();
    }
}

