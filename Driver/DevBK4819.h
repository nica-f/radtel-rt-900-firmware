#ifndef  __RF_RFIC_H__
    #define  __RF_RFIC_H__

/**************************IO************************************/
#define RFIC_SCN_H     GPIOB->BSRR = GPIO_Pin_10
#define RFIC_SCN_L     GPIOB->BRR  = GPIO_Pin_10
    
#define RFIC_SCK_H     GPIOB->BSRR = GPIO_Pin_11
#define RFIC_SCK_L     GPIOB->BRR  = GPIO_Pin_11
    
#define RFIC_SDA_IN    GpioModeSwitch( GPIOB,GPIO_Pin_2,0)
#define RFIC_SDA_OUT   GpioModeSwitch( GPIOB,GPIO_Pin_2,1)
#define RFIC_SDA_H     GPIOB->BSRR = GPIO_Pin_2
#define RFIC_SDA_L     GPIOB->BRR  = GPIO_Pin_2
#define RFIC_SDA_VAL   (GPIOB->IDR & GPIO_Pin_2)



/**************************************************************/
enum { GPIOx_RFIC_L=0, GPIOx_RFIC_H };
enum { BAND_WIDE, BAND_NARROW };
enum { RFIC_IDLE, RFIC_RXON, RFIC_TXON, RFIC_TONE, RFIC_TXTONE };
enum { ModeAudio=0,ModeScramble,ModeDtmf,ModeFSK,ModeSelcall,ModeDet1050, ModeAM, ModeFM };//work mode

#define RF_GPIO0    0X0040
#define RF_GPIO1    0X0020
#define RF_GPIO2    0X0010
#define RF_GPIO3    0X0008
#define RF_GPIO4    0X0004
#define RF_GPIO5    0X0002
#define RF_GPIO6    0X0001

typedef enum
{
    SUBAUDIO_NONE,
	SUBAUDIO_CTS,
	SUBAUDIO_DCS_N,
	SUBAUDIO_DCS_I,
} SUBAUDIO_TYPE;


extern const uint16_t  DCS_TAB[105];
extern const uint16_t  CTCS_TAB[51];

extern uint8_t OFFSET_MODULATION[];                  // 调制度
#define  DEPTH_MIC_MODULATION        OFFSET_MODULATION[0]   
#define  DEPTH_CTS_MODULATION        OFFSET_MODULATION[1]   
#define  DEPTH_DCS_MODULATION        OFFSET_MODULATION[2]   
#define  VOLUMN_WIDEBAND              OFFSET_MODULATION[3]   
#define  VOLUMN_NARROWBAND           OFFSET_MODULATION[4]  

#define  NOISE_400M                  OFFSET_MODULATION[5]  
#define  NOISE_136M                  OFFSET_MODULATION[6]   
#define  NOISE_200M                  OFFSET_MODULATION[7]   
#define  NOISE_300M                  OFFSET_MODULATION[8]  
#define  NOISE_OFFSET                OFFSET_MODULATION[9]
#define  XTAL_ADJUST                 OFFSET_MODULATION[10]

extern uint8_t *TXPWR_U_400[3];
extern uint8_t *TXPWR_V_136[3];
extern uint8_t *TXPWR_V_200[3];
extern uint8_t *TXPWR_U_350[3];

extern uint8_t TXPWR_H_U_400[16];
extern uint8_t TXPWR_H_V_136[16];
extern uint8_t TXPWR_H_V_200[16];
extern uint8_t TXPWR_H_U_350[16];

extern uint8_t TXPWR_M_U_400[16];
extern uint8_t TXPWR_M_V_136[16];
extern uint8_t TXPWR_M_V_200[16];
extern uint8_t TXPWR_M_U_350[16];

extern uint8_t TXPWR_L_U_400[16];
extern uint8_t TXPWR_L_V_136[16];
extern uint8_t TXPWR_L_V_200[16];
extern uint8_t TXPWR_L_U_350[16];

extern uint8_t TH_SQL_TAB[16];                     
extern uint8_t TH_SQL_TAB_MUTE[16];
extern uint8_t OFFSET_SQL_U_400[16];
extern uint8_t OFFSET_SQL_V_136[16];
extern uint8_t OFFSET_SQL_V_200[16];
extern uint8_t OFFSET_SQL_U_350[16];
extern uint08_t OFFSET_SQL_18_100[32];

extern const uint08_t xtal26MAdjust[];

/**************************函数声明区************************************/
extern void Rfic_WriteWord( uint8_t devAddr,uint16_t  devData );
extern uint16_t Rfic_ReadWord(uint8_t devAddr);

extern void Rfic_Sleep(void);
extern void Rfic_WakeUp(void);

extern void  Rfic_Init(void);
extern void  Rfic_ConfigRxMode(void);
extern void  Rfic_ConfigTxMode(void);
extern void  Rfic_RxTxOnOffSetup(uint8_t ON_FLAG);
extern void  Rfic_SetAfout(uint8_t state);
extern void  Rfic_SetPA(uint16_t dat);

extern void Rfic_ReadStatuesReg(void);
extern Boolean Rfic_GetSQLinkState(void);
extern uint16_t Rfic_GetRssiVal(void);
extern uint8_t Rfic_GetNoiseVal(void);
extern uint16_t Rfic_GetTail(void);

extern void Rfic_AdjustMicPGA(void);
extern void Rfic_MicIn_Enable(void);
extern void Rfic_MicIn_Disable(void);

extern uint32_t  GOLAY_ENCODE(uint16_t dcsCode);
extern void  CTS_DCS_RECE_Initial(void);
extern void  CTCSS_WithRfic(uint32_t CTS_Data);
extern void  DTCSS_WithRfic(uint32_t DCS_Code);
extern uint16_t Rfic_DecoderDetect( uint8_t ctsDcsType );
extern void RF_SendTail( uint8_t OnOrOff );
extern uint16_t Rfic_SubaudioDetect( void );

extern void Rfic_GpioSetBit( uint16_t gpiox, uint8_t val );
extern void Rfic_GpioFlash( uint8_t gpiox );

extern void Rfic_SetToneFreq( uint16_t dat );
extern void  Rfic_TxSingleTone_On(uint8_t txOn);
extern void Rfic_TxSingleTone_Off(void);

extern void Rfic_SwitchFM_AM(uint8_t mode);
/*****************************************************************/
/*                            F S K                              */
/*****************************************************************/
extern void Rfic_EnterFSKMode(void);
extern void Rfic_ExitFSKMode(void);
extern uint8_t Rfic_FskTransmit(uint16_t *pData);
extern uint8_t Rfic_GetFskRxFlag(void);
extern uint8_t Rfic_ReadFskData(uint16_t *pData);
/*****************************************************************/
/*                            DTMF                               */
/*****************************************************************/
extern void Rfic_EnterDTMFMode(uint8_t flagTx);
extern void Rfic_ExitDTMFMode(void);
extern void Rfic_SetDtmfFreq( uint16_t tone1Freq, uint16_t tone2Freq);
extern uint8_t Rfic_ReadDTMF(void);
extern uint8_t Rfic_GetDTMF_Link(void);
/*****************************************************************/
/*                           Freq Scan                           */
/*****************************************************************/
extern void Rfic_FreqScan_Enable(void);
extern void Rfic_FreqScan_Disable(void);
extern uint32_t Rfic_CheckFreqScan(void);
extern uint8_t Rfic_GetSCtsDcsType(void);
extern void Rfic_CtcDcsScan_Setup(uint32_t freq);
extern uint32_t Rfic_GetCtsDcsData(void);
extern void Rfic_ScanQT_Enable(void);
extern void Rfic_ScanQT_Disable(void);

#endif
