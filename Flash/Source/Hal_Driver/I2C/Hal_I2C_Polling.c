#include "HW.h"
#include "Hal.h"
#include "Hal_I2C.h"
#include "Hal_I2C_Polling.h"

static void HAL_I2C_START(void);
static void HAL_I2C_STOP(void);
static void HAL_I2C_BitOut(U8 Data);
static U8 HAL_I2C_BitIn(void);
static void HAL_I2C_SendAck(void);
static void HAL_I2C_SendNack(void);
static U8 HAL_I2C_TXD(U8 ByteData);
static U8 HAL_I2C_RXD(void);

// HW Polling I2C
// I2C Speed : 5us -> 200KHz (I2C Max : 400KHz)

U8 HAL_I2C_ByteWrite_Command(U8 CommandCode, U32 TwrDelay)
{
    U8 AckFail_F = 1;
    U8 RetryCnt = 0;
    
    while(AckFail_F)
    {
        if(RetryCnt >= 2)
        {
            RetryCnt = 0;
            PM_I2C = PM_I2C & PM_I2C_SDA_OUTPUT;
            P_I2C_SCL = CLEAR;
            P_I2C_SDA = SET;            
            break;
        }

        HAL_I2C_START();
        AckFail_F = HAL_I2C_TXD(DEVICE_ID | WRITE_COMMAND);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        AckFail_F = HAL_I2C_TXD(CommandCode);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        HAL_I2C_STOP();
    }

    HAL_Delay(TwrDelay);

    return AckFail_F;
}

U8 HAL_I2C_ByteWrite_16bitAddrToData(U16 Addr, U8 Data, U32 TwrDelay)
{
    U8 AddressUpper = 0;
    U8 AddressLower = 0;
    U8 AckFail_F = 1;
    U8 RetryCnt = 0;

    AddressLower = (U8)Addr;
    AddressUpper = (U8)(Addr >> 8);

    while(AckFail_F)
    {
        if(RetryCnt >= 2)
        {
            RetryCnt = 0;
            PM_I2C = PM_I2C & PM_I2C_SDA_OUTPUT;
            P_I2C_SCL = CLEAR;
            P_I2C_SDA = SET;            
            break;
        }

        HAL_I2C_START();
        AckFail_F = HAL_I2C_TXD(DEVICE_ID | WRITE_COMMAND);
        
        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        AckFail_F = HAL_I2C_TXD(AddressUpper);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        AckFail_F = HAL_I2C_TXD(AddressLower);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        AckFail_F = HAL_I2C_TXD(Data);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        HAL_I2C_STOP();
    }

    HAL_Delay(TwrDelay);
    return AckFail_F;
}


U8 HAL_I2C_ByteWrite_8bitAddrToData(U8 Addr, U8 Data, U32 TwrDelay)
{
    U8 AckFail_F = 1;
    U8 RetryCnt = 0;

    while(AckFail_F)
    {
        if(RetryCnt >= 2)
        {
            RetryCnt = 0;
            PM_I2C = PM_I2C & PM_I2C_SDA_OUTPUT;
            P_I2C_SCL = CLEAR;
            P_I2C_SDA = SET;            
            break;
        }

        HAL_I2C_START();
        AckFail_F = HAL_I2C_TXD(DEVICE_ID | WRITE_COMMAND);
        
        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        AckFail_F = HAL_I2C_TXD(Addr);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        AckFail_F = HAL_I2C_TXD(Data);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        HAL_I2C_STOP();
    }

    HAL_Delay(TwrDelay);
    return AckFail_F;
}


U8 HAL_I2C_ByteRead_16bitAddrToData(U16 Addr, U8 *rData, U32 TwrDelay)
{
    U8 AddressUpper = 0;
    U8 AddressLower = 0;
    U8 AckFail_F = 1;
    U8 RetryCnt = 0;
    U8 i = 0;

    AddressLower = (U8)Addr;
    AddressUpper = (U8)(Addr >> 8);

    while(AckFail_F)
    {
        if(RetryCnt >= 2)
        {
            RetryCnt = 0;
            PM_I2C = PM_I2C & PM_I2C_SDA_OUTPUT;
            P_I2C_SCL = CLEAR;
            P_I2C_SDA = SET;            
            break;
        }

        HAL_I2C_START();
        AckFail_F = HAL_I2C_TXD(DEVICE_ID | WRITE_COMMAND);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        AckFail_F = HAL_I2C_TXD(AddressUpper);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        AckFail_F = HAL_I2C_TXD(AddressLower);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        HAL_I2C_START();
        AckFail_F = HAL_I2C_TXD(DEVICE_ID | READ_COMMAND);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        *rData = HAL_I2C_RXD();
        HAL_I2C_SendNack();
        HAL_I2C_STOP();
    }

    HAL_Delay(TwrDelay);
    return AckFail_F;
}


U8 HAL_I2C_ByteRead_8bitAddrToData(U8 Addr, U8 *rData, U32 TwrDelay)
{
    U8 AckFail_F = 1;
    U8 RetryCnt = 0;
    U8 i = 0;

    while(AckFail_F)
    {
        if(RetryCnt >= 2)
        {
            RetryCnt = 0;
            PM_I2C = PM_I2C & PM_I2C_SDA_OUTPUT;
            P_I2C_SCL = CLEAR;
            P_I2C_SDA = SET;            
            break;
        }

        HAL_I2C_START();
        AckFail_F = HAL_I2C_TXD(DEVICE_ID | WRITE_COMMAND);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        AckFail_F = HAL_I2C_TXD(Addr);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        HAL_I2C_START();
        AckFail_F = HAL_I2C_TXD(DEVICE_ID | READ_COMMAND);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        *rData = HAL_I2C_RXD();
        HAL_I2C_SendNack();
        HAL_I2C_STOP();
    }

    HAL_Delay(TwrDelay);
    return AckFail_F;
}


U8 HAL_I2C_PageWrite_16bitAddrToData(U16 Addr, U8 const *TxBuf, U16 TxLength, U32 TwrDelay)
{
    U8 AddressUpper = 0;
    U8 AddressLower = 0;
    U8 AckFail_F = 1;
    U8 RetryCnt = 0;
    U8 i = 0;
    U8 j = 0;

    AddressLower = (U8)Addr;
    AddressUpper = (U8)(Addr >> 8);

    while(AckFail_F)
    {
        if(RetryCnt >= 2)
        {
            RetryCnt = 0;
            PM_I2C = PM_I2C & PM_I2C_SDA_OUTPUT;
            P_I2C_SCL = CLEAR;
            P_I2C_SDA = SET;            
            break;
        }

        HAL_I2C_START();
        AckFail_F = HAL_I2C_TXD(DEVICE_ID | WRITE_COMMAND);
        
        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        AckFail_F = HAL_I2C_TXD(AddressUpper);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        AckFail_F = HAL_I2C_TXD(AddressLower);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        for(j = 0; j < TxLength; j++)
        {
            AckFail_F = HAL_I2C_TXD(TxBuf[j]);
        }

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        HAL_I2C_STOP();
    }

    HAL_Delay(TwrDelay);
    return AckFail_F;
}


U8 HAL_I2C_PageWrite_8bitAddrToData(U8 Addr, U8 const *TxBuf, U16 TxLength, U32 TwrDelay)
{
    U8 AckFail_F = 1;
    U8 RetryCnt = 0;
    U8 i = 0;
    U8 j = 0;

    while(AckFail_F)
    {
        if(RetryCnt >= 2)
        {
            RetryCnt = 0;
            PM_I2C = PM_I2C & PM_I2C_SDA_OUTPUT;
            P_I2C_SCL = CLEAR;
            P_I2C_SDA = SET;            
            break;
        }

        HAL_I2C_START();
        AckFail_F = HAL_I2C_TXD(DEVICE_ID | WRITE_COMMAND);
        
        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        AckFail_F = HAL_I2C_TXD(Addr);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        for(j = 0; j < TxLength; j++)
        {
            AckFail_F = HAL_I2C_TXD(TxBuf[j]);
        }

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        HAL_I2C_STOP();
    }

    HAL_Delay(TwrDelay);
    return AckFail_F;
}


U8 HAL_I2C_PageRead_16bitAddrToData(U16 Addr, U8 *RxBuf, U16 RxLength, U32 TwrDelay)
{
    U8 AddressUpper = 0;
    U8 AddressLower = 0;
    U8 AckFail_F = 1;
    U8 RetryCnt = 0;
    U8 i = 0;
    U8 j = 0;

    AddressLower = (U8)Addr;
    AddressUpper = (U8)(Addr >> 8);

    while(AckFail_F)
    {
        if(RetryCnt >= 2)
        {
            RetryCnt = 0;
            PM_I2C = PM_I2C & PM_I2C_SDA_OUTPUT;
            P_I2C_SCL = CLEAR;
            P_I2C_SDA = SET;            
            break;
        }

        HAL_I2C_START();
        AckFail_F = HAL_I2C_TXD(DEVICE_ID | WRITE_COMMAND);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        AckFail_F = HAL_I2C_TXD(AddressUpper);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        AckFail_F = HAL_I2C_TXD(AddressLower);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        HAL_I2C_START();
        AckFail_F = HAL_I2C_TXD(DEVICE_ID | READ_COMMAND);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        for(j=0; j<RxLength; j++)
        {
            RxBuf[j] = HAL_I2C_RXD();

            if(j < RxLength - 1)
            {
                HAL_I2C_SendAck();
            }
            else
            {
                HAL_I2C_SendNack();
            }
        }
        
        HAL_I2C_STOP();
    }

    HAL_Delay(TwrDelay);
    return AckFail_F;
}


U8 HAL_I2C_PageRead_8bitAddrToData(U8 Addr, U8 *RxBuf, U16 RxLength, U32 TwrDelay)
{
    U8 AckFail_F = 1;
    U8 RetryCnt = 0;
    U8 i = 0;
    U8 j = 0;

    while(AckFail_F)
    {
        if(RetryCnt >= 2)
        {
            RetryCnt = 0;
            PM_I2C = PM_I2C & PM_I2C_SDA_OUTPUT;
            P_I2C_SCL = CLEAR;
            P_I2C_SDA = SET;            
            break;
        }

        HAL_I2C_START();
        AckFail_F = HAL_I2C_TXD(DEVICE_ID | WRITE_COMMAND);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        AckFail_F = HAL_I2C_TXD(Addr);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        HAL_I2C_START();
        AckFail_F = HAL_I2C_TXD(DEVICE_ID | READ_COMMAND);

        if(AckFail_F == SET)
        {
            RetryCnt++;
            continue;
        }

        for(j=0; j<RxLength; j++)
        {
            RxBuf[j] = HAL_I2C_RXD();

            if(j < RxLength - 1)
            {
                HAL_I2C_SendAck();
            }
            else
            {
                HAL_I2C_SendNack();
            }
        }
        
        HAL_I2C_STOP();
    }

    HAL_Delay(TwrDelay);
    return AckFail_F;
}


static void HAL_I2C_START(void)
{
    PM_I2C = PM_I2C & PM_I2C_SDA_OUTPUT;  // Port Output Set
    HAL_Delay(DELAY_1us * 5);
    P_I2C_SDA = SET;
    HAL_Delay(DELAY_1us * 5);
    P_I2C_SCL = CLEAR;
    HAL_Delay(DELAY_1us * 5);    
    P_I2C_SCL = SET;
    HAL_Delay(DELAY_1us * 5);
    P_I2C_SDA = CLEAR;
    HAL_Delay(DELAY_1us * 5);
    P_I2C_SCL = CLEAR;
    HAL_Delay(DELAY_1us * 5);
}

static void HAL_I2C_STOP(void)
{
    PM_I2C = PM_I2C & PM_I2C_SDA_OUTPUT;  // Port Output Set
    HAL_Delay(DELAY_1us * 5);
    P_I2C_SDA = CLEAR;
    HAL_Delay(DELAY_1us * 5);
    P_I2C_SCL = CLEAR;
    HAL_Delay(DELAY_1us * 5);
    P_I2C_SCL = SET;
    HAL_Delay(DELAY_1us * 5);
    P_I2C_SDA = SET;
    HAL_Delay(DELAY_1us * 5);
    P_I2C_SCL = CLEAR;
    HAL_Delay(DELAY_1us * 5);
}


static void HAL_I2C_BitOut(U8 Data)
{
    PM_I2C = PM_I2C & PM_I2C_SDA_OUTPUT;
    HAL_Delay(DELAY_1us * 5);
    P_I2C_SCL = CLEAR;
    HAL_Delay(DELAY_1us * 5);
    Data = Data & 0x80;  //First Bit 0 or 1

    if(Data == 0x80)
    {
        P_I2C_SDA = SET;
    }
    else
    {
        P_I2C_SDA = CLEAR;
    }

    HAL_Delay(DELAY_1us * 5);
    P_I2C_SCL = SET;
    HAL_Delay(DELAY_1us * 5);
    P_I2C_SCL = CLEAR;
    HAL_Delay(DELAY_1us * 5);
}

static U8 HAL_I2C_BitIn(void)
{
    U8 Data = 0;
    
    PM_I2C = PM_I2C | PM_I2C_SDA_INPUT;
    HAL_Delay(DELAY_1us * 5);
    P_I2C_SCL = CLEAR;
    HAL_Delay(DELAY_1us * 5);
    P_I2C_SCL = SET;
    HAL_Delay(DELAY_1us * 5);

    if(P_I2C_SDA == SET)
    {
        Data = Data | 0x01;
    }
    else
    {
        Data = Data | 0x00;
    }

    P_I2C_SCL = CLEAR;
    HAL_Delay(DELAY_1us * 5);

    return Data;
}

static void HAL_I2C_SendAck(void)
{
    PM_I2C = PM_I2C & PM_I2C_SDA_OUTPUT;
    HAL_Delay(DELAY_1us * 5);
    P_I2C_SDA = CLEAR;
    HAL_Delay(DELAY_1us * 5);
    P_I2C_SCL = SET;
    HAL_Delay(DELAY_1us * 5);
    P_I2C_SCL = CLEAR;
    HAL_Delay(DELAY_1us * 5);
}

static void HAL_I2C_SendNack(void)
{
    PM_I2C = PM_I2C & PM_I2C_SDA_OUTPUT;
    HAL_Delay(DELAY_1us * 5);
    P_I2C_SDA = SET;
    HAL_Delay(DELAY_1us * 5);
    P_I2C_SCL = SET;
    HAL_Delay(DELAY_1us * 5);
    P_I2C_SCL = CLEAR;
    HAL_Delay(DELAY_1us * 5);
}

static U8 HAL_I2C_TXD(U8 ByteData)
{
    U8 i = 0;
    U8 AckBit_F = 0;

    HAL_WDT_Resume();

    for(i=0; i<8; i++)
    {
        HAL_I2C_BitOut(ByteData);
        ByteData = ByteData << 1;
    }

    AckBit_F = HAL_I2C_BitIn();
    return AckBit_F;
}

static U8 HAL_I2C_RXD(void)
{
    U8 i = 0;
    U8 ReadByte = 0;
    U8 Data = 0;

    HAL_WDT_Resume();

    for(i=0; i<8; i++)
    {
        ReadByte = HAL_I2C_BitIn();
        Data = Data | ReadByte;
        Data = Data << 1;
    }

    //HAL_I2C_SendNack();

    return Data;
}



// void HAL_I2C_BitOut(U8 Data)
// U8 HAL_I2C_BitIn(U8 Data)
// void HAL_I2C_TXD(void)
// void HAL_I2C_RXD(void)

// void HAL_I2C_ByteWrite_Command(U8 CommandCode)
// void HAL_I2C_ByteWrite_AddrToData(U16 Addr, U8 Data)
// void HAL_I2C_PageWrite_AddrToData(U16 Addr, U8 Length, U8 *wDataArray)
// U8 HAL_I2C_ByteRead_AddrToData(U16 Addr)
// void HAL_I2C_PageRead_AddrToData(U16 Addr, U8 Length, U8 *rDataArray)

