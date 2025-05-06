#ifndef __DUALSTANDBY_H
    #define __DUALSTANDBY_H

typedef struct
{
    U8   dualRxFlag;                             //˫�ؽ��ձ�־,�غ��ŵ����յ��ź�ʱ��λ
    U8   dualOnFlag;                             //˫�ؿ�����־
    U8   dualRxTime;                             //˫���л�ʱ��
    U8   UpdateFalg;                             //������ʾ��־���������غ��ŵ����յ��ź�ʱ���±�־ʹ��
    U8   dualResumeFlag;                         // ˫���ŵ���־
    U8   dualResumeTime;                         // N����Զ��ص����ŵ�
}STR_DUAL;

extern STR_DUAL dualStandby; 

extern void DualChannelSwitch2Main(void);
extern void DualStandbyWorkON(void);
extern void DualStandbyWorkOFF(void);
extern void ResetDualRxTime(void);
extern void DualStandbyTask(void);

#endif
