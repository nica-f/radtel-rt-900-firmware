#include "includes.h"

//定义对讲机参数全局变量
STR_RADIOINFORM g_radioInform;
STR_FMINFOS g_FMInform;
STR_SYSTEM  g_sysRunPara;
STR_INPUTBOX g_inputbuf;


STR_CHANNEL_VFO g_ChannelVfoInfo;
STR_CH_VFO_INFO *g_CurrentVfo;

volatile uint08_t g_msCont;
volatile uint08_t g_msFlag;
volatile uint08_t g_10msCont;
volatile uint08_t g_100msCont;
volatile uint08_t g_10msFlag;
volatile uint08_t g_50msFlag;
volatile uint08_t g_100msFlag;
volatile uint08_t g_500msFlag;

Boolean g_UpdateDisplay;
uint08_t g_rfState;
uint08_t g_rfRxState;
uint08_t g_rfTxState;

uint08_t inputTypeBack;


