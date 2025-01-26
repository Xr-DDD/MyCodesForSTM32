#ifndef JGB37_H
#define JGB37_H

#include "stm32f1xx_hal.h"
#include "tim.h"
/*
    设置专门用于计算转速的定时器CALC_SPEED_TIM_X
    使得定时器每1s进入一次溢出中断 pre = 7200-1 acc = 10000-1
/*
/*ENCODER编码器驱动*********************************************************************/
#define A_ENCODER_TIM_HANDLE      &htim1
#define A_ENCODER_TIM_CHANNEL_A   TIM_CHANNEL_1
#define A_ENCODER_TIM_CHANNEL_B   TIM_CHANNEL_2

#define B_ENCODER_TIM_HANDLE      &htim2
#define B_ENCODER_TIM_CHANNEL_A   TIM_CHANNEL_1
#define B_ENCODER_TIM_CHANNEL_B   TIM_CHANNEL_2

#define CALC_SPEED_TIM_X          TIM4
#define CALC_SPEED_TIM_HANDLE     &htim4
/*TB6612电机驱动***********************************************************************/
#define PWMA_TIM_HANDLE     &htim3
#define PWMA_TIM_CHANNEL    TIM_CHANNEL_1

#define PWMB_TIM_HANDLE     &htim3
#define PWMB_TIM_CHANNEL    TIM_CHANNEL_2

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

#define MOTOR_TIM_AUTORELOAD    (65535)
/**************************************************************************************/
typedef struct
{
    uint16_t A_encoder_value;
    uint16_t B_encoder_value;
    uint16_t A_motor_speed;
    uint16_t B_motor_speed;
    float A_pwm_duty;
    float B_pwm_duty;
    
}JGB37_ValueStructure;
/**************************************************************************************/
void JGB37_Encoder_Start(void);
void JGB37_Encoder_Stop(void);
void JGB37_Encoder_GetValue(JGB37_ValueStructure* jgb37);
void JGB37_Encoder_CalcSpeed(JGB37_ValueStructure* jgb37, TIM_HandleTypeDef *htim); //在溢出中断回调函数中使用 每1s进入一次溢出中断 pre = 7200-1 acc = 10000-1

void JGB37_Motor_Start(void);
void JGB37_Motor_Stop(void);
void JGB37_Motor_SetDuty(JGB37_ValueStructure* jgb37);

// /* 溢出中断回调 */
// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
// {
//     JGB37_Encoder_CalcSpeed(&jgb37, htim);
// }
#endif

