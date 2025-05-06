#ifndef __VOICEBROADCAST_H
    #define __VOICEBROADCAST_H

/**************************************************************************************************/
/*****��������������������*************************************************************************/
/**************************************************************************************************/
#include "VoiceIndex.h"

/**************************************************************************************************/
typedef struct
{
    U32 length;          //��Ƶ�ļ��ܳ���
    U32 dataAddr;        //��Ƶ�ļ���ʼ��ַ
}STR_VOICE_INDEX;

//����DMA����ʹ�õĽṹ��
typedef struct
{
    U32 logicAddr;       //ʵ�ʲ���ʱ��ȡ�ĵ�ַ
    U32 usedLen;         //�Ѿ����ŵ����ݳ���
    volatile U8  finishFlag;      //������ɱ�־
    volatile U8  dmaBufUsed;      //��ǰʹ�õĻ�������
    volatile U8  dmaBufAUseFlag;  //��ǰʹ�õĻ��������Ƿ�ʼʹ��
    volatile U8  dmaBufBUseFlag;  //��ǰʹ�õĻ��������Ƿ�ʼʹ��
    U16 dmaBufA[1024];
    U16 dmaBufB[1024];
    U8  lastPackage;
}STR_VOICE_PLAY;

typedef struct
{
    STR_VOICE_INDEX voiceIndex;
    STR_VOICE_PLAY voicePlay;
}STR_VOICE_ONFO;

//��Ϊ��������ʱʹ�õĽṹ��
typedef struct
{
    U8  voiceState;     //�������ű�־���ж��Ƿ�����������ģʽ 
    U8  busyFlag;    //�Ƿ����ڲ���״̬
    U8  voiceCnt;       //��ǰ��Ҫ��������������
    U8  voiceBuf[6];    //��ǰ�������������
}STR_VOICE;

extern STR_VOICE voice;
extern STR_VOICE_ONFO g_voiceInform;
extern U8 FastChangeVoice;

extern void VoiceOutput_Interrupt(void);
extern void AudioHard_Init(void);

extern void Audio_PlayVoice(U8 Data);
extern void Audio_PlayVoiceLock(U8 Data);
extern void Audio_PlayNumInQueue(U8 Data);
extern void Audio_PlayChanNum(U8 Data);	

extern U8 Audio_CheckBusy(void);
extern void Audio_PlayStop(void);
extern void Audio_PlayTask(void);
extern void VoiceBroadcastWithBeepLock(U8 voiceDat,ENUM_BEEPMODE beepData);

#endif
