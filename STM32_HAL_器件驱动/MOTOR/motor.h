#ifndef MOTOR_H
#define MOTOR_H

#include "stm32f1xx_hal.h"
#include "tim.h"
/*******************************************************************************************************************************/
#define STYB_GPIO_Port           GPIOB
#define STYB_Pin            GPIO_PIN_6

#define AIN1_GPIO_Port           GPIOB
#define AIN1_Pin            GPIO_PIN_5

#define AIN2_GPIO_Port           GPIOB
#define AIN2_Pin            GPIO_PIN_4

#define BIN1_GPIO_Port           GPIOB
#define BIN1_Pin            GPIO_PIN_7

#define BIN2_GPIO_Port           GPIOB
#define BIN2_Pin            GPIO_PIN_8

#define PWMA_TIM_HANDLE     &htim2
#define PWMA_TIM_CHANNEL    TIM_CHANNEL_1

#define PWMB_TIM_HANDLE     &htim2
#define PWMB_TIM_CHANNEL    TIM_CHANNEL_2
/**********************************************************************************************************************************/
void MOTOR_Start(void);
void MOTOR_Stop(void);
void MOTOR_SetDuty(int A_duty, int B_duty);
//speed: -100~+100

#endif


