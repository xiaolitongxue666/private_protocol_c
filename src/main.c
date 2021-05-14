/* File: main.c */
/* Author: LeonLi */
/* Date: Fri May 14 14:24:22 CST 2021 */

// Include
#include "common.h"
#include "protocol_communicate.h"

static const unsigned char TestDataBindCommand[31] =
{
    0x88,   //��������֡ͷ���� 0x88 // 1
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,    //���ն�Ψһ��ʶ UUID // 12
    0x00,   //���ܱ�ʶ ������ // 1
    0x10,   //Э��汾 1.0 // 1
    0x0d,   //֡�峤�� // 1
    0x09,   //֡�幦����  0x09 ������ // 1 //CRC ���㷶Χ
    0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,    //���ص�Ƭ��UUID // 12 //CRC ���㷶Χ
    0x74,0x48   // CRC16 // 2
};

void main(void)
{
    ProtocolDataParse(TestDataBindCommand, 31);
}