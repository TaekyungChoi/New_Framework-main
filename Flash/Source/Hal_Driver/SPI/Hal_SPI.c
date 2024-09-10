#include "HW.h"
#include "Hal_SPI.h"

void HAL_SPI_CH_START(fp_void fp)
{
    fp();
}

void HAL_SPI_CH_STOP(fp_void fp)
{
    fp();
}

MD_STATUS HAL_SPI_Send_Receive(U8* const TxBuffer, U8* const RxBuffer, U16 Cnt, fp_Param_pU8_U16_pU8 fp)
{
    MD_STATUS Status = MD_OK;

    Status = fp(TxBuffer, Cnt, RxBuffer);

    return Status;
}

MD_STATUS HAL_SPI_Send(U8* const TxBuffer, U16 Cnt, fp_Param_pU8_U16 fp)
{
    MD_STATUS Status = MD_OK;

    Status = fp(TxBuffer, Cnt);

    return Status;
}

MD_STATUS HAL_SPI_Receive(U8* const RxBuffer, U16 Cnt, fp_Param_pU8_U16 fp)
{
    MD_STATUS Status = MD_OK;

    Status = fp(RxBuffer, Cnt);

    return Status;
}