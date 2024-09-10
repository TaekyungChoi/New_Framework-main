#include "HW.h"
#include "Hal_UART.h"

Uart_Flag_T Uart_F[NUM_UART_MAX];
UartRx_Ringbuffer_T UartRx[NUM_UART_MAX];



void HAL_UART_CH_START(fp_void fp)
{
    fp();
}

void HAL_UART_CH_STOP(fp_void fp)
{
    fp();
}

void HAL_UART_InitVariable(void)
{
    memset(&Uart_F[0], 0, sizeof(Uart_Flag_T) * NUM_UART_MAX);
    memset(&UartRx[0], 0, sizeof(UartRx_Ringbuffer_T) * NUM_UART_MAX);
}


//--------------------------------------//
//---- Tx Packet Fixation Structure ----//
//--------------------------------------//

MD_STATUS HAL_UART_Send(U8* const TxBuffer, U16 Cnt, fp_Param_pU8_U16 fp, NUM_UART_T UartNum)
{
    MD_STATUS Status = MD_OK;

    Uart_F[UartNum].TxBusy_F = SET;
    Status = fp(TxBuffer, Cnt);

    return Status;    
}

U8 HAL_UART_GetTxBusyF(NUM_UART_T UartNum)
{
    return Uart_F[UartNum].TxBusy_F;
}


//--------------------------------------//


//--------------------------------------//
//---- Rx Packet Fixation Structure ----//
//--------------------------------------//

MD_STATUS HAL_UART_Receive(U8* const RxBuffer, U16 Cnt, fp_Param_pU8_U16 fp)
{
    MD_STATUS Status = MD_OK;

    Status = fp(RxBuffer, Cnt);

    return Status;    
}

U8 HAL_UART_GetRxCompleteF(NUM_UART_T UartNum)
{
    return Uart_F[UartNum].RxComplete_F;
}

U8 HAL_UART_GetRxErrF(NUM_UART_T UartNum)
{
    return Uart_F[UartNum].RxErr_F;
}


//--------------------------------------//


// Uart_Flag_T *HAL_UART_GetTxStructAddr(void)
// {
//     return Uart_F;
// }


// UartRx_Ringbuffer_T *HAL_UART_GetRxStructAddr(void)
// {
//     return UartRx;
// }



//---------------------------------//
//---- Rx RingBuffer Structure ----//
//---------------------------------//

U8 HAL_UART_CheckAnyRxData(NUM_UART_T UartNum, U16 ByteCount)
{
    U16 CntBuf;

    if ( UartRx[UartNum].ParsingAddrIdx > UartRx[UartNum].TargetAddrIdx )
    {
        CntBuf = (UartRx[UartNum].TargetAddrIdx + (U16)UART_RX_BUFFER_MAX) - UartRx[UartNum].ParsingAddrIdx;
    }
    else
    {
    	CntBuf = UartRx[UartNum].TargetAddrIdx - UartRx[UartNum].ParsingAddrIdx;
    }

    if ( CntBuf < ByteCount )
    {
		return(0);
    }	
    
    return(1);
}



U8 HAL_UART_GetRxTargetAddrOverFlowF(NUM_UART_T UartNum)
{
    return UartRx[UartNum].OverFlow_F;
}

U16 HAL_UART_ReadRxTargetAddrIdx(NUM_UART_T UartNum)
{
    return UartRx[UartNum].TargetAddrIdx;
}

U16 HAL_UART_ReadRxParsingAddrIdx(NUM_UART_T UartNum)
{
    return UartRx[UartNum].ParsingAddrIdx;
}


U8 HAL_UART_ReadCurrentRxData(NUM_UART_T UartNum)
{
    U8 Data = 0;
    U16 Idx = 0;

    Idx = UartRx[UartNum].TargetAddrIdx;
    Data = UartRx[UartNum].DataBuffer[Idx];

    return Data;
}

U8 HAL_UART_ReadParsingRxData(NUM_UART_T UartNum)
{
    U8 Data = 0;
    U16 Idx = 0;

    Idx = UartRx[UartNum].ParsingAddrIdx;
    Data = UartRx[UartNum].DataBuffer[Idx];

    return Data;
}

void HAL_UART_IncreaseRxParsingAddrIdx(NUM_UART_T UartNum)
{
    UartRx[UartNum].ParsingAddrIdx++;
}

void HAL_UART_ClearRxParsingAddrIdx(NUM_UART_T UartNum)
{
    UartRx[UartNum].ParsingAddrIdx = CLEAR;
}

void HAL_UART_ClearRxBuffer(NUM_UART_T UartNum)
{
    memset(UartRx[UartNum].DataBuffer, 0, sizeof(UartRx[UartNum].DataBuffer));
    UartRx[UartNum].ParsingAddrIdx = CLEAR;
    UartRx[UartNum].TargetAddrIdx = CLEAR;
}

//---------------------------------//

