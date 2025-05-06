#ifndef __APPFM_H
    #define __APPFM_H

//����FMʱ�����
#define FM_FREQSW_TIME    10      //������Ƶ���л�ʱ��10msΪ��λ
#define FM_SEEK_TIMEOUT   1000    //�������Զ�������ʱʱ�� 10S
#define FM_SEEK_TIME      FM_SEEK_TIMEOUT - 20 //�������Զ�������ʱʱ��
#define FM_RETURN_TIME    200     //�������˳��󷵻�ʱ��

#define FM_MAX_CH_NUM     30      //�������洢�ŵ�����    

//��������������״̬
enum {FM_STOP=0,FM_SLEEP,FM_READY, FM_SEEK, FM_PLAY};              
typedef struct
{
    U8  mode;                 //����������״̬
    U8  band;                 //����Ƶ�� 0:76-108  1:65-76 
    U16 freq;                 //��������ǰƵ��
    U16 timeOut;              //��ʱʱ�䣬�����������˳��󷵻�
    U8  fmChList[4];          //��������Ч�ŵ��б�
    U8  fmChActive;           //�������ŵ�ģʽ�Ƿ���Ч
}STR_FMSTATE;

extern STR_FMSTATE    fmInfo;
/********************************************************************/
extern Boolean CheckFmChActive(U8 curChanNum);
extern void ResumeFmMode(void);
extern void FmBandConfig(void);
extern Boolean CheckFmVfoMode(void);
extern void FmCheckChannelActive(void);
extern void FmCheckTimeOut(void);
extern void FmEnterSleepMode(void);
extern void FMSwitchExit(void);
extern void EnterFmMode(void);
extern void ExitFmMode(void);
extern void FmTaskFunc(void);
extern void ResetFmSleepTime(void);
extern void KeyProcess_Fm(U8 keyEvent);

#endif
