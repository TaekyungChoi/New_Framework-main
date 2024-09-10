#ifndef _HAL_I2C_POLLING_H_
#define _HAL_I2C_POLLING_H_


U8 HAL_I2C_ByteWrite_Command(U8 CommandCode, U32 TwrDelay);
U8 HAL_I2C_ByteWrite_16bitAddrToData(U16 Addr, U8 Data, U32 TwrDelay);
U8 HAL_I2C_ByteWrite_8bitAddrToData(U8 Addr, U8 Data, U32 TwrDelay);
U8 HAL_I2C_ByteRead_16bitAddrToData(U16 Addr, U8 *rData, U32 TwrDelay);
U8 HAL_I2C_ByteRead_8bitAddrToData(U8 Addr, U8 *rData, U32 TwrDelay);
U8 HAL_I2C_PageWrite_16bitAddrToData(U16 Addr, U8 const *TxBuf, U16 TxLength, U32 TwrDelay);
U8 HAL_I2C_PageWrite_8bitAddrToData(U8 Addr, U8 const *TxBuf, U16 TxLength, U32 TwrDelay);
U8 HAL_I2C_PageRead_16bitAddrToData(U16 Addr, U8 *RxBuf, U16 RxLength, U32 TwrDelay);
U8 HAL_I2C_PageRead_8bitAddrToData(U8 Addr, U8 *RxBuf, U16 RxLength, U32 TwrDelay);


#endif