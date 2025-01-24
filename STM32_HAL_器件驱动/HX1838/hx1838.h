#ifndef _HX1838_H_
#define _HX1838_H_

#include "stm32f1xx_hal.h"
#include "tim.h"

/*
    设置定时器PSC使一个计数为1us

    两个定时器捕获通道需要设置为：
    一个直接模式 + 一个间接模式
    一个检测上升沿 + 一个检测下降沿
    对这些模式的设置顺序没有要求

    需要开启：
    定时器捕获中断 + 定时器溢出中断
*/
/********************************************************************************* */
#define HX1838_TIM_X                        (TIM1)
#define HX1838_TIM_HANDLE                   (&htim1)
#define HX1838_TIM_CHANNEL_1                (TIM_CHANNEL_1)
#define HX1838_TIM_CHANNEL_2                (TIM_CHANNEL_2)
#define HX1838_HAL_TIM_ACTIVE_CHANNEL_1     (HAL_TIM_ACTIVE_CHANNEL_1)
#define HX1838_HAL_TIM_ACTIVE_CHANNEL_2     (HAL_TIM_ACTIVE_CHANNEL_2)
#define HX1838_TIM_UPDATE_VALUE             (65536)
/********************************************************************************* */
#define IR_KEY_5    (56)
#define IR_KEY_2    (24)
#define IR_KEY_8    (74)
#define IR_KEY_4    (16)
#define IR_KEY_6    (90)
/********************************************************************************* */
typedef struct
{
    uint8_t capture_isbusy;             //定时器捕获忙
    uint8_t capture_cnt;                //定时器捕获次数
    uint8_t update_cnt;                 //定时器更新次数
    uint32_t capture_value[66 + 1];     //定时器捕获值
    uint16_t pulse_width[66];           //接收到的脉冲宽度
    uint8_t rx_data;                    //解码出的数据

}HX1838_ValueStrueture;
/********************************************************************************* */
void HX1838_Start(void);
void HX1838_Stop(void);
void HX1838_Decode(HX1838_ValueStrueture* hx1838);
void HX1838_TIM_Overflow(HX1838_ValueStrueture* hx1838, TIM_HandleTypeDef *htim); //在溢出中断回调中使用
void HX1838_TIM_InputCapture(HX1838_ValueStrueture* hx1838, TIM_HandleTypeDef *htim); //在捕获中断回调中使用


// /* 溢出中断回调 */
// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
// {
//     HX1838_TIM_Overflow(&hx1838, htim);
// }

// /* 捕获中断回调 */
// void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
// {
//     HX1838_TIM_InputCapture(&hx1838, htim);
// }

#endif
