#ifndef _HAL_TIM_H_
#define _HAL_TIM_H_


// typedef enum
// {
//     TAU0_CH0 = 0,
//     TAU0_CH1,
//     TAU0_CH2,
//     TAU0_CH3,
//     TAU0_CH4,
//     TAU0_CH5,
//     TAU0_CH6,
//     TAU0_CH7,

//     TAU1_CH0 = 10,
//     TAU1_CH1,
//     TAU1_CH2,
//     TAU1_CH3
// }TIM_CHANNEL;


#define TAU0_CH0    0
#define TAU0_CH1    1
#define TAU0_CH2    2
#define TAU0_CH3    3
#define TAU0_CH4    4
#define TAU0_CH5    5
#define TAU0_CH6    6
#define TAU0_CH7    7
#define TAU1_CH0    10
#define TAU1_CH1    11
#define TAU1_CH2    12
#define TAU1_CH3    13

#define FUNC_TAU0_CH0_START    R_TAU0_Channel0_Start
#define FUNC_TAU0_CH0_STOP     R_TAU0_Channel0_Stop
#define FUNC_TAU0_CH1_START    R_TAU0_Channel1_Start
#define FUNC_TAU0_CH1_STOP     R_TAU0_Channel1_Stop
#define FUNC_TAU0_CH2_START    R_TAU0_Channel2_Start
#define FUNC_TAU0_CH2_STOP     R_TAU0_Channel2_Stop
#define FUNC_TAU0_CH3_START    R_TAU0_Channel3_Start
#define FUNC_TAU0_CH3_STOP     R_TAU0_Channel3_Stop
#define FUNC_TAU0_CH4_START    R_TAU0_Channel4_Start
#define FUNC_TAU0_CH4_STOP     R_TAU0_Channel4_Stop
#define FUNC_TAU0_CH5_START    R_TAU0_Channel5_Start
#define FUNC_TAU0_CH5_STOP     R_TAU0_Channel5_Stop
#define FUNC_TAU0_CH6_START    R_TAU0_Channel6_Start
#define FUNC_TAU0_CH6_STOP     R_TAU0_Channel6_Stop
#define FUNC_TAU0_CH7_START    R_TAU0_Channel7_Start
#define FUNC_TAU0_CH7_STOP     R_TAU0_Channel7_Stop
#define FUNC_TAU1_CH0_START    R_TAU1_Channel0_Start
#define FUNC_TAU1_CH0_STOP     R_TAU1_Channel0_Stop
#define FUNC_TAU1_CH1_START    R_TAU1_Channel1_Start
#define FUNC_TAU1_CH1_STOP     R_TAU1_Channel1_Stop
#define FUNC_TAU1_CH2_START    R_TAU1_Channel2_Start
#define FUNC_TAU1_CH2_STOP     R_TAU1_Channel2_Stop
#define FUNC_TAU1_CH3_START    R_TAU1_Channel3_Start
#define FUNC_TAU1_CH3_STOP     R_TAU1_Channel3_Stop

#define FUNC_GET_PULSEWIDTH_USER        R_TAU0_Channel7_Get_PulseWidth
#define FUNC_GET_PULSEWIDTH_USER_1


void HAL_TIM_ElapsedPeriod_START(fp_void fp);
void HAL_TIM_ElapsedPeriod_STOP(fp_void fp);
void HAL_TIM_SquareWaveOutput_START(fp_void fp);
void HAL_TIM_SquareWaveOutput_STOP(fp_void fp);
void HAL_TIM_PWM_START(fp_void fp);
void HAL_TIM_PWM_STOP(fp_void fp);
void HAL_TIM_PWM_OUTLOW(U8 CHANNEL);
void HAL_TIM_PWM_DUTY_SET(U8 CHANNEL, U16 Vsp);
void HAL_TIM_InputPulseWidth_START(fp_void fp);
void HAL_TIM_InputPulseWidth_STOP(fp_void fp);
U32 HAL_TIM_InputPulseWidth_GET(fp_U32Ptr ptr);

// void HAL_TIM_ElapsedPeriod_START(U8 CHANNEL);
// void HAL_TIM_ElapsedPeriod_STOP(U8 CHANNEL);
// void HAL_TIM_SquareWaveOutput_START(U8 CHANNEL);
// void HAL_TIM_SquareWaveOutput_STOP(U8 CHANNEL);
// void HAL_TIM_PWM_START(U8 CHANNEL);
// void HAL_TIM_PWM_STOP(U8 CHANNEL);
// void HAL_TIM_PWM_OUTLOW(U8 CHANNEL);
// void HAL_TIM_PWM_DUTY_SET(U8 CHANNEL, U16 Vsp);
// void HAL_TIM_InputPulseWidth_START(U8 CHANNEL);
// void HAL_TIM_InputPulseWidth_STOP(U8 CHANNEL);
// U32 HAL_TIM_InputPulseWidth_GET(U8 CHANNEL);






#endif