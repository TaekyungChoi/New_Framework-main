#ifndef _HAL_UART_H_
#define _HAL_UART_H_

#define FUNC_UART_CH00_START     R_UART0_Start
#define FUNC_UART_CH00_STOP      R_UART0_Stop
#define FUNC_UART_CH01_START     R_UART1_Start
#define FUNC_UART_CH01_STOP      R_UART1_Stop
#define FUNC_UART_CH02_START     R_UART2_Start
#define FUNC_UART_CH02_STOP      R_UART2_Stop
#define FUNC_UART_CH03_START     R_UART3_Start
#define FUNC_UART_CH03_STOP      R_UART3_Stop

#define FUNC_UART_SEND_USER_0                   R_UART0_Send
#define FUNC_UART_RECEIVE_USER_0                R_UART0_Receive

#define FUNC_UART_SEND_USER_1                   R_UART1_Send
#define FUNC_UART_RECEIVE_USER_1                R_UART1_Receive

#define FUNC_UART_SEND_USER_2                   R_UART2_Send
#define FUNC_UART_RECEIVE_USER_2                R_UART2_Receive

#define FUNC_UART_SEND_USER_3                   R_UART3_Send
#define FUNC_UART_RECEIVE_USER_3                R_UART3_Receive


#define UART_RX_BUFFER_MAX      500
//#define UART_NUM        4


#define USE_UART0_RX_RINGBUFFER
//#define USE_UART0_RX_FIXATION

#define USE_UART1_RX_RINGBUFFER
//#define USE_UART1_RX_FIXATION

#define USE_UART2_RX_RINGBUFFER
//#define USE_UART2_RX_FIXATION

//#define USE_UART3_RX_RINGBUFFER
#define USE_UART3_RX_FIXATION


typedef enum
{
    NUM_UART0,
    NUM_UART1,
    NUM_UART2,
    NUM_UART3,
    NUM_UART_MAX
}NUM_UART_T;

typedef struct _UartFlag_
{
    U8 TxBusy_F;
    U8 RxComplete_F;
    U8 RxErr_F;
}Uart_Flag_T;

typedef struct _UartRx_
{
    U8 DataBuffer[UART_RX_BUFFER_MAX];
    U16 TargetAddrIdx;
    U16 ParsingAddrIdx;
    U8 OverFlow_F;
}UartRx_Ringbuffer_T;


void HAL_UART_CH_START(fp_void fp);
void HAL_UART_CH_STOP(fp_void fp);
void HAL_UART_InitVariable(void);

MD_STATUS HAL_UART_Send(U8* const TxBuffer, U16 Cnt, fp_Param_pU8_U16 fp, NUM_UART_T UartNum);
MD_STATUS HAL_UART_Receive(U8* const RxBuffer, U16 Cnt, fp_Param_pU8_U16 fp);
U8 HAL_UART_GetTxBusyF(NUM_UART_T UartNum);
U8 HAL_UART_GetRxCompleteF(NUM_UART_T UartNum);
U8 HAL_UART_GetRxErrF(NUM_UART_T UartNum);

// Rx RingBuffer Structure
U8 HAL_UART_CheckAnyRxData(NUM_UART_T UartNum, U16 ByteCount);
U8 HAL_UART_GetRxTargetAddrOverFlowF(NUM_UART_T UartNum);
U16 HAL_UART_ReadRxTargetAddrIdx(NUM_UART_T UartNum);
U16 HAL_UART_ReadRxParsingAddrIdx(NUM_UART_T UartNum);
U8 HAL_UART_ReadCurrentRxData(NUM_UART_T UartNum);
U8 HAL_UART_ReadParsingRxData(NUM_UART_T UartNum);
void HAL_UART_IncreaseRxParsingAddrIdx(NUM_UART_T UartNum);
void HAL_UART_ClearRxParsingAddrIdx(NUM_UART_T UartNum);


#endif