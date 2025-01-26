#include "key3.h"

uint8_t KEY3_GetValue(void)
{
    uint8_t key_value = 0;
    uint16_t time_count = 0;
    
	if(HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == GPIO_PIN_RESET){
	HAL_Delay(50);
	if(HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == GPIO_PIN_RESET)
	{
        key_value = 1;//single click

        while(HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == GPIO_PIN_RESET && time_count < LONG_CLICK_COUNT)
        {
            time_count++;
            HAL_Delay(10);
        }

        if(time_count >= LONG_CLICK_COUNT)
        {
            key_value = 3;//long click
        }
        else
        {	
            while(time_count < LONG_CLICK_COUNT && key_value != 2)
            {
                time_count++;
                HAL_Delay(10);
                if(HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == GPIO_PIN_RESET){
                HAL_Delay(50);
                if(HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == GPIO_PIN_RESET)
                {
                    key_value = 2;//double click
                }
                }
            }
        }
	}
    }
	while(HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin) == GPIO_PIN_RESET && time_count < MAX_PRESS_TIME_COUNT)
    {
        time_count++;
    }
    return key_value;
}

