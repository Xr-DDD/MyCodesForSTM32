#ifndef SG90_H
#define SG90_H

#include "stm32f1xx_hal.h"
#include "tim.h"

/*
    需要一个定时器的一个通道产生一路PWM
    注意这个定时器的溢出值将会被设置为20ms时溢出
    若pre设置为1us 则Autoreload = 20000
*/

/*************************************************************************************************** */
#define SG90_TIM_HANDLE    &htim2
#define SG90_TIM_CHANNEL   TIM_CHANNEL_3
/*************************************************************************************************** */
void SG90_Init(void);   // Set Autoreload = 20ms
void SG90_Start(void);
void SG90_Stop(void);
void SG90_SetDegree(uint16_t degree); // 0~180

#endif

//Set Prescaler = 1us
//Set Autoreload = 20ms

