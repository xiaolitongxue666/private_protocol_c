/* File: common.h */
/* Author: LeonLi */
/* Date: Fri May 14 13:59:56 CST 2021 */
#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include<string.h>

// Macro
#define DEBUG_TEST_FLAG

#define UUID_LENGTH 12

void HexDump(const char* buf, int len);

unsigned short Crc16_CCITT(unsigned char *Data, unsigned long DataSize);

#endif
