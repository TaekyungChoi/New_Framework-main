#include "HW.h"
#include "PortDefine.h"
#include "Hal_ADC.h"

U16 ADCValue[ANI_MAX] = {0, };

U8 ADCInterrupt_F = 0;

void HAL_ADC_START_IT(void)
{
    R_ADC_Start();
}

void HAL_ADC_STOP_IT(void)
{
    R_ADC_Stop();
}

void HAL_ADC_Operation_START(void)
{
    R_ADC_Set_OperationOn();
}

void HAL_ADC_Operation_STOP(void)
{
    R_ADC_Set_OperationOff();
}


// U16 *HAL_ADC_GetADCValueAddr(void)
// {
//     return ADCValue;
// }

//----------------------------------------------------//
//---- ADC Convert : Channel OneShot Select Method----//
//----------------------------------------------------//

U16 HAL_ADC_GetAdcValue(U8 Channel)
{
    return ADCValue[Channel];
}

void HAL_ADC_SetADCValue(U8 Channel)
{
    U16 *ptr = NULL;

    ptr = ADCValue;

    ptr[Channel] = (U16)(ADCR >> 6U);
}

void HAL_ADC_SetInterruptFlag(U8 Set_F)
{
    if(Set_F == SET)
    {
        ADCInterrupt_F = SET;
    }
    else
    {
        ADCInterrupt_F = CLEAR;
    }
}

U8 HAL_ADC_GetInterruptFlag(void)
{
    return ADCInterrupt_F;
}

void HAL_ADC_IncreaseChannel(void)
{
    ADS = ADS + 1;

	if(ADS >= ANI_MAX)
	{
		ADS = 0;
	}
}

U8 HAL_ADC_GetChannel(void)
{
    return ADS;
}

//----------------------------------------------------//

