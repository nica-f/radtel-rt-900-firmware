#ifndef __APPDTMF_H
    #define __APPDTMF_H

enum{ CALLTYPE_NONE, CALLTYPE_NID, CALLTYPE_ID, CALLTYPE_GROUP, CALLTYPE_ALL };
    
#define DTMF_ANI_LEN       3      //���屾��ID����
    
typedef struct 
{
    const U16 tone1Freq;
    const U16 tone2Freq;
}DTMFCODESTRUCT;

typedef struct
{
    U8  machineId[5];//�����豸ID
    U8  dtmfAlarmWord;         //������
    U8  dtmfFlag;              //BIT1:  PTT�ɿ����ͱ���ID
                                  //BIT0:  PTT���·��ͱ���ID
    U8  onTime;                //DTMF�����ʱ��  ��Χ��80-2000MS ������Ϊ10MS��,ȡֵ:0 1 2 3 .... 195 Ĭ�ϣ�0
    U8  offTime;               //DTMF����ʱ��  ��Χ��80-2000MS ������Ϊ10MS��,ȡֵ:0 1 2 3 .... 195 Ĭ�ϣ�0
    U8  separator;            // �ָ���
    U8  groupCall;            // �����
}__attribute__( ( packed ) )STF_DTMFSTORE;

//����ģʽ
enum{DTMF_ONLINE=1,DTMF_OFFLINE=2,DTMF_ALARMCODE=4,DTMF_ALARMID,DTMF_TYPEIN,DTMF_ANI=8};

//DTMF����״̬
enum {DTMF_OVER = 0,DTMF_SETUP,DTMF_FREQ,DTMF_STOP};
typedef struct
{
    U8  id[5];
    U8  name[11];
} STR_CONTACT;

typedef struct
{
    U8  code[16];              //DTMF���͵ı���
    U8  cntRxDtmf;             //DTMF��������
    U8  state;                 //����״̬
    U8  enCodeNum;             //��ǰ�������
    U8  enCode;                //��ǰ��Ҫ���͵ı���
    U8  sendFlag;              //���ڷ����־
    U16 timeOut;               //DTMF����ʱ����߷���ȴ�ʱ��
    U16 detTime;               //DTMF���ʱ��
    U8  timeRxOut;             //���ս��볬ʱʱ��
    String aniCode[8];            //���з�����
    String callCode[8];           //������Ϣ
    U8  callType;              //��������   ����\����ݸ���\���\Ⱥ��
    U8  matchTime[2];          //ƥ�����ʱ��
    U8  flagAck;               //���ʶ��ش���־
    U8  timerDlyTxEnd;         //���������ʱʱ��

    U8  timerDtmfGroupRst;     //DTMF���и�λʱ��   30s�ڲ���Ҫ�ٴμ��
    U8  flagDtmfMatch;         //DTMF���м���־

    STR_CONTACT contact[20];

    U8  onlineCode[16];      // ������  
    U8  offlineCode[16];     // ������
    U8  killCode[16];         // ң����
    U8  reliveCode[16];       // ������

}STR_DTMFINFO;

extern STF_DTMFSTORE g_dtmfStore;
extern STR_DTMFINFO dtmfInfo;
extern const DTMFCODESTRUCT DTMFCODE[21];
/************************************************************/
extern void EnterDtmfEditMode(void);
extern void ExitDtmfEditMode(void);
extern void GetDtmfEditCode(void);
extern void ResetDtmfEditCode(void);
extern void KeyProcess_DtmfInput(U8 keyEvent);

extern void DtmfSendKeypadCode(U8 code);
extern void DtmfSendTxOver(void);
extern void DtmfSendCodeOn(U8 type);
extern void DtmfTask(void);
extern void Task_HangUp(void);
extern void DtmfReceiveSetup(void);
extern void DtmfReceiveTask(void);
extern void DtmfClrMatchTimer(void);
extern void DtmfRstMatchTimer(U8 set);

extern void ClearDisANIFlag(void);
extern void DtmfSendANIAck(void);

extern void DtmfInfoInit(void);
extern U8 DtmfGetMatchStatue(void);


#endif
