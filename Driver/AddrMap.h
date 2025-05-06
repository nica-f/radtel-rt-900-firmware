#ifndef _DATAADDRMAPTYPE_H_
    #define _DATAADDRMAPTYPE_H_

//����ʹ�õ���EEPROM�ĵ�ַ
#define CHAN_SIZE                 32       //�ŵ���Ϣ��С
#define CHAN_ADDR                 0x0000   //�ŵ��׵�ַ
#define NAME_ADDR_SHIFT          20       //�ŵ����Ƶ�ַƫ��
#define NAME_SIZE                 12       //�ŵ�������Ϣ��СΪ16�ֽ�
#define BANK_SIZE                 2048     //һ������֧��64���ŵ�
#define BANK_CH_NUM               64       //һ������֧��64���ŵ�

#define VFO_INFO_ADDR             0x8000   //Ƶ��ģʽ�洢��ַ
#define VFO_SIZE                  32       //Ƶ��ģʽ�ŵ���Ϣ��С
#define VFO1_ADDR                 0x8000   //Ƶ��ģʽ��ַ
#define VFO2_ADDR                 0x8020   //Ƶ��ģʽ��ַ

#define RADIO_IMFOS_ADDR          0X9000   //�Խ��� Ƶ��ģʽ/������Ϣ/������ ��ַ      
#define RADIO_SIZE                32       //��ѡ��Ϣ��С
#define RADIO1_ADDR               0x9000   //��ѡ�׵�ַ
#define RADIO2_ADDR               0x9020   //��ѡ�׵�ַ

#define FM_SIDZE                  32
#define FM_CH_ADDR                0x9040   //�������ŵ�Ƶ��洢��ַ,�ð汾��ʱ����Ҫ


//˫����Ƶ[DTMF]
#define DTMFINFOR_ADDR            0xA000   

//ң�����ַ16���ֽ�
#define DTMF_KILLED_ADDR          0xA010   

//����DTMF�洢��ַ  16  
#define DTMF_SIZE                 10
#define DTMF_CODE_ADDR            0xA020

//������������ʹ�õ�ַ
#define BANK_NAME_SIZE            16      //�ŵ�����֧��12���ֽ�,��16���ֽڴ洢
#define BANK_NAME_ADDR            0xA200   

//GPS��λʹ����ϵ�����ƺ�ʹ��ID,��������ʹ�õ�ַ
#define MARCHINE_ID_ADDR          0xB000   //����ID�洢��ַ 20��
#define MARCHINE_NAME_ADDR        0xB0C0   //��ϵ�����ƣ�����GPS��ʾ20�� ����һ��16�ֽ�   

//�û��Զ����ŵ�����
#define USER_CHNAME_ADDR          0xB500   //�û��Զ����ŵ����Ƶ�ַ

/************************************************************************/
#define FACTORY_DATE_ADDR         0xC000   //��������

/************************************************************************/
#define EXTEND_ADDR               0xD000   //��Ƶ��Ƶ��ַ

/************************************************************************/
/*����������Ϣ�洢*/
/************************************************************************/
//�����ŵ��š���������ʹ�õ�ַ
#define SYSTEMRAN_ADDR            0xE000
#define F1CHAN_ADDR               0xE000  
#define F2CHAN_ADDR               0xE002
#define FM_ADDR                   0xE004

//ң�б�־
#define KILLMODE_ADDR             0xE006

//��ʱ������
#define F1WXCHAN_ADDR             0XE00A  // A������Ԥ��Ƶ��
#define F2WXCHAN_ADDR             0XE00C  // B������Ԥ��Ƶ��

/************************************************************************/
/*                         �� �� �� Ϣ �� ַ  0xF000��ʼ                */
/************************************************************************/
#define DEBUG_ADDR                0XF000
//��ص�ѹ 
#define DEV_BATT_ADDR             0XF200 
//���ƶ�
#define RF_MODULATION_ADDR        0XF210
//��Ӣ��
#define DEV_LANGUAGE_ADDR         0XF220
//����ʹ��
#define DEV_BTEN_ADDR             0XF221 

// APC���
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

// SQL����
#define RF_SQL_TAB_ADDR           0XF0C0
#define RF_SQL_TAB_MUTE_ADDR      0XF0D0
#define RF_SQL_U_400_ADDR         0XF0E0  //��������ֵ
#define RF_SQL_V_136_ADDR         0XF0F0  //��������ֵ
#define RF_SQL_V_200_ADDR         0XF100  //��������ֵ
#define RF_SQL_U_350_ADDR         0XF110  //��������ֵ

//18-108M���겹�� ÿ��5M
#define RF_SQL_18_100_ADDR        0XF140  //��������ֵ 


//���յ��TV
#define RF_TV_U_400_ADDR          0XF130
#define RF_TV_V_136_ADDR          0XF140
#define RF_TV_V_200_ADDR          0XF150
#define RF_TV_AM_ADDR             0XF160

#define BAND_ADDR                 0XF230  // V/U/200M Ƶ�η�Χ
#define BAND2_ADDR                0XF240  //300M Ƶ�η�Χ 

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


