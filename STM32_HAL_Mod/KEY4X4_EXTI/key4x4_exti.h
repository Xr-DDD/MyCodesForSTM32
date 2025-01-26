#ifndef KEY4X4_EXTI_H
#define KEY4X4_EXTI_H

#include "stm32f1xx_hal.h"

#define Raw1_GPIO_Port       GPIOA
#define Raw1_Pin        GPIO_PIN_0 //exti input falling edge pull up

#define Raw2_GPIO_Port       GPIOA
#define Raw2_Pin        GPIO_PIN_1 //exti input falling edge pull up

#define Raw3_GPIO_Port       GPIOA
#define Raw3_Pin        GPIO_PIN_2 //exti input falling edge pull up

#define Raw4_GPIO_Port       GPIOA
#define Raw4_Pin        GPIO_PIN_3 //exti input falling edge pull up

#define Column1_GPIO_Port    GPIOA
#define Column1_Pin     GPIO_PIN_4 //gpio output low level

#define Column2_GPIO_Port    GPIOA
#define Column2_Pin     GPIO_PIN_5 //gpio output low level

#define Column3_GPIO_Port    GPIOA
#define Column3_Pin     GPIO_PIN_6 //gpio output low level

#define Column4_GPIO_Port    GPIOA
#define Column4_Pin     GPIO_PIN_7 //gpio output low level

//NVIC ENABLE ON
uint8_t KEY4X4_EXTI_GetValue(uint16_t GPIO_Pin);
//return key value: 0(default) or 1~16(key value)
void KEY4X4_EXTI_Loop_Delayms(uint32_t nms);

#endif

/* example */
/*  USER CODE BEGIN PFP */
/*
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch(KEY4X4_EXTI_GetValue(GPIO_Pin))
	{
		case 1 : HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);break;
	}
}
*/
/* USER CODE END PFP */


