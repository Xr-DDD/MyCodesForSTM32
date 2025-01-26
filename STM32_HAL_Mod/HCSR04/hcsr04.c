#include "hcsr04.h"

static void HCSR04_Delayus(uint16_t nus) // 72MHz
{
    while (nus--)
    {
        for (uint8_t i = 0; i < 8; i++)
            ;
    }
}

void HCSR04_Delayms(uint16_t nms)
{
    HAL_Delay(nms);
}

void HCSR04_Start(void)
{
    HAL_GPIO_WritePin(HCSR04_TRIG_GPIO_Port, HCSR04_TRIG_Pin, GPIO_PIN_RESET); // Trig置低
    HAL_TIM_Base_Start_IT(HCSR04_TIM_HANDLE);
    HAL_TIM_IC_Start_IT(HCSR04_TIM_HANDLE, HCSR04_TIM_CHANNEL_1);
    HAL_TIM_IC_Start_IT(HCSR04_TIM_HANDLE, HCSR04_TIM_CHANNEL_2);
}

void HCSR04_Stop(void)
{
    HAL_TIM_Base_Stop_IT(HCSR04_TIM_HANDLE);
    HAL_TIM_IC_Stop_IT(HCSR04_TIM_HANDLE, HCSR04_TIM_CHANNEL_1);
    HAL_TIM_IC_Stop_IT(HCSR04_TIM_HANDLE, HCSR04_TIM_CHANNEL_2);
}

void HCSR04_TIM_Overflow(HCSR04_ValueStructure *hcsr04, TIM_HandleTypeDef *htim) // 在溢出中断回调中使用
{
    if (HCSR04_TIM_X == htim->Instance)
    {
        if ((*hcsr04).capture_isbusy)
        {
            (*hcsr04).update_cnt++;
        }

        if ((*hcsr04).update_cnt > 2) // 捕获超时
        {
            (*hcsr04).capture_isbusy = 0;
            (*hcsr04).update_cnt = 0;
            (*hcsr04).capture_rising_edge = 0;
            (*hcsr04).capture_falling_edge = 0;
            (*hcsr04).pulse_width = 0;
            (*hcsr04).distance = -1; // 捕获超时
        }
    }
}

void HCSR04_TIM_InputCapture(HCSR04_ValueStructure *hcsr04, TIM_HandleTypeDef *htim) // 在捕获中断回调中使用
{
    if (HCSR04_TIM_X == htim->Instance)
    {
        if (HCSR04_HAL_TIM_ACTIVE_CHANNEL_1 == htim->Channel) // 捕获上升沿
        {
            (*hcsr04).capture_rising_edge = HAL_TIM_ReadCapturedValue(HCSR04_TIM_HANDLE, HCSR04_TIM_CHANNEL_1);
            (*hcsr04).capture_isbusy = 1; // 定时器溢出计数开启
        }
        else if (HCSR04_HAL_TIM_ACTIVE_CHANNEL_2 == htim->Channel) // 捕获下降沿
        {
            if ((*hcsr04).capture_isbusy) // 如果已经捕获了上升沿 捕获成功
            {
                (*hcsr04).capture_isbusy = 0; // 定时器溢出计数停止
                (*hcsr04).capture_falling_edge = HAL_TIM_ReadCapturedValue(HCSR04_TIM_HANDLE, HCSR04_TIM_CHANNEL_2);
                (*hcsr04).pulse_width = (*hcsr04).update_cnt * HCSR04_TIM_UPDATE_VALUE + (*hcsr04).capture_falling_edge - (*hcsr04).capture_rising_edge;
                (*hcsr04).update_cnt = 0;
                (*hcsr04).distance = (*hcsr04).pulse_width * 0.017f; // 捕获成功
            }
            else // 没捕获到上升沿 捕获出错
            {
                (*hcsr04).capture_isbusy = 0;
                (*hcsr04).update_cnt = 0;
                (*hcsr04).capture_rising_edge = 0;
                (*hcsr04).capture_falling_edge = 0;
                (*hcsr04).pulse_width = 0;
                (*hcsr04).distance = -2; // 捕获出错
            }
        }
    }
}

void HCSR04_SendTrig(void)
{
    // 发送Trig信号
    HAL_GPIO_WritePin(HCSR04_TRIG_GPIO_Port, HCSR04_TRIG_Pin, GPIO_PIN_SET);
    HCSR04_Delayus(12);
    HAL_GPIO_WritePin(HCSR04_TRIG_GPIO_Port, HCSR04_TRIG_Pin, GPIO_PIN_RESET);
}

/************************************************************************************************************* */
static void SildingWindow(float arr_window[], uint8_t n, float data)
{
    if (data != arr_window[n - 1])
    {
        for (uint8_t i = 0; i < n - 1; i++)
        {
            arr_window[i] = arr_window[i + 1];
        }
        arr_window[n - 1] = data;
    }
}

static void ShellSort(float arr_origin[], float arr_order[], uint8_t n)
{
    for (uint8_t i = 0; i < n; i++)
    {
        arr_order[i] = arr_origin[i];
    }
    for (uint8_t gap = n / 2; gap > 0; gap /= 2)
    {
        for (uint8_t i = 0; i < n; i++)
        {
            uint8_t temp = arr_order[i];
            uint8_t j;
            for (j = i; j >= gap && arr_order[j - gap] > temp; j -= gap)
            {
                arr_order[j] = arr_order[j - gap];
            }
            arr_order[j] = temp;
        }
    }
}

static float MedianFilter(float arr_order[], uint8_t n)
{
    float result = 0;
    for (uint8_t i = n / 4 + 1; i < n * 3 / 4 + 1; i++)
    {
        result += arr_order[i];
    }
    result /= (n / 2);
    return result;
}
/************************************************************************************************************* */
static float distance_origin[HCSR04_FLITER_SIZE] = {0};
static float distance_order[HCSR04_FLITER_SIZE] = {0};
void HCSR04_GetDistance_Proc(HCSR04_ValueStructure *hcsr04) // 放在循环中连续检测距离
{
    HCSR04_SendTrig();
    SildingWindow(distance_origin, HCSR04_FLITER_SIZE, (*hcsr04).distance);
    if (distance_origin[HCSR04_FLITER_SIZE - 1] != 0)
    {
        ShellSort(distance_origin, distance_order, HCSR04_FLITER_SIZE);
        (*hcsr04).distance_avg = MedianFilter(distance_order, HCSR04_FLITER_SIZE);
    }
}

void HCSR04_ClearHistory(HCSR04_ValueStructure *hcsr04) // 删除历史记录 防止之前的数据影响接下来的检测
{
    for(uint8_t i = 0; i < HCSR04_FLITER_SIZE; i++)
    {
        distance_origin[i] = 0;
        distance_order[i] = 0;
    }
    (*hcsr04).distance = 0;
    (*hcsr04).distance_avg = 0;

}



