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

typedef int_fast8_t         Boolean;         // ����Ϊ1bit


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
//������Ҫʹ�õĵĳ���
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
    uint08_t         time;                       //���볬ʱʱ��
    uint08_t         len;                        //������ִ�����
    uint08_t         pos;
    uint08_t         maxLen;                     //�����������󳤶�
    uint08_t         inputType;                 //���뷨����
    uint08_t         isFirstInput;             //�Ƿ��ǵ�һ������
    String          buf[20];                    //������ִ�����
} STR_INPUTBOX;
//--------------------------����Ϊϵͳ������Ҫ�Ľṹ��--------------------------------------------------------
enum {RF_NONE=0,RF_RX,RF_TX};
enum {RX_READY=0,GET_CALL,WAIT_RXEND,RX_MONI};            //RXSTATE
enum {TX_READY=0,WAIT_PTT_RELEASE,PTT_RELEASE,TX_STOP,ALARM_TXID,TX_KILLED}; //TXSTATE
enum {VFO_MODE=0,CHAN_MODE};
enum {CHAN_DISABLE=0,CHAN_ACTIVE};

//���巢��ʹ�ýṹ��
typedef struct
{
    uint16_t   totTime;                                //���䳬ʱʱ��
    uint16_t   voxDetDly;                              //������ʱ��⣬��������  
    uint16_t   voxWorkDly;                             //���ؽ���������ʱʱ��
    uint16_t   relayTailSetTime;                       //���м�β������ʱ��
    uint08_t    txChEnable;                             //�ŵ�ģʽ�·�������
    uint08_t    txEnable[4];                            //��������
}__attribute__( ( packed ) )STR_TXFLAG;
//�������ʹ�ýṹ��
typedef struct
{
    uint08_t    rxReceived;                             //�Ѿ����յ���Ƶ�ź�,��������Ƶδ�⿪����־λ��1     
    uint16_t   relayTailDetTime;                       //���м�β�����ʱ��
    uint16_t   codeDetTime;                            //����Ƶ���ʱ��
    uint16_t   rxFlashTime;                            //������˸��־
    uint16_t   txDly;                                  //����ת������ʱ
    uint08_t    rxReceiveOn;                            //���յ���Ƶ�ź�,����Ƶ�ѽ⿪�������ȣ���־λ��1  
}__attribute__( ( packed ) )STR_RXFLAG;

typedef struct
{
    uint08_t  codeLen;                                 //�����DTMF���볤��
    uint08_t  code[16];                                //Ҫ���͵�DTMF����
}STR_DTMFTYPEIN;

typedef struct
{       
    uint08_t    sysRunMode;
    STR_TXFLAG    rfTxFlag;
    STR_RXFLAG    rfRxFlag;
    uint08_t    moniFlag;
    uint08_t    ledState;                               //�ֵ�Ͳ����
    uint16_t   keyAutoTime;                            //�Զ�������ʱ��
    uint16_t   lcdAutoLight;                           //�Զ�����ʱ��
    uint08_t    dtmfToneFlag;                           //����DTMF���ű�־
    uint08_t    pttFlag;                                //PTT��־λ�������л�PTTA B ʹ��
    uint08_t    batState;                               //��ص��� 0:��ص�������    1: ��ص�������
    uint08_t    lcdBackSwtch;                           //Һ�������״̬
    STR_DTMFTYPEIN txDtmfCode;                    //������Ҫ���͵�DTMF����,����ѡ����Ҫ���͵ı���
    uint08_t    flagDisANI;                             //�������ʾ��־
    uint32_t   decoderCode;                            //��������
    uint08_t    moduleType;                             //�����룬���ݻ������жϷ���Ƶ��
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

#define BAND_BUF_CNT       4  //Ĭ��֧��UV˫��

typedef struct
{
    uint16_t freq[2*BAND_BUF_CNT];
    uint32_t freq32[2*BAND_BUF_CNT];
}STR_BANDBUF;

//����Ƶ�η�Χ�ṹ��
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
/***************************�Խ����ŵ���Ϣ����********************************************************/
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
                        //BIT6: ��խ��       0: �����25K��1: խ����12.5K��2:20K ���� Ĭ��: ���  
                        //BIT5 BIT4: ���վ���ģʽ 0:QT  1:DTMF  2:QT+DTMF  3:QT*DTMF
                        //BIT3: ��æ�ŵ����� 00: OFF 01: ON  Ĭ��: ��
                        //BIT2: ɨ�����     00: OFF 01: ON  Ĭ��: ��
                        //BIT1: ����
                        //BIT0: �����־ 0:��  1:�� (�����빦�ܵĻ���)
    //uint08_t  channelName[16];  //�ŵ�����      
    uint32_t decoderCode;   
}STR_CHANNEL;

/***************************�Խ���Ƶ��ģʽ����********************************************************/
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
                         //BIT6: ��խ��       0: �����25K��1: խ����12.5K�� 2:20K ���� Ĭ��: ���
                         //BIT4 BIT5: 
                         //����:���� 
                         //BIT0:
    uint08_t  remain1;   
    uint08_t  STEP;         // ����Ƶ�� :��� 0-7    
    uint08_t  Offset[7];  
    uint08_t  spMute;       
    uint32_t decoderCode; 
}STR_VFOMODE; 

/*----------------------------------------------------------------------------------------------------------
      �����ŵ�����ʹ�ýṹ��
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
    STR_FREQINFO *rx;    //��Ƶʱ��ʹ��
    STR_FREQINFO *tx;    //��Ƶʱ��ʹ��
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
   STR_CH_VFO_INFO   chVfoInfo[2];      //��������洢��AB����Ϣ
   STR_VFOMODE vfoInfo[2];              
   STR_CHANNEL channelInfo[2];
   uint08_t   scanList[999/8 + 1];     //ɨ���б�
   uint08_t   chanActiveList[999/8 + 1];//��Ч�ŵ��б�
   uint08_t   switchAB;         //AB���л�
   uint08_t   dualAB;
   uint08_t   BandFlag;         //����Ƶ��
   uint08_t   haveChannel;      //�Ƿ������Ч�ŵ�
   uint08_t   haveScan;         //�Ƿ���ڿ���ɨ����ŵ�
   uint16_t  channelNum[2];
   uint16_t  currentChannelNum;
}STR_CHANNEL_VFO;
/*----------------------------------------------------------------------------------------------------------
      ����ʹ�õ�λ����Ϣ
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
      �Խ�����ѡ������Ϣ(Radio Information)  
-----------------------------------------------------------------------------------------------------------*/
typedef struct
{ 
    uint08_t   sqlLevel;        //SQL�����ƽ          0 ~ 9 
    uint08_t   saveLevel;       //ʡ��ģʽ             0: ��      1: 1:1     2: 1:2     3: 1:3    4: 1:4
    uint08_t   voxLevel;        //VOX���ط���          0: 1~ 9
    uint08_t   autoBack;        //ABR�Զ�����          0-5s                
    uint08_t   dualRxFlag;      //TDR����˫��          0: ��      1: ��  (������ʾʱ: 0:�� 1: A+B 2: A+C 3: B+C)  
    uint08_t   totLevel;        //TOT���䳬ʱ��ʱ��        0-180�루����Ϊ15�룩��ȡֵ:0 1 2 3 .... 12 Ĭ�ϣ�0Ϊ�ر�      
    uint08_t   beepsSwitch;     //BEEP��ʾ��           0: ��      1: �� 
    uint08_t   voiceSw;         //VOICE������ʾ����    0:��       1: ����
    
    uint08_t   language;        //��ʾ����ʾ����       0: Ӣ��    1: ����       
    uint08_t   dtmfTone;        //DTMF����      0: ��  1: ��������     2: ����������     3: ��������  + ����������   
    uint08_t   scanMode;        //SCREV   ɨ��ģʽ   00: ʱ��  01: �ز�  10: ����   Ĭ��: �ز�        
    uint08_t   pttIdMode;       //PTTID              00: ��      01: BOT(���俪ʼ)   10: EOT(�������)   11: ���� Ĭ��: ��
    uint08_t   pttIdTime;       //PTTLT��ID��ʱ         0-3������Ϊ100 ms��  
    uint08_t   channleDisA;     //MDFA A���ŵ���ʾ��ʽ  00: �ŵ�����+�ŵ���  01: Ƶ��+�ŵ��� (S19���� 0:�ŵ�Ƶ�� 1:�ŵ��� 2:�ŵ�����)
    uint08_t   channleDisB;     //MDFB B���ŵ���ʾ��ʽ  00: �ŵ�����+�ŵ���  01: Ƶ��+�ŵ��� (S19���� 0:�ŵ�Ƶ�� 1:�ŵ��� 2:�ŵ�����)     
    uint08_t   txBusyLock;      //BCL  ��æ����        0: ��      1: ��  

    uint08_t   keyAutoLock;     //AUTOLK�����Զ�����   0: ��      1: ��   S19:OFF/5/10/15
    uint08_t   alarmMode;       //ALMOD ����ģʽ       0:�ֳ�  1:���䱨����    2: ���䱨����
    uint08_t   alarmLocal;      //����ʱ�����Ƿ񷢳������� 0: ��      1: ��
    uint08_t   dualTxMode;      //TXAB  ˫�ط���       0: ��      1: A��   2: B��   3: C��
    uint08_t   tailSwitch;      //STE   β������       0: ��      1: ��
    uint08_t   rpste;           //RPSTE ���м�β������ 0-1000MS������Ϊ100MS����ȡֵ:0 1 2 3 .... 10 Ĭ�ϣ�0 
    uint08_t   rptrl;           //RPTRL ���м�β����� 0-1000MS������Ϊ100MS����ȡֵ:0 1 2 3 .... 10 Ĭ�ϣ�0     
    uint08_t   txOffTone;       //ROGER ���������ʾ�� 0: ��      1: �� 

    uint08_t   switchAB;        //��ǰ����ģʽ     0:B��       1:A��
    uint08_t   fmEnale;         //FM��Ƶ����������ʹ��  1:���� 0:������
    UNION_VM chOrVfoMode;    //��������ʱ��4λB��ģʽ ��4λA��ģʽ
    uint08_t   keyLock;         //LOCK   ������    0: ��      1: ��
    UNION_FLAG2  OpFlag1;    //bit0~1:  ������ʾ:0:��: 1:Ԥ��ͼ��(��˾logo)  2:Ԥ���ַ�2�� 3:��ص�ѹ 
                             //bit2~3:  ������ʾ��: 0:�� 1:����  2:����
    uint08_t   reserve1;
    uint08_t   rtone;           //1750Hz�м�Tone  
    uint08_t   reserve2;

    uint08_t   voxDelay;        //������ʱʱ�� 0.5S -- 2.0S ����0.1S
    uint08_t   menuExitTime;    //�˵��Զ��˳�ʱ��
    uint08_t   reserve3[6];      //����

    uint08_t   reserve4;
    uint08_t   weatherNum;
    uint08_t   reserve5[2];
    uint08_t   userSideKey[4];  //֧�ֲ���Զ��幦�ܣ�ĿǰĬ��4��
    
    uint08_t   bank;
    uint08_t   reserve6;
    uint08_t   fmOrAm;
    uint08_t   reserve7[5];
}STR_RADIOINFORM;  

/*----------------------------------------------------------------------------------------------------------
      ���屨��ģʽʹ�ýṹ��       
-----------------------------------------------------------------------------------------------------------*/
typedef struct
{
    uint08_t  alarmStates;              //����״̬ 
    uint08_t  toneFlag;                 //��������־���������ߵݼ�ģʽ
    uint16_t alarmFreq;                //����Ƶ��
    uint16_t freqSwTime;               //����Ƶ�ʱ仯ʱ��
    uint16_t ledFlashTime;             //����LED��˸ʱ��
    uint16_t alarmTime;                //����ʱ��
}STR_ALARM;

/***************************�������洢�ṹ��********************************************************/
typedef struct
{
    uint16_t  FmCurFreq;    //Ƶ��ģʽ������Ƶ��
    uint16_t  FmCHs[30];    //�������ŵ�
    uint08_t   fmChNum;      //�������ŵ���
    uint08_t   fmChVfo;      //�������ŵ���Ƶ��ģʽ�л�
} __attribute__( ( packed ) )STR_FMINFOS;

/*----------------------------------------------------------------------------------------------------------
      ���巢��Ƶ��ѡ�к���չ����ʹ�ýṹ��       
-----------------------------------------------------------------------------------------------------------*/
typedef struct
{
    uint08_t  moduleType;          //
    uint08_t  txEn220M;            //220M��������  220-260M
    uint08_t  txEn350M;            //350M��������  350-390M
    uint08_t  txEn520M;            //520M��������  480-520M
    uint08_t  amRxEn;              //����Ƶ�ν������� ��ʱ��ʹ��
}STR_RF_MODELE;

#define changeIntToHex(dec)		( ( ((dec)/10) <<4 ) + ((dec)%10) )
#define changeHexToInt(hex)		( ( ((hex) >> 4) * 10 ) + ((hex) & 0x0f) )
#endif

