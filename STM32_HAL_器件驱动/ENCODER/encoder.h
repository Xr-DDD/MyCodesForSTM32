#ifndef ENCODER_H
#define ENCODER_H

#include "stm32f1xx_hal.h"
#include "tim.h"
/****************************************************************/
#define ENCODER_TIM_HANDLE      &htim1
#define ENCODER_TIM_CHANNEL_A   TIM_CHANNEL_1
#define ENCODER_TIM_CHANNEL_B   TIM_CHANNEL_2
/****************************************************************/
void ENCODER_Start(void);
void ENCODER_Stop(void);
uint16_t ENCODER_GetValue(void);
#endif