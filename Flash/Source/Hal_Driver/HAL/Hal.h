#ifndef _HAL_MAIN_H_
#define _HAL_MAIN_H_


#define DELAY_1us     1L
#define DELAY_10us    10L
#define DELAY_100us   100L
#define DELAY_1ms     1000L
#define DELAY_10ms    10000L
#define DELAY_100ms   100000L
#define DELAY_1s      1000000L
#define DELAY_10s     10000000L



void HAL_WDT_Resume(void);
void HAL_Delay(U32 us_time);

U8 HexToAscii_Nibble(U8 Data);
U8 HexToAscii_Byte(U8 HighLow, U8 Value);
U8 AsciiToHex_2Byte(U8 Upper, U8 Lower);
U8 AsciiToHex_Byte(U8 AsciiData);
U8 CalDataChecksum(U8 *ptr, U16 Len);







#endif