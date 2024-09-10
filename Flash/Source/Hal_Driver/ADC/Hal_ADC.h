#ifndef _HAL_ADC_H_
#define _HAL_ADC_H_

// ADC
typedef enum
{
	PHOTO,  // ANI0   
	GAS,
	STEPMOTOR1_FEEDBACK,
	STEPMOTOR2_FEEDBACK,
	SMPS_FEEDBACK,
	HUMI,
	EW_C,
	EW_V,

	ETC
} ANI_PERI_T;

#define ANI0_PERI PHOTO
#define ANI1_PERI GAS
#define ANI2_PERI STEPMOTOR1_FEEDBACK
#define ANI3_PERI STEPMOTOR2_FEEDBACK
#define ANI4_PERI SMPS_FEEDBACK
#define ANI5_PERI HUMI
#define ANI6_PERI EW_C
#define ANI7_PERI EW_V

#define ANI_MAX   ANI2_PERI

void HAL_ADC_START_IT(void);
void HAL_ADC_STOP_IT(void);
void HAL_ADC_Operation_START(void);
void HAL_ADC_Operation_STOP(void);
//U16 *HAL_ADC_GetADCValueAddr(void);
void HAL_ADC_SetADCValue(U8 Channel);
U16 HAL_ADC_GetAdcValue(U8 Channel);
void HAL_ADC_SetInterruptFlag(U8 Set_F);
U8 HAL_ADC_GetInterruptFlag(void);
U8 HAL_ADC_GetChannel(void);
void HAL_ADC_IncreaseChannel(void);

#endif