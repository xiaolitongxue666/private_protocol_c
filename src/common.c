/* File: common.c */
/* Author: LeonLi */
/* Date: Fri May 14 13:59:54 CST 2021 */

#include "common.h"

void HexDump(const char* buf, int len)
{
    if (len < 1 || buf == NULL) return;

    const char *hexChars = "0123456789ABCDEF";
    int i = 0;
    char c = 0x00;
    char str_print_able[17];
    char str_hex_buffer[16 * 3 + 1];

    for (i = 0; i < (len / 16) * 16; i += 16)
    {
        int j = 0;
        for (j = 0; j < 16; j++)
        {
            c = buf[i + j];

            // hex
            int z = j * 3;
            str_hex_buffer[z++] = hexChars[(c >> 4) & 0x0F];
            str_hex_buffer[z++] = hexChars[c & 0x0F];
            str_hex_buffer[z++] = (j < 10 && !((j + 1) % 8)) ? '_' : ' ';

            // string with space repalced
            if (c < 32 || c == '\0' || c == '\t' || c == '\r' || c == '\n' || c == '\b')
                str_print_able[j] = '.';
            else
                str_print_able[j] = c;
        }
        str_hex_buffer[16 * 3] = 0x00;
        str_print_able[j] = 0x00;

        printf("%04x  %s %s\n", i, str_hex_buffer, str_print_able);
    }

    // 处理剩下的不够16字节长度的部分
    int leftSize = len % 16;
    if (leftSize < 1) return;
    int j = 0;
    int pos = i;
    for (; i < len; i++)
    {
        c = buf[i];

        // hex
        int z = j * 3;
        str_hex_buffer[z++] = hexChars[(c >> 4) & 0x0F];
        str_hex_buffer[z++] = hexChars[c & 0x0F];
        str_hex_buffer[z++] = ' ';

        // string with space repalced
        if (c < 32 || c == '\0' || c == '\t' || c == '\r' || c == '\n' || c == '\b')
            str_print_able[j] = '.';
        else
            str_print_able[j] = c;
        j++;
    }
    str_hex_buffer[leftSize * 3] = 0x00;
    str_print_able[j] = 0x00;

    for (j = leftSize; j < 16; j++)
    {
        int z = j * 3;
        str_hex_buffer[z++] = ' ';
        str_hex_buffer[z++] = ' ';
        str_hex_buffer[z++] = ' ';
    }
    str_hex_buffer[16 * 3] = 0x00;
    printf("%04x  %s %s\n", pos, str_hex_buffer, str_print_able);
}

unsigned short Crc16_CCITT(unsigned char *Data, unsigned long DataSize)
{
    unsigned short CRC16;
    unsigned short i, j, temp_u16_data;

    CRC16 = 0xffff;
    for (i = 0; i < DataSize; i++)
    {
        CRC16 = *Data^CRC16;
        for (j = 0; j < 8; j++)
        {
            temp_u16_data = CRC16 & 0x0001;
            CRC16 = CRC16 >> 1;
            if (temp_u16_data)
                CRC16 = CRC16 ^ 0xa001;//PS:多项式A001是8005按位颠倒后的结果
        }
        *Data++;
    }

    return(CRC16);
}