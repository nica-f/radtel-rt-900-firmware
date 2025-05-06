#ifndef _DATAADDRMAPTYPE_H_
    #define _DATAADDRMAPTYPE_H_

//定义使用到的EEPROM的地址
#define CHAN_SIZE                 32       //信道信息大小
#define CHAN_ADDR                 0x0000   //信道首地址
#define NAME_ADDR_SHIFT          20       //信道名称地址偏移
#define NAME_SIZE                 12       //信道名称信息大小为16字节
#define BANK_SIZE                 2048     //一个区域支持64个信道
#define BANK_CH_NUM               64       //一个区域支持64个信道

#define VFO_INFO_ADDR             0x8000   //频率模式存储地址
#define VFO_SIZE                  32       //频率模式信道信息大小
#define VFO1_ADDR                 0x8000   //频率模式地址
#define VFO2_ADDR                 0x8020   //频率模式地址

#define RADIO_IMFOS_ADDR          0X9000   //对讲机 频率模式/功能信息/收音机 地址      
#define RADIO_SIZE                32       //可选信息大小
#define RADIO1_ADDR               0x9000   //可选首地址
#define RADIO2_ADDR               0x9020   //可选首地址

#define FM_SIDZE                  32
#define FM_CH_ADDR                0x9040   //收音机信道频点存储地址,该版本暂时不需要


//双音多频[DTMF]
#define DTMFINFOR_ADDR            0xA000   

//遥毙码地址16个字节
#define DTMF_KILLED_ADDR          0xA010   

//定义DTMF存储地址  16  
#define DTMF_SIZE                 10
#define DTMF_CODE_ADDR            0xA020

//定义区域名称使用地址
#define BANK_NAME_SIZE            16      //信道名称支持12个字节,按16个字节存储
#define BANK_NAME_ADDR            0xA200   

//GPS定位使用联系人名称和使用ID,本机名称使用地址
#define MARCHINE_ID_ADDR          0xB000   //本机ID存储地址 20组
#define MARCHINE_NAME_ADDR        0xB0C0   //联系人名称，用于GPS显示20组 名称一组16字节   

//用户自定义信道名称
#define USER_CHNAME_ADDR          0xB500   //用户自定义信道名称地址

/************************************************************************/
#define FACTORY_DATE_ADDR         0xC000   //出厂日期

/************************************************************************/
#define EXTEND_ADDR               0xD000   //扩频缩频地址

/************************************************************************/
/*本机运行信息存储*/
/************************************************************************/
//定义信道号、收音机等使用地址
#define SYSTEMRAN_ADDR            0xE000
#define F1CHAN_ADDR               0xE000  
#define F2CHAN_ADDR               0xE002
#define FM_ADDR                   0xE004

//遥毙标志
#define KILLMODE_ADDR             0xE006

//暂时不增加
#define F1WXCHAN_ADDR             0XE00A  // A段天气预报频段
#define F2WXCHAN_ADDR             0XE00C  // B段天气预报频段

/************************************************************************/
/*                         调 试 信 息 地 址  0xF000开始                */
/************************************************************************/
#define DEBUG_ADDR                0XF000
//电池电压 
#define DEV_BATT_ADDR             0XF200 
//调制度
#define RF_MODULATION_ADDR        0XF210
//中英文
#define DEV_LANGUAGE_ADDR         0XF220
//蓝牙使能
#define DEV_BTEN_ADDR             0XF221 

// APC输出
#define RF_ADJUST_BASE_ADDR       0XF000
#define RF_PWR_H_U_400_ADDR       0XF000
#define RF_PWR_H_V_136_ADDR       0XF010
#define RF_PWR_H_V_200_ADDR       0XF020
#define RF_PWR_H_U_350_ADDR       0XF030
#define RF_PWR_M_U_400_ADDR       0XF040
#define RF_PWR_M_V_136_ADDR       0XF050
#define RF_PWR_M_V_200_ADDR       0XF060
#define RF_PWR_M_U_350_ADDR       0XF070
#define RF_PWR_L_U_400_ADDR       0XF080
#define RF_PWR_L_V_136_ADDR       0XF090
#define RF_PWR_L_V_200_ADDR       0XF0A0
#define RF_PWR_L_U_350_ADDR       0XF0B0

// SQL门限
#define RF_SQL_TAB_ADDR           0XF0C0
#define RF_SQL_TAB_MUTE_ADDR      0XF0D0
#define RF_SQL_U_400_ADDR         0XF0E0  //静噪修正值
#define RF_SQL_V_136_ADDR         0XF0F0  //静噪修正值
#define RF_SQL_V_200_ADDR         0XF100  //静噪修正值
#define RF_SQL_U_350_ADDR         0XF110  //静噪修正值

//18-108M静躁补偿 每隔5M
#define RF_SQL_18_100_ADDR        0XF140  //静躁修正值 


//接收电调TV
#define RF_TV_U_400_ADDR          0XF130
#define RF_TV_V_136_ADDR          0XF140
#define RF_TV_V_200_ADDR          0XF150
#define RF_TV_AM_ADDR             0XF160

#define BAND_ADDR                 0XF230  // V/U/200M 频段范围
#define BAND2_ADDR                0XF240  //300M 频段范围 

/************************************************************************/
#define ADDR_ICON_WX              (0x73A00 + FLASH_FNT_BASIC_ADDR)
#define ADDR_ICON_FM              (0x73AB0 + FLASH_FNT_BASIC_ADDR)
#define ADDR_ICON_PROGRAM        (0x73B10 + FLASH_FNT_BASIC_ADDR)
#define ADDR_ICON_SEARCH         (0x70B30 + FLASH_FNT_BASIC_ADDR)
#define ADDR_ICON_VHF             (0x70B50 + FLASH_FNT_BASIC_ADDR)
#define ADDR_ICON_UHF             (0x70B80 + FLASH_FNT_BASIC_ADDR)
#define ADDR_ICON_200             (0x70BB0 + FLASH_FNT_BASIC_ADDR)
#define ADDR_ICON_350             (0x70BE0 + FLASH_FNT_BASIC_ADDR)


#endif


