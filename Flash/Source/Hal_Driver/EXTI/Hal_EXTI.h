#ifndef _HAL_EXTI_H_
#define _HAL_EXTI_H_



#define INTP_0      0
#define INTP_1      1
#define INTP_2      2
#define INTP_3      3
#define INTP_4      4
#define INTP_5      5
#define INTP_6      6
#define INTP_7      7
#define INTP_8      8
#define INTP_9      9
#define INTP_10     10
#define INTP_11     11

#define FUNC_INTP_START_USER        R_INTC4_Start
#define FUNC_INTP_STOP_USER         R_INTC4_Stop

#define FUNC_INTP_START_USER_1      R_INTC11_Start
#define FUNC_INTP_STOP_USER_1       R_INTC11_Stop

void HAL_EXTI_START(fp_void fp);
void HAL_EXTI_STOP(fp_void fp);




#endif