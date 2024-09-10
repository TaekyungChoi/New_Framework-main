#ifndef _HAL_GPIO_H_
#define _HAL_GPIO_H_


#define IO_OUTPUT   0
#define IO_INPUT    1


#define _PORT0 0
#define _PORT1 1
#define _PORT2 2
#define _PORT3 3
#define _PORT4 4
#define _PORT5 5
#define _PORT6 6
#define _PORT7 7
#define _PORT8 8
#define _PORT9 9
#define _PORT10 10
#define _PORT11 11
#define _PORT12 12
#define _PORT13 13
#define _PORT14 14
#define _PORT15 15

#define PIN_0 0x01
#define PIN_1 0x02
#define PIN_2 0x04
#define PIN_3 0x08
#define PIN_4 0x10
#define PIN_5 0x20
#define PIN_6 0x40
#define PIN_7 0x80


void HAL_PORT_Latch_SET(U8 u8PortNum, U8 u8Value, U8 P_HighLow);
void HAL_PORT_InOutMode_SET(U8 u8PortNum, U8 u8Value, U8 InOut);
void HAL_PORT_PullUpMode_SET(U8 u8PortNum, U8 u8Value, U8 P_Set);
void HAL_PORT_NChOpenDrainMode_SET(U8 u8PortNum, U8 u8Value, U8 P_Set);
void HAL_PORT_TTLInputMode_SET(U8 u8PortNum, U8 u8Value, U8 P_Set);

#endif