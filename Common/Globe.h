#ifndef __GLOBE_H
    #define __GLOBE_H

/**************************************************************************/
#define FREQ_BAND_VHF           0                
#define FREQ_BAND_UHF           1
#define FREQ_BAND_200M          2
#define FREQ_BAND_350M          3
#define FREQ_BAND_AM            4        //AMÆµ¶Î    
/**************************************************************************/

extern STR_RADIOINFORM g_radioInform;
extern STR_FMINFOS g_FMInform;
extern STR_SYSTEM  g_sysRunPara;
extern STR_CHANNEL_VFO g_ChannelVfoInfo;
extern STR_CH_VFO_INFO *g_CurrentVfo;
extern STR_INPUTBOX g_inputbuf;

extern volatile uint08_t g_msCont;
extern volatile uint08_t g_msFlag;
extern volatile uint08_t g_10msCont;
extern volatile uint08_t g_100msCont;
extern volatile uint08_t g_10msFlag;
extern volatile uint08_t g_50msFlag;
extern volatile uint08_t g_100msFlag;
extern volatile uint08_t g_500msFlag;

extern Boolean g_UpdateDisplay;
extern uint08_t g_rfState;
extern uint08_t g_rfRxState;
extern uint08_t g_rfTxState;

extern uint08_t inputTypeBack;
#endif
