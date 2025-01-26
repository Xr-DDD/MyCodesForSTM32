#include "encoder.h"

void ENCODER_Start(void)
{
    HAL_TIM_Encoder_Start(ENCODER_TIM_HANDLE,ENCODER_TIM_CHANNEL_A);
    HAL_TIM_Encoder_Start(ENCODER_TIM_HANDLE,ENCODER_TIM_CHANNEL_B);
}

uint16_t ENCODER_GetValue(void)
{
    return __HAL_TIM_GetCounter(ENCODER_TIM_HANDLE);
}

void ENCODER_Stop(void)
{
    HAL_TIM_Encoder_Stop(ENCODER_TIM_HANDLE,ENCODER_TIM_CHANNEL_A);
    HAL_TIM_Encoder_Stop(ENCODER_TIM_HANDLE,ENCODER_TIM_CHANNEL_B);
}