/* File: protocol_communicate.h */
/* Author: LeonLi */
/* Date: Fri May 14 09:32:01 CST 2021 */
#ifndef _PROTOCOL_COMMUNICATE_H_
#define _PROTOCOL_COMMUNICATE_H_

// Include
#include <stdbool.h>

// Functions
char  ProtocolDataParse(unsigned char *DataBuff, unsigned char DataLength);

//AUTHORIZE_STATUS
char SendReadAuthorizeStatusProtocolFrame(void);
char SendWriteAuthorizeStatusProtocolFrame(unsigned AuthorizeStatus);

//LOCK_STATUS
char SendReadLockStatusProtocolFrame(void);
char SendWriteLockStatusProtocolFrame(unsigned LockStatus);

//SEAL_STATUS
char SendReadSealStatusProtocolFrame(void);
char SendWriteSealStatusProtocolFrame(unsigned SealStatus);

//SUB1G_FREQ
char SendReadSub1GFreqProtocolFrame(void);

//BATTERY_POWER
char SendReadBatteryPowerProtocolFrame(void);

//HEART_BEAT_TIME_INTERVAL
char SendReadHeartBeatTimeIntervalProtocolFrame(void);
char SendWriteHeartBeatTimeIntervalProtocolFrame(unsigned HeartBeatTimeInterval);

//HEART_BEAT_OVERTIME
char SendReadHeartBeatOverTimeProtocolFrame(void);
char SendWriteHeartBeatOverTimeProtocolFrame(unsigned HeartBeatOverTime);

//BIND_LOCK_CONTROL
char SendWriteBindProtocolFrame(unsigned char *Bind_UUID);

//UNBIND_LOCK_CONTROL
char SendWriteUnBindProtocolFrame(unsigned char *UnBind_UUID);

#endif
