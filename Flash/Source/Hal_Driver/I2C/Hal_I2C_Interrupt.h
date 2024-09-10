#ifndef _HAL_I2C_INTERRUPT_
#define _HAL_I2C_INTERRUPT_

MD_STATUS HAL_I2C_INT_ByteWrite_16bitAddrToData(U16 Addr, U8 Data);
MD_STATUS HAL_I2C_INT_ByteWrite_8bitAddrToData(U8 Addr, U8 Data);

MD_STATUS HAL_I2C_INT_ByteRead_16bitAddrToData(U16 Addr, U8* RxBuffer);
MD_STATUS HAL_I2C_INT_ByteRead_8bitAddrToData(U8 Addr, U8* RxBuffer);

MD_STATUS HAL_I2C_INT_PageWrite_16bitAddrToData(U16 Addr, U8* TxBuffer, U16 TxNum);
MD_STATUS HAL_I2C_INT_PageWrite_8bitAddrToData(U8 Addr, U8* TxBuffer, U16 TxNum);

MD_STATUS HAL_I2C_INT_PageRead_16bitAddrToData(U16 Addr, U8* RxBuffer, U16 RxNum);
MD_STATUS HAL_I2C_INT_PageRead_8bitAddrToData(U8 Addr, U8* RxBuffer, U16 RxNum);


#endif