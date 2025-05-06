#include  "includes.h"

/*----------------------------------------------------------------------*/
#define  Rfic_delay(x)  DelayUs(x)
/*----------------------------------------------------------------------*/

#define CTC_ERR   0    //0=0.1Hz error mode;1=0.1% error mode
#define CTC_IN    10   //~=1   Hz for ctcss in  threshold
#define CTC_OUT   15   //~=1.5 Hz for ctcss out threshold

#define DAC_GAIN  15   //0~15

#define VOL_GAIN  63   //0~63, 0=mute, LSB->0.5dB
//#define VOL_GAIN  59   //0~63, 0=mute, LSB->0.5dB

#define FSK_BAUD  0X3065  // 1200
#define FSK2400   1

#define REG_32 0X4244                // Freq Scan BIT0: 1:Enable 0:Disable    BIT15:14: Scan Time[00-0.2sec 01-0.4sec 10-0.8sec 11-1.6sec]
#define REG_37 0x1D00
#define REG_52 CTC_ERR<<12 | CTC_IN<<6 | CTC_OUT

#define REG_59 0x0028

#define FSK_LEN              8       // 8Word = 16Byte
/*----------------------------------------------------------------------*/
static  uint16_t  PREDCS_CODE;    
static  uint16_t  reg0CH = 0x0000;
static  uint8_t   ctsDcsCodeType;
static uint08_t RF_Baseband_Mode = ModeFM;       

uint32_t  GOLAY_ENCODE(uint16_t dcsCode)
{
    uint32_t DCS_TEMP;
    uint32_t dcsData;
    uint08_t i;
    uint16_t m,n;
    uint16_t DCS_BIT,DCS_KMDATA,DCS_RESULT,DCS_SOURCE ;

    dcsData = 0;
    DCS_SOURCE = dcsCode | 0x800;
    dcsData |= DCS_SOURCE;
    DCS_BIT = 1;
    DCS_RESULT = 0;
    for(i = 1; i < 13;i++)
    {
        m = DCS_RESULT & 0x0002;
        n = DCS_SOURCE & DCS_BIT;
        if(((m != 0)&&(n != 0))||((m == 0)&&(n == 0)))
        {
            DCS_KMDATA = 0x0000;
        }
        else
        {   
            DCS_KMDATA = 0x0C75;
        }
        DCS_BIT <<= 1;
        DCS_RESULT >>= 1;
        DCS_RESULT ^= DCS_KMDATA;
    }
    DCS_RESULT <<= 4;
    DCS_TEMP = (uint32_t)DCS_RESULT;
    dcsData = (dcsData << 1) | (DCS_TEMP << 8);
    dcsData >>= 1;
    return dcsData;
}

void  CTCSS_WithRfic(uint32_t CTS_Data)
{
    uint32_t CTS_BUFF;
    uint08_t temp;
    
    temp = DEPTH_CTS_MODULATION;
    if(g_CurrentVfo->scarmble > 0)
    {
        temp += 15;
    }
    Rfic_WriteWord(0x51,0x9000 | (temp&0x7f));    
    CTS_BUFF = CTS_Data * 206489L/100000;
    Rfic_WriteWord(0x07,CTS_BUFF);
    Rfic_WriteWord(0x07,0X01CD| (0x1<<13));
    Rfic_WriteWord(0x52,0x0292);
}

void  DTCSS_WithRfic(uint32_t DCS_Code)
{
    //uint08_t gain;
    uint16_t  mask=0x8000;
    uint32_t  dcsData;
    uint08_t  temp;

    PREDCS_CODE = DCS_Code & (~BIT15);
    dcsData = GOLAY_ENCODE(PREDCS_CODE); 
    if(g_CurrentVfo->tx->dcsCtsType == SUBAUDIO_DCS_I)
    {
        mask = 0xA000;
    }

    temp = DEPTH_DCS_MODULATION;
    if(g_CurrentVfo->scarmble > 0)
    {
        temp += 20;
    }
    Rfic_WriteWord(0x51, mask|(temp&0x7f)); //0x80c0 [15]ctcss/dcs en,[13]pos/neg dcs,[12]ctcss/dcs mode,[11]24/23bit,
                            //[6:5]ctcss/dcs coarse tuning gain,[4:0]ctcss/dcs fine tuning gain
                            //Gain = ((32+subau_gain[4:0])<<subau_gain[6:5])/512
    Rfic_WriteWord(0x07,0x0ad7); //134.4Hz,
    Rfic_WriteWord(0x08,dcsData&0x000fff); //set low 12 bit
    Rfic_WriteWord(0x08,((dcsData&0xfff000) >> 12) | 0x8000); //set high 12 bit
}

void RF_SendTail( uint08_t OnOrOff )
{
    uint16_t temp;

    temp = Rfic_ReadWord(0x52) & 0X1FFF;
    if( OnOrOff )
    {
        if(g_CurrentVfo->tx->dcsCtsType > SUBAUDIO_CTS)
        {
            temp |= 0X8000;
        }
        else
        {
            Rfic_WriteWord(0x51,0x9000 | (DEPTH_CTS_MODULATION&0x7f));    
            Rfic_WriteWord(0x07, 0x0471);  // 55.1
        }
    }
    else
    {
        Rfic_WriteWord(0x51,0x0000);    
    }
    Rfic_WriteWord(0X52, temp);
}

void Rfic_ReadStatuesReg(void)
{
    reg0CH = Rfic_ReadWord(0x0C);
}

uint16_t Rfic_GetTail(void)
{
    if(g_CurrentVfo->rx->dcsCtsType > SUBAUDIO_CTS)
    {
        return ((reg0CH & BIT10) >> 10);
    }
    else
    {
        return ((reg0CH & BIT11) >> 11);
    }
}

uint16_t Rfic_SubaudioDetect( void )
{ 
    if(g_CurrentVfo->rx->dcsCtsType > SUBAUDIO_CTS)
    {
        if(g_CurrentVfo->rx->dcsCtsType == SUBAUDIO_DCS_I)
        {
            return ((reg0CH & BIT15) >> 15);
        }
        else
        {
            return ((reg0CH & BIT14) >> 14);
        }
    }
    else
    {
        return ((reg0CH & BIT10) >> 10);
    }
}

void  CTS_DCS_RECE_Initial(void)
{   
    if(g_CurrentVfo->rx->dcsCtsType > SUBAUDIO_CTS)
    {
        DTCSS_WithRfic(g_CurrentVfo->rx->dcsCtsNum);
    }
    else if(g_CurrentVfo->rx->dcsCtsType == SUBAUDIO_CTS)
    {
        CTCSS_WithRfic(g_CurrentVfo->rx->dcsCtsNum);
    }
    else
    {
        CTCSS_WithRfic(551);
    }
}

void  CTS_DCS_SEND_Initial(void)
{
    RF_SendTail(OFF);
    if(g_CurrentVfo->tx->dcsCtsType != SUBAUDIO_NONE)
    {      
        if(g_CurrentVfo->tx->dcsCtsType > SUBAUDIO_CTS)
        {
            DTCSS_WithRfic(g_CurrentVfo->tx->dcsCtsNum);
        }
        else
        {
            CTCSS_WithRfic(g_CurrentVfo->tx->dcsCtsNum);
        }
    }
    else
    {
        Rfic_WriteWord(0x51,0x0000); 
    }
}


/************************************************************************/
/* 函数名称: Rfic_GpioSetBit                                         */
/* 参数变量: gpiox:   0 - 7                                             */
/*           val  :   0,1                                               */
/*   返回值: none                                                       */
/* 描述说明: 设置GPIO输出电平                                           */
/***********************************************************************/
void Rfic_GpioSetBit( uint16_t gpiox, uint08_t val )
{
    uint16_t temp;
    
    temp = Rfic_ReadWord(0x33); 
    //bit[15:8]=Gpio_out_en_b;bit[7:0]=Gpio_out_val  
    
    temp &= (~(gpiox << 8));
    if(val == GPIOx_RFIC_H)    
    {        
        temp |= gpiox;        
    }
    else
    {
        temp &= (~gpiox); 
    }
    
    Rfic_WriteWord(0x33,temp);   
}

uint08_t Rfic_GetTxPAPara()
{
    uint08_t index;
    uint08_t *bufAPC;
    uint32_t calcFreq;

    calcFreq = g_CurrentVfo->tx->frequency / 100000;
    if(g_CurrentVfo->tx->frequency >= 40000000)
    {
        index = (calcFreq - 400) / 10;
        if(index >= 12)
        {
            index = 12;
        }
        bufAPC = TXPWR_U_400[g_CurrentVfo->txPower];
    }
    else if(g_CurrentVfo->tx->frequency >= 30000000)
    {
        if(g_CurrentVfo->tx->frequency >= 35000000)
        {   
            index = (calcFreq - 350) / 5;
        }
        else
        {
            index = 0;
        }
        bufAPC = TXPWR_U_350[g_CurrentVfo->txPower];
    }
    else if(g_CurrentVfo->tx->frequency >= 20000000)
    {
        index = (calcFreq - 200) / 5;
        if(index > 12)
        {
            index = 12;
        }
        bufAPC = TXPWR_V_200[g_CurrentVfo->txPower];
    }
    else if(g_CurrentVfo->tx->frequency >= 13000000)
    {
        index = (calcFreq - 130) / 3;
        if(index >= 15)
        {
            index = 15;
        }
        bufAPC = TXPWR_V_136[g_CurrentVfo->txPower];
    }
    else
    {
        index = 0;
        bufAPC = TXPWR_V_136[g_CurrentVfo->txPower];
    }

    return bufAPC[index];
}

void Rfic_SetPA(uint16_t dat)
{
    uint16_t tblPAGain[] = {0xFF, 0XD7, 0XD7};

    if(dat == 0)
    { 
        Rfic_WriteWord( 0x36, 0X007F );// REG_36[7]: 1:Enable PACTL output  0:Disable
    }
    else
    {    
        Rfic_WriteWord( 0x36, (dat << 8) | tblPAGain[g_CurrentVfo->txPower % 3] );// REG_36[7]: 1:Enable PACTL output  0:Disable
    }
}

void Rfic_AdjustMicPGA(void)
{
    uint16_t temp;
    
    temp = Rfic_ReadWord(0x7d) & 0XFFE0;
    Rfic_WriteWord(0x7d, temp | (DEPTH_MIC_MODULATION & 0X1F));
}

void Rfic_MicIn_Disable(void)
{
    uint16_t reg;
    
    reg = Rfic_ReadWord(0X30) &0xFFFB;
    Rfic_WriteWord(0X30, reg);
}

void Rfic_MicIn_Enable(void)
{
    uint16_t reg;

    reg = Rfic_ReadWord(0x30) | 0x0004;
    Rfic_WriteWord(0x30, reg);
}
  
const uint16_t tblScramble[] = {0X891F, 0X8D27 };//3.4K  3.5K
void Rfic_SetScramble(uint08_t group, uint32_t freq)
{
    uint16_t temp;

    temp = Rfic_ReadWord(0x31);

    if(freq >= 10800000 && freq < 13600000)
    {
        Rfic_WriteWord(0X31, temp & (~BIT1));

        temp = Rfic_ReadWord(0x40) & 0xF000;
        Rfic_WriteWord(0x40, temp | 0X04E0);
        return;
    }
    
    if( group > 0 )
    {
        if(group > 2)
        {
            group = 2;
        }
    
        Rfic_WriteWord(0X31, temp | BIT1);
        Rfic_WriteWord(0X71, tblScramble[group - 1]);

        temp = Rfic_ReadWord(0x40) & 0xF000;
         Rfic_WriteWord(0x40, temp | 0X04EA);
    }
    else
    {
        Rfic_WriteWord(0X31, temp & (~BIT1));

        temp = Rfic_ReadWord(0x40) & 0xF000;
        Rfic_WriteWord(0x40, temp | 0X04EA);
    }
}

#define ADD1  1
#define ADD2  2
#define ADD3  3
#define ADD4  4
#define SUB1  -1 & 0xf
#define SUB2  -2 & 0xf
#define SUB3  -3 & 0xf
void RF_SetAfResponse(uint08_t tx, uint08_t f3k, uint08_t db) //参数：发射or接收，3k频响or 300hz频响，调整-1~+4dB
{ //v3版本芯片必须修改！！！

    uint16_t d1 = 0;
	uint16_t d2 = 0;

	switch(f3k) //3khz or 300hz
	{
		case 1: //for 3khz
			d1 = 0xf50b; //default

			switch(db&0xf)
			{
				case ADD1: //+1dB
					d1 = 0xe61c;
					break;
					
				case ADD2: //+2dB
					d1 = 0xdf22;
					break;
					
				case ADD3: //+3dB
					d1 = 0xd42d;
					break;
					
				case ADD4: //+4dB
					d1 = 0xcc35;
					break;
					
				case SUB1: //-1dB
					d1 = 0xfa02;
					break;
				case SUB2: //-2dB
					d1 = 0xfcfa;
					break;
				case SUB3: //-3dB
					d1 = 0xfef0;
					break;
					
	
			}		
			break;
	
		case 0: //for 300hz
			d1 = 0x9009; //default
			d2 = 0x31a9; 
		
			switch(db&0xf)
			{
				case ADD1: //+1dB
					d1 = 0x8f90;
					d2 = 0x31f3;
					break;
					
				case ADD2: //+2dB
					d1 = 0x8f46;
					d2 = 0x31e7;
					break;
					
				case ADD3: //+3dB
					d1 = 0x8ed8;
					d2 = 0x3232;
					break;
					
				case ADD4: //+4dB
					d1 = 0x8d8f;
					d2 = 0x3359;
					break;
					
				case SUB1: //-1dB
					d1 = 0x91c1;
					d2 = 0x3040;
					break;
					
				case SUB2: //-2dB
					d1 = 0x920b;
					d2 = 0x3010;
					break;
					
				case SUB3: //-3dB
					d1 = 0x935a;
					d2 = 0x2eff;
					break;
			}
			break;
	
	}


	switch(tx) //Tx or Rx
	{
	    case 1: //for Tx
	        switch(f3k) 
	        {
		        case 1: //for 3khz
		            Rfic_WriteWord(0x74,d1);
		            break;

				case 0: //for 300hz
				    Rfic_WriteWord(0x44,d1);
				    Rfic_WriteWord(0x45,d2);
				    break;
	        }
			
	        break;

		case 0: //for Rx
	        switch(f3k) 
	        {
		        case 1: //for 3khz
		            Rfic_WriteWord(0x75,d1);
		            break;

				case 0: //for 300hz
				    Rfic_WriteWord(0x54,d1);
				    Rfic_WriteWord(0x55,d2);
				    break;
	        }
			
		    break;
	}
	
}


void Rfic_Sleep(void) 
{
    Rfic_WriteWord(0x30,0x0000);
    Rfic_WriteWord(0x37,REG_37); //current~=200uA

}

void Rfic_WakeUp(void) 
{
    Rfic_WriteWord(0x37,REG_37 | 0xF); //[1]xtal;[0]bg
}


void  Rfic_Init(void)
{     
    uint16_t temp;

    //Soft Reset RF
    Rfic_WriteWord(0x00,0x8000);
    Rfic_WriteWord(0x00,0x0000);
    
    //Power Up RF
    Rfic_WriteWord(0x37,REG_37 | 0x0F); 

    //AGC TABLE
    Rfic_WriteWord(0x13,0x03BE);
    Rfic_WriteWord(0x12,0x037B);
    Rfic_WriteWord(0x11,0x027B);
    Rfic_WriteWord(0x10,0x007A);
    Rfic_WriteWord(0x14,0x0019);
    Rfic_WriteWord(0x49,0x2A38);
    Rfic_WriteWord(0x7B,0x8420);

    //Set MIC Sensitivity
    Rfic_WriteWord(0x7D, 0xE952);//bit[4:0]=MicSens

    //Set Volume 
    Rfic_WriteWord(0x48, 0xB000 | VOL_GAIN<<4 | DAC_GAIN);

    Rfic_WriteWord(0X1E, 0X4C58);
    Rfic_WriteWord(0X1F, 0XA656);

    Rfic_WriteWord(0x3E,0xA037);

    Rfic_WriteWord(0x3F, 0X07FE);
    Rfic_WriteWord(0X2A, 0X7FFF);
    Rfic_WriteWord(0X28, 0X6B00);
    Rfic_WriteWord(0X53, 0XE678);
    Rfic_WriteWord(0X2C, 0X5705);
    Rfic_WriteWord(0X4B, 0X7102);

    temp = Rfic_ReadWord(0x40) & 0xF000;
    Rfic_WriteWord(0x40, temp | 0X04D2);

    Rfic_WriteWord(0x77,0x88ef); 
    Rfic_WriteWord(0x26,0x13A0);  

    Rfic_WriteWord(0X4E, 0X6F15);
    Rfic_WriteWord(0X4F, 0X3F3E);

    Rfic_WriteWord(0x09,0x6F | 0x0<<12); 
    Rfic_WriteWord(0x09,0x6B | 0x1<<12);
    Rfic_WriteWord(0x09,0x67 | 0x2<<12);
    Rfic_WriteWord(0x09,0x62 | 0x3<<12);
    Rfic_WriteWord(0x09,0x50 | 0x4<<12);
    Rfic_WriteWord(0x09,0x47 | 0x5<<12);
    Rfic_WriteWord(0x09,0x3A | 0x6<<12);
    Rfic_WriteWord(0x09,0x2C | 0x7<<12);
    Rfic_WriteWord(0x09,0x41 | 0x8<<12);
    Rfic_WriteWord(0x09,0x37 | 0x9<<12);
    Rfic_WriteWord(0x09,0x25 | 0xA<<12);
    Rfic_WriteWord(0x09,0x17 | 0xB<<12);
    Rfic_WriteWord(0x09,0xE4 | 0xC<<12);
    Rfic_WriteWord(0x09,0xCB | 0xD<<12);
    Rfic_WriteWord(0x09,0xB5 | 0xE<<12);
    Rfic_WriteWord(0x09,0x9F | 0xF<<12);

    Rfic_WriteWord(0x74,0xfa02);
    Rfic_WriteWord(0x44,0x8f88);
    Rfic_WriteWord(0x45,0x3201);  
}

/************************************************************************/
/* 函数名称: RDA1846S_BandInitiall                                      */
/* 参数变量: INI_Band  0:窄带   1:宽带                                  */
/*   返回值: 无                                                         */
/* 描述说明: RDA1846S宽窄带初始化                                       */
/************************************************************************/
const uint08_t xtal26MAdjust[] = {40, 35, 30, 25, 20, 15, 10, 5, 0, 5, 10, 15, 20, 25, 30, 35, 40 };
void  Rfic_BandInitial(uint32_t freq)
{
    uint32_t calcFreq;
    uint16_t adjustDat;

    calcFreq = freq;
    if(XTAL_ADJUST > 16)
    {
        XTAL_ADJUST = 8; // ZERO
    }
    adjustDat = calcFreq * xtal26MAdjust[XTAL_ADJUST] / 10000000L;
    if(XTAL_ADJUST > 8)
    {
        calcFreq += adjustDat;
    }
    else
    {
        calcFreq -= adjustDat;
    }

    Rfic_WriteWord(0x38,(uint16_t)calcFreq);
    Rfic_WriteWord(0x39,(uint16_t)(calcFreq >> 16));

    if(g_CurrentVfo->wideNarrow == BAND_WIDE || g_sysRunPara.sysRunMode == MODE_WEATHER)
    {
        Rfic_WriteWord(0x43,0x3028);
    }
    else
    {
        Rfic_WriteWord(0x43,0x4048);
    }
}

/*********************************************************************
* 函 数 名: RfRxTxOnOffSetup
* 功能描述: Rfic接收/发射开关设置 
* 全局变量: 
* 输入参数：ON_FLAG:0:关闭  1:RX on  2:输出侧音  3:TX on  4:发射并输出侧音
* 输出参数:
* 返　　回:
* 说    明：2019.03.10 hht  v1.0
***********************************************************************/
void Rfic_RxTxOnOffSetup(uint08_t ON_FLAG)
{
    if(g_CurrentVfo->wideNarrow == BAND_WIDE && (ON_FLAG == RFIC_RXON || ON_FLAG == RFIC_TXON))
    {
        Rfic_WriteWord(0x30, 0x0200);
    }
    else
    {
        Rfic_WriteWord(0x30, 0x0000);
    }
    
    switch(ON_FLAG)
    {
        case RFIC_RXON:
            Rfic_WriteWord(0x30, 0xBFF1);
            break;

        case RFIC_TXON:
            Rfic_WriteWord(0x30, 0xC1FE);
            break;

        case RFIC_TONE: 
            Rfic_WriteWord(0x30, 0X0302);
            break;

        case RFIC_TXTONE:
            Rfic_WriteWord(0X30, 0XC3FA);
            break;
        default:
        case RFIC_IDLE:
            //Rfic_WriteWord(0x30, 0x0000);
            break;
    }   
}

uint08_t Rfic_GetRxTxState(void)
{
    uint16_t temp;

    temp = Rfic_ReadWord(0x30);
    if(temp & 0X0002)
    {// TX
        return 1;
    }
    else
    {// RX
        return 0;
    }
}

uint16_t Rfic_GetRssiVal(void)
{
    uint16_t temp;

    temp = Rfic_ReadWord(0x67) & 0x01FF;
    temp >>= 1;

    return temp;
}

uint08_t Rfic_GetNoiseVal(void)
{
    uint16_t temp;

    temp = Rfic_ReadWord(0x65) & 0X7F;

    return temp;
}


/***********************************************************************
* 函  数  名：Rfic_SQLSetup
* 功      能：静噪等级设置
* 寄存器说明: REG_78H
*             rssi_sq_th_in[7:0]   REG_78H[15:8]
*             rssi_sq_th_out[7:0]  REG_78H[7:0]
***********************************************************************/
void Rfic_SQLSetup()
{
    uint08_t index;
    uint08_t i;
    uint16_t noise = 0x3837;
    uint16_t UINT_BUFF;
    uint32_t freqTmp;

    UINT_BUFF = TH_SQL_TAB[g_radioInform.sqlLevel];
    freqTmp = g_CurrentVfo->rx->frequency / 100000;
    if(g_CurrentVfo->rx->frequency >= 40000000)
    {
        index = (freqTmp - 400) / 10;
        if(index >= 12)
        {
            index = 12;
        }
        if( TH_SQL_TAB[g_radioInform.sqlLevel] > OFFSET_SQL_U_400[index] )
        {
            UINT_BUFF = UINT_BUFF - OFFSET_SQL_U_400[index];
            i = TH_SQL_TAB_MUTE[g_radioInform.sqlLevel] - OFFSET_SQL_U_400[index];
        }
        noise = 0X302F;   
    }
    else if(g_CurrentVfo->rx->frequency >= 30000000)
    {
        if(g_CurrentVfo->rx->frequency >= 35000000)
        {
            index = (freqTmp - 350) / 5;
        }
        else
        {
            index = 0;
        }   
        if( TH_SQL_TAB[g_radioInform.sqlLevel] > OFFSET_SQL_U_350[index] )
        {
            UINT_BUFF = UINT_BUFF - OFFSET_SQL_U_350[index];
            i = TH_SQL_TAB_MUTE[g_radioInform.sqlLevel] - OFFSET_SQL_U_350[index];
        }
    }
    else if(g_CurrentVfo->rx->frequency >= 13000000 && g_CurrentVfo->rx->frequency < 20000000)
    {
        index = (freqTmp - 130) / 5;
        if(index > 9)
        {
            index = 9;
        }    
        if( TH_SQL_TAB[g_radioInform.sqlLevel] > OFFSET_SQL_V_136[index] )
        {
            UINT_BUFF = UINT_BUFF - OFFSET_SQL_V_136[index];
            i = TH_SQL_TAB_MUTE[g_radioInform.sqlLevel] - OFFSET_SQL_V_136[index];
        }
        noise = 0x3130;    
    }
    else
    {
        if(g_CurrentVfo->rx->frequency >= 20000000)
        {
            index = (freqTmp - 200) / 5;
            if(index > 12)
            {
                index = 12;
            }   
            if( TH_SQL_TAB[g_radioInform.sqlLevel] > OFFSET_SQL_V_200[index] )
            {
                UINT_BUFF = UINT_BUFF - OFFSET_SQL_V_200[index];
                i = TH_SQL_TAB_MUTE[g_radioInform.sqlLevel] - OFFSET_SQL_V_200[index];
            }
            noise = 0x3130;   
        }
        else if(g_CurrentVfo->rx->frequency >= 1800000 && (g_CurrentVfo->rx->frequency < 10800000))
        {
            index = ((freqTmp - 15) / 5) & 0x1F;
            if( TH_SQL_TAB[g_radioInform.sqlLevel] > OFFSET_SQL_18_100[index] )
            {
                UINT_BUFF = UINT_BUFF - OFFSET_SQL_18_100[index];
                i = TH_SQL_TAB_MUTE[g_radioInform.sqlLevel] - OFFSET_SQL_18_100[index];
            }            
            noise = 0x3837;
        }
        else if(g_CurrentVfo->rx->frequency >= 1800000 && (g_CurrentVfo->rx->frequency < 10800000))
        {
            UINT_BUFF = UINT_BUFF - 20;
            noise = 0x3837;
        }
        else
        {
            UINT_BUFF = 113; 
            i = UINT_BUFF - 5;    
        }
    }

    UINT_BUFF = (UINT_BUFF << 8) | i;
    Rfic_WriteWord(0X78, UINT_BUFF);
    Rfic_WriteWord(0X4F, noise);
}

/*********************************************************************
* 函 数 名: RfSetAfout
* 功能描述: Rfic输出音频类型
* 全局变量: 
* 输入参数: 0:MUTE 1 RX AFOUT   2:BEEP/ TX Side Ton  3:RX ALARM TONE 接收报警音
* 输出参数:
* 返　　回:
* 说    明：2019.03.10 hht  v1.0
***********************************************************************/
const uint16_t afState[] =
{
    0x0000, // MUTE 
    0x0100, // RX AFOUT 
    0x0200, // RX ALARM TON
    0x0300, // BEEP
    0x0600, // CTC/DCS Rx out for Testing
    0x0800, // FSK Rx out for Testing 
};

void Rfic_SetAfout(uint08_t state)
{
    uint16_t reg47h,volData = 25;
    
    reg47h = 0x6040;
    reg47h |= afState[state&0x0F];

    if(RF_Baseband_Mode == ModeAM && state == 1)   
    {
        reg47h |= 0x0600;
    }
    Rfic_WriteWord(0x47,reg47h );

    if(state == 3 || state == 0xF1)
    {//Beep音 独立调整音量大小
        Rfic_WriteWord(0x48,0xB800 | 10<<4 | 3); 
    }
    else
    {
        if( g_CurrentVfo->wideNarrow == BAND_WIDE )
        {
            volData = VOLUMN_WIDEBAND & 0X3F;
        }
        else
        {
            volData = VOLUMN_NARROWBAND & 0X3F;
        }

        if(RF_Baseband_Mode == ModeAM)
        {
            Rfic_WriteWord(0x48,0xB3AA); 
        }
        else
        {
            Rfic_WriteWord(0x48,0x8000 | volData<<4 | DAC_GAIN); 
        }
    }
}

extern void Rfic_SwitchFM_AM(uint8_t mode)
{
    if(mode == RF_Baseband_Mode)
    {
        return;
    }

    if( mode == ModeAM )
    {
        RF_Baseband_Mode = ModeAM;
    }
    else
    {
        RF_Baseband_Mode = ModeFM;
    }
}

void  Rfic_ConfigRxMode(void)
{
    GetHardWorkBand(g_CurrentVfo->rx->frequency/10000);
    if(g_CurrentVfo->rx->frequency >= 10800000 && g_CurrentVfo->rx->frequency < 13600000 )
    {
        Rfic_SwitchFM_AM(ON);
    }
    else
    {
        Rfic_SwitchFM_AM(OFF);
    }
    RF_PowerSet(g_ChannelVfoInfo.BandFlag,PWR_OFF);
    Rfic_WriteWord(0x37, REG_37 | 0x0F | BIT9);
    Rfic_RxTxOnOffSetup(RFIC_IDLE);
    Rfic_BandInitial(g_CurrentVfo->rx->frequency);
    Rfic_SQLSetup();
    CTS_DCS_RECE_Initial();
    Rfic_SetScramble(g_CurrentVfo->scarmble,g_CurrentVfo->rx->frequency);
    Rfic_RxTxOnOffSetup(RFIC_RXON);
    RF_PowerSet(g_ChannelVfoInfo.BandFlag,PWR_RXON);
}

void  Rfic_ConfigTxMode(void)
{
    uint16_t temp,gain;

    RF_PowerSet(g_ChannelVfoInfo.BandFlag,PWR_OFF);
    Rfic_SwitchFM_AM(ModeFM);
    Rfic_WriteWord(0x37, REG_37 | 0x0F);
    Rfic_RxTxOnOffSetup(RFIC_IDLE);
    Rfic_BandInitial(g_CurrentVfo->tx->frequency);
    CTS_DCS_SEND_Initial();
    gain = DEPTH_MIC_MODULATION % 32;
    temp = Rfic_ReadWord(0x7D) & 0XFFE0;
    temp |= gain;
    Rfic_WriteWord(0x7d, temp);
    Rfic_SetScramble(g_CurrentVfo->scarmble,g_CurrentVfo->tx->frequency);
    Rfic_RxTxOnOffSetup(RFIC_TXON);
    Rfic_SetPA(Rfic_GetTxPAPara());
    RF_PowerSet(g_ChannelVfoInfo.BandFlag,PWR_TXON);
    LedTxSwitch(LED_ON);
}

#define DTMF_TH   20                  // 0 ~ 63
void Rfic_EnterDTMFMode(uint08_t flagTx)
{
    Rfic_WriteWord(0x24,0x807F | DTMF_TH << 7); //[12:7]threshold
    if(flagTx == 1)
    {
        Rfic_WriteWord(0x70, 0xE0E0);               // BIT8 - 14: Tone1 Gain/ BIT0 - 6  Tone2/FSK Gain
    }

    Rfic_WriteWord(0x3F, 0X0800);
}

void Rfic_ExitDTMFMode(void)
{
    uint16_t temp;

    temp = Rfic_ReadWord(0x24) & 0xffdf;
    Rfic_WriteWord(0x24, temp);
    Rfic_WriteWord(0x70, 0X0000);
    Rfic_SetScramble(g_CurrentVfo->scarmble,g_CurrentVfo->rx->frequency);
}

void Rfic_SetDtmfFreq( uint16_t tone1Freq, uint16_t tone2Freq)
{
    Rfic_WriteWord(0x71, tone1Freq);
    Rfic_WriteWord(0x72, tone2Freq);
} 


extern uint08_t Rfic_GetDTMF_Link(void)
{
    uint16_t temp;

    temp = Rfic_ReadWord(0x3F);
    if((temp & 0x0800) == 0)
    {
        return 0;
    }

    temp = reg0CH;
    if(temp & 0x0001)
    {
        Rfic_WriteWord(0x02, 0x0000); // Clear Int
        return 1;
    }

    return 0;
}

extern uint08_t Rfic_ReadDTMF(void)
{
    uint16_t temp;

    temp = (Rfic_ReadWord(0x0B) >> 8) & 0X0F;
    return temp;
}


void Rfic_EnterFSKMode(void)
{
#if FSK2400
    Rfic_WriteWord(0x58,0x00C9);
#else
    Rfic_WriteWord(0x58,0x00C1);
#endif //FSK2400

    //Rfic_WriteWord(0X70, 0X00E0);  // Gain
    Rfic_WriteWord(0X70, 0X00AC);  // Gain
    
#if FSK2400
    Rfic_WriteWord(0x72,FSK_BAUD<<1); //2400bps
#else
    Rfic_WriteWord(0x72,FSK_BAUD); //1200bps
#endif //FSK2400

    Rfic_WriteWord(0x5C,0x5665); 
    Rfic_WriteWord(0x5D,(FSK_LEN*2-1)<<8); //[15:8]fsk tx length(byte) 

    Rfic_WriteWord(0x59, REG_59 | 0X4000); //Clear FiFO
    Rfic_WriteWord(0X59, REG_59 | 0X1000); // ENABLE FSK RX
    Rfic_WriteWord(0x3F, 0X2000);
}

void Rfic_ExitFSKMode(void)
{
    Rfic_WriteWord(0x70, 0X0000);
    Rfic_WriteWord(0X58, 0X0000);
}

uint08_t Rfic_FskTransmit(uint16_t *pData)
{
    uint08_t i;

    Rfic_WriteWord(0x3F, 0X8000);
    Rfic_WriteWord(0x59, REG_59 | 0x8000);
    Rfic_WriteWord(0x59, REG_59);

    for(i = 0; i < FSK_LEN; i++)
    {
        Rfic_WriteWord(0X5f, pData[i]);
    }
    Rfic_WriteWord(0x59, REG_59 | 0x0800);
    DelayMs(130);
    Rfic_WriteWord(0x59, REG_59);
    return 1;
}


uint08_t Rfic_GetFskRxFlag(void)
{
    uint16_t temp;

    temp = Rfic_ReadWord(0x3f);
    if((temp & 0x2000) == 0)
    {
        return 0;
    }

    temp = reg0CH;
    if(temp & 0x01)
    {
        return 1;
    }

    return 0;
}

uint08_t Rfic_ReadFskData(uint16_t *pData)
{
    uint08_t i;
    uint16_t temp;

    for(i = 0; i < FSK_LEN; i++)
    {
        pData[i] = Rfic_ReadWord(0x5F);
    }

    Rfic_WriteWord(0x02, 0x0000);
    temp = Rfic_ReadWord(0x0B);
    if(temp & 0x10)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


#define MDC_LEN               14  // 0 - 127
void Rfic_EnterMDC1200Mode(void)
{
    //uint16_t reg5E;
    Rfic_WriteWord(0x58, 0X37C3);
    Rfic_WriteWord(0X72, 0x3065);

    Rfic_WriteWord(0X70, 0X00B4);  // Gain

    Rfic_WriteWord(0x5D,((MDC_LEN*2-1)<<8)); //[15:8]ffsk tx length(byte)

    Rfic_WriteWord(0x59,REG_59 | 0x4000); //[14]fifo clear
    Rfic_WriteWord(0x59,REG_59 | 0x1000); //[12]fsk_rx_en;[13]scrb=0

    Rfic_WriteWord(0x3F,0x3000); //rx sucs/fifo_af irq mask=1
}

void Rfic_ExitMDC1200Mode(void)
{
    Rfic_WriteWord(0x70, 0X0000);
    Rfic_WriteWord(0X58, 0X0000);    
}

extern void Rfic_MDC1200ToneTx(void)
{
    const uint08_t MDC_SYNC[5] = {0xFB,0x72,0x40,0x99,0xA7};
    const uint16_t MDC_TXDATA[14] = {0XB604, 0X37D9, 0X8388, 0XE28E, 0X66EC, 0XAEE4, 0XC3DB,  0X158F, 0X19A7, 0X499F, 0X82D4, 0XFAE5, 0X1A96, 0XC9C0,};

    uint16_t rdata = 0;
    uint08_t i,cnt = 200;

    Rfic_WriteWord(0x3F,0x8000); //tx sucs irq mask=1
    
    Rfic_WriteWord(0x59,REG_59 | 0x8000); //[15]fifo clear; [7:4]prmb_size
	Rfic_WriteWord(0x59,REG_59);


	rdata = MDC_SYNC[0]; rdata <<= 8; rdata |= MDC_SYNC[1];
	Rfic_WriteWord(0x5A,rdata);
	
	rdata = MDC_SYNC[2]; rdata <<= 8; rdata |= MDC_SYNC[3];
	Rfic_WriteWord(0x5B,rdata);
	
	rdata = MDC_SYNC[4]; rdata <<= 8; rdata |= 0x30;  
	Rfic_WriteWord(0x5C,rdata);

	for(i=0;i<MDC_LEN;i++)
	{
        Rfic_WriteWord(0x5F,MDC_TXDATA[i]); //push data to fifo
	}

    DelayMs(20);

    Rfic_WriteWord(0x59,REG_59 | 0x0800); //[11]fsk_tx_en;[13]scrb=0

    while(cnt && !(rdata&0x1)) //polling int
    {
        DelayMs(5);
        rdata = Rfic_ReadWord(0x0C);
		cnt--;
    }
	
    Rfic_WriteWord(0x02,0x0000); //clear int


    Rfic_WriteWord(0x3F,0x0000); //tx sucs irq mask=0
    Rfic_WriteWord(0x59,REG_59); //fsk_tx_en=0, fsk_rx_en=0

    //return 0;
}

uint08_t Rfic_GetMDC1200RxFlag(void)
{
    uint16_t temp;

    temp = reg0CH;
    if(temp & 0x01)
    {
        Rfic_WriteWord(0x02, 0x0000); // Clear Int
        return 1;
    }

    return 0;
}

uint08_t Rfic_ReadMDC1200Data(uint16_t *pData)
{   
    return 0;
}
/**************************************************************
*  函 数 名: Rfic_SetTone1Freq
*  参    数: 频率转化后的数据, dat = freq(kHz) * 10.32444
*  描    述: 设置 Tone1 的频率
**************************************************************/
void Rfic_SetToneFreq( uint16_t dat )
{
    // REG_71H: Tone1 Freq   REG_72H: Tone2_Freq
    uint32_t tone1Freq;
    
    //tone1Freq = (uint32_t) dat * 1032444 / 100000;
    tone1Freq = (uint32_t) dat * 1032444L / 10000;
    Rfic_WriteWord( 0X71, tone1Freq );
}

void  Rfic_TxSingleTone_On(uint08_t txOn)
{      
    uint16_t temp;
    
    temp = Rfic_ReadWord(0X70) & 0X70FF;
    temp = temp | 0x8000 | ((60 % 128) << 8);// Gain: 60
    Rfic_WriteWord(0x70, temp);

    
    if(txOn)
    {
        Rfic_RxTxOnOffSetup(RFIC_TXTONE);
    }
    else
    {
        Rfic_RxTxOnOffSetup(RFIC_TONE);
    }

    Rfic_SetAfout(3); 
}

void Rfic_TxSingleTone_Off(void)
{
    uint32_t freq;
    Rfic_SetToneFreq(0);
    Rfic_WriteWord(0x70, 0X0000);

    if(Rfic_GetRxTxState() == 1)
    {// 发射Tone转为发射但不发Tone音
        Rfic_RxTxOnOffSetup(RFIC_TXON);
        freq = g_CurrentVfo->tx->frequency;
    }
    else
    {
        Rfic_RxTxOnOffSetup(RFIC_RXON);//切换到接收模式
        freq = g_CurrentVfo->rx->frequency;
    }
    
    Rfic_SetAfout(0);
    Rfic_SetScramble(g_CurrentVfo->scarmble,freq);
}

extern Boolean Rfic_GetSQLinkState(void)
{
    //静噪等级为0时，直接开启
    if(g_radioInform.sqlLevel == 0)
    {
        return TRUE;
    }
	
    if( reg0CH & BIT1)
    {
        return TRUE;
    }
	
    return FALSE;
}


void Rfic_FreqScan_Enable(void)
{
    Rfic_WriteWord(0x32, REG_32 | 0X0001);
}

void Rfic_FreqScan_Disable(void)
{
    Rfic_WriteWord(0x32, REG_32);
}

uint32_t Rfic_CheckFreqScan(void)
{
    uint16_t temp;
    uint32_t freqTemp;

    temp = Rfic_ReadWord(0x0D);
    if(temp & 0x8000)
    {
        return 0;
    }

    freqTemp = temp & 0x7FF;
    freqTemp <<= 16;
    
    freqTemp = freqTemp + Rfic_ReadWord(0x0E);
    return freqTemp;
}

void Rfic_CtcDcsScan_Setup(uint32_t freq)
{
    Rfic_WriteWord(0x37, REG_37 | 0x0F | BIT9);
    Rfic_RxTxOnOffSetup(RFIC_IDLE);
    Rfic_BandInitial(freq);
    Rfic_WriteWord(0x51, 0x0300); // Set Subaudio Filter BW Mode
    Rfic_RxTxOnOffSetup(RFIC_RXON);
}

uint08_t Rfic_GetSCtsDcsType(void)
{
    return ctsDcsCodeType;
}

void Rfic_ScanQT_Enable(void)
{
    Rfic_RxTxOnOffSetup(RFIC_IDLE);
    Rfic_WriteWord(0x51, 0x0300); // Set Subaudio Filter BW Mode
    Rfic_RxTxOnOffSetup(RFIC_RXON);
}

void Rfic_ScanQT_Disable(void)
{
    Rfic_RxTxOnOffSetup(RFIC_IDLE);
    Rfic_WriteWord(0x51, 0x0000); 
    Rfic_RxTxOnOffSetup(RFIC_RXON);
}




uint32_t Rfic_GetCtsDcsData(void)
{
    uint32_t subaudio;
    uint08_t i;
    uint16_t temp;

    temp = Rfic_ReadWord(0x69);
    if(!(temp & 0x8000))// DCS Found
    {
        subaudio = temp & 0x0FFF;
        subaudio <<= 12;
        subaudio = subaudio | (Rfic_ReadWord(0x6A) & 0X0FFF);
        ctsDcsCodeType = SUBAUDIO_DCS_N;
        
        return subaudio;
    }

    temp = Rfic_ReadWord(0x68);
    if(!(temp & 0x8000))
    {
        subaudio = temp & 0x1FFF;
        ctsDcsCodeType = SUBAUDIO_CTS;
        return subaudio;
    }
    ctsDcsCodeType = SUBAUDIO_NONE;

    return 0;
}

void Rfic_ByteWrite(uint08_t ByteData)
{
    uint08_t MaskData = 0x80;            // MSB first 
    
    while(MaskData)                           // 16times as loop 
    {
        RFIC_SCK_L;
        if(MaskData & ByteData)
        {
            RFIC_SDA_H;
        }
        else
        {
            RFIC_SDA_L; 
        }
        Rfic_delay(5);
        RFIC_SCK_H;
        Rfic_delay(5);
        MaskData >>= 1;
    }
}

void Rfic_WriteWord(uint08_t devAddr,uint16_t devData)
{
    RFIC_SCN_L;
    Rfic_delay(5);
    Rfic_ByteWrite(devAddr);
    Rfic_ByteWrite(devData >> 8);
    Rfic_ByteWrite(devData);
    RFIC_SCN_H;
    Rfic_delay(5);
    RFIC_SCK_L;
}


uint16_t Rfic_ReadWord(uint08_t devAddr)
{
    uint16_t MaskData = 0x8000;           // MSB first 
    uint16_t devData = 0;            // 读取的字节数据

    devAddr |= BIT7;
    RFIC_SCN_L;
    Rfic_delay(5);
    Rfic_ByteWrite(devAddr);
    RFIC_SCK_L;
    Rfic_delay(5);    
    RFIC_SDA_IN;                       // set as input
    RFIC_SDA_H;
    Rfic_delay(5);
    while(MaskData)
    {
        devData <<= 1;
        RFIC_SCK_H;
        if(RFIC_SDA_VAL)
        {       
            devData |= 0x0001;
        }
        Rfic_delay(5);
        RFIC_SCK_L;
        Rfic_delay(5);
        MaskData >>= 1;
    }
    RFIC_SDA_OUT;                       // set as output
    RFIC_SCN_H;
    Rfic_delay(5);
    RFIC_SDA_L;
    RFIC_SCK_L;
    
    return(devData);
}

