#ifndef _HAL_SPI_H_
#define _HAL_SPI_H_


#define FUNC_CSI_CH00_START     R_CSI00_Start
#define FUNC_CSI_CH00_STOP      R_CSI00_Stop
#define FUNC_CSI_CH01_START     R_CSI01_Start
#define FUNC_CSI_CH01_STOP      R_CSI01_Stop
#define FUNC_CSI_CH10_START     R_CSI10_Start
#define FUNC_CSI_CH10_STOP      R_CSI10_Stop
#define FUNC_CSI_CH11_START     R_CSI11_Start
#define FUNC_CSI_CH11_STOP      R_CSI11_Stop
#define FUNC_CSI_CH20_START     R_CSI20_Start
#define FUNC_CSI_CH20_STOP      R_CSI20_Stop
#define FUNC_CSI_CH21_START     R_CSI21_Start
#define FUNC_CSI_CH21_STOP      R_CSI21_Stop
#define FUNC_CSI_CH30_START     R_CSI30_Start
#define FUNC_CSI_CH30_STOP      R_CSI30_Stop
#define FUNC_CSI_CH31_START     R_CSI31_Start
#define FUNC_CSI_CH31_STOP      R_CSI31_Stop

#define FUNC_SPI_SEND_RECEIVE_USER      R_CSI21_Send_Receive
#define FUNC_SPI_SEND_USER              R_CSI21_Send
#define FUNC_SPI_RECEIVE_USER           R_CSI21_Receive

#define FUNC_SPI_SEND_RECEIVE_USER_1
#define FUNC_SPI_SEND_USER_1
#define FUNC_SPI_RECEIVE_USER_1


void HAL_SPI_CH_START(fp_void fp);
void HAL_SPI_CH_STOP(fp_void fp);
MD_STATUS HAL_SPI_Send_Receive(U8* const TxBuffer, U8* const RxBuffer, U16 Cnt, fp_Param_pU8_U16_pU8 fp);
MD_STATUS HAL_SPI_Send(U8* const TxBuffer, U16 Cnt, fp_Param_pU8_U16 fp);
MD_STATUS HAL_SPI_Receive(U8* const RxBuffer, U16 Cnt, fp_Param_pU8_U16 fp);

#endif