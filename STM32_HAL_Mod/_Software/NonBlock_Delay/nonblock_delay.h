#ifndef _NONBLOCK_DELAY_H_
#define _NONBLOCK_DELAY_H_

#include "stm32f1xx_hal.h"
#include "tim.h"

#define NONBLOCK_TIM_X                        (TIM1)
#define NONBLOCK_TIM_HANDLE                   (&htim1)
#define NONBLOCK_TIM_UPDATE_VALUE             (65536)
/**************************************************************************** */
typedef struct
{
	uint8_t enable;
	uint8_t interrupt_cnt_start;
	uint16_t interrupt_cnt;
	void (*func)(void);

}NONBLOCK_ValueStructure;
/***************************************************************************** */
void NONBLOCK_Init(NONBLOCK_ValueStructure* nonblock);
void NONBLOCK_TIM_Overflow(NONBLOCK_ValueStructure* nonblock, TIM_HandleTypeDef *htim); //在溢出中断回调中使用
void NONBLOCK_Start(NONBLOCK_ValueStructure* nonblock); //启用非阻塞延迟执行函数 该函数不会影响中断服务中的其他函数
void NONBLOCK_Stop(NONBLOCK_ValueStructure* nonblock); //停用非阻塞延迟执行函数 该函数不会影响中断服务中的其他函数
void NONBLOCK_Delay(NONBLOCK_ValueStructure* nonblock, uint16_t delayms); //非阻塞延迟delayms后执行nonblock.func函数;

// /* 溢出中断回调 */
// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
// {
//     NONBLOCK_TIM_Overflow(&nonblock, htim);
// }

// /*example*/
// void do_something(void)
// {
// 	//do something
//	NONBLOCK_Stop(); //只执行一次
// }
// while(1)
// {
//	nonblock.func = do_something;
// 	NONBLOCK_Delay(&nonblock, 1000);
//	NONBLOCK_Start();
// 	do_otherthing();
// }

#endif

