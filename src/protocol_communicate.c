/* File: protocol_communicate.c */
/* Author: LeonLi */
/* Date: Fri May 14 09:31:59 CST 2021 */

// Include
#include<stdio.h>
#include<string.h>
#include "common.h"
#include "protocol.h"
#include "protocol_communicate.h"

// Macro
#define PROTOCOL_DATA_BUFFER_LENGTH 128


// Global variables
#ifdef DEBUG_TEST_FLAG

extern unsigned char BranchLock_UUID[BRANCH_LOCK_MAX_NUM][UUID_LENGTH];
extern unsigned char CommunicateWithBranchLockIndex;
extern unsigned char BindBranchLockNum;

#endif

// Functions
//Roles
//enum Roles{
//    LockControl =      0x00,
//    BranchLock      //  0x01
//};
void ProtocolModuleInit(enum ProtocolRoles Roles)
{
    //Init protocol module register command
    ProtocolFrameBodyCommandCodeWriteAndReadFunctionRegister();

#ifdef DEBUG_TEST_FLAG

    //LockControl test
    if(Roles == LockControl)
    {

        //Set to communicate with 'branch lock' index 0
        //WriteCommunicateWithBranchLockIndex(1);

        //AUTHORIZE_STATUS
        //SendWriteAuthorizeStatusProtocolFrame(AUTHORIZE_STATUS);
        //SendReadAuthorizeStatusProtocolFrame();

        //LOCK_STATUS
        //SendWriteLockStatusProtocolFrame(Lock);
        //SendReadLockStatusProtocolFrame();

        //SEAL_STATUS
        //SendWriteSealStatusProtocolFrame(Seal);
        //SendReadSealStatusProtocolFrame();

        //SUB1G_FREQ
        //SendReadSub1GFreqProtocolFrame();

        //BATTERY_POWER
        //SendReadBatteryPowerProtocolFrame();

        //HEART_BEAT_TIME_INTERVAL
        //SendWriteHeartBeatTimeIntervalProtocolFrame(5);
        //SendReadHeartBeatTimeIntervalProtocolFrame();

        //HEART_BEAT_OVERTIME
        //SendWriteHeartBeatOverTimeProtocolFrame(8);
        //SendReadHeartBeatOverTimeProtocolFrame();

        //BIND_LOCK_CONTROL
        //unsigned char Bind_UUID[UUID_LENGTH] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b};
        //SendWriteBindProtocolFrame(Bind_UUID);

        //UNBIND_LOCK_CONTROL
        //unsigned char UnBind_UUID[UUID_LENGTH] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b};
        //SendWriteUnBindProtocolFrame(UnBind_UUID);
    }
#endif

}


//AUTHORIZE_STATUS
char SendReadAuthorizeStatusProtocolFrame(void)
{
    unsigned char ProtocolFrameData[PROTOCOL_FRAME_MAX_LENGTH] = { 0 };
    char Result = -1;
    unsigned char ProtocolFrameBodyData = AUTHORIZE_STATUS;

    WriteProtocolFrameLastRequestCommandCode(AUTHORIZE_STATUS);

    Result = ConstructRequestProtocolFrameData(ProtocolFrameData,
                                               PROTOCOL_FRAME_MAX_LENGTH,
                                               &ProtocolFrameBodyData,
                                               1,
                                               STATUS_REQUEST);
    return Result;
}

char SendWriteAuthorizeStatusProtocolFrame(unsigned AuthorizeStatus)
{
    unsigned char ProtocolFrameData[PROTOCOL_FRAME_MAX_LENGTH] = { 0 };
    char Result = -1;
    unsigned char ProtocolFrameBodyData[2] = { 0 };
    ProtocolFrameBodyData[0] = AUTHORIZE_STATUS;
    ProtocolFrameBodyData[1] = AuthorizeStatus;

    WriteProtocolFrameLastRequestCommandCode(AUTHORIZE_STATUS);

    Result = ConstructRequestProtocolFrameData(ProtocolFrameData,
                                               PROTOCOL_FRAME_MAX_LENGTH,
                                               (unsigned char*)&ProtocolFrameBodyData,
                                               2,
                                               SETTING_REQUEST);
    return Result;
}

//LOCK_STATUS
char SendReadLockStatusProtocolFrame(void)
{
    unsigned char ProtocolFrameData[PROTOCOL_FRAME_MAX_LENGTH] = { 0 };
    char Result = -1;
    unsigned char ProtocolFrameBodyData = LOCK_STATUS;

    WriteProtocolFrameLastRequestCommandCode(LOCK_STATUS);

    Result = ConstructRequestProtocolFrameData(ProtocolFrameData,
                                               PROTOCOL_FRAME_MAX_LENGTH,
                                               &ProtocolFrameBodyData,
                                               1,
                                               STATUS_REQUEST);
    return Result;
}

char SendWriteLockStatusProtocolFrame(unsigned LockStatus)
{
    unsigned char ProtocolFrameData[PROTOCOL_FRAME_MAX_LENGTH] = { 0 };
    char Result = -1;
    unsigned char ProtocolFrameBodyData[2] = { 0 };
    ProtocolFrameBodyData[0] = LOCK_STATUS;
    ProtocolFrameBodyData[1] = LockStatus;

    WriteProtocolFrameLastRequestCommandCode(LOCK_STATUS);

    Result = ConstructRequestProtocolFrameData(ProtocolFrameData,
                                               PROTOCOL_FRAME_MAX_LENGTH,
                                               (unsigned char*)&ProtocolFrameBodyData,
                                               2,
                                               SETTING_REQUEST);
    return Result;
}

//SEAL_STATUS
char SendReadSealStatusProtocolFrame(void)
{
    unsigned char ProtocolFrameData[PROTOCOL_FRAME_MAX_LENGTH] = { 0 };
    char Result = -1;
    unsigned char ProtocolFrameBodyData = SEAL_STATUS;

    WriteProtocolFrameLastRequestCommandCode(SEAL_STATUS);

    Result = ConstructRequestProtocolFrameData(ProtocolFrameData,
                                               PROTOCOL_FRAME_MAX_LENGTH,
                                               &ProtocolFrameBodyData,
                                               1,
                                               STATUS_REQUEST);
    return Result;
}

char SendWriteSealStatusProtocolFrame(unsigned SealStatus)
{
    unsigned char ProtocolFrameData[PROTOCOL_FRAME_MAX_LENGTH] = { 0 };
    char Result = -1;
    unsigned char ProtocolFrameBodyData[2] = { 0 };
    ProtocolFrameBodyData[0] = SEAL_STATUS;
    ProtocolFrameBodyData[1] = SealStatus;

    WriteProtocolFrameLastRequestCommandCode(SEAL_STATUS);

    Result = ConstructRequestProtocolFrameData(ProtocolFrameData,
                                               PROTOCOL_FRAME_MAX_LENGTH,
                                               (unsigned char*)&ProtocolFrameBodyData,
                                               2,
                                               SETTING_REQUEST);
    return Result;
}

//SUB1G_FREQ
char SendReadSub1GFreqProtocolFrame(void)
{
    unsigned char ProtocolFrameData[PROTOCOL_FRAME_MAX_LENGTH] = { 0 };
    char Result = -1;
    unsigned char ProtocolFrameBodyData = SUB1G_FREQ;

    WriteProtocolFrameLastRequestCommandCode(SUB1G_FREQ);

    Result = ConstructRequestProtocolFrameData(ProtocolFrameData,
                                               PROTOCOL_FRAME_MAX_LENGTH,
                                               &ProtocolFrameBodyData,
                                               1,
                                               STATUS_REQUEST);
    return Result;
}

//BATTERY_POWER
char SendReadBatteryPowerProtocolFrame(void)
{
    unsigned char ProtocolFrameData[PROTOCOL_FRAME_MAX_LENGTH] = { 0 };
    char Result = -1;
    unsigned char ProtocolFrameBodyData = BATTERY_POWER;

    WriteProtocolFrameLastRequestCommandCode(BATTERY_POWER);

    Result = ConstructRequestProtocolFrameData(ProtocolFrameData,
                                               PROTOCOL_FRAME_MAX_LENGTH,
                                               &ProtocolFrameBodyData,
                                               1,
                                               STATUS_REQUEST);
    return Result;
}


//HEART_BEAT_TIME_INTERVAL
char SendReadHeartBeatTimeIntervalProtocolFrame(void)
{
    unsigned char ProtocolFrameData[PROTOCOL_FRAME_MAX_LENGTH] = { 0 };
    char Result = -1;
    unsigned char ProtocolFrameBodyData = HEART_BEAT_TIME_INTERVAL;

    WriteProtocolFrameLastRequestCommandCode(HEART_BEAT_TIME_INTERVAL);

    Result = ConstructRequestProtocolFrameData(ProtocolFrameData,
                                               PROTOCOL_FRAME_MAX_LENGTH,
                                               &ProtocolFrameBodyData,
                                               1,
                                               STATUS_REQUEST);
    return Result;
}

char SendWriteHeartBeatTimeIntervalProtocolFrame(unsigned HeartBeatTimeInterval)
{
    unsigned char ProtocolFrameData[PROTOCOL_FRAME_MAX_LENGTH] = { 0 };
    char Result = -1;
    unsigned char ProtocolFrameBodyData[2] = { 0 };
    ProtocolFrameBodyData[0] = HEART_BEAT_TIME_INTERVAL;
    ProtocolFrameBodyData[1] = HeartBeatTimeInterval;

    WriteProtocolFrameLastRequestCommandCode(HEART_BEAT_TIME_INTERVAL);

    Result = ConstructRequestProtocolFrameData(ProtocolFrameData,
                                               PROTOCOL_FRAME_MAX_LENGTH,
                                               (unsigned char*)&ProtocolFrameBodyData,
                                               2,
                                               SETTING_REQUEST);
    return Result;
}

//HEART_BEAT_OVERTIME
char SendReadHeartBeatOverTimeProtocolFrame(void)
{
    unsigned char ProtocolFrameData[PROTOCOL_FRAME_MAX_LENGTH] = { 0 };
    char Result = -1;
    unsigned char ProtocolFrameBodyData = HEART_BEAT_OVERTIME;

    WriteProtocolFrameLastRequestCommandCode(HEART_BEAT_OVERTIME);

    Result = ConstructRequestProtocolFrameData(ProtocolFrameData,
                                               PROTOCOL_FRAME_MAX_LENGTH,
                                               &ProtocolFrameBodyData,
                                               1,
                                               STATUS_REQUEST);
    return Result;
}

char SendWriteHeartBeatOverTimeProtocolFrame(unsigned HeartBeatOverTime)
{
    unsigned char ProtocolFrameData[PROTOCOL_FRAME_MAX_LENGTH] = { 0 };
    char Result = -1;
    unsigned char ProtocolFrameBodyData[2] = { 0 };
    ProtocolFrameBodyData[0] = HEART_BEAT_OVERTIME;
    ProtocolFrameBodyData[1] = HeartBeatOverTime;

    WriteProtocolFrameLastRequestCommandCode(HEART_BEAT_OVERTIME);

    Result = ConstructRequestProtocolFrameData(ProtocolFrameData,
                                               PROTOCOL_FRAME_MAX_LENGTH,
                                               (unsigned char*)&ProtocolFrameBodyData,
                                               2,
                                               SETTING_REQUEST);
    return Result;
}

//BIND_LOCK_CONTROL
char SendWriteBindProtocolFrame(unsigned char *Bind_UUID)
{
    unsigned char ProtocolFrameData[PROTOCOL_FRAME_MAX_LENGTH] = { 0 };
    char Result = -1;
    unsigned char ProtocolFrameBodyData[UUID_LENGTH + 1] = { 0 };
    ProtocolFrameBodyData[0] = BIND_LOCK_CONTROL;
    memcpy(&(ProtocolFrameBodyData[1]) , Bind_UUID, UUID_LENGTH);

    Result = ConstructRequestProtocolFrameData(ProtocolFrameData,
                                               PROTOCOL_FRAME_MAX_LENGTH,
                                               (unsigned char*)&ProtocolFrameBodyData,
                                               UUID_LENGTH + 1,
                                               SETTING_REQUEST);
    return Result;
}

//UNBIND_LOCK_CONTROL
char SendWriteUnBindProtocolFrame(unsigned char *UnBind_UUID)
{
    unsigned char ProtocolFrameData[PROTOCOL_FRAME_MAX_LENGTH] = { 0 };
    char Result = -1;
    unsigned char ProtocolFrameBodyData[UUID_LENGTH + 1] = { 0 };
    ProtocolFrameBodyData[0] = UNBIND_LOCK_CONTROL;
    memcpy(&(ProtocolFrameBodyData[1]) , UnBind_UUID, UUID_LENGTH);

    Result = ConstructRequestProtocolFrameData(ProtocolFrameData,
                                               PROTOCOL_FRAME_MAX_LENGTH,
                                               (unsigned char*)&ProtocolFrameBodyData,
                                               UUID_LENGTH + 1,
                                               SETTING_REQUEST);
    return Result;
}

char ProtocolDataParse(unsigned char *DataBuff, unsigned char DataLength)
{
    unsigned char EncryptedFlag     = 0;
    unsigned char ProtocolVersion   = 0;
    unsigned char FrameBody_Length  = 0;

    unsigned char   ProcessDataIndex    = 0;
    unsigned short  CalculateCrcValue   = 0;
    unsigned short  ReceiveCrcValue     = 0;

    // Check receive data length
    if((DataLength < PROTOCOL_FRAME_MIN_LENGTH) || (DataLength > PROTOCOL_FRAME_MAX_LENGTH))
    {
        printf("Error: Parse protocol frame data length %d error ! \n\r", DataLength);
        return -1;
    }

    /* ======================================================================================== */

    // Check header type
    if((DataBuff[ProcessDataIndex] < SETTING_REQUEST) || (DataBuff[ProcessDataIndex] > STATUS_ACK))
    {
        printf("Error: Protocol receive data header type %d error ! \n\r", DataBuff[ProcessDataIndex]);
        return -1;
    }
    ProcessDataIndex++;

    /* ======================================================================================== */

    // Check header dest device uuid
    /* Call UUID get function */
    /* Because self uuid can't change, so can save it as a global variable in this file*/
//#ifdef DEBUG_TEST_FLAG
//    //UUID 96 bits
//    unsigned char UUID[UUID_LENGTH] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b};
//#endif
    /* End */
    if(memcmp(BranchLock_UUID[CommunicateWithBranchLockIndex], &DataBuff[ProcessDataIndex], UUID_LENGTH) != 0)// 0:means equal
    {
        printf("Error: Protocol receive data dst uuid error ! \n\r");
#ifdef DEBUG_TEST_FLAG
        unsigned char i =0;
        for(i=0; i<UUID_LENGTH; i++)
        {
            printf("Debug: UUID[%d] = 0x%X : DataBuff[%d] = 0x%X .\n\r" , i, BranchLock_UUID[CommunicateWithBranchLockIndex][i], i, DataBuff[1+i]);
        }
#endif
        return -1;
    }
    ProcessDataIndex += UUID_LENGTH;

    /* ======================================================================================== */

    // Get protocol parameters
    EncryptedFlag       = DataBuff[ProcessDataIndex++];
    ProtocolVersion     = DataBuff[ProcessDataIndex++];
    FrameBody_Length    = DataBuff[ProcessDataIndex++];

    /* ======================================================================================== */

    // Calculate CRC
    CalculateCrcValue = Crc16_CCITT(&DataBuff[ProcessDataIndex], DataLength - PROTOCOL_FRAME_TAIL_CRC_LENGTH - PROTOCOL_FRAME_HEAD_LENGTH);
    ProcessDataIndex += FrameBody_Length;

    ReceiveCrcValue = DataBuff[ProcessDataIndex];
    ReceiveCrcValue = ReceiveCrcValue << 8;
    ReceiveCrcValue = ReceiveCrcValue | DataBuff[ProcessDataIndex+1];

    if(CalculateCrcValue != ReceiveCrcValue)
    {
        printf("Error: Protocol receive data calculate CRC error ! \n\r");
#ifdef DEBUG_TEST_FLAG
        printf("Debug: Calculate Crc = 0x%X : Receive CRC = 0x%X .\n\r" , CalculateCrcValue, ReceiveCrcValue);
#endif
        return -1;
    }

    // Call frame body parse function
    return ProtocolFrameBodyParse(&DataBuff[PROTOCOL_FRAME_HEAD_LENGTH], FrameBody_Length, DataBuff[0]);
}