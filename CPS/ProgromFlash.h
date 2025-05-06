#ifndef __INC_PROGROMTYPE_H__
    #define __INC_PROGROMTYPE_H__
/***************************************************************************************/
#define FLASH_PRO_HEAD           0xA5       //�����ͷ  

#define FLASH_PRO_CMD_ADDR       0x01
#define FLASH_PRO_PACKED_ADDR    0x02
#define FLASH_PRO_LEN_ADDR       0x04
#define FLASH_PRO_DATA_ADDR      0x06

//��������
#define PRO_CMD_HANDSHAKE        0x02
#define PRO_CMD_ADDR             0x03
#define PRO_CMD_EARSE            0x04
#define PRO_CMD_END              0x06      //��������
#define PRO_CMD_WRITE            0x57

#define PRO_CMD_ERROR            0xEE

//����������
#define ERROR_CODE_OK            0X59       //������ȷ
#define ERROR_CODE_HEAD          0x01       //��ͷ����
#define ERROR_CODE_HAND          0x02       //���������
#define ERROR_CODE_CMD           0x03       //�������
#define ERROR_CODE_DATA          0x04       //���ݴ���
#define ERROR_CODE_WRITE         0x05       //Flashд�����
#define ERROR_CODE_ADDR          0x06       //Flash��ַ����

//�������ģʽ
#define ERASE_MODE               0X45
#define ERASE_MODE_CHIP          0X01       //��Ƭ����
#define ERASE_MODE_4K            0X02       //����4k
#define ERASE_MODE_32K           0X03       //����32k
#define ERASE_MODE_64K           0X04       //����64k

enum{FLASH_PRG_CHECKHEAD=0,FLASH_PRG_CMD,FLASH_PRG_END,FLASH_PRG_ERROR};

typedef struct
{
    U8  cmd;                  //��ǰ���յ�������
    U32 StartAddr;            //Flash��ʼ�༭���׵�ַ
    U16 packageNum;           //��ǰ�Ѿ����յ������ݰ�
    U16 length;               //��ǰ���յ������ݳ���
    U16 txLength;             //���͵����ݳ���
    U8  txBuf[64];
}STR_FLASH_PROGROM;

extern STR_FLASH_PROGROM    flashProgrom;    
/***************************************************************************************/
#define UART_MAX_NUM           1040        //���ݻ�����72���ֽڣ���������Flash�༭ʹ��

#define UARTBUF_NUM      144//72        //���ݻ�����72���ֽ�

#define UART_TIMEOUT     2000      //2S��δ���յ����ݳ�ʱ�˳�

#define PROGROMLEN       64        //д�볤�ȹ̶�Ϊ32�ֽ�

enum{PRG_CHECKHEAD=0,PRG_FRQRANGE,PRG_WR,PRG_END,PRG_ERROR};

typedef  void (*pFunction)(void);

typedef struct
{
    U8  states;                 //дƵ״̬
    U8  errCnt;                 //�������
    U8  enterMode;              //�Ƿ�����дƵģʽ��־
    U8  recFlag;                //���յ����ݱ�־
    U16 dataNum;                //���յ������ݳ���
    U16 timeOut;                //��дƵ��ʱʱ��
    U8  packageTime;            //�������ݰ�ʱ��
    U8  rxBuf[1040];    //�������ݻ���
}STR_PROGROM;

extern STR_PROGROM progrom;

/***************************************************************************************/
extern const U8  strModelType[];
/***************************************************************************************/
extern Boolean CheckLinkHead(void);
extern void ProgromInit(void);
extern void CheckProgromMode(U8  rxData);
extern void UartSendBuf(U8  *buf,U16 len);
extern void EnterProgromMode(void);
extern void EnterFlashProgromMode(void);

#endif
