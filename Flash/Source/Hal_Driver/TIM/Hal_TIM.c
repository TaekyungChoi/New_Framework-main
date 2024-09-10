#include "HW.h"
#include "Hal_TIM.h"


void HAL_TIM_ElapsedPeriod_START(fp_void fp)
{
    fp();
}

void HAL_TIM_ElapsedPeriod_STOP(fp_void fp)
{
    fp();
}

void HAL_TIM_SquareWaveOutput_START(fp_void fp)
{
    fp();
}

void HAL_TIM_SquareWaveOutput_STOP(fp_void fp)
{
    fp();
}

void HAL_TIM_PWM_START(fp_void fp)
{
    fp();
}

void HAL_TIM_PWM_STOP(fp_void fp)
{
    fp();
}

void HAL_TIM_PWM_OUTLOW(U8 CHANNEL)
{
    switch(CHANNEL)
    {
        case TAU0_CH0:
        break;

        case TAU0_CH1:
        break;

        case TAU0_CH2:
            
        break;

        case TAU0_CH3:
        break;

        case TAU0_CH4:
        break;

        case TAU0_CH5:
        break;

        case TAU0_CH6:
        break;

        case TAU0_CH7:
        break;

        case TAU1_CH0:
        break;

        case TAU1_CH1:
            TOL1 &= ~_0002_TAU_CH1_OUTPUT_LEVEL_L;
            TO1 &= ~_0002_TAU_CH1_OUTPUT_VALUE_1;        
        break;        

        case TAU1_CH2:
        break;

        case TAU1_CH3:
            TOL1 &= ~_0008_TAU_CH3_OUTPUT_LEVEL_L;
            TO1 &= ~_0008_TAU_CH3_OUTPUT_VALUE_1;        
        break;

        default:
        break;
    }    
}


void HAL_TIM_PWM_DUTY_SET(U8 CHANNEL, U16 Vsp)
{
    switch(CHANNEL)
    {
        case TAU0_CH0:
        break;

        case TAU0_CH1:
        break;

        case TAU0_CH2:
            
        break;

        case TAU0_CH3:
        break;

        case TAU0_CH4:
        break;

        case TAU0_CH5:
        break;

        case TAU0_CH6:
        break;

        case TAU0_CH7:
        break;

        case TAU1_CH0:
        break;

        case TAU1_CH1:
            TDR11 = Vsp;        
        break;        

        case TAU1_CH2:
        break;

        case TAU1_CH3:
            TDR13 = Vsp;        
        break;

        default:
        break;
    }
}

void HAL_TIM_InputPulseWidth_START(fp_void fp)
{
    fp();
}

void HAL_TIM_InputPulseWidth_STOP(fp_void fp)
{
    fp();
}

U32 HAL_TIM_InputPulseWidth_GET(fp_U32Ptr ptr)
{
    static U32 Width = 0;

    ptr(&Width);

    return Width;
}

