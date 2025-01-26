#ifndef KEY4X4_H
#define KEY4X4_H

#include "stm32f1xx_hal.h"

#define Raw1_GPIO_Port       GPIOA
#define Raw1_Pin        GPIO_PIN_0 //gpio output high level

#define Raw2_GPIO_Port       GPIOA
#define Raw2_Pin        GPIO_PIN_1 //gpio output high level

#define Raw3_GPIO_Port       GPIOA
#define Raw3_Pin        GPIO_PIN_2 //gpio output high level

#define Raw4_GPIO_Port       GPIOA
#define Raw4_Pin        GPIO_PIN_3 //gpio output high level

#define Column1_GPIO_Port    GPIOA
#define Column1_Pin     GPIO_PIN_4 //gpio input pull up

#define Column2_GPIO_Port    GPIOA
#define Column2_Pin     GPIO_PIN_5 //gpio input pull up

#define Column3_GPIO_Port    GPIOA
#define Column3_Pin     GPIO_PIN_6 //gpio input pull up

#define Column4_GPIO_Port    GPIOA
#define Column4_Pin     GPIO_PIN_7 //gpio input pull up

uint8_t KEY4X4_GetValue(void);
//return key value: 0(default) or 1~16(key value)

#endif

/* example */
/*  
    switch(KEY4X4_GetValue())
    {
        case 1 : HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);break;
    }
*/
