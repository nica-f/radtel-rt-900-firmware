#ifndef __DISPLAYMENU_H
    #define __DISPLAYMENU_H

#define MENU_MAX_CNT              55

typedef struct
{
    uint8_t voiceId;
    const char nameEn[16];  //英文名称
    const char nameCn[16];  //中文名称
}STR_MENU_ITEM;

//定义菜单序列
enum{   
    S_SQL,
    S_STEP,
    S_TXPR,
    S_SAVE, 
    S_VOXLV, 
    S_WN, 
    S_ABR, 
    S_TDR,
    S_BEEP,
    S_TOT,
    S_MEMCH, 
    S_DELCH,
    S_RXCTS,
    S_RXDCS,
    S_TXCTS, 
    S_TXDCS,
    S_CHNAME,
    S_ROGE, 
    S_VOIC,
    S_LAN,
    S_BUSYLOCK,
    S_SCREV,
    S_SK1,
    S_SKL1,
    S_SK2,
    S_OFFSE,
    S_SFTD,
    S_PONTYPE,
    //少一个信令码
    S_PTTID, 
    S_DTST, 
    S_AUTOLK, 
    //扫描添加
    S_RTONE, 
    S_PTTLT,
    S_MENUEXIT,
    S_VOXDLY,
    S_RPSTE,
    S_RPTRL,
    S_MDF1, 
    S_MDF2,
    S_TAIL,  
    S_ALMOD, 
    //接收结束提示音  
    S_RESET,    
    S_INFO,
    //AM/FM调制方式
};
extern String disBuf[17];
/********************************************************************************************************************/
extern const STR_MENU_ITEM MenuList[];
extern U8 inputTypeBack;
extern void DisplayInputType(void);
extern void MenuShowInputChar(void);
extern void Menu_GetSubItemString(U8 menuIndex);
extern void Menu_DisplayFreqError(void);
extern void Menu_Display(void);

#endif
