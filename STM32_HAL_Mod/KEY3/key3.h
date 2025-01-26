#ifndef KEY3_H
#define KEY3_H

#include "stm32f1xx_hal.h"

#define KEY3_GPIO_Port     GPIOA
#define KEY3_Pin      GPIO_PIN_1

#define LONG_CLICK_COUNT        (50)
#define MAX_PRESS_TIME_COUNT    (100)

uint8_t KEY3_GetValue(void);
//return key value: 0(default) or 1(single) or 2(double) or 3(long)

#endif

/* example */
/*  
    switch(KEY3_GetValue())
    {
        case 1 : HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
    }
*/

