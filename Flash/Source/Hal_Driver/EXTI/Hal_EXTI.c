#include "HW.h"
#include "Hal_EXTI.h"


void HAL_EXTI_START(fp_void fp)
{
    fp();
}

void HAL_EXTI_STOP(fp_void fp)
{
    fp();
}