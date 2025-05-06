#ifndef _VOICEINDEX_H
    #define _VOICEINDEX_H

/***********************************************************/
/*****定义语音片播报命令************************************/
/***********************************************************/
//                             命令码          播报内容
#define  vo_Null               0x00
#define  vo_0                  0x10         // 0
#define  vo_1         	       0x11         // 1
#define  vo_2         	       0x12         // 2
#define  vo_3         	       0x13         // 3
#define  vo_4         	       0x14         // 4
#define  vo_5         	       0x15         // 5
#define  vo_6         	       0x16         // 6
#define  vo_7         	       0x17         // 7
#define  vo_8         	       0x18         // 8
#define  vo_9         	       0x19         // 9
#define  vo_10         	       0x1A         // 10
#define  vo_20         	       0x1B         // 10
#define  vo_30         	       0x1C         // 10
#define  vo_40         	       0x1D         // 10
#define  vo_50         	       0x1E         // 10
#define  vo_60         	       0x1F         // 10
#define  vo_70         	       0x20         // 10
#define  vo_80         	       0x21         // 10
#define  vo_90         	       0x22         // 10
#define  vo_100         	   0x23         // 百
                               
#define  vo_Welcome	           0x24         // 欢迎使用
#define  vo_keylock            0x25         // 键盘锁定
#define  vo_unlock             0x26         // 键盘开锁
#define  vo_scanbegin          0x27         // 开始扫描
#define  vo_scanstop           0x28         // 停止扫描
#define  vo_ScramblerOn        0x00         // 保密通话
#define  vo_scrambleroff       0x00         // 保密解除
#define  vo_Function           0x29         // 功能选择
#define  vo_CTCSS              0x2A         // 模拟亚音
#define  vo_DCS                0x2B         // 数字亚音
#define  vo_power              0x2C         // 发射功率
#define  vo_savemode           0x2D         // 省电模式
#define  vo_Memorychl          0x2E         // 存储信道
#define  vo_Deletechl          0x2F         // 信道删除
#define  vo_Step               0x30         // 步进频率
#define  vo_Squelch            0x31         // 静噪等级
#define  vo_BackLight          0x32         // 背光选择
#define  vo_Txovertime         0x33         // 发射超时
#define  vo_VOX                0x34         // 声控发射
#define  vo_Freqdir            0x35         // 频差方向
#define  vo_Offsetfreq         0x36         // 频差频率
#define  vo_Txmemory           0x37         // 发射存储
#define  vo_Rxmemory           0x38         // 接收存储
#define  vo_EmerCall           0x39         // 紧急呼叫
#define  vo_Lowvoltage         0x3A         // 电量不足
#define  vo_Channelmode        0x3B         // 信道模式
#define  vo_Freqmode           0x3C         // 频率模式
#define  vo_Voicepromrt        0x3D         // 语言选择
#define  vo_bandselect         0x3E         // 频段选择
#define  vo_Dualstandby        0x3F         // 双频守候
#define  vo_Chlbandwidth       0x40         // 信道带宽
#define  vo_Optsignal          0x41         // 可选信令
#define  vo_Mutemode           0x42         // 静音方式
#define  vo_Busylockout        0x43         // 遇忙禁发
#define  vo_Beepprompt         0x44         // 提示音
#define  vo_ANIcode            0x45         // 身份码
#define  vo_initialization     0x46         // 初始化
#define  vo_Confirm            0x47         // 确定
#define  vo_Cancel             0x48         // 取消
#define  vo_ON                 0x49         // 开启
#define  vo_OFF                0x4A         // 关闭
#define  vo_Twotone            0x00         // 两音信令
#define  vo_Fivetone           0x00         // 五音信令
#define  vo_Digitalsignal      0x00         // 数字信令
#define  vo_Repeater           0x00         // 中继台
#define  vo_Menu               0x4B         // 菜单设置

#define  vo_zero               0x4E         // 
#define  vo_ten                0x58         // 
#define  vo_hundred            0x61         // 

                               
#define  vo_eleven             0x8C         // 
#define  vo_twelve             0x8D         // 
#define  vo_thirteen           0x8E         // 
#define  vo_fourteen           0x8F         // 
#define  vo_fifteen            0x90         // 
#define  vo_sixteen            0x91         // 
#define  vo_seventeen          0x92         // 
#define  vo_eighteen           0x93         // 
#define  vo_nineteen           0x94         // 
#define  vo_twenty             0x5A         // 
#define  vo_thirty             0x5B         // 
#define  vo_forty              0x5C         // 
#define  vo_fifty              0x5D         // 
#define  vo_sixty              0x5E         // 
#define  vo_seventy            0x5F         // 
#define  vo_eighty             0x60         // 
#define  vo_ninety             0x61         // 
#define  vo_and                0x00         // 
                               
#define  vo_switch_en          0x3E         // 将中文语音播报切换为英文
#define  vo_index_start        0x10         // 语音播报索引地址

#define  vo_beep_Start         0x95       

#endif

