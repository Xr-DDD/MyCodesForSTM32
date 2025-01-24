#include "motor.h"

void MOTOR_Start(void)
{
    HAL_TIM_PWM_Start(PWMA_TIM_HANDLE,PWMA_TIM_CHANNEL);
    HAL_TIM_PWM_Start(PWMB_TIM_HANDLE,PWMB_TIM_CHANNEL);
    HAL_GPIO_WritePin(STYB_GPIO_Port,STYB_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_RESET);
}


void MOTOR_Stop(void)
{
    HAL_TIM_PWM_Stop(PWMA_TIM_HANDLE,PWMA_TIM_CHANNEL);
    HAL_TIM_PWM_Stop(PWMB_TIM_HANDLE,PWMB_TIM_CHANNEL);
    HAL_GPIO_WritePin(STYB_GPIO_Port,STYB_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_RESET);
}

void MOTOR_SetDuty(int A_duty, int B_duty)
{
    HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,(A_duty >= 0));
	HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,(A_duty < 0));
    HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,(B_duty >= 0));
	HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,(B_duty < 0));
    if(A_duty > 100 || A_duty < -100)A_duty = 100;
    if(B_duty > 100 || B_duty < -100)B_duty = 100;
    __HAL_TIM_SetCompare(PWMA_TIM_HANDLE,PWMA_TIM_CHANNEL,(uint16_t)(__HAL_TIM_GetAutoreload(PWMA_TIM_HANDLE)*(A_duty)/100));
    __HAL_TIM_SetCompare(PWMB_TIM_HANDLE,PWMB_TIM_CHANNEL,(uint16_t)(__HAL_TIM_GetAutoreload(PWMB_TIM_HANDLE)*(B_duty)/100));
}


