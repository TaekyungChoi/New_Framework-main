#include "Hal_Driver.h"
#include "App_Main.h"


void UserMain(void)
{
    DI();
    InitSystem();
    InitUserPortDefine();
    InitVariable();
    EI();

    while(1)
    {
        HAL_WDT_Resume();
        ProcessEventHandler();
        TaskEventHandler();
    }
}


void InitSystem(void)
{

}

void InitUserPortDefine(void)
{

}

void InitVariable(void)
{

}

void ProcessEventHandler(void)
{

}

void TaskEventHandler(void)
{
    
}



// Interval Timer 100us
void TIM_TAU0_CH0_InterruptCallback(void)
{

}

// SquareWave Output 250us
void TIM_TAU0_CH1_InterruptCallback(void)  
{
    
}

// Interval Timer 1ms
void TIM_TAU0_CH2_InterruptCallback(void)
{
    
}

// Interval Timer 1us
void TIM_TAU0_CH6_InterruptCallback(void)
{
    
}

// PWM Master Channel 10ms
void TIM_TAU1_CH0_InterruptCallback(void)
{

}

// PWM Slave Channel
void TIM_TAU1_CH1_InterruptCallback(void)
{

}

// INTP CH4 Channel
void INTP_CH4_InterruptCallback(void)
{
    
}

