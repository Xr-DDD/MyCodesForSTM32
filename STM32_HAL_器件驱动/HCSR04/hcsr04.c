#include "hcsr04.h"

void HCSR04_Start(void)
{
    HAL_TIM_Base_Start_IT(HCSR04_TIM_HANDLE);
    HAL_TIM_IC_Start_IT(HCSR04_TIM_HANDLE,HCSR04_TIM_CHANNEL_1);
    HAL_TIM_IC_Start_IT(HCSR04_TIM_HANDLE,HCSR04_TIM_CHANNEL_2);
}

void HCSR04_Stop(void)
{
    HAL_TIM_Base_Stop_IT(HCSR04_TIM_HANDLE);
    HAL_TIM_IC_Stop_IT(HCSR04_TIM_HANDLE,HCSR04_TIM_CHANNEL_1);
    HAL_TIM_IC_Stop_IT(HCSR04_TIM_HANDLE,HCSR04_TIM_CHANNEL_2);
}

void HCSR04_TIM_OverFlow(HCSR04_ValueStructure* hcsr04, TIM_HandleTypeDef *htim) //在溢出中断回调中使用
{
    if(HCSR04_TIM_X == htim->Instance)
    {
        if((*hcsr04).capture_isbusy)
        {
            (*hcsr04).update_cnt++;
        }

        if((*hcsr04).update_cnt > 2) //捕获超时
        {
            (*hcsr04).capture_isbusy = 0;
            (*hcsr04).update_cnt = 0;
            (*hcsr04).capture_rising_edge = 0;
            (*hcsr04).capture_falling_edge = 0;
            (*hcsr04).pulse_width = 0;
        }
    }
}

void HCSR04_TIM_InputCapture(HCSR04_ValueStructure* hcsr04, TIM_HandleTypeDef *htim) //在捕获中断回调中使用
{
    if(HCSR04_TIM_X == htim->Instance)
	{
        if(HCSR04_HAL_TIM_ACTIVE_CHANNEL_1 == htim->Channel) //捕获上升沿
        {
            (*hcsr04).capture_rising_edge = HAL_TIM_ReadCapturedValue(HCSR04_TIM_HANDLE,HCSR04_TIM_CHANNEL_1);
            (*hcsr04).capture_isbusy = 1; //定时器溢出计数开启
        }
        else if(HCSR04_HAL_TIM_ACTIVE_CHANNEL_2 == htim->Channel) //捕获下降沿
        {
            if((*hcsr04).capture_isbusy) //如果已经捕获了上升沿
            {
                (*hcsr04).capture_isbusy = 0; //定时器溢出计数停止
                (*hcsr04).capture_falling_edge = HAL_TIM_ReadCapturedValue(HCSR04_TIM_HANDLE,HCSR04_TIM_CHANNEL_2);
                (*hcsr04).pulse_width = (*hcsr04).update_cnt * HCSR04_TIM_UPDATE_VALUE+ (*hcsr04).capture_falling_edge - (*hcsr04).capture_rising_edge;
                (*hcsr04).update_cnt = 0;
            }
            else //捕获出错
            {
                (*hcsr04).capture_isbusy = 0;
                (*hcsr04).update_cnt = 0;
                (*hcsr04).capture_rising_edge = 0;
                (*hcsr04).capture_falling_edge = 0;
                (*hcsr04).pulse_width = 0;
            }
        }
    }
}

void HCSR04_SendTrig(void)
{
    //发送Trig信号
    HAL_GPIO_WritePin(HCSR04_TRIG_GPIO_Port,HCSR04_TRIG_Pin,GPIO_PIN_SET);
    for(uint8_t i = 0; i < 100; i++);
    HAL_GPIO_WritePin(HCSR04_TRIG_GPIO_Port,HCSR04_TRIG_Pin,GPIO_PIN_RESET);
}

void HCSR04_GetDistance(HCSR04_ValueStructure* hcsr04);
{
    if((*hcsr04).pulse_width == 0)
    {
        (*hcsr04).distance = -1; //捕获尚未开始 捕获失败
    }
    else if((*hcsr04).pulse_width > 38000)
    {
        (*hcsr04).distance = -2; //超出捕获距离 捕获异常
    }
    else
    {
        (*hcsr04).distance = (*hcsr04).pulse_width*0.017f;
    }
}
