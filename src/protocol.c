/* File: protocol.c */
/* Author: LeonLi */
/* Date: Thu May 13 16:25:05 CST 2021 */

// Include
#include "common.h"
#include "protocol.h"

// Parse protocol
bool ProtocolParse(unsigned char* DataBuff, unsigned char DataLength)
{
#ifdef DEBUG_TEST_FLAG
    HexDump(DataBuff, DataLength);
#endif

}