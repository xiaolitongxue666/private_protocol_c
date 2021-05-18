/* File: main.c */
/* Author: LeonLi */
/* Date: Fri May 14 14:24:22 CST 2021 */

// Include
#include "common.h"
#include "protocol_communicate.h"
#include "protocol.h"

#ifdef DEBUG_TEST_FLAG

//BATTERY_POWER
unsigned char TestDataBatteryPowerStatusCommand[19] =
{
        STATUS_REQUEST,   //设置请求帧头类型 0x8a // 1
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,    //接收端唯一标识 UUID // 12
        0x00,   //加密标识 不加密 // 1
        0x10,   //协议版本 1.0 // 1
        0x01,   //帧体长度 // 1
        BATTERY_POWER,   //帧体功能码  BATTERY_POWER 电池电量 // 1 //CRC 计算范围
        0x43,0x7f   // CRC16 // 2
};

//HEART_BEAT_TIME_INTERVAL
unsigned char TestDataHeartBeatTimeIntervalSettingCommand[20] =
{
    SETTING_REQUEST,   //设置请求帧头类型 0x88 // 1
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,    //接收端唯一标识 UUID // 12
    0x00,   //加密标识 不加密 // 1
    0x10,   //协议版本 1.0 // 1
    0x02,   //帧体长度 // 1
    HEART_BEAT_TIME_INTERVAL,   //帧体功能码  HEART_BEAT_TIME_INTERVAL 绑定锁控 // 1 //CRC 计算范围
    0x05,    //心跳包超时时间 // 1 //CRC 计算范围
    0x13,0xc2   // CRC16 // 2
};

//HEART_BEAT_OVERTIME
unsigned char TestDataHeartBeatOverTimeSettingCommand[20] =
{
    SETTING_REQUEST,   //设置请求帧头类型 0x88 // 1
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,    //接收端唯一标识 UUID // 12
    0x00,   //加密标识 不加密 // 1
    0x10,   //协议版本 1.0 // 1
    0x02,   //帧体长度 // 1
    HEART_BEAT_OVERTIME,   //帧体功能码  HEART_BEAT_TIME_INTERVAL 绑定锁控 // 1 //CRC 计算范围
    0x08,    //心跳包超时时间 // 1 //CRC 计算范围
    0x46,0x02   // CRC16 // 2
};

//BIND_LOCK_CONTROL
unsigned char TestDataBindSettingCommand[31] =
{
    SETTING_REQUEST,   //设置请求帧头类型 0x88 // 1
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,    //接收端唯一标识 UUID // 12
    0x00,   //加密标识 不加密 // 1
    0x10,   //协议版本 1.0 // 1
    0x0d,   //帧体长度 // 1
    BIND_LOCK_CONTROL,   //帧体功能码  BIND_LOCK_CONTROL 绑定锁控 // 1 //CRC 计算范围
    0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,    //锁控单片机UUID // 12 //CRC 计算范围
    0xF5,0x4A   // CRC16 // 2
};

//UNBIND_LOCK_CONTROL
unsigned char TestDataUnBindSettingCommand[31] =
{
    SETTING_REQUEST,   //设置请求帧头类型 0x88 // 1
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,    //接收端唯一标识 UUID // 12
    0x00,   //加密标识 不加密 // 1
    0x10,   //协议版本 1.0 // 1
    0x0d,   //帧体长度 // 1
    UNBIND_LOCK_CONTROL,   //帧体功能码  UNBIND_LOCK_CONTROL 绑定锁控 // 1 //CRC 计算范围
    0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,    //锁控单片机UUID // 12 //CRC 计算范围
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

    //ProtocolDataParse(TestDataHeartBeatOverTimeSettingCommand, 20);

    ProtocolDataParse(TestDataBatteryPowerStatusCommand, 19);
#endif

}