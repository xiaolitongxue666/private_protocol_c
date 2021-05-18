/* File: protocol.h */
/* Author: LeonLi */
/* Date: Thu May 13 16:25:08 CST 2021 */
#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

// Include
#include <stdbool.h>

// Macro
#define PROTOCOL_VERSION 0x10

#define PROTOCOL_FRAME_BODY_COMMAND_REGISTER_MAX_NUM   30

#define PROTOCOL_FRAME_BODY_MAX_LENGTH 47

#define PROTOCOL_FRAME_HEAD_TYPE_LENGTH 1

#define PROTOCOL_FRAME_HEAD_TYPE_INDEX 0

#define PROTOCOL_FRAME_MAX_LENGTH  64

#define PROTOCOL_FRAME_MIN_LENGTH  19

#define PROTOCOL_FRAME_HEAD_LENGTH 16

#define PROTOCOL_FRAME_BODY_COMMAND_CODE_LENGTH 1

#define PROTOCOL_FRAME_TAIL_CRC_LENGTH 2

// Header type
enum ProtocolFrameHeadType{
    SETTING_REQUEST =   0x88,
    SETTING_ACK,    //  0x89
    STATUS_REQUEST, //  0x8a
    STATUS_ACK      //  0x8b
};

// Command code
enum ProtocolFrameBodyCommandCodeEnum{
    AUTHORIZE_STATUS =              0x01,
    LOCK_STATUS,                //  0x02
    SEAL_STATUS,                //  0x03
    SUB1G_FREQ,                 //  0x04
    BATTERY_POWER,              //  0x05
    HEART_BEAT_TIME_INTERVAL,   //  0x06
    HEART_BEAT_OVERTIME,        //  0x07
    BIND_LOCK_CONTROL,          //  0x08
    UNBIND_LOCK_CONTROL,        //  0x09
};

//Control status
enum AuthorizeStatus{
    Authorize =      0x00,
    Unauthorized //  0x01
};

//Lock status
enum LockStatus{
    Lock =      0x00,
    Unlock  //  0x01
};

//Seal status
enum SealStatus{
    Seal =      0x00,
    Unseal //   0x01
};

// Struct
typedef struct
{
    enum    ProtocolFrameBodyCommandCodeEnum ProtocolFrameBodyCommandCode;
    char     (*ProtocolFrameBodyCommandCodeReadFunctionPoint)(void*);
    char     (*ProtocolFrameBodyCommandCodeWriteFunctionPoint)(void*, unsigned long);
}ProtocolFrameBodyCommandCodeWriteAndReadFunctionStruct;

static ProtocolFrameBodyCommandCodeWriteAndReadFunctionStruct ProtocolFrameBodyCommandCodeWriteAndReadFunctionRegisterArray[PROTOCOL_FRAME_BODY_COMMAND_REGISTER_MAX_NUM];

// Functions
void ProtocolFrameBodyCommandCodeWriteAndReadFunctionRegister(void);

char ProtocolFrameBodyParse(unsigned char* DataBuff, unsigned char DataLength, unsigned char ProtocolFrameHeadType);

char ProtocolFrameBodyParseSettingRequest(unsigned char* DataBuff, unsigned char DataLength);

#endif
