#include "jgb37.h"
/*************************************************************************************** */
void JGB37_Encoder_Start(void)
{
    HAL_TIM_Encoder_Start(A_ENCODER_TIM_HANDLE,A_ENCODER_TIM_CHANNEL_A);
    HAL_TIM_Encoder_Start(A_ENCODER_TIM_HANDLE,A_ENCODER_TIM_CHANNEL_B);
    HAL_TIM_Encoder_Start(B_ENCODER_TIM_HANDLE,B_ENCODER_TIM_CHANNEL_A);
    HAL_TIM_Encoder_Start(B_ENCODER_TIM_HANDLE,B_ENCODER_TIM_CHANNEL_B);
}

void JGB37_Encoder_Stop(void)
{
    HAL_TIM_Encoder_Stop(A_ENCODER_TIM_HANDLE,A_ENCODER_TIM_CHANNEL_A);
    HAL_TIM_Encoder_Stop(A_ENCODER_TIM_HANDLE,A_ENCODER_TIM_CHANNEL_B);
    HAL_TIM_Encoder_Stop(B_ENCODER_TIM_HANDLE,B_ENCODER_TIM_CHANNEL_A);
    HAL_TIM_Encoder_Stop(B_ENCODER_TIM_HANDLE,B_ENCODER_TIM_CHANNEL_B);
}

void JGB37_Motor_Start(void)
{
    HAL_TIM_PWM_Start(PWMA_TIM_HANDLE,PWMA_TIM_CHANNEL);
    HAL_TIM_PWM_Start(PWMB_TIM_HANDLE,PWMB_TIM_CHANNEL);
    HAL_GPIO_WritePin(STYB_GPIO_Port,STYB_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_RESET);
}

void JGB37_Motor_Stop(void)
{
    HAL_TIM_PWM_Stop(PWMA_TIM_HANDLE,PWMA_TIM_CHANNEL);
    HAL_TIM_PWM_Stop(PWMB_TIM_HANDLE,PWMB_TIM_CHANNEL);
    HAL_GPIO_WritePin(STYB_GPIO_Port,STYB_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_RESET);
}

void JGB37_Encoder_GetValue(JGB37_ValueStructure* jgb37)
{
    (*jgb37).A_encoder_value = __HAL_TIM_GetCounter(A_ENCODER_TIM_HANDLE);
    (*jgb37).B_encoder_value = __HAL_TIM_GetCounter(B_ENCODER_TIM_HANDLE);
}

JGB37_Encoder_CalcSpeed(JGB37_ValueStructure* jgb37, TIM_HandleTypeDef *htim)
{
    if(CALC_SPEED_TIM_X == htim->Instance)
    {
        (*jgb37).A_motor_speed = (*jgb37).A_encoder_value; //保存旧编码器值
        (*jgb37).B_motor_speed = (*jgb37).B_encoder_value;
        JGB37_Encoder_GetValue(jgb37);// 每1s更新一次编码器值
        (*jgb37).A_motor_speed = (*jgb37).A_encoder_value - (*jgb37).A_motor_speed; //新值减去旧值得到转速（码数/秒）
        (*jgb37).B_motor_speed = (*jgb37).B_encoder_value - (*jgb37).B_motor_speed;
    }
}


void JGB37_Motor_SetDuty(JGB37_ValueStructure* jgb37)
{
    HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,((*jgb37).A_pwm_duty >= 0));
	HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,((*jgb37).A_pwm_duty < 0));
    HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,((*jgb37).B_pwm_duty >= 0));
	HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,((*jgb37).B_pwm_duty < 0));
    if((*jgb37).A_pwm_duty > 100 || (*jgb37).A_pwm_duty < -100)(*jgb37).A_pwm_duty = 100;
    if((*jgb37).B_pwm_duty > 100 || (*jgb37).B_pwm_duty < -100)(*jgb37).B_pwm_duty = 100;
    __HAL_TIM_SetCompare(PWMA_TIM_HANDLE,PWMA_TIM_CHANNEL,(uint16_t)(__HAL_TIM_GetAutoreload(PWMA_TIM_HANDLE)*((*jgb37).A_pwm_duty)/100));
    __HAL_TIM_SetCompare(PWMB_TIM_HANDLE,PWMB_TIM_CHANNEL,(uint16_t)(__HAL_TIM_GetAutoreload(PWMB_TIM_HANDLE)*((*jgb37).B_pwm_duty)/100));
}

