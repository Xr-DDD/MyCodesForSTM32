#include "hx1838.h"

/********************************************************************************* */
uint8_t hx1838_equal(uint16_t width1, uint16_t width2)
{
    if(width1 > width2)
    {
        return (width1 - width2) < 400;
    }
    else
    {
        return (width2 - width1) < 400;
    }
}

void HX1838_Start(void)
{
    HAL_TIM_Base_Start_IT(HX1838_TIM_HANDLE);
    HAL_TIM_IC_Start_IT(HX1838_TIM_HANDLE,HX1838_TIM_CHANNEL_1);
    HAL_TIM_IC_Start_IT(HX1838_TIM_HANDLE,HX1838_TIM_CHANNEL_2);
}

void HX1838_Stop(void)
{
    HAL_TIM_Base_Stop_IT(HX1838_TIM_HANDLE);
    HAL_TIM_IC_Stop_IT(HX1838_TIM_HANDLE,HX1838_TIM_CHANNEL_1);
    HAL_TIM_IC_Stop_IT(HX1838_TIM_HANDLE,HX1838_TIM_CHANNEL_2);
}

void HX1838_Decode(HX1838_ValueStrueture* hx1838)
{
    (*hx1838).rx_data = 0x00;
    if(hx1838_equal((*hx1838).pulse_width[0],9000) && hx1838_equal((*hx1838).pulse_width[1],4500)) //引导码
    {
        for(uint8_t i = 2; i < 2 + 16 + 16; i+=2) //地址码和地址反码
        {
            if(!hx1838_equal((*hx1838).pulse_width[i],560))
            {
                (*hx1838).rx_data = 0xff; //error
            }
        }
        for(uint8_t i = 34,j = 0; i < 34 + 16; i+=2, j++)//数据码
        {
            if(hx1838_equal((*hx1838).pulse_width[i],560) && hx1838_equal((*hx1838).pulse_width[i+1],560)) //0码
            {
                (*hx1838).rx_data &= ~(0x80 >> j);
            }
            else if(hx1838_equal((*hx1838).pulse_width[i],560) && hx1838_equal((*hx1838).pulse_width[i+1],1680)) //1码
            {
                (*hx1838).rx_data |= (0x80 >> j);
            }
            else
            {
                (*hx1838).rx_data = 0xff; //error
            }
        }
        for(uint8_t i = 50; i < 50 + 16; i+=2)//数据反码 未校验
        {
            if(!hx1838_equal((*hx1838).pulse_width[i],560))
            {
                (*hx1838).rx_data = 0xff; //error
            }
        }
    }
}
/************************************************************************************************************************************** */
void HX1838_TIM_Overflow(HX1838_ValueStrueture* hx1838, TIM_HandleTypeDef *htim)
{
    if(HX1838_TIM_X == htim->Instance)
    {
        if((*hx1838).capture_isbusy)
        {
            (*hx1838).update_cnt++;
        }
        if((*hx1838).update_cnt > 2) //捕获超时
        {
            (*hx1838).update_cnt = 0;
            (*hx1838).capture_isbusy = 0;
            (*hx1838).capture_cnt = 0;
        }
    }
}

void HX1838_TIM_InputCapture(HX1838_ValueStrueture* hx1838, TIM_HandleTypeDef *htim)
{
    if(HX1838_TIM_X == htim->Instance)
	{
        if(HX1838_HAL_TIM_ACTIVE_CHANNEL_1 == htim->Channel)
        {
            (*hx1838).capture_value[(*hx1838).capture_cnt] = HAL_TIM_ReadCapturedValue(HX1838_TIM_HANDLE, HX1838_TIM_CHANNEL_1) + (*hx1838).update_cnt * HX1838_TIM_UPDATE_VALUE;
        }
        else if(HX1838_HAL_TIM_ACTIVE_CHANNEL_2 == htim->Channel)
        {
            (*hx1838).capture_value[(*hx1838).capture_cnt] = HAL_TIM_ReadCapturedValue(HX1838_TIM_HANDLE, HX1838_TIM_CHANNEL_2) + (*hx1838).update_cnt * HX1838_TIM_UPDATE_VALUE;
        }

        if((*hx1838).capture_cnt < 66 + 1) 
        {
            (*hx1838).capture_cnt++;
            (*hx1838).capture_isbusy = 1;
        }
        else //捕获完毕
        {
            for((*hx1838).capture_cnt = 0; (*hx1838).capture_cnt < 66; (*hx1838).capture_cnt++)
            {
                (*hx1838).pulse_width[(*hx1838).capture_cnt] = (*hx1838).capture_value[(*hx1838).capture_cnt + 1] - (*hx1838).capture_value[(*hx1838).capture_cnt];
            }
            (*hx1838).update_cnt = 0;
            (*hx1838).capture_isbusy = 0;
            (*hx1838).capture_cnt = 0;
        }
    }
}
