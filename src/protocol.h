/* File: protocol.h */
/* Author: LeonLi */
/* Date: Thu May 13 16:25:08 CST 2021 */
#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

// Include
#include <stdbool.h>

// Macro
#define PROTOCOL_VERSION 0x10

#define PROTOCOL_BODY_COMMAND_REGISTER_MAX_NUM   30

#define PROTOCOL_BODY_LENGTH 47

#define PROTOCOL_HEADER_TYPE_LENGTH 1

#define PROTOCOL_DATA_MAX_SIZE  64

#define PROTOCOL_DATA_MIN_SIZE  19

#define FRAME_HEADER_LENGTH 16

#define PARA_CODE_LENGTH 1

#define CRC_DATA_LENGTH 2

//#define MASTER_DEVICE 0x00
//#define SLAVE_DEVICE  0x01

// Global variables
//unsigned char software_version          = 0;
//unsigned char heart_beat_time_interval  = 5;    //seconds
//unsigned char heart_beat_overtime       = 15;   //seconds
//unsigned int DeviceRole = SLAVE_DEVICE;

// Header type
enum HeaderType{
    SETTING_REQUEST = 0x88,
    SETTING_ACK,
    STATUS_REQUEST,
    STATUS_ACK
};

// Command code
enum CommandCode{
    CONTROL_STATUS = 0x01,
    LOCK_STATUS,
    SEAL_STATUS,
    SUB1G_FREQ,
    BATTERY_POWER,
    HEART_BEAT_TIME_INTERVAL,
    HEART_BEAT_OVERTIME,
    BIND_LOCK_CONTROL,
    UNBIND_LOCK_CONTROL,
};

//Lock status
enum LockStatus{
    LOCK = 0x00,
    UNLOCK
};

//Seal status
enum SealStatus{
    Seal = 0x00,
    Unseal
};


// Struct
typedef struct
{
    enum    CommandCode FrameBody_CommandCode;                              //protocol command code
    char     (*FrameBody_CommandCodeReadFunction)(void*);                    //read function point
    char     (*FrameBody_CommandCodeWriteFunction)(void*, unsigned long);    //write function point
}ProtocolBodyCommandReadWriteFunctionPointStruct;

static ProtocolBodyCommandReadWriteFunctionPointStruct ProtocolBodyCommandReadWriteFunctionRegisterArray[PROTOCOL_BODY_COMMAND_REGISTER_MAX_NUM];

// Functions
void ProtocolBodyCommandReadWriteFunctionRegister(void);

char  ProtocolBodyParse(unsigned char* DataBuff, unsigned char DataLength, unsigned char HeaderType);

char  SubProtocolBodyParseSettingRequest(unsigned char* DataBuff, unsigned char DataLength);

#endif
