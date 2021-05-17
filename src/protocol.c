/* File: protocol.c */
/* Author: LeonLi */
/* Date: Thu May 13 16:25:05 CST 2021 */

// Include
#include "common.h"
#include "protocol.h"

// Register protocol command
char  ProtocolBodyCommandRegister(   enum    CommandCode ParaCode,
                                    void*   ParaReadFunction,
                                    void*   ParaWriteFunction)
{
    unsigned char i;
    char  Result = 0;

    for(i = 0; i < PROTOCOL_BODY_COMMAND_REGISTER_MAX_NUM; ++i)
    {
        if(ProtocolBodyCommandReadWriteFunctionRegisterArray[i].FrameBody_CommandCode == 0)//not register
        {
            ProtocolBodyCommandReadWriteFunctionRegisterArray[i].FrameBody_CommandCode              = ParaCode;
            ProtocolBodyCommandReadWriteFunctionRegisterArray[i].FrameBody_CommandCodeReadFunction  = ParaReadFunction;
            ProtocolBodyCommandReadWriteFunctionRegisterArray[i].FrameBody_CommandCodeWriteFunction = ParaWriteFunction;
            Result = 1;
            break;
        }
    }

    if(i == PROTOCOL_BODY_COMMAND_REGISTER_MAX_NUM)
    {
        printf("Para register failed at(0x%04x)\n", ParaCode);
    }
    return Result;
}

// Command functions
//HEART_BEAT_TIME_INTERVAL
char  ProtocolBodyHeartBeatIntervalControl(unsigned char *DataBuffer, unsigned char DataLength)
{
    unsigned char HeartBeatInterval = 0;

    if(DataLength > 1)
    {
        printf("Error: HEART_BEAT_TIME_INTERVAL command length %d error, should be %d . \n\r", DataLength, 1);
        return -1;
    }

    HeartBeatInterval = *DataBuffer;

#ifdef DEBUG_TEST_FLAG
    printf("Setting branch lock heart beat interval is %d s .\n\r" , HeartBeatInterval);
#endif

    //TODO: Set branch lock heart beat interval to data struct or data base

    return 0;
}

//HEART_BEAT_OVERTIME
char  ProtocolBodyHeartBeatOverTimeControl(unsigned char *DataBuffer, unsigned char DataLength)
{
    unsigned char HeartBeatOverTime = 0;

    if(DataLength > 1)
    {
        printf("Error: HEART_BEAT_OVERTIME command length %d error, should be %d . \n\r", DataLength, 1);
        return -1;
    }

    HeartBeatOverTime = *DataBuffer;

#ifdef DEBUG_TEST_FLAG
    printf("Setting branch lock heart beat over time is %d s .\n\r" , HeartBeatOverTime);
#endif

    //TODO: Set branch lock heart beat over time to data struct or data base

    return 0;
}

//BIND_LOCK_CONTROL
char  ProtocolBodyBindLockControl(unsigned char *DataBuffer, unsigned char DataLength)
{
    unsigned char LockControl_UUID[UUID_LENGTH] = {0};

    if(DataLength > UUID_LENGTH)
    {
        printf("Error: BIND_LOCK_CONTROL command length %d error, should be %d . \n\r", DataLength, UUID_LENGTH);
        return -1;
    }

    memcpy(LockControl_UUID, DataBuffer, DataLength);

#ifdef DEBUG_TEST_FLAG
    printf("%s - (line:%d)\n",__FILE__,__LINE__);
    HexDump(LockControl_UUID, UUID_LENGTH);
#endif

    //TODO: Set branch lock bind uuid to data struct or data base

    return 0;
}

//UNBIND_LOCK_CONTROL
char  ProtocolBodyUnBindLockControl(unsigned char *DataBuffer, unsigned char DataLength)
{
    unsigned char LockControl_UUID[UUID_LENGTH] = {0};

    if(DataLength > UUID_LENGTH)
    {
        printf("Error: UNBIND_LOCK_CONTROL command length %d error, should be %d . \n\r", DataLength, UUID_LENGTH);
        return -1;
    }

    memcpy(LockControl_UUID, DataBuffer, DataLength);

#ifdef DEBUG_TEST_FLAG
    printf("%s - (line:%d)\n",__FILE__,__LINE__);
    HexDump(LockControl_UUID, UUID_LENGTH);
#endif

    //TODO: Set branch lock unbind uuid to data struct or data base

    return 0;
}

// Init protocol module
void ProtocolBodyCommandReadWriteFunctionRegister(void)
{
    memset(&ProtocolBodyCommandReadWriteFunctionRegisterArray, 0x0, sizeof(ProtocolBodyCommandReadWriteFunctionRegisterArray));

    //HEART_BEAT_TIME_INTERVAL
    ProtocolBodyCommandRegister(HEART_BEAT_TIME_INTERVAL, NULL, ProtocolBodyHeartBeatIntervalControl);

    //HEART_BEAT_OVERTIME
    ProtocolBodyCommandRegister(HEART_BEAT_OVERTIME, NULL, ProtocolBodyHeartBeatOverTimeControl);

    //BIND_LOCK_CONTROL
    ProtocolBodyCommandRegister(BIND_LOCK_CONTROL, NULL, ProtocolBodyBindLockControl);

    //UNBIND_LOCK_CONTROL
    ProtocolBodyCommandRegister(UNBIND_LOCK_CONTROL, NULL, ProtocolBodyUnBindLockControl);


}

// Construct response
char ConstructSendData(unsigned char* DataBuff, unsigned char DataLength, unsigned char HeaderType, unsigned char ParaCode)
{
    unsigned char ConstructDataIndex = 0;
    unsigned char ResponseDataBuffer[PROTOCOL_DATA_MAX_SIZE] = { 0 };
    char result = -1;

#ifdef DEBUG_TEST_FLAG
    //UUID 96 bits
    unsigned char UUID[UUID_LENGTH] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c};
#endif

    // Header type
    if((HeaderType < SETTING_REQUEST) || (HeaderType > STATUS_ACK)){
        printf("Error: Construct send data header type %d error ! \n\r", HeaderType);
        return result;
    }
    ResponseDataBuffer[ConstructDataIndex++] = HeaderType;

    // Send to UUID
    //TODO: Use MCU hal lib get the real uuid
    memcpy(ResponseDataBuffer + ConstructDataIndex, UUID, UUID_LENGTH);
    ConstructDataIndex += UUID_LENGTH;

    // 加密标识
    ResponseDataBuffer[ConstructDataIndex++] = 0x00;

    // 协议版本
    ResponseDataBuffer[ConstructDataIndex++] = PROTOCOL_VERSION;

    // 帧体长度
    ResponseDataBuffer[ConstructDataIndex++] = DataLength;

    // Send body data
    if( (DataLength + PROTOCOL_HEADER_TYPE_LENGTH + UUID_LENGTH + CRC_DATA_LENGTH) >  PROTOCOL_DATA_MAX_SIZE)
    {
        printf("Error: Construct send data length %d error ! \n\r", DataLength);
        return result;
    }
    memcpy(ResponseDataBuffer + ConstructDataIndex, DataBuff, DataLength);
    ConstructDataIndex += DataLength;

    // CRC
    unsigned short CRC = Crc16_CCITT(DataBuff, DataLength);
#if 0
    memcpy(ResponseDataBuffer + ConstructDataIndex, (unsigned char*)(&CRC), CRC_DATA_LENGTH);
    ConstructDataIndex += CRC_DATA_LENGTH;
#else
    ResponseDataBuffer[ConstructDataIndex++] = CRC >> 8;
    ResponseDataBuffer[ConstructDataIndex++] = CRC & 0x00FF;
#endif

    printf("Construct send data CRC is 0x%X . \n\r", CRC);
    printf("Construct data index is %d . \n\r", ConstructDataIndex);

#ifdef DEBUG_TEST_FLAG
    printf("%s - (line:%d)\n",__FILE__,__LINE__);
    HexDump(ResponseDataBuffer, ConstructDataIndex);
#endif

    //TODO: Call real send function for different ways
}


// Sub parse protocol
char GetProtocolBodyCommandReadWriteFunctionRegisterArrayIndex(enum CommandCode ParaCode)
{
    unsigned char i = 0;
    for(i = 0; i < PROTOCOL_BODY_COMMAND_REGISTER_MAX_NUM; i++)
    {
        if(ProtocolBodyCommandReadWriteFunctionRegisterArray[i].FrameBody_CommandCode == ParaCode){
            break;
        }
    }
    if(i >= PROTOCOL_BODY_COMMAND_REGISTER_MAX_NUM){
        i = -1;
    }
    return i;
}

char SubProtocolBodyParseSettingRequest(unsigned char* DataBuff, unsigned char DataLength)
{
    char    Result = -1;
    unsigned char   BodyDataBuffer[PROTOCOL_BODY_LENGTH] = { 0 };
    unsigned char   ConstructBodyDataIndex = 0;

//#ifdef DEBUG_TEST_FLAG
//    printf("%s - (line:%d)\n",__FILE__,__LINE__);
//    HexDump(DataBuff, DataLength);
//#endif

    unsigned char i = GetProtocolBodyCommandReadWriteFunctionRegisterArrayIndex(DataBuff[0]);;
    if((i >= 0) && (ProtocolBodyCommandReadWriteFunctionRegisterArray[i].FrameBody_CommandCodeWriteFunction != NULL))
    {
        Result = ProtocolBodyCommandReadWriteFunctionRegisterArray[i].FrameBody_CommandCodeWriteFunction(&DataBuff[1], DataLength-1);
    }
    else
    {
        printf("Parse setting request command code (0x%04x) error !\n", DataBuff[1]);
    }

    BodyDataBuffer[ConstructBodyDataIndex++] = DataBuff[0];
    BodyDataBuffer[ConstructBodyDataIndex++] = Result;

//#ifdef DEBUG_TEST_FLAG
//    printf("%s - (line:%d)\n",__FILE__,__LINE__);
//    HexDump(BodyDataBuffer, ConstructBodyDataIndex);
//#endif

    Result = ConstructSendData(BodyDataBuffer, ConstructBodyDataIndex, SETTING_REQUEST, DataBuff[1]);

    return Result;
}

// Parse protocol
char ProtocolBodyParse(unsigned char* DataBuff, unsigned char DataLength, unsigned char HeaderType)
{
    char result = -1;

//#ifdef DEBUG_TEST_FLAG
//    printf("%s - (line:%d)\n",__FILE__,__LINE__);
//    HexDump(DataBuff, DataLength);
//#endif

    switch(HeaderType)
    {
        case SETTING_REQUEST:
            printf("Receive setting request command .\n\r");
            result = SubProtocolBodyParseSettingRequest(DataBuff, DataLength);
            break;
        case SETTING_ACK:
            printf("Receive setting ack command .\n\r");
            result =  0;
            break;
        case STATUS_REQUEST:
            printf("Receive status request command .\n\r");
            result = 0;
            break;
        case STATUS_ACK:
            printf("Receive status ack command .\n\r");
            result = 0;
            break;
        default:
            printf("Error: Receive error command 0x%X .\n\r" , HeaderType);
            result = -1;
            break;
    }
    return result;
}
