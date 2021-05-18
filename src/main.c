/* File: main.c */
/* Author: LeonLi */
/* Date: Fri May 14 14:24:22 CST 2021 */

// Include
#include "common.h"
#include "protocol_communicate.h"
#include "protocol.h"

void main(void)
{
    //Init protocol module register command
    ProtocolFrameBodyCommandCodeWriteAndReadFunctionRegister();

#ifdef DEBUG_TEST_FLAG

    //AUTHORIZE_STATUS
    //Control status
    //enum AuthorizeStatus{
    //    Authorize =      0x00,
    //    Unauthorized //  0x01
    //};

    //use
    //SendWriteAuthorizeStatusProtocolFrame(AUTHORIZE_STATUS);
    //or
    unsigned char TestDataAuthorizeSettingCommand[20] =
            {
                    SETTING_REQUEST,   //设置请求帧头类型 0x88 // 1
                    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,    //接收端唯一标识 UUID // 12
                    0x00,   //加密标识 不加密 // 1
                    0x10,   //协议版本 1.0 // 1
                    0x02,   //帧体长度 // 1
                    AUTHORIZE_STATUS,   //帧体功能码  LOCK_STATUS  // 1 //CRC 计算范围
                    Authorize,  // 1 //CRC 计算范围
                    0x20,0x00   // CRC16 // 2
            };

    // use
    //SendReadAuthorizeStatusProtocolFrame();
    // or
    unsigned char TestDataAuthorizeStatusCommand[19] =
            {
                    STATUS_REQUEST,   //设置请求帧头类型 0x8a // 1
                    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,    //接收端唯一标识 UUID // 12
                    0x00,   //加密标识 不加密 // 1
                    0x10,   //协议版本 1.0 // 1
                    0x01,   //帧体长度 // 1
                    AUTHORIZE_STATUS,   //帧体功能码  LOCK_STATUS // 1 //CRC 计算范围
                    0x80,0x7e   // CRC16 // 2
            };

    //LOCK_STATUS
    //Lock status
    //enum LockStatus{
    //  LOCK =      0x00,
    //  UNLOCK  //  0x01
    //};

    //use
    //SendWriteLockStatusProtocolFrame(Lock);
    //or
    unsigned char TestDataLockSettingCommand[20] =
    {
        SETTING_REQUEST,   //设置请求帧头类型 0x88 // 1
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,    //接收端唯一标识 UUID // 12
        0x00,   //加密标识 不加密 // 1
        0x10,   //协议版本 1.0 // 1
        0x02,   //帧体长度 // 1
        LOCK_STATUS,   //帧体功能码  LOCK_STATUS  // 1 //CRC 计算范围
        Lock,    //心跳包超时时间 // 1 //CRC 计算范围
        0xd0,0x00   // CRC16 // 2
    };

    //use
    //SendReadLockStatusProtocolFrame();
    //or
    unsigned char TestDataLockStatusCommand[19] =
    {
        STATUS_REQUEST,   //设置请求帧头类型 0x8a // 1
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,    //接收端唯一标识 UUID // 12
        0x00,   //加密标识 不加密 // 1
        0x10,   //协议版本 1.0 // 1
        0x01,   //帧体长度 // 1
        LOCK_STATUS,   //帧体功能码  LOCK_STATUS // 1 //CRC 计算范围
        0x81,0x3e   // CRC16 // 2
    };

    //SEAL_STATUS
    //Seal status
    //enum SealStatus{
    //    Seal =      0x00,
    //    Unseal //   0x01
    //};

    //use
    //SendWriteSealStatusProtocolFrame(Seal);
    //or
    unsigned char TestDataSealSettingCommand[20] =
    {
        SETTING_REQUEST,   //设置请求帧头类型 0x88 // 1
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,    //接收端唯一标识 UUID // 12
        0x00,   //加密标识 不加密 // 1
        0x10,   //协议版本 1.0 // 1
        0x02,   //帧体长度 // 1
        SEAL_STATUS,   //帧体功能码  SEAL_STATUS  // 1 //CRC 计算范围
        Seal,    //心跳包超时时间 // 1 //CRC 计算范围
        0x40,0x01   // CRC16 // 2
    };

    //use
    //SendReadSealStatusProtocolFrame();
    //or
    unsigned char TestDataSealStatusCommand[19] =
    {
        STATUS_REQUEST,   //设置请求帧头类型 0x8a // 1
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,    //接收端唯一标识 UUID // 12
        0x00,   //加密标识 不加密 // 1
        0x10,   //协议版本 1.0 // 1
        0x01,   //帧体长度 // 1
        SEAL_STATUS,   //帧体功能码  SEAL_STATUS // 1 //CRC 计算范围
        0x41,0xff   // CRC16 // 2
    };

    //SUB1G_FREQ

    //use
    //SendReadSub1GFreqProtocolFrame();
    //or
    unsigned char TestDataSub1GFreqStatusCommand[19] =
    {
        STATUS_REQUEST,   //设置请求帧头类型 0x8a // 1
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,    //接收端唯一标识 UUID // 12
        0x00,   //加密标识 不加密 // 1
        0x10,   //协议版本 1.0 // 1
        0x01,   //帧体长度 // 1
        SUB1G_FREQ,   //帧体功能码  SUB1G_FREQ Sub1G 通信频率 // 1 //CRC 计算范围
        0x83,0xbe   // CRC16 // 2
    };

    //BATTERY_POWER

    //use
    //SendReadBatteryPowerProtocolFrame();
    //or
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

    //use
    //SendWriteHeartBeatTimeIntervalProtocolFrame(5);
    //or
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

    //use
    //SendReadHeartBeatTimeIntervalProtocolFrame();
    //or
    unsigned char TestDataHeartBeatTimeIntervalStatusCommand[19] =
    {
        STATUS_REQUEST,   //设置请求帧头类型 0x8a // 1
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,    //接收端唯一标识 UUID // 12
        0x00,   //加密标识 不加密 // 1
        0x10,   //协议版本 1.0 // 1
        0x01,   //帧体长度 // 1
        HEART_BEAT_TIME_INTERVAL,   //帧体功能码  HEART_BEAT_TIME_INTERVAL 心跳包间隔 // 1 //CRC 计算范围
        0x42,0x3f   // CRC16 // 2
    };

    //HEART_BEAT_OVERTIME
    unsigned char TestDataHeartBeatOverTimeSettingCommand[20] =
    {
        SETTING_REQUEST,   //设置请求帧头类型 0x88 // 1
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,    //接收端唯一标识 UUID // 12
        0x00,   //加密标识 不加密 // 1
        0x10,   //协议版本 1.0 // 1
        0x02,   //帧体长度 // 1
        HEART_BEAT_OVERTIME,   //帧体功能码  HEART_BEAT_OVERTIME 绑定锁控 // 1 //CRC 计算范围
        0x08,    //心跳包超时时间 // 1 //CRC 计算范围
        0x46,0x02   // CRC16 // 2
    };

    unsigned char TestDataHeartBeatOverTimeStatusCommand[19] =
    {
        STATUS_REQUEST,   //设置请求帧头类型 0x8a // 1
        0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,    //接收端唯一标识 UUID // 12
        0x00,   //加密标识 不加密 // 1
        0x10,   //协议版本 1.0 // 1
        0x01,   //帧体长度 // 1
        HEART_BEAT_OVERTIME,   //帧体功能码  HEART_BEAT_OVERTIME 心跳包间隔 // 1 //CRC 计算范围
        0x82,0xfe   // CRC16 // 2
    };

    //BIND_LOCK_CONTROL
    //use
    //unsigned char Bind_UUID[UUID_LENGTH] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b};
    //SendWriteBindProtocolFrame(Bind_UUID);
    //or
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
    //use
    unsigned char UnBind_UUID[UUID_LENGTH] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b};
    SendWriteUnBindProtocolFrame(UnBind_UUID);
    //or
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

    //printf("AUTHORIZE_STATUS======================================================================= \n\r");
    //AUTHORIZE_STATUS
    //Setting
    //ProtocolDataParse(TestDataAuthorizeSettingCommand, 20);
    //Status
    //ProtocolDataParse(TestDataAuthorizeStatusCommand, 19);

    //printf("LOCK_STATUS======================================================================= \n\r");
    //LOCK_STATUS
    //Setting
    //ProtocolDataParse(TestDataLockSettingCommand, 20);
    //Status
    //ProtocolDataParse(TestDataLockStatusCommand, 19);

    //printf("SEAL_STATUS======================================================================= \n\r");
    //SEAL_STATUS
    //Setting
    //ProtocolDataParse(TestDataSealSettingCommand, 20);
    //Status
    //ProtocolDataParse(TestDataSealStatusCommand, 19);

    //printf("SUB1G_FREQ======================================================================= \n\r");
    //SUB1G_FREQ
    //ProtocolDataParse(TestDataSub1GFreqStatusCommand, 19);

    //printf("BATTERY_POWER======================================================================= \n\r");
    //BATTERY_POWER
    //ProtocolDataParse(TestDataBatteryPowerStatusCommand, 19);

    //printf("HEART_BEAT_TIME_INTERVAL======================================================================= \n\r");
    //HEART_BEAT_TIME_INTERVAL
    //Setting
    //ProtocolDataParse(TestDataHeartBeatTimeIntervalSettingCommand, 20);
    //Status
    //ProtocolDataParse(TestDataHeartBeatTimeIntervalStatusCommand, 19);

    //printf("HEART_BEAT_OVERTIME======================================================================= \n\r");
    //HEART_BEAT_OVERTIME
    //Setting
    //ProtocolDataParse(TestDataHeartBeatOverTimeSettingCommand, 20);
    //Status
    //ProtocolDataParse(TestDataHeartBeatOverTimeStatusCommand, 19);

    //printf("BIND_LOCK_CONTROL======================================================================= \n\r");
    //BIND_LOCK_CONTROL
    //ProtocolDataParse(TestDataUnBindSettingCommand, 31);

    //printf("UNBIND_LOCK_CONTROL======================================================================= \n\r");
    //UNBIND_LOCK_CONTROL
    //ProtocolDataParse(TestDataBindSettingCommand, 31);


#endif

}