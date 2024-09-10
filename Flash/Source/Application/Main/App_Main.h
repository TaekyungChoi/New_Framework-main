#ifndef _APP_MAIN_H_
#define _APP_MAIN_H_


void UserMain(void);
void InitSystem(void);
void InitUserPortDefine(void);
void InitVariable(void);
void ProcessEventHandler(void);
void TaskEventHandler(void);

void TIM_TAU0_CH0_InterruptCallback(void);
void TIM_TAU0_CH1_InterruptCallback(void);  
void TIM_TAU0_CH2_InterruptCallback(void);
void TIM_TAU0_CH6_InterruptCallback(void);
void TIM_TAU1_CH0_InterruptCallback(void);
void TIM_TAU1_CH1_InterruptCallback(void);
void INTP_CH4_InterruptCallback(void);


#endif