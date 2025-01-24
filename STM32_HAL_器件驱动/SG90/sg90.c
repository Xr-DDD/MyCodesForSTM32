#include "sg90.h"

void SG90_Init()
{
    __HAL_TIM_SetAutoreload(SG90_TIM_HANDLE, 20000);// 20ms per cycle
}

void SG90_Start()
{
    HAL_TIM_PWM_Start(SG90_TIM_HANDLE,SG90_TIM_CHANNEL);
}

void SG90_Stop()
{
    HAL_TIM_PWM_Stop(SG90_TIM_HANDLE,SG90_TIM_CHANNEL);
}

void SG90_SetDegree(uint16_t degree)
{
    uint16_t compare = 500;
    if(degree > 180)degree = 180;
    compare = 11.11 * (degree + 45);
    __HAL_TIM_SetCompare(SG90_TIM_HANDLE, SG90_TIM_CHANNEL, compare);
}

