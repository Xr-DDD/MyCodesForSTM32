#ifndef SG90_H
#define SG90_H

#include "stm32f1xx_hal.h"
#include "tim.h"

#define SG90_TIM_HANDLE    &htim2
#define SG90_TIM_CHANNEL   TIM_CHANNEL_2
/*************************************************************************************************** */
void SG90_Init(void);   // Set Autoreload = 20ms
void SG90_Start(void);
void SG90_Stop(void);
void SG90_SetDegree(uint16_t degree); // 0~180

#endif

//Set Prescaler = 1us
//Set Autoreload = 20ms

