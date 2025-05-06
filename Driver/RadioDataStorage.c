#include "includes.h"

const U8  addrMap[8] = {0xFE,0xFC,0xF8,0xF0,0xE0,0xC0,0x80,0x00};

U8  powerOnMsg[17] = {0};
STR_RF_MODELE g_rfMoudel;
STR_BAND bandRang;
/*********************************************************************
* �� �� ��: Flash_ModifyChannelData
* ��������: �����ŵ���Ϣ��������Ϣ���ݺ��ŵ�����
* ���������channelNum:�ŵ���  chData:����ָ��  chName:�ŵ���������ָ��
* �������:
* ��������:
* ˵    ����
***********************************************************************/
extern void Flash_ModifyChannelData(U16 channelNum,U8 * chData,U8 * chName)
{
    U8  buf[4*1024]; // 4K
    U32 indexSector; // ����
    U32 indexChannelNum;
    U32 addr = CHAN_ADDR;
    
    //����洢�ŵ��߼���ַ
    indexSector = channelNum / 128; // 4k / 32byte = 128
    addr = addr + (indexSector * 0x1000);

    //�����ŵ�λ��
    indexChannelNum = channelNum % 128;

    // ��������/����FLASH
    SpiFlash_ReadBytes(addr, buf, 4*1024);
    SpiFlash_EraseSector(addr);

    //�޸��ŵ����ݣ����ı��ŵ�����
    memcpy(buf + (indexChannelNum * CHAN_SIZE), chData, sizeof(STR_CHANNEL));
    //�����ŵ�����
    memcpy(buf + (indexChannelNum * CHAN_SIZE + NAME_ADDR_SHIFT), chName, NAME_SIZE);
    
    SpiFlash_WriteBytes(addr, buf, 4*1024);
}

/*********************************************************************
* ��������: �����ŵ���Ϣ��������Ϣ���ݺ��ŵ�����
* ���������channelNum:�ŵ���  chData:�ŵ���Ϣ����ָ�� chName:�ŵ���������ָ��
* �������:
* ��������:
* ˵    ���������иı�ʱ�Ż�������ݴ洢����
***********************************************************************/
extern void Flash_SaveChannelData(U16 channelNum,U8 * chData,U8 * chName)
{
    U32 addr;
    U8  channelBuf[32] = {0x00};

    addr = g_ChannelVfoInfo.currentChannelNum*CHAN_SIZE+CHAN_ADDR;
    SpiFlash_ReadBytes(addr,channelBuf, CHAN_SIZE);

    //�ж������Ƿ��иı�
    if(memcmp(channelBuf,chData,sizeof(STR_CHANNEL)) != 0 || memcmp(chName,&chData[NAME_ADDR_SHIFT],NAME_SIZE) != 0)
    {
        Flash_ModifyChannelData(channelNum,chData,chName);
    }
}

/*********************************************************************
* ��������: ɾ��ָ���ŵ�����
* ���������channelNum:�ŵ���
* �������:
* ��������:
* ˵    ����ֻɾ��ǰ8���ֽ�Ƶ�����ݣ���������0
***********************************************************************/
extern void Flash_DeleteChannelData(U16 channelNum)
{
    U32 addr;
    U8  resetBuf[8];

    addr = channelNum*CHAN_SIZE+CHAN_ADDR;
    memset(resetBuf,0x00,8);
    SpiFlash_WriteBytes(addr,resetBuf, 8);
}

/*********************************************************************
* �� �� ��: Flash_GetLogicAddrShift
* ��������: ��ȡ��ַƫ��λ��
* ���������addr:�洢���ַ   useByte:��Ҫʹ�õ���byte bit/8
* �������:
* ��������:
* ˵    ����
***********************************************************************/
U16 Flash_GetLogicAddrShift(U32 addr,U8  useByte)
{
    U8  i,j;
    U8  addrMask;
    U8  addrMap[32];
    U16 addrOffset = 0xFF;  // ��ַƫ��

    SpiFlash_ReadBytes(addr, addrMap,useByte);

    for(i = 0; i < useByte; i++)
    {
        addrMask = 0x01;
        for(j = 0; j < 8; j++)
        {
            if(addrMap[i] & addrMask)
            {
                addrOffset = i * 8 + j;

                return addrOffset;
            }
            else
            {
                addrMask <<= 1;
            }
        }
    }
    return addrOffset;
}

// ����Խ��� �Խ���������Ϣ/�������ŵ���Ϣ
extern void Flash_SaveRadioImfosData(void)
{
    U8  addrOffset;
    U8  dataMap;
    U32 logicAddr;
    U16 checkSum,CheckSumRd;
    U8  buf[96] = {0x00};//�Խ���������Ϣ1+�Խ���������Ϣ2+������������Ϣ = 94Byte + 2Byte(CheckSum)
                            // (84 - 16Byte) / 96 = 42  ˥������: 42
    U8  cmpBuf[80];
    
    //��ȡ�洢λ����Ϣ
    addrOffset = Flash_GetLogicAddrShift(RADIO_IMFOS_ADDR,6);

    memcpy(buf, (U8  *)&g_radioInform.sqlLevel, sizeof(STR_RADIOINFORM));
    //���ڴ洢������ʾ��Ϣ
    memcpy(buf+64,powerOnMsg, 16);

    //����CRCУ��
    checkSum = CRC_ValidationCalc(buf,94);
    memcpy(buf+94,(U8  *)&checkSum,2);

    if(addrOffset < 41)
    {
        logicAddr = addrOffset * 96 + RADIO_IMFOS_ADDR + 16;
        //��ȡ��ǰУ��ͱȽ�
        SpiFlash_ReadBytes(logicAddr+94, (U8  *)&CheckSumRd, 2);
        if(CheckSumRd == checkSum)
        {
            SpiFlash_ReadBytes(logicAddr, cmpBuf, 80);
            if(memcmp(cmpBuf,buf,80) == 0)
            {//������ֱͬ�ӷ���
                return;
            }
        }
        //�����иı�ű���
        logicAddr += 96;
        SpiFlash_WriteBytes(logicAddr, buf, 96);
        
        //��ǵ�ַ������
        dataMap = addrMap[(addrOffset%8)];
        SpiFlash_WriteBytes((RADIO_IMFOS_ADDR + (addrOffset/8)), &dataMap, 1);
    }
    else
    {// ����
        SpiFlash_EraseSector(RADIO_IMFOS_ADDR);
        SpiFlash_WriteBytes((RADIO_IMFOS_ADDR + 16), buf, 96);
    }
}

// ��ȡ�Խ��� Ƶ��ģʽ����/�Խ���������Ϣ/��������Ϣ
extern void Flash_ReadRadioImfosData(void)
{
    U8  addrOffset;
    U32 logicAddr;
    U16 checkSum;
    U8  buf[96]={0x00};//�Խ���������Ϣ1+�Խ���������Ϣ2+������������Ϣ = 94Byte + 2Byte(CheckSum)
                           // (4K - 16Byte) / 96 = 42  ˥������: 42
    //��ȡ�洢λ����Ϣ
    addrOffset = Flash_GetLogicAddrShift(RADIO_IMFOS_ADDR,6);
    
    if(addrOffset < 42)
    {
        logicAddr = addrOffset* 96 + RADIO_IMFOS_ADDR + 16;
        SpiFlash_ReadBytes(logicAddr, buf, 96);
        
        memcpy((U8  *)&checkSum,&buf[94],2);
        if(checkSum == CRC_ValidationCalc(buf,94))
        {// У��ͨ��
            memcpy((U8  *)&g_radioInform.sqlLevel, buf, sizeof(STR_RADIOINFORM));
            memcpy(powerOnMsg, buf+64,16);
            return;
        }
    }
    // ���ݴ���У��δͨ��/�ӱ�������ȡ����
    SpiFlash_EraseSector(RADIO_IMFOS_ADDR);
    ResetRadioFunData();

}

//����Խ���Ƶ��ģʽ����,ʹ��һ��flash 4K,ǰ16byte����ָʾ������
//A��Ƶ��ģʽ+B��Ƶ��ģʽ = 64 + 2Byte(CheckSum)
//(4K - 16Byte) / 66 = 61  ˥������: 61
// ǰ16�ֽ�����˥���㷨  ʵ��ʹ��41bit
U8  VfoBuf[66]={0x00};
extern void Flash_SaveVfoData(U8  workAB)
{
    U8  addrOffset;
    U8  dataMap;
    U32 logicAddr;
    U16 checkSum;

    if(workAB == 1)
    {
        if(memcmp(VfoBuf+32,g_ChannelVfoInfo.vfoInfo[1].freq,32) == 0)
        {//����δ�ı䲻����
            return;
        }
        memcpy(VfoBuf+32, g_ChannelVfoInfo.vfoInfo[1].freq, 32);
    }
    else if(workAB == 0)
    {
        if(memcmp(VfoBuf,g_ChannelVfoInfo.vfoInfo[0].freq,32) == 0)
        {//����δ�ı䲻����
            return;
        }
        memcpy(VfoBuf, g_ChannelVfoInfo.vfoInfo[0].freq,32);
    }
    else if(workAB == 0XFF)
    {// дƵ��
        
    }
    else
    {//��λר��
        memcpy(VfoBuf, g_ChannelVfoInfo.vfoInfo[0].freq,32);
        memcpy(VfoBuf+32, g_ChannelVfoInfo.vfoInfo[1].freq, 32);
    }
    checkSum = CRC_ValidationCalc(VfoBuf,64);

    memcpy(VfoBuf+64,(U8  *)&checkSum,2);

    addrOffset = Flash_GetLogicAddrShift(VFO_INFO_ADDR,8);

    if(addrOffset < 60)
    {//�����ַʱ����Ҫ����
        logicAddr = (addrOffset + 1) * 66+ VFO_INFO_ADDR + 16;
        SpiFlash_WriteBytes(logicAddr, VfoBuf, 66);
        //��ǵ�ַ������
        dataMap = addrMap[(addrOffset%8)];
        SpiFlash_WriteBytes((VFO_INFO_ADDR + (addrOffset/8)), &dataMap, 1);

    }
    else
    {//���������д��
        SpiFlash_EraseSector(VFO_INFO_ADDR);
        SpiFlash_WriteBytes((VFO_INFO_ADDR + 16), VfoBuf, 66);
    }
}

//��ȡ�Խ���Ƶ��ģʽ����
extern void Flash_ReadVfoData(U8  workAB)
{
    U8  addrOffset;
    U32 logicAddr;
    U16 checkSum;

    addrOffset = Flash_GetLogicAddrShift(VFO_INFO_ADDR,8);
    if(addrOffset < 61)
    {
        logicAddr = (addrOffset * 66) + VFO_INFO_ADDR + 16;
        SpiFlash_ReadBytes(logicAddr, VfoBuf, 66);

        memcpy((U8  *)&checkSum,&VfoBuf[64],2);
        if(checkSum == CRC_ValidationCalc(VfoBuf,64))
        {//����У����ȷ
            if(workAB == 1)
            {
                memcpy(&g_ChannelVfoInfo.vfoInfo[1], VfoBuf+32, 32);
            }
            else
            {
                memcpy(&g_ChannelVfoInfo.vfoInfo[0], VfoBuf, 32);
            }
            return;
        }
    }
    //���ݴ��󣬴ӳ�ʼ�����ݻָ�
    SpiFlash_EraseSector(VFO_INFO_ADDR);
    ResetVfoModeData();

}

//����Խ����ŵ���,����Ԥ���ŵ���,��������ǰƵ��
//Ԥ��14Byte + 2Byte(CheckSum)
//(4K - 32Byte) / 16 = 254  ˥������: 254
// ǰ16�ֽ�����˥���㷨  ʵ��ʹ��61bit
extern void Flash_SaveSystemRunData(void)
{
    U16 addrOffset;
    U8  dataMap;
    U32 logicAddr;
    U16 checkSum;
    U8  buf[16]={0x00};

    addrOffset = Flash_GetLogicAddrShift(SYSTEMRAN_ADDR,32);

    //��ȡ����
    memcpy(buf, (U8  *)&g_ChannelVfoInfo.channelNum, 2);

    //����CRCУ��
    checkSum = CRC_ValidationCalc(buf,14);
    memcpy(buf+14,(U8  *)&checkSum,2);

    if(addrOffset < 253)
    {
        logicAddr = (addrOffset + 1) * 16 + SYSTEMRAN_ADDR + 32;
        SpiFlash_WriteBytes(logicAddr, buf, 16);
        //��ǵ�ַ������
        dataMap = addrMap[(addrOffset%8)];
        SpiFlash_WriteBytes((SYSTEMRAN_ADDR + (addrOffset/8)), &dataMap, 1);
    }
    else
    {//���������д��
        SpiFlash_EraseSector(SYSTEMRAN_ADDR);
        SpiFlash_WriteBytes((SYSTEMRAN_ADDR + 32), buf, 16);
    }
}

//��ȡ�Խ����ŵ���,����Ԥ���ŵ���,��������ǰƵ��
//Ԥ��14Byte + 2Byte(CheckSum)
//(4K - 32Byte) / 16 = 254  ˥������: 254
// ǰ16�ֽ�����˥���㷨  ʵ��ʹ��61bit
extern void Flash_ReadSystemRunData(void)
{
    U16 addrOffset;
    U32 logicAddr;
    U16 checkSum;
    U8  buf[16]={0x00};

    addrOffset = Flash_GetLogicAddrShift(SYSTEMRAN_ADDR,32);

    if(addrOffset < 254)
    {
        logicAddr = (addrOffset * 16) + SYSTEMRAN_ADDR + 32;
        SpiFlash_ReadBytes(logicAddr, buf, 16);

        memcpy((U8  *)&checkSum,&buf[14],2);
        if(checkSum == CRC_ValidationCalc(buf,14))
        {//����У����ȷ
            memcpy((U8  *)&g_ChannelVfoInfo.channelNum, buf, 2);
            
            return;
        }
    }
    //���ݴ��󣬴ӳ�ʼ�����ݻָ�
    g_ChannelVfoInfo.channelNum[0] = 0;
    g_ChannelVfoInfo.channelNum[1] = 0;
}

//����DTMF����ID
extern void Flash_SaveDtmfInfo(void)
{
     U8  buf[288]={0xFF};
     
     SpiFlash_ReadBytes(DTMFINFOR_ADDR, buf, 288); //32+16*16

     memcpy(buf,(U8  *)&g_dtmfStore, sizeof(g_dtmfStore));
     SpiFlash_EraseSector(DTMFINFOR_ADDR);

     SpiFlash_WriteBytes(DTMFINFOR_ADDR, buf, 288);
}

//����̶�Ƶ����Ϣ
const U8  fixBand1[][16] = 
{
  {0x01,0x01,0x36,0x01,0x74,0x01,0x04,0x00,0x06,0x00,0x01,0x02,0x00,0x02,0x60,0x00},
}; 

const U8  fixBand2[][8] = 
{
  {0x00,0x03,0x50,0x03,0x90,0x00,0x00,0x00},
}; 

// ��ȡ�Խ��� ���Բ���
extern void Flash_ReadDebugImfosData(void)
{
    U8  bandData[16];
    U8  bandData1[16];
    U8  i;

    SpiFlash_ReadBytes(RF_PWR_H_U_400_ADDR, &i, 1);
    if(i != 0xFF)
    {
        SpiFlash_ReadBytes(RF_PWR_H_U_400_ADDR, TXPWR_H_U_400, 16);
        SpiFlash_ReadBytes(RF_PWR_H_V_136_ADDR, TXPWR_H_V_136, 16);
        SpiFlash_ReadBytes(RF_PWR_H_V_200_ADDR, TXPWR_H_V_200, 16);
    
        SpiFlash_ReadBytes(RF_PWR_L_U_400_ADDR, TXPWR_L_U_400, 16);
        SpiFlash_ReadBytes(RF_PWR_L_V_136_ADDR, TXPWR_L_V_136, 16);
        SpiFlash_ReadBytes(RF_PWR_L_V_200_ADDR, TXPWR_L_V_200, 16);
        
        SpiFlash_ReadBytes(RF_SQL_TAB_ADDR, TH_SQL_TAB, 10 );
        SpiFlash_ReadBytes(RF_SQL_TAB_MUTE_ADDR, TH_SQL_TAB_MUTE, 10);
    
        SpiFlash_ReadBytes(RF_SQL_U_400_ADDR, OFFSET_SQL_U_400, 16);
        SpiFlash_ReadBytes(RF_SQL_V_136_ADDR, OFFSET_SQL_V_136, 16);
        SpiFlash_ReadBytes(RF_SQL_V_200_ADDR, OFFSET_SQL_V_200, 16);
        SpiFlash_ReadBytes(RF_SQL_U_350_ADDR, OFFSET_SQL_U_350, 16);

        SpiFlash_ReadBytes(RF_MODULATION_ADDR, OFFSET_MODULATION, 16);

        //SpiFlash_ReadBytes(DEV_BATT_ADDR, battery.voltList, BAT_LEVEL_NUM);
    }
    
    //��ȡ������
    Flash_ReadRfMoudelType();
    g_sysRunPara.moduleType = g_rfMoudel.moduleType;
    
    if(g_sysRunPara.moduleType >= 0x30 && g_sysRunPara.moduleType <= 0x35)
    {
        g_sysRunPara.moduleType &= 0x0F;
    }
    else
    {
        g_sysRunPara.moduleType = 0;
    }
    memcpy(bandData,fixBand1[0],16);
    memcpy(bandData1,fixBand2[0],8);
    
    g_sysRunPara.rfTxFlag.txEnable[0] = bandData[0];
    g_sysRunPara.rfTxFlag.txEnable[1] = bandData[5];
    g_sysRunPara.rfTxFlag.txEnable[2] = bandData[10];

    // ����Ƶ�η�Χ
    for(i = 0; i < 16; i++)
    {
       bandData[i] = changeHexToInt(bandData[i]);
    }
    // U��Ƶ�ʷ�Χ
    bandRang.bandFreq.vhfL   = bandData[1]*1000+bandData[2]*10;
    bandRang.bandFreq.vhfH   = bandData[3]*1000+bandData[4]*10;
    bandRang.bandFreq.freqVL = bandRang.bandFreq.vhfL*10000;
    bandRang.bandFreq.freqVH = bandRang.bandFreq.vhfH*10000;

    // V��Ƶ�ʷ�Χ
    bandRang.bandFreq.uhfL   = bandData[6]*1000+bandData[7]*10;
    bandRang.bandFreq.uhfH   = bandData[8]*1000+bandData[9]*10;
    bandRang.bandFreq.freqUL = bandRang.bandFreq.uhfL*10000;
    bandRang.bandFreq.freqUH = bandRang.bandFreq.uhfH*10000;
    
    // 200MƵ�ʷ�Χ
    bandRang.bandFreq.vhf2L   = bandData[11]*1000+bandData[12]*10;
    bandRang.bandFreq.vhf2H   = bandData[13]*1000+bandData[14]*10;
    bandRang.bandFreq.freqV2L = bandRang.bandFreq.vhf2L*10000;
    bandRang.bandFreq.freqV2H = bandRang.bandFreq.vhf2H*10000;

    //350MƵ�ʷ�Χ
    for(i = 0; i < 8; i++)
    {
       bandData1[i] = changeHexToInt(bandData1[i]);
    }
    bandRang.bandFreq.B350ML = bandData1[1]*1000+bandData1[2]*10;
    bandRang.bandFreq.B350MH = bandData1[3]*1000+bandData1[4]*10;
    bandRang.bandFreq.freq350ML = bandRang.bandFreq.B350ML*10000;
    bandRang.bandFreq.freq350MH = bandRang.bandFreq.B350MH*10000;
}

//���淢�������Ƶ��ѡ����
//Ԥ��14Byte + 2Byte(CheckSum)
//(4K - 32Byte) / 16 = 254  ˥������: 254
// ǰ16�ֽ�����˥���㷨  ʵ��ʹ��61bit
extern void Flash_SaveRfMoudelType(void)
{
    
}

//��ȡ�Խ������������Ƶ��ѡ����
//Ԥ��14Byte + 2Byte(CheckSum)
//(4K - 32Byte) / 16 = 254  ˥������: 254
// ǰ16�ֽ�����˥���㷨  ʵ��ʹ��61bit
extern void Flash_ReadRfMoudelType(void)
{
    
}

//����Խ���������ģʽ�ŵ�����
//����������64Byte + 2Byte(CheckSum)
//(4K - 16Byte) / 66 = 61  ˥������: 61
// ǰ16�ֽ�����˥���㷨  ʵ��ʹ��120bit
extern void Flash_SaveFmData(void)
{
    
}

//��ȡ��������ǰƵ�ʣ��ŵ�����
//����������64Byte + 2Byte(CheckSum)
//(4K - 16Byte) / 66 = 61  ˥������: 61
// ǰ16�ֽ�����˥���㷨  ʵ��ʹ��120bit
extern void Flash_ReadFmData(void)
{
    
}

