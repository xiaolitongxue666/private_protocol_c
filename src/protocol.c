/* File: protocol.c */
/* Author: LeonLi */
/* Date: Thu May 13 16:25:05 CST 2021 */

// Include
#include "common.h"
#include "protocol.h"

// Global variables
#ifdef DEBUG_TEST_FLAG
unsigned char LockControl_UUID[UUID_LENGTH] = {0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01};
#else
unsigned char LockControl_UUID[UUID_LENGTH] = {0};
#endif

#ifdef DEBUG_TEST_FLAG
unsigned char BranchLock_UUID[BRANCH_LOCK_MAX_NUM][UUID_LENGTH] =
                                             {{0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01},
                                              {0x00,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02},
                                              {0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03},
                                              {0x00,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04},
                                              {0x00,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05,0x05},
                                              {0x00,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06},
                                              {0x00,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07},
                                              {0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08}};

unsigned char CommunicateWithBranchLockIndex = 0;

unsigned char BindBranchLockNum = 0;

unsigned char ProtocolFrameLastRequestCommandCode = 0;

#else
unsigned char BranchLock_UUID[BRANCH_LOCK_MAX_NUM][UUID_LENGTH] = {0};
unsigned char CommunicateWithBranchLockIndex = 0;
#endif

// Set 'branch lock' uuid that can control by 'lock control'
void WriteCommunicateWithBranchLockIndex(unsigned char Index)
{
    CommunicateWithBranchLockIndex = Index;
}


// Protocol frame last request command code
void WriteProtocolFrameLastRequestCommandCode(unsigned char CommandCode)
{
    ProtocolFrameLastRequestCommandCode = CommandCode;
}

unsigned char ReadProtocolFrameLastRequestCommandCode(void)
{
    return ProtocolFrameLastRequestCommandCode;
}


// Register protocol command
char  ProtocolBodyCommandRegister(  enum    ProtocolFrameBodyCommandCodeEnum ProtocolFrameBodyCommandCode,
                                    void*   ProtocolFrameBodyCommandCodeReadFunctionPoint,
                                    void*   ProtocolFrameBodyCommandCodeWriteFunctionPoint)
{
    unsigned char i;
    char  Result = 0;

    for(i = 0; i < PROTOCOL_FRAME_BODY_COMMAND_REGISTER_MAX_NUM; ++i)
    {
        if(ProtocolFrameBodyCommandCodeWriteAndReadFunctionRegisterArray[i].ProtocolFrameBodyCommandCode == 0)//not register
        {
            ProtocolFrameBodyCommandCodeWriteAndReadFunctionRegisterArray[i].ProtocolFrameBodyCommandCode                   = ProtocolFrameBodyCommandCode;
            ProtocolFrameBodyCommandCodeWriteAndReadFunctionRegisterArray[i].ProtocolFrameBodyCommandCodeReadFunctionPoint  = ProtocolFrameBodyCommandCodeReadFunctionPoint;
            ProtocolFrameBodyCommandCodeWriteAndReadFunctionRegisterArray[i].ProtocolFrameBodyCommandCodeWriteFunctionPoint = ProtocolFrameBodyCommandCodeWriteFunctionPoint;
            Result = 0;
            break;
        }
    }

    if(i == PROTOCOL_FRAME_BODY_COMMAND_REGISTER_MAX_NUM)
    {
        printf("Protocol body command code 0x%X register error !\n", ProtocolFrameBodyCommandCode);
    }
    return Result;
}

// Command functions
//AUTHORIZE_STATUS
char ProtocolFrameBodyAuthorizeRead(unsigned char* ProtocolFrameBodyDataBuffer)
{
    unsigned char AuthorizeStatus = 0;
    unsigned char ConstructProtocolFrameBodyDataCount = 0;

    //TODO: Read battery status function
    AuthorizeStatus = Authorize;//Test
    printf("%s - (line:%d) Seal status is [%s] .\n\r" , __FILE__, __LINE__, AuthorizeStatus>0?"Unauthorized":"Authorize");

    ProtocolFrameBodyDataBuffer[ConstructProtocolFrameBodyDataCount++] = AUTHORIZE_STATUS;
    ProtocolFrameBodyDataBuffer[ConstructProtocolFrameBodyDataCount++] = 0x01;
    ProtocolFrameBodyDataBuffer[ConstructProtocolFrameBodyDataCount++] = AuthorizeStatus;

    return ConstructProtocolFrameBodyDataCount;
}

char ProtocolFrameBodyAuthorizeWrite(unsigned char *ProtocolFrameBodyDataBuffer, unsigned char ProtocolFrameBodyDataLength)
{
    unsigned char AuthorizeStatus = 0;

    if(ProtocolFrameBodyDataLength > 1)
    {
        printf("Error: AUTHORIZE_STATUS command length %d error, should be %d . \n\r", ProtocolFrameBodyDataLength, 1);
        return -1;
    }

    AuthorizeStatus = *ProtocolFrameBodyDataBuffer;
    printf("Authorize status is [%s] .\n\r" , AuthorizeStatus>0?"Unauthorized":"Authorize");

    //TODO: Write heart beat interval function

    return 0;
}

//LOCK_STATUS
char ProtocolFrameBodyLockRead(unsigned char* ProtocolFrameBodyDataBuffer)
{
    unsigned char LockStatus = 0;
    unsigned char ConstructProtocolFrameBodyDataCount = 0;

    //TODO: Read battery status function
    LockStatus = Lock;//Test
    printf("%s - (line:%d) Seal status is [%s] .\n\r" , __FILE__, __LINE__, LockStatus>0?"Unlock":"Lock");

    ProtocolFrameBodyDataBuffer[ConstructProtocolFrameBodyDataCount++] = LOCK_STATUS;
    ProtocolFrameBodyDataBuffer[ConstructProtocolFrameBodyDataCount++] = 0x01;
    ProtocolFrameBodyDataBuffer[ConstructProtocolFrameBodyDataCount++] = LockStatus;

    return ConstructProtocolFrameBodyDataCount;
}

char ProtocolFrameBodyLockWrite(unsigned char *ProtocolFrameBodyDataBuffer, unsigned char ProtocolFrameBodyDataLength)
{
    unsigned char LockStatus = 0;

    if(ProtocolFrameBodyDataLength > 1)
    {
        printf("Error: LOCK_STATUS command length %d error, should be %d . \n\r", ProtocolFrameBodyDataLength, 1);
        return -1;
    }

    LockStatus = *ProtocolFrameBodyDataBuffer;
    printf("Write lock status is [%s] .\n\r" , LockStatus>0?"Unlock":"Lock");

    //TODO: Write heart beat interval function

    return 0;
}

//SEAL_STATUS
char ProtocolFrameBodySealRead(unsigned char* ProtocolFrameBodyDataBuffer)
{
    unsigned char SealStatus = 0;
    unsigned char ConstructProtocolFrameBodyDataCount = 0;

    //TODO: Read battery status function
    SealStatus = Seal;//Test
    printf("%s - (line:%d) Seal status is [%s] .\n\r" , __FILE__, __LINE__, SealStatus>0?"Unseal":"Seal");

    ProtocolFrameBodyDataBuffer[ConstructProtocolFrameBodyDataCount++] = SEAL_STATUS;
    ProtocolFrameBodyDataBuffer[ConstructProtocolFrameBodyDataCount++] = 0x01;
    ProtocolFrameBodyDataBuffer[ConstructProtocolFrameBodyDataCount++] = SealStatus;

    return ConstructProtocolFrameBodyDataCount;
}

char ProtocolFrameBodySealWrite(unsigned char *ProtocolFrameBodyDataBuffer, unsigned char ProtocolFrameBodyDataLength)
{
    unsigned char SealStatus = 0;

    if(ProtocolFrameBodyDataLength > 1)
    {
        printf("Error: SEAL_STATUS command length %d error, should be %d . \n\r", ProtocolFrameBodyDataLength, 1);
        return -1;
    }

    SealStatus = *ProtocolFrameBodyDataBuffer;
    printf("Write seal status is [%s] .\n\r" , SealStatus>0?"Unseal":"Seal");

    //TODO: Write heart beat interval function

    return 0;
}

//SUB1G_FREQ
char ProtocolFrameBodyCommandDataSub1GFreqRead(unsigned char* ProtocolFrameBodyDataBuffer)
{
    unsigned short Sub1GFreqR = 0;
    unsigned char ConstructProtocolFrameBodyDataCount = 0;

    //TODO: Read battery status function
    Sub1GFreqR = 434;//Test
    printf("%s - (line:%d) Sub1G freq is %d MHz .\n\r" , __FILE__, __LINE__, Sub1GFreqR);

    ProtocolFrameBodyDataBuffer[ConstructProtocolFrameBodyDataCount++] = SUB1G_FREQ;
    ProtocolFrameBodyDataBuffer[ConstructProtocolFrameBodyDataCount++] = 0x02;
    memcpy(&(ProtocolFrameBodyDataBuffer[ConstructProtocolFrameBodyDataCount]), &Sub1GFreqR, 2);
    ConstructProtocolFrameBodyDataCount += 2;

    return ConstructProtocolFrameBodyDataCount;
}

//BATTERY_POWER
char ProtocolFrameBodyCommandDataBatteryPowerRead(unsigned char* ProtocolFrameBodyDataBuffer)
{
    unsigned char BatteryPower = 0;
    unsigned char ConstructProtocolFrameBodyDataCount = 0;

    //TODO: Read battery status function
    BatteryPower = 90;//Test
    printf("%s - (line:%d) Read battery power is %d s .\n\r" , __FILE__, __LINE__, BatteryPower);

    ProtocolFrameBodyDataBuffer[ConstructProtocolFrameBodyDataCount++] = BATTERY_POWER;
    ProtocolFrameBodyDataBuffer[ConstructProtocolFrameBodyDataCount++] = 0x01;
    ProtocolFrameBodyDataBuffer[ConstructProtocolFrameBodyDataCount++] = BatteryPower;

    return ConstructProtocolFrameBodyDataCount;
}

//HEART_BEAT_TIME_INTERVAL
char ProtocolFrameBodyHeartBeatIntervalRead(unsigned char* ProtocolFrameBodyDataBuffer)
{
    unsigned char HeartBeatInterval = 0;
    unsigned char ConstructProtocolFrameBodyDataCount = 0;

    //TODO: Read battery status function
    HeartBeatInterval = 5;//Test
    printf("%s - (line:%d) Heart beat interval is %d s .\n\r" , __FILE__, __LINE__, HeartBeatInterval);

    ProtocolFrameBodyDataBuffer[ConstructProtocolFrameBodyDataCount++] = HEART_BEAT_TIME_INTERVAL;
    ProtocolFrameBodyDataBuffer[ConstructProtocolFrameBodyDataCount++] = 0x01;
    ProtocolFrameBodyDataBuffer[ConstructProtocolFrameBodyDataCount++] = HeartBeatInterval;

    return ConstructProtocolFrameBodyDataCount;
}

char ProtocolFrameBodyHeartBeatIntervalWrite(unsigned char *ProtocolFrameBodyDataBuffer, unsigned char ProtocolFrameBodyDataLength)
{
    unsigned char HeartBeatInterval = 0;

    if(ProtocolFrameBodyDataLength > 1)
    {
        printf("Error: HEART_BEAT_OVERTIME command length %d error, should be %d . \n\r", ProtocolFrameBodyDataLength, 1);
        return -1;
    }

    HeartBeatInterval = *ProtocolFrameBodyDataBuffer;
    printf("Write heart beat interval is %d s .\n\r" , HeartBeatInterval);

    //TODO: Write heart beat interval function

    return 0;
}

//HEART_BEAT_OVERTIME
char ProtocolFrameBodyHeartBeatOverTimeRead(unsigned char* ProtocolFrameBodyDataBuffer)
{
    unsigned char HeartBeatOverTime = 0;
    unsigned char ConstructProtocolFrameBodyDataCount = 0;

    //TODO: Read heart beat over time function
    HeartBeatOverTime = 8;//Test
    printf("%s - (line:%d) Heart beat over time is %d s .\n\r" , __FILE__, __LINE__, HeartBeatOverTime);

    ProtocolFrameBodyDataBuffer[ConstructProtocolFrameBodyDataCount++] = HEART_BEAT_OVERTIME;
    ProtocolFrameBodyDataBuffer[ConstructProtocolFrameBodyDataCount++] = 0x01;
    ProtocolFrameBodyDataBuffer[ConstructProtocolFrameBodyDataCount++] = HeartBeatOverTime;

    return ConstructProtocolFrameBodyDataCount;
}

char ProtocolFrameBodyHeartBeatOverTimeWrite(unsigned char *ProtocolFrameBodyDataBuffer, unsigned char ProtocolFrameBodyDataLength)
{
    unsigned char HeartBeatOverTime = 0;

    if(ProtocolFrameBodyDataLength > 1)
    {
        printf("Error: HEART_BEAT_OVERTIME command length %d error, should be %d . \n\r", ProtocolFrameBodyDataLength, 1);
        return -1;
    }

    HeartBeatOverTime = *ProtocolFrameBodyDataBuffer;

    printf("Write heart beat interval is %d s .\n\r" , HeartBeatOverTime);

    //TODO: Write heart beat overtime function

    return 0;
}

//BIND_LOCK_CONTROL
char ProtocolFrameBodyBindLockWrite(unsigned char *ProtocolFrameBodyDataBuffer, unsigned char ProtocolFrameBodyDataLength)
{
    if(ProtocolFrameBodyDataLength > UUID_LENGTH)
    {
        printf("Error: BIND_LOCK_CONTROL command length %d error, should be %d . \n\r", ProtocolFrameBodyDataLength, UUID_LENGTH);
        return -1;
    }

    memcpy(LockControl_UUID, ProtocolFrameBodyDataBuffer, ProtocolFrameBodyDataLength);

    printf("%s - (line:%d)\n",__FILE__,__LINE__);
    printf(" =====>>> Branch lock bind to lock control's UUID : \n\r");
    HexDump(LockControl_UUID, UUID_LENGTH);

    //TODO: Set branch lock bind uuid to data struct or data base

    return 0;
}

//UNBIND_LOCK_CONTROL
char ProtocolFrameBodyUnBindLockWrite(unsigned char *ProtocolFrameBodyDataBuffer, unsigned char ProtocolFrameBodyDataLength)
{
    if(ProtocolFrameBodyDataLength > UUID_LENGTH)
    {
        printf("Error: UNBIND_LOCK_CONTROL command length %d error, should be %d . \n\r", ProtocolFrameBodyDataLength, UUID_LENGTH);
        return -1;
    }
    memcpy(LockControl_UUID, ProtocolFrameBodyDataBuffer, ProtocolFrameBodyDataLength);

    printf("%s - (line:%d)\n",__FILE__,__LINE__);
    printf(" =====>>> Branch lock unbind to lock control's UUID : \n\r");
    HexDump(LockControl_UUID, UUID_LENGTH);

    //TODO: Set branch lock unbind uuid to data struct or data base

    return 0;
}

// Init protocol module
void ProtocolFrameBodyCommandCodeWriteAndReadFunctionRegister(void)
{
    memset(&ProtocolFrameBodyCommandCodeWriteAndReadFunctionRegisterArray, 0x0, sizeof(ProtocolFrameBodyCommandCodeWriteAndReadFunctionRegisterArray));

    //AUTHORIZE_STATUS
    ProtocolBodyCommandRegister(AUTHORIZE_STATUS, ProtocolFrameBodyAuthorizeRead, ProtocolFrameBodyAuthorizeWrite);

    //LOCK_STATUS
    ProtocolBodyCommandRegister(LOCK_STATUS, ProtocolFrameBodyLockRead, ProtocolFrameBodyLockWrite);

    //SEAL_STATUS
    ProtocolBodyCommandRegister(SEAL_STATUS, ProtocolFrameBodySealRead, ProtocolFrameBodySealWrite);

    //SUB1G_FREQ
    ProtocolBodyCommandRegister(SUB1G_FREQ, ProtocolFrameBodyCommandDataSub1GFreqRead,NULL);

    //BATTERY_POWER
    ProtocolBodyCommandRegister(BATTERY_POWER, ProtocolFrameBodyCommandDataBatteryPowerRead,NULL);

    //HEART_BEAT_TIME_INTERVAL
    ProtocolBodyCommandRegister(HEART_BEAT_TIME_INTERVAL, ProtocolFrameBodyHeartBeatIntervalRead, ProtocolFrameBodyHeartBeatIntervalWrite);

    //HEART_BEAT_OVERTIME
    ProtocolBodyCommandRegister(HEART_BEAT_OVERTIME, ProtocolFrameBodyHeartBeatOverTimeRead, ProtocolFrameBodyHeartBeatOverTimeWrite);

    //BIND_LOCK_CONTROL
    ProtocolBodyCommandRegister(BIND_LOCK_CONTROL, NULL, ProtocolFrameBodyBindLockWrite);

    //UNBIND_LOCK_CONTROL
    ProtocolBodyCommandRegister(UNBIND_LOCK_CONTROL, NULL, ProtocolFrameBodyUnBindLockWrite);

}

// Construct protocol data
char ConstructRequestProtocolFrameData(unsigned char* ProtocolFrameData, unsigned char ProtocolFrameDataLength,unsigned char* ProtocolFrameBodyData, unsigned char ProtocolFrameBodyDataLength, unsigned char ProtocolFrameHeadType)
{
    unsigned char ConstructProtocolFrameDataCount = 0;
    char Result = -1;

    // Protocol frame data length
    if((ProtocolFrameDataLength < 0) || (ProtocolFrameDataLength > PROTOCOL_FRAME_MAX_LENGTH)){
        printf("Error: Construct protocol frame data length %d error ! \n\r", ProtocolFrameDataLength);
        return Result;
    }

    // Header type
    if((ProtocolFrameHeadType < SETTING_REQUEST) || (ProtocolFrameHeadType > STATUS_ACK)){
        printf("Error: Construct protocol frame header type %d error ! \n\r", ProtocolFrameHeadType);
        return Result;
    }
    ProtocolFrameData[ConstructProtocolFrameDataCount++] = ProtocolFrameHeadType;
    // Send to UUID
    //TODO: Use MCU hal lib get the real uuid
    memcpy(ProtocolFrameData + ConstructProtocolFrameDataCount, BranchLock_UUID[CommunicateWithBranchLockIndex], UUID_LENGTH);
    ConstructProtocolFrameDataCount += UUID_LENGTH;

    // ????????
    ProtocolFrameData[ConstructProtocolFrameDataCount++] = 0x00;

    // ????????
    ProtocolFrameData[ConstructProtocolFrameDataCount++] = PROTOCOL_VERSION;

    // ????????
    ProtocolFrameData[ConstructProtocolFrameDataCount++] = ProtocolFrameBodyDataLength;

    // Protocol frame body data
    if((ProtocolFrameBodyDataLength + PROTOCOL_FRAME_HEAD_LENGTH + PROTOCOL_FRAME_TAIL_CRC_LENGTH) >  PROTOCOL_FRAME_MAX_LENGTH)
    {
        printf("Error: Construct protocol frame length %d error ! \n\r", ProtocolFrameBodyDataLength);
        return Result;
    }
    memcpy(ProtocolFrameData + ConstructProtocolFrameDataCount, ProtocolFrameBodyData, ProtocolFrameBodyDataLength);
    ConstructProtocolFrameDataCount += ProtocolFrameBodyDataLength;

    // Construct protocol frame body CRC
    unsigned short CRC = Crc16_CCITT(ProtocolFrameBodyData, ProtocolFrameBodyDataLength);
    ProtocolFrameData[ConstructProtocolFrameDataCount++] = CRC >> 8;
    ProtocolFrameData[ConstructProtocolFrameDataCount++] = CRC & 0x00FF;

    //Debug
    //printf("%s - (line:%d) Construct protocol frame body CRC is 0x%X . \n\r", __FILE__, __LINE__, CRC);
    //printf("%s - (line:%d) Protocol frame body length is %d . \n\r", __FILE__, __LINE__, ProtocolFrameBodyDataLength);

#ifdef DEBUG_TEST_FLAG
    //Test
    printf("%s - (line:%d) ------- 'lock control' send request -------.\n\r" , __FILE__, __LINE__);

    //Debug
    //printf("%s - (line:%d) ------- Construct request protocol frame hex dump -------.\n\r" , __FILE__, __LINE__);
    HexDump(ProtocolFrameData, ConstructProtocolFrameDataCount);

    //Parse construct frame
    //printf("%s - (line:%d) Parse construct frame.\n\r" , __FILE__, __LINE__);
    ProtocolDataParse(ProtocolFrameData, ConstructProtocolFrameDataCount);
#endif

}


char ConstructResponseProtocolFrameData(unsigned char* ProtocolFrameBodyData, unsigned char ProtocolFrameBodyDataLength, unsigned char ProtocolFrameHeadType)
{
    unsigned char ConstructProtocolFrameDataCount = 0;
    unsigned char ProtocolFrameData[PROTOCOL_FRAME_MAX_LENGTH] = { 0 };
    char Result = -1;

    // Header type
    if((ProtocolFrameHeadType < SETTING_REQUEST) || (ProtocolFrameHeadType > STATUS_ACK)){
        printf("Error: Construct protocol frame header type %d error ! \n\r", ProtocolFrameHeadType);
        return Result;
    }
    ProtocolFrameData[ConstructProtocolFrameDataCount++] = ProtocolFrameHeadType;

    // Send to UUID
    //TODO: Use MCU hal lib get the real uuid
    memcpy(ProtocolFrameData + ConstructProtocolFrameDataCount, LockControl_UUID, UUID_LENGTH);
    ConstructProtocolFrameDataCount += UUID_LENGTH;

    // ????????
    ProtocolFrameData[ConstructProtocolFrameDataCount++] = 0x00;

    // ????????
    ProtocolFrameData[ConstructProtocolFrameDataCount++] = PROTOCOL_VERSION;

    // ????????
    ProtocolFrameData[ConstructProtocolFrameDataCount++] = ProtocolFrameBodyDataLength;

    // Protocol frame body data
    if((ProtocolFrameBodyDataLength + PROTOCOL_FRAME_HEAD_LENGTH + PROTOCOL_FRAME_TAIL_CRC_LENGTH) >  PROTOCOL_FRAME_MAX_LENGTH)
    {
        printf("Error: Construct protocol frame length %d error ! \n\r", ProtocolFrameBodyDataLength);
        return Result;
    }
    memcpy(ProtocolFrameData + ConstructProtocolFrameDataCount, ProtocolFrameBodyData, ProtocolFrameBodyDataLength);
    ConstructProtocolFrameDataCount += ProtocolFrameBodyDataLength;

    // Construct protocol frame body CRC
    unsigned short CRC = Crc16_CCITT(ProtocolFrameBodyData, ProtocolFrameBodyDataLength);
    ProtocolFrameData[ConstructProtocolFrameDataCount++] = CRC >> 8;
    ProtocolFrameData[ConstructProtocolFrameDataCount++] = CRC & 0x00FF;

    //printf("%s - (line:%d) Construct protocol frame body CRC is 0x%X . \n\r", __FILE__, __LINE__, CRC);
    //printf("%s - (line:%d) Protocol frame body length is %d . \n\r", __FILE__, __LINE__, ProtocolFrameBodyDataLength);

#ifdef DEBUG_TEST_FLAG
    //Test
    printf("%s - (line:%d) ------- 'branch lock' send ack -------.\n\r" , __FILE__, __LINE__);

    //Debug
    //printf("%s - (line:%d) ------- Construct response protocol frame hex dump -------.\n\r" , __FILE__, __LINE__);
    HexDump(ProtocolFrameData, ConstructProtocolFrameDataCount);

    //Parse construct frame
    //printf("%s - (line:%d) Parse construct frame.\n\r" , __FILE__, __LINE__);
    ProtocolDataParse(ProtocolFrameData, ConstructProtocolFrameDataCount);
#endif

    //TODO: Call real send function for different ways
}


// Protocol frame body parse
char GetProtocolBodyCommandReadWriteFunctionRegisterArrayIndex(enum ProtocolFrameBodyCommandCodeEnum ProtocolFrameBodyCommandCode)
{
    unsigned char Index = 0;
    for(Index = 0; Index < PROTOCOL_FRAME_BODY_COMMAND_REGISTER_MAX_NUM; Index++)
    {
        if(ProtocolFrameBodyCommandCodeWriteAndReadFunctionRegisterArray[Index].ProtocolFrameBodyCommandCode == ProtocolFrameBodyCommandCode){
            break;
        }
    }
    if(Index >= PROTOCOL_FRAME_BODY_COMMAND_REGISTER_MAX_NUM){
        Index = -1;
    }
    return Index;
}

char ProtocolFrameBodyParseSettingRequest(unsigned char* ProtocolFrameBodyData, unsigned char ProtocolFrameBodyLength)
{
    char    Result = -1;
    unsigned char   ConstructProtocolFrameBodyData[PROTOCOL_FRAME_BODY_MAX_LENGTH] = { 0 };
    unsigned char   ConstructProtocolFrameBodyDataCount = 0;

//#ifdef DEBUG_TEST_FLAG
//    printf("%s - (line:%d) ------- Receive setting request protocol frame body hex dump -------.\n\r" , __FILE__, __LINE__);
//    HexDump(ProtocolFrameBodyData, ProtocolFrameBodyLength);
//#endif

    unsigned char i = GetProtocolBodyCommandReadWriteFunctionRegisterArrayIndex(ProtocolFrameBodyData[0]);// Command code
    if((i >= 0) && (ProtocolFrameBodyCommandCodeWriteAndReadFunctionRegisterArray[i].ProtocolFrameBodyCommandCodeWriteFunctionPoint != NULL))
    {
                                                                                                                                 // Command data            // Command data length
        Result = ProtocolFrameBodyCommandCodeWriteAndReadFunctionRegisterArray[i].ProtocolFrameBodyCommandCodeWriteFunctionPoint(&ProtocolFrameBodyData[1], ProtocolFrameBodyLength-1);
    }
    else
    {
        printf("Parse setting request protocol frame body command code (0x%04x) error !\n", ProtocolFrameBodyData[1]);
    }

    ConstructProtocolFrameBodyData[ConstructProtocolFrameBodyDataCount++] = ProtocolFrameBodyData[0];// Command code
    ConstructProtocolFrameBodyData[ConstructProtocolFrameBodyDataCount++] = Result;

#ifdef DEBUG_TEST_FLAG
    //Debug
    //printf("%s - (line:%d) ------- Construct setting ack protocol frame body hex dump -------\n\r" , __FILE__, __LINE__);
    //HexDump(ConstructProtocolFrameBodyData, ConstructProtocolFrameBodyDataCount);
#endif

    Result = ConstructResponseProtocolFrameData(ConstructProtocolFrameBodyData, ConstructProtocolFrameBodyDataCount, SETTING_ACK);

    return Result;
}

char ProtocolFrameBodyParseSettingAck(unsigned char* ProtocolFrameBodyData, unsigned char ProtocolFrameBodyLength)
{
    char    Result = -1;

#ifdef DEBUG_TEST_FLAG
    printf("%s - (line:%d) ------- Receive setting ack protocol frame body hex dump -------.\n\r" , __FILE__, __LINE__);
    HexDump(ProtocolFrameBodyData, ProtocolFrameBodyLength);
#endif

    if(ProtocolFrameBodyLength != PROTOCOL_SETTING_ACK_BODY_LENGTH)
    {
        printf("%s - (line:%d) Receive protocol frame setting ack body length %d error !\n\r" , __FILE__, __LINE__, ProtocolFrameBodyLength);
        return Result;
    }

    //Debug
    //printf("%s - (line:%d) Receive protocol frame setting ack body command code %d .\n\r" , __FILE__, __LINE__, *ProtocolFrameBodyData);
    //printf("%s - (line:%d) Receive protocol frame setting ack body setting result [%s] .\n\r" , __FILE__, __LINE__, (*(ProtocolFrameBodyData + 1))>0?"Setting ack error":"Setting ack right");

    if(*ProtocolFrameBodyData == ReadProtocolFrameLastRequestCommandCode())
    {
        Result = *(ProtocolFrameBodyData + 1);
    }
    return Result;
}

char ProtocolFrameBodyParseStatusRequest(unsigned char* ProtocolFrameBodyData, unsigned char ProtocolFrameBodyLength)
{
    char    Result = -1;
    unsigned char   ConstructProtocolFrameBodyData[PROTOCOL_FRAME_BODY_MAX_LENGTH] = { 0 };

//#ifdef DEBUG_TEST_FLAG
//    printf("%s - (line:%d)\n",__FILE__,__LINE__);
//    printf("  ------- Receive status request protocol frame body hex dump -------  \n\r");
//    HexDump(ProtocolFrameBodyData, ProtocolFrameBodyLength);
//#endif

    if((ProtocolFrameBodyLength < 1) || (ProtocolFrameBodyLength > PROTOCOL_FRAME_BODY_MAX_LENGTH)){
        printf("Parse getting request data length %d error !\n\r", ProtocolFrameBodyLength);
        return Result;
    }

    unsigned char i = GetProtocolBodyCommandReadWriteFunctionRegisterArrayIndex(ProtocolFrameBodyData[0]);;
    if((i >= 0) && (ProtocolFrameBodyCommandCodeWriteAndReadFunctionRegisterArray[i].ProtocolFrameBodyCommandCodeReadFunctionPoint != NULL)){
        Result = ProtocolFrameBodyCommandCodeWriteAndReadFunctionRegisterArray[i].ProtocolFrameBodyCommandCodeReadFunctionPoint(ConstructProtocolFrameBodyData);
    }
    else{
        printf("Parse status request command code (0x%04x) error !\n", ProtocolFrameBodyData[0]);
        return Result;
    }

//#ifdef DEBUG_TEST_FLAG
//    printf("%s - (line:%d)\n",__FILE__,__LINE__);
//    printf("  ------- Status ack protocol frame body hex dump -------  \n\r");
//    HexDump(ConstructProtocolFrameBodyData, Result);
//#endif

    Result = ConstructResponseProtocolFrameData(ConstructProtocolFrameBodyData, Result, STATUS_ACK);

    return Result;
}

char ProtocolFrameBodyParseStatusAck(unsigned char* ProtocolFrameBodyData, unsigned char ProtocolFrameBodyLength)
{
    char    Result = -1;

#ifdef DEBUG_TEST_FLAG
    printf("%s - (line:%d) ------- Receive status ack protocol frame body hex dump -------.\n\r" , __FILE__, __LINE__);
    HexDump(ProtocolFrameBodyData, ProtocolFrameBodyLength);
#endif

    if(ProtocolFrameBodyLength > PROTOCOL_STATUS_ACK_BODY_LENGTH)
    {
        printf("%s - (line:%d) Receive protocol frame status ack body length %d error !\n\r" , __FILE__, __LINE__, ProtocolFrameBodyLength);
        return Result;
    }

    //Debug
    printf("%s - (line:%d) Receive protocol frame setting ack body command code %d .\n\r" , __FILE__, __LINE__, *ProtocolFrameBodyData);
    printf("%s - (line:%d) Receive protocol frame setting ack body command data length %d .\n\r" , __FILE__, __LINE__, *(ProtocolFrameBodyData + 1));

    if(*ProtocolFrameBodyData != ReadProtocolFrameLastRequestCommandCode())
    {
        printf("%s - (line:%d) Receive protocol frame status ack body command code %d error !\n\r" , __FILE__, __LINE__, *ProtocolFrameBodyData);
        return Result;
    }
    else
    {
        unsigned char   TempChar = 0;
        unsigned short  TempShort = 0;
        unsigned char   TempArray[UUID_LENGTH] = {0};

        switch(*ProtocolFrameBodyData) {
            case AUTHORIZE_STATUS:
                TempChar = *(ProtocolFrameBodyData + 2);
                printf("%s - (line:%d) Receive protocol frame setting ack body command code AUTHORIZE_STATUS is %d .\n\r" , __FILE__, __LINE__, TempChar);
                break;
            case LOCK_STATUS:
                TempChar = *(ProtocolFrameBodyData + 2);
                printf("%s - (line:%d) Receive protocol frame setting ack body command code LOCK_STATUS is %d .\n\r" , __FILE__, __LINE__, TempChar);
                break;
            case SEAL_STATUS:
                TempChar = *(ProtocolFrameBodyData + 2);
                printf("%s - (line:%d) Receive protocol frame setting ack body command code SEAL_STATUS is %d .\n\r" , __FILE__, __LINE__, TempChar);
                break;
            case SUB1G_FREQ:
                //TempChar = *(ProtocolFrameBodyData + 2);
                memcpy(&TempShort, (ProtocolFrameBodyData + 2), 2);
                printf("%s - (line:%d) Receive protocol frame setting ack body command code SUB1G_FREQ is %d .\n\r" , __FILE__, __LINE__, TempShort);
                break;
            case BATTERY_POWER:
                TempChar = *(ProtocolFrameBodyData + 2);
                printf("%s - (line:%d) Receive protocol frame setting ack body command code BATTERY_POWER is %d .\n\r" , __FILE__, __LINE__, TempChar);
                break;
            case HEART_BEAT_TIME_INTERVAL:
                TempChar = *(ProtocolFrameBodyData + 2);
                printf("%s - (line:%d) Receive protocol frame setting ack body command code HEART_BEAT_TIME_INTERVAL is %d .\n\r" , __FILE__, __LINE__, TempChar);
                break;
            case HEART_BEAT_OVERTIME:
                TempChar = *(ProtocolFrameBodyData + 2);
                printf("%s - (line:%d) Receive protocol frame setting ack body command code HEART_BEAT_OVERTIME is %d .\n\r" , __FILE__, __LINE__, TempChar);
                break;
        }
    }
    return Result;
}

// Parse protocol
char ProtocolFrameBodyParse(unsigned char* ProtocolFrameBodyData, unsigned char ProtocolFrameBodyLength, unsigned char ProtocolFrameHeadType)
{
    char Result = -1;

    switch(ProtocolFrameHeadType)
    {
        case SETTING_REQUEST:
            printf("%s - (line:%d) Parse setting request .\n\r" , __FILE__, __LINE__);
            Result = ProtocolFrameBodyParseSettingRequest(ProtocolFrameBodyData, ProtocolFrameBodyLength);
            break;
        case SETTING_ACK:
            printf("%s - (line:%d) Parse setting ack .\n\r" , __FILE__, __LINE__);
            Result = ProtocolFrameBodyParseSettingAck(ProtocolFrameBodyData, ProtocolFrameBodyLength);
            break;
        case STATUS_REQUEST:
            printf("%s - (line:%d) Parse status request .\n\r" , __FILE__, __LINE__);
            Result = ProtocolFrameBodyParseStatusRequest(ProtocolFrameBodyData, ProtocolFrameBodyLength);
            Result = 0;
            break;
        case STATUS_ACK:
            printf("%s - (line:%d) Parse status ack .\n\r" , __FILE__, __LINE__);
            ProtocolFrameBodyParseStatusAck(ProtocolFrameBodyData, ProtocolFrameBodyLength);
            break;
        default:
            printf("%s - (line:%d) Error: Receive error head type 0x%X .\n\r" , __FILE__, __LINE__,ProtocolFrameHeadType);
            Result = -1;
            break;
    }
    return Result;
}
