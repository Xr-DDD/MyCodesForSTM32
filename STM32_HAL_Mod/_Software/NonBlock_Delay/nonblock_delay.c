#include "nonblock_delay.h"

void NONBLOCK_Init(NONBLOCK_ValueStructure* nonblock)
{
    HAL_TIM_Base_Start_IT(NONBLOCK_TIM_HANDLE);
    (*nonblock).enable = 0;
    (*nonblock).interrupt_cnt = 0;
    (*nonblock).interrupt_cnt_start = 0;
}

void NONBLOCK_TIM_Overflow(NONBLOCK_ValueStructure* nonblock, TIM_HandleTypeDef *htim) //在溢出中断回调中使用
{
    
    if(NONBLOCK_TIM_X == htim->Instance)
    {
        if((*nonblock).enable)
        {
            if((*nonblock).interrupt_cnt_start)
            {
                (*nonblock).interrupt_cnt++;
            }
        }
    }
}

void NONBLOCK_Start(NONBLOCK_ValueStructure* nonblock) //启用非阻塞延迟执行函数 该函数不会影响中断服务中的其他函数
{
    (*nonblock).enable = 1;
}
void NONBLOCK_Stop(NONBLOCK_ValueStructure* nonblock) //停用非阻塞延迟执行函数 该函数不会影响中断服务中的其他函数
{
    (*nonblock).enable = 0;
}

void NONBLOCK_Delay(NONBLOCK_ValueStructure* nonblock, uint16_t delayms)
{
    if(!(*nonblock).interrupt_cnt_start)
    {
        (*nonblock).interrupt_cnt = 0;
        (*nonblock).interrupt_cnt_start = 1;
    }
    if((*nonblock).interrupt_cnt * NONBLOCK_TIM_UPDATE_VALUE /1000 >= delayms)
    {
        (*nonblock).interrupt_cnt = 0;
        (*nonblock).interrupt_cnt_start = 0;
        (*nonblock).func();
    }
}

