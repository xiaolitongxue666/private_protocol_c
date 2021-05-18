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

// Functions

#ifdef DEBUG_TEST_FLAG

extern unsigned char BranchLock_UUID[UUID_LENGTH];

#endif


char  ProtocolDataParse(unsigned char *DataBuff, unsigned char DataLength)
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
    if(memcmp(BranchLock_UUID, &DataBuff[ProcessDataIndex], UUID_LENGTH) != 0)// 0:means equal
    {
        printf("Error: Protocol receive data dst uuid error ! \n\r");
#ifdef DEBUG_TEST_FLAG
        unsigned char i =0;
        for(i=0; i<UUID_LENGTH; i++)
        {
            printf("Debug: UUID[%d] = 0x%X : DataBuff[%d] = 0x%X .\n\r" , i, BranchLock_UUID[i], i, DataBuff[1+i]);
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