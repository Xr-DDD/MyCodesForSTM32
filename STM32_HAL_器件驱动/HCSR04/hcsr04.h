#ifndef _HCSR04_H_
#define _HCSR04_H_

/*
    需要设置一个GPIO输出TRIG信号(10us高电平脉冲)
    需要设置定时器输入捕获接收EHCO信号(一定长度的高电平脉冲)

    设置定时器PSC使一个计数为1us

    两个定时器捕获通道需要设置为：
    一个直接模式 + 一个间接模式
    一个检测上升沿 + 一个检测下降沿

    需要开启中断：
    定时器捕获中断 + 定时器溢出中断
*/

#include "stm32f1xx_hal.h"
#include "tim.h"

#define HCSR04_TRIG_GPIO_Port               (GPIOB)
#define HCSR04_TRIG_Pin                     (GPIO_PIN_0)

#define HCSR04_TIM_X                        (TIM1)
#define HCSR04_TIM_HANDLE                   (&htim1)
#define HCSR04_TIM_CHANNEL_1                (TIM_CHANNEL_1)
#define HCSR04_TIM_CHANNEL_2                (TIM_CHANNEL_2)
#define HCSR04_HAL_TIM_ACTIVE_CHANNEL_1     (HAL_TIM_ACTIVE_CHANNEL_1)
#define HCSR04_HAL_TIM_ACTIVE_CHANNEL_2     (HAL_TIM_ACTIVE_CHANNEL_2)
#define HCSR04_TIM_UPDATE_VALUE             (65536)
/*******************************************************************************************************************/
typedef struct
{
    uint8_t capture_isbusy;             //定时器捕获忙
    uint8_t update_cnt;                 //定时器更新次数
    uint16_t capture_rising_edge;       //上升沿捕获值
    uint16_t capture_falling_edge;      //下降沿捕获值
    uint32_t pulse_width;               //脉冲宽度
    float distance;                     //检测到的距离

}HCSR04_ValueStructure;
/*******************************************************************************************************************/
void HCSR04_Start(void);
void HCSR04_Stop(void);
void HCSR04_TIM_Overflow(HCSR04_ValueStructure* hcsr04, TIM_HandleTypeDef *htim); //在溢出中断回调中使用
void HCSR04_TIM_InputCapture(HCSR04_ValueStructure* hcsr04, TIM_HandleTypeDef *htim); //在捕获中断回调中使用
void HCSR04_SendTrig(void);
void HCSR04_GetDistance(HCSR04_ValueStructure* hcsr04);

// /* 溢出中断回调 */
// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
// {
//     HCSR04_TIM_Overflow(&hcsr04, htim);
// }
// /* 捕获中断回调 */
// void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
// {
//     HCSR04_TIM_InputCapture(&hcsr04, htim);
// }

#endif
