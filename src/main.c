/* File: main.c */
/* Author: LeonLi */
/* Date: Fri May 14 14:24:22 CST 2021 */

// Include
#include "common.h"
#include "protocol_communicate.h"
#include "protocol.h"

#ifdef DEBUG_TEST_FLAG

//HEART_BEAT_TIME_INTERVAL
unsigned char TestDataHeartBeatTimeIntervalSettingCommand[20] =
{
    0x88,   //��������֡ͷ���� 0x88 // 1
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,    //���ն�Ψһ��ʶ UUID // 12
    0x00,   //���ܱ�ʶ ������ // 1
    0x10,   //Э��汾 1.0 // 1
    0x02,   //֡�峤�� // 1
    HEART_BEAT_TIME_INTERVAL,   //֡�幦����  HEART_BEAT_TIME_INTERVAL ������ // 1 //CRC ���㷶Χ
    0x05,    //��������ʱʱ�� // 1 //CRC ���㷶Χ
    0x13,0xc2   // CRC16 // 2
};

//HEART_BEAT_OVERTIME
unsigned char TestDataHeartBeatOverTimeSettingCommand[20] =
{
        0x88,   //��������֡ͷ���� 0x88 // 1
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,    //���ն�Ψһ��ʶ UUID // 12
        0x00,   //���ܱ�ʶ ������ // 1
        0x10,   //Э��汾 1.0 // 1
        0x02,   //֡�峤�� // 1
        HEART_BEAT_OVERTIME,   //֡�幦����  HEART_BEAT_TIME_INTERVAL ������ // 1 //CRC ���㷶Χ
        0x08,    //��������ʱʱ�� // 1 //CRC ���㷶Χ
        0x46,0x02   // CRC16 // 2
};

//BIND_LOCK_CONTROL
unsigned char TestDataBindSettingCommand[31] =
{
    0x88,   //��������֡ͷ���� 0x88 // 1
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,    //���ն�Ψһ��ʶ UUID // 12
    0x00,   //���ܱ�ʶ ������ // 1
    0x10,   //Э��汾 1.0 // 1
    0x0d,   //֡�峤�� // 1
    BIND_LOCK_CONTROL,   //֡�幦����  BIND_LOCK_CONTROL ������ // 1 //CRC ���㷶Χ
    0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,    //���ص�Ƭ��UUID // 12 //CRC ���㷶Χ
    0xF5,0x4A   // CRC16 // 2
};

//UNBIND_LOCK_CONTROL
unsigned char TestDataUnBindSettingCommand[31] =
{
    0x88,   //��������֡ͷ���� 0x88 // 1
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,    //���ն�Ψһ��ʶ UUID // 12
    0x00,   //���ܱ�ʶ ������ // 1
    0x10,   //Э��汾 1.0 // 1
    0x0d,   //֡�峤�� // 1
    UNBIND_LOCK_CONTROL,   //֡�幦����  UNBIND_LOCK_CONTROL ������ // 1 //CRC ���㷶Χ
    0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,    //���ص�Ƭ��UUID // 12 //CRC ���㷶Χ
    0x74,0x48   // CRC16 // 2
};

#endif

void main(void)
{
    ProtocolBodyCommandReadWriteFunctionRegister();

#ifdef DEBUG_TEST_FLAG
    //ProtocolDataParse(TestDataBindSettingCommand, 31);

    //ProtocolDataParse(TestDataUnBindSettingCommand, 31);

    //ProtocolDataParse(TestDataHeartBeatTimeIntervalSettingCommand, 20);

    ProtocolDataParse(TestDataHeartBeatOverTimeSettingCommand, 20);
#endif

}