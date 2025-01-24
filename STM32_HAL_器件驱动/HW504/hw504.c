#include "hw504.h"

void HW504_GetValue(HW504_ValueStructure* hw504);
{
    HAL_ADC_Start(HW504_XY_ADC_HANDLE);
    if(HAL_ADC_PollForConversion(HW504_XY_ADC_HANDLE,10) == HAL_OK)
	{
		(*hw504).x = HAL_ADC_GetValue(HW504_XY_ADC_HANDLE);
	}
    HAL_ADC_Start(HW504_XY_ADC_HANDLE);
    if(HAL_ADC_PollForConversion(HW504_XY_ADC_HANDLE,10) == HAL_OK)
	{
		(*hw504).y = HAL_ADC_GetValue(HW504_XY_ADC_HANDLE);
	}
    HAL_ADC_Stop(HW504_XY_ADC_HANDLE);
    (*hw504).z = HAL_GPIO_ReadPin(HW504_Z_GPIO_Port, HW504_Z_Pin);
}

