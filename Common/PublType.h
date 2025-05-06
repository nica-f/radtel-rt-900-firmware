#ifndef __INC_PUBLTYPE_H__
    #define __INC_PUBLTYPE_H__  
//-----------------------------------------------------------------------------
typedef char                String;

 
typedef int8_t              S8;          
typedef int16_t             S16;          
typedef int32_t             S32;       
typedef int64_t             S64; 

typedef uint8_t             uint08_t;
typedef uint8_t             U8;       
typedef uint16_t            U16;   
typedef uint32_t            U32;   
typedef uint64_t            U64;        

typedef int_fast8_t         Boolean;         // 至少为1bit


#define __BYTE              uint8_t

typedef void (*pFunction)(void);

#define BIT0            0x0001
#define BIT1            0x0002
#define BIT2            0x0004
#define BIT3            0x0008
#define BIT4            0x0010
#define BIT5            0x0020
#define BIT6            0x0040
#define BIT7            0x0080
#define BIT8            0x0100
#define BIT9            0x0200
#define BIT10           0x0400
#define BIT11           0x0800
#define BIT12           0x1000
#define BIT13           0x2000
#define BIT14           0x4000  
#define BIT15           0x8000
//----------------------------------------------------------------------------------------------------------
//定义需要使用的的常亮
#define FERROR          1
#define OK              0

typedef enum 
{
    OFF=0,ON
}ENUM_ONOFF;

typedef enum
{
  FALSE = 0, TRUE  = !FALSE
}
bool;

enum {LANG_EN=0,LANG_CN};
//----------------------------------------------------------------------------------------------------------
enum{KEY_CLICKED=0,KEY_LONG,KEY_CONTINUE};
//-------------------------------------------------------------------------------------------------------------
typedef union 
{
    uint32_t dest;
    uint08_t src[4];
}Uninouint32_t;

//------------------------------------------------------------------------------------------------------------
#define INPUT_TIME_OUT         50
#define INPUT_DTMF_TIME_OUT    100

typedef struct
{
    uint08_t         time;                       //输入超时时间
    uint08_t         len;                        //输入的字串长度
    uint08_t         pos;
    uint08_t         maxLen;                     //允许输入的最大长度
    uint08_t         inputType;                 //输入法类型
    uint08_t         isFirstInput;             //是否是第一次输入
    String          buf[20];                    //输入的字串资料
} STR_INPUTBOX;
//--------------------------以下为系统运行需要的结构体--------------------------------------------------------
enum {RF_NONE=0,RF_RX,RF_TX};
enum {RX_READY=0,GET_CALL,WAIT_RXEND,RX_MONI};            //RXSTATE
enum {TX_READY=0,WAIT_PTT_RELEASE,PTT_RELEASE,TX_STOP,ALARM_TXID,TX_KILLED}; //TXSTATE
enum {VFO_MODE=0,CHAN_MODE};
enum {CHAN_DISABLE=0,CHAN_ACTIVE};

//定义发射使用结构体
typedef struct
{
    uint16_t   totTime;                                //发射超时时间
    uint16_t   voxDetDly;                              //声控延时检测，用于声音  
    uint16_t   voxWorkDly;                             //声控结束后发射延时时间
    uint16_t   relayTailSetTime;                       //过中继尾音消除时间
    uint08_t    txChEnable;                             //信道模式下发射允许
    uint08_t    txEnable[4];                            //发射允许
}__attribute__( ( packed ) )STR_TXFLAG;
//定义接收使用结构体
typedef struct
{
    uint08_t    rxReceived;                             //已经接收到射频信号,但是亚音频未解开，标志位置1     
    uint16_t   relayTailDetTime;                       //过中继尾音检测时间
    uint16_t   codeDetTime;                            //亚音频检测时间
    uint16_t   rxFlashTime;                            //接收闪烁标志
    uint16_t   txDly;                                  //发射转接收延时
    uint08_t    rxReceiveOn;                            //接收到射频信号,亚音频已解开，打开喇叭，标志位置1  
}__attribute__( ( packed ) )STR_RXFLAG;

typedef struct
{
    uint08_t  codeLen;                                 //输入的DTMF编码长度
    uint08_t  code[16];                                //要发送的DTMF编码
}STR_DTMFTYPEIN;

typedef struct
{       
    uint08_t    sysRunMode;
    STR_TXFLAG    rfTxFlag;
    STR_RXFLAG    rfRxFlag;
    uint08_t    moniFlag;
    uint08_t    ledState;                               //手电筒功能
    uint16_t   keyAutoTime;                            //自动锁键盘时间
    uint16_t   lcdAutoLight;                           //自动背光时间
    uint08_t    dtmfToneFlag;                           //按键DTMF拨号标志
    uint08_t    pttFlag;                                //PTT标志位，用于切换PTTA B 使用
    uint08_t    batState;                               //电池电量 0:电池电量正常    1: 电池电量过低
    uint08_t    lcdBackSwtch;                           //液晶背光灯状态
    STR_DTMFTYPEIN txDtmfCode;                    //输入需要发送的DTMF编码,或者选择需要发送的编码
    uint08_t    flagDisANI;                             //身份码显示标志
    uint32_t   decoderCode;                            //破码数据
    uint08_t    moduleType;                             //机型码，根据机型来判断发射频率
}STR_SYSTEM;

typedef struct
{
    uint16_t    vhfL;
    uint16_t    vhfH;
    uint16_t    uhfL;
    uint16_t    uhfH;
    uint16_t    vhf2L;
    uint16_t    vhf2H;
    uint16_t    B350ML;
    uint16_t    B350MH;
    uint32_t    freqVL;
    uint32_t    freqVH;
    uint32_t    freqUL;
    uint32_t    freqUH;
    uint32_t    freqV2L;
    uint32_t    freqV2H;
    uint32_t    freq350ML;
    uint32_t    freq350MH;
}STR_FREQBAND;

#define BAND_BUF_CNT       4  //默认支持UV双段

typedef struct
{
    uint16_t freq[2*BAND_BUF_CNT];
    uint32_t freq32[2*BAND_BUF_CNT];
}STR_BANDBUF;

//定义频段范围结构体
typedef union
{
    STR_FREQBAND bandFreq;
    STR_BANDBUF  bandbuf;
}STR_BAND;

//-------------------------------------------------------------------------------------------------------------
typedef union {
	__BYTE	Byte;
	struct {
			__BYTE	b0:1;
			__BYTE	b1:1;
			__BYTE	b2:1;
			__BYTE	b3:1;
			__BYTE	spMute:2;
			__BYTE	b6:1;
			__BYTE	b7:1;
	} Bit;
} ChParaFlag1;    

typedef union {
    __BYTE  Byte;
    struct {
            __BYTE  b0:2;
            __BYTE  b2:1;
            __BYTE  b3:1;
            __BYTE  b4:1;
            __BYTE  b5:1;
            __BYTE	b6:1;
			__BYTE	b7:1;
    } Bit;
}VfoParaFlag1;
/***************************对讲机信道信息定义********************************************************/
typedef struct
{
    uint32_t rxFreq;    
    uint32_t txFreq;      
    uint16_t rxDCSCTSNum; 
    uint16_t txDCSCTSNum; 
    uint08_t  dtmfgroup;    
    uint08_t  pttID;       
    uint08_t  txPower;      
    ChParaFlag1 chFlag3; /*channel flag 3*/
                        //BIT6: 宽窄带       0: 宽带（25K）1: 窄带（12.5K）2:20K 带宽 默认: 宽带  
                        //BIT5 BIT4: 接收静音模式 0:QT  1:DTMF  2:QT+DTMF  3:QT*DTMF
                        //BIT3: 繁忙信道锁定 00: OFF 01: ON  默认: 无
                        //BIT2: 扫描添加     00: OFF 01: ON  默认: 无
                        //BIT1: 保留
                        //BIT0: 破码标志 0:无  1:有 (带破码功能的机器)
    //uint08_t  channelName[16];  //信道名称      
    uint32_t decoderCode;   
}STR_CHANNEL;

/***************************对讲机频率模式定义********************************************************/
typedef struct
{
    uint08_t  freq[8];      
    uint16_t rxDCSCTSNum; 
    uint16_t txDCSCTSNum;  
    uint08_t  remain0[2];
  
    uint08_t  dtmfgroup;        
    uint08_t  ANI;                       
    uint08_t  txPower;     
    VfoParaFlag1 vfoFlag;     /*channel flag 3*/
                         //BIT6: 宽窄带       0: 宽带（25K）1: 窄带（12.5K） 2:20K 带宽 默认: 宽带
                         //BIT4 BIT5: 
                         //其他:保留 
                         //BIT0:
    uint08_t  remain1;   
    uint08_t  STEP;         // 步进频率 :序号 0-7    
    uint08_t  Offset[7];  
    uint08_t  spMute;       
    uint32_t decoderCode; 
}STR_VFOMODE; 

/*----------------------------------------------------------------------------------------------------------
      定义信道运行使用结构体
-----------------------------------------------------------------------------------------------------------*/
typedef struct
{
    uint32_t frequency;
    uint08_t  dcsCtsType;
    uint32_t dcsCtsNum;
}STR_FREQINFO;

typedef struct
{
    STR_FREQINFO freqRx;
    STR_FREQINFO freqTx;
    STR_FREQINFO *rx;    //倒频时候使用
    STR_FREQINFO *tx;    //倒频时候使用
    uint08_t  wideNarrow;
    uint08_t  txPower;
    uint08_t  fhssFlag;
    uint08_t  scarmble;
    uint08_t  spMute;
    uint08_t  busyLock;
    uint08_t  dtmfgroup;
    uint08_t  chVfoMode;
    uint08_t  freqDir;
    uint08_t  freqStep;
    uint32_t freqOffset;
    uint08_t  reverseFlag;
    uint08_t  pttIdMode;
    uint08_t  channelName[16];
}STR_CH_VFO_INFO;

typedef struct
{
   STR_CH_VFO_INFO   chVfoInfo[2];      //计算后工作存储，AB段信息
   STR_VFOMODE vfoInfo[2];              
   STR_CHANNEL channelInfo[2];
   uint08_t   scanList[999/8 + 1];     //扫描列表
   uint08_t   chanActiveList[999/8 + 1];//有效信道列表
   uint08_t   switchAB;         //AB段切换
   uint08_t   dualAB;
   uint08_t   BandFlag;         //工作频段
   uint08_t   haveChannel;      //是否存在有效信道
   uint08_t   haveScan;         //是否存在可以扫描的信道
   uint16_t  channelNum[2];
   uint16_t  currentChannelNum;
}STR_CHANNEL_VFO;
/*----------------------------------------------------------------------------------------------------------
      定义使用的位域信息
-----------------------------------------------------------------------------------------------------------*/
typedef union {
    __BYTE  Byte;
    struct {
            __BYTE  b0:1;
            __BYTE  b1:1;
            __BYTE  b2:1;
            __BYTE  b3:1;
            __BYTE  b4:1;
            __BYTE  b5:1;
            __BYTE  b6:1;
            __BYTE  b7:1;
    } Bit;
}UNION_FLAG1;

typedef union {
    __BYTE  Byte;
    struct {
            __BYTE  b0:2;
            __BYTE  b2:2;
            __BYTE  b4:1;
            __BYTE  b5:1;
            __BYTE  b6:1;
            __BYTE  b7:1;
    } Bit;
}UNION_FLAG2;

typedef union {
    __BYTE  Byte;
    struct {
            __BYTE  TxTone:1;
            __BYTE  Remain:3;
            __BYTE  AutoOff:4;
    } Bit;
}UNION_FLAG3;

typedef union {
    __BYTE  Byte;
    struct {
            __BYTE  chVofA:4;
            __BYTE  chVofB:4;
    } Bit;
}UNION_VM;
/*----------------------------------------------------------------------------------------------------------
      对讲机可选功能信息(Radio Information)  
-----------------------------------------------------------------------------------------------------------*/
typedef struct
{ 
    uint08_t   sqlLevel;        //SQL静噪电平          0 ~ 9 
    uint08_t   saveLevel;       //省电模式             0: 关      1: 1:1     2: 1:2     3: 1:3    4: 1:4
    uint08_t   voxLevel;        //VOX声控发射          0: 1~ 9
    uint08_t   autoBack;        //ABR自动背光          0-5s                
    uint08_t   dualRxFlag;      //TDR启动双守          0: 关      1: 开  (三段显示时: 0:关 1: A+B 2: A+C 3: B+C)  
    uint08_t   totLevel;        //TOT发射超时定时器        0-180秒（步进为15秒）。取值:0 1 2 3 .... 12 默认：0为关闭      
    uint08_t   beepsSwitch;     //BEEP提示音           0: 关      1: 开 
    uint08_t   voiceSw;         //VOICE操作提示语音    0:无       1: 开启
    
    uint08_t   language;        //显示和提示语音       0: 英文    1: 中文       
    uint08_t   dtmfTone;        //DTMF侧音      0: 关  1: 按键侧音     2: 发身份码侧音     3: 按键侧音  + 发身份码侧音   
    uint08_t   scanMode;        //SCREV   扫描模式   00: 时间  01: 载波  10: 搜索   默认: 载波        
    uint08_t   pttIdMode;       //PTTID              00: 无      01: BOT(发射开始)   10: EOT(发射结束)   11: 两者 默认: 无
    uint08_t   pttIdTime;       //PTTLT发ID延时         0-3（步进为100 ms）  
    uint08_t   channleDisA;     //MDFA A段信道显示方式  00: 信道名称+信道号  01: 频率+信道号 (S19机型 0:信道频率 1:信道号 2:信道名称)
    uint08_t   channleDisB;     //MDFB B段信道显示方式  00: 信道名称+信道号  01: 频率+信道号 (S19机型 0:信道频率 1:信道号 2:信道名称)     
    uint08_t   txBusyLock;      //BCL  遇忙禁发        0: 关      1: 开  

    uint08_t   keyAutoLock;     //AUTOLK键盘自动锁定   0: 关      1: 开   S19:OFF/5/10/15
    uint08_t   alarmMode;       //ALMOD 报警模式       0:现场  1:发射报警音    2: 发射报警码
    uint08_t   alarmLocal;      //报警时本机是否发出报警音 0: 关      1: 开
    uint08_t   dualTxMode;      //TXAB  双守发射       0: 关      1: A段   2: B段   3: C段
    uint08_t   tailSwitch;      //STE   尾音消除       0: 关      1: 开
    uint08_t   rpste;           //RPSTE 过中继尾音消除 0-1000MS（步进为100MS）。取值:0 1 2 3 .... 10 默认：0 
    uint08_t   rptrl;           //RPTRL 过中继尾音检测 0-1000MS（步进为100MS）。取值:0 1 2 3 .... 10 默认：0     
    uint08_t   txOffTone;       //ROGER 发射结束提示音 0: 关      1: 开 

    uint08_t   switchAB;        //当前工作模式     0:B段       1:A段
    uint08_t   fmEnale;         //FM调频收音机允许使用  1:允许 0:不允许
    UNION_VM chOrVfoMode;    //独立设置时高4位B段模式 低4位A段模式
    uint08_t   keyLock;         //LOCK   键盘锁    0: 关      1: 开
    UNION_FLAG2  OpFlag1;    //bit0~1:  开机显示:0:无: 1:预设图标(公司logo)  2:预设字符2行 3:电池电压 
                             //bit2~3:  开机提示音: 0:无 1:音调  2:语音
    uint08_t   reserve1;
    uint08_t   rtone;           //1750Hz中继Tone  
    uint08_t   reserve2;

    uint08_t   voxDelay;        //声控延时时间 0.5S -- 2.0S 步进0.1S
    uint08_t   menuExitTime;    //菜单自动退出时间
    uint08_t   reserve3[6];      //保留

    uint08_t   reserve4;
    uint08_t   weatherNum;
    uint08_t   reserve5[2];
    uint08_t   userSideKey[4];  //支持侧键自定义功能，目前默认4个
    
    uint08_t   bank;
    uint08_t   reserve6;
    uint08_t   fmOrAm;
    uint08_t   reserve7[5];
}STR_RADIOINFORM;  

/*----------------------------------------------------------------------------------------------------------
      定义报警模式使用结构体       
-----------------------------------------------------------------------------------------------------------*/
typedef struct
{
    uint08_t  alarmStates;              //报警状态 
    uint08_t  toneFlag;                 //报警音标志，递增或者递减模式
    uint16_t alarmFreq;                //报警频率
    uint16_t freqSwTime;               //报警频率变化时间
    uint16_t ledFlashTime;             //报警LED闪烁时间
    uint16_t alarmTime;                //报警时间
}STR_ALARM;

/***************************收音机存储结构体********************************************************/
typedef struct
{
    uint16_t  FmCurFreq;    //频率模式收音机频率
    uint16_t  FmCHs[30];    //收音机信道
    uint08_t   fmChNum;      //收音机信道号
    uint08_t   fmChVfo;      //收音机信道和频率模式切换
} __attribute__( ( packed ) )STR_FMINFOS;

/*----------------------------------------------------------------------------------------------------------
      定义发射频段选中和扩展发射使用结构体       
-----------------------------------------------------------------------------------------------------------*/
typedef struct
{
    uint08_t  moduleType;          //
    uint08_t  txEn220M;            //220M发射允许  220-260M
    uint08_t  txEn350M;            //350M发射允许  350-390M
    uint08_t  txEn520M;            //520M发射允许  480-520M
    uint08_t  amRxEn;              //航空频段接收允许 暂时不使用
}STR_RF_MODELE;

#define changeIntToHex(dec)		( ( ((dec)/10) <<4 ) + ((dec)%10) )
#define changeHexToInt(hex)		( ( ((hex) >> 4) * 10 ) + ((hex) & 0x0f) )
#endif

