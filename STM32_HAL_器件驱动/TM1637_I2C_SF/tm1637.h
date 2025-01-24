#ifndef TM1637_H
#define TM1637_H

#include "stm32f1xx_hal.h"
/**修改引脚配置*********************************************************************************************/
#define TM1637_SCL_GPIO_Port    GPIOA
#define TM1637_SCL_Pin     GPIO_PIN_0
#define TM1637_SDA_GPIO_Port    GPIOA
#define TM1637_SDA_Pin     GPIO_PIN_1
/**********************************************************************************************************/
#define TM1637_SCL_H()     HAL_GPIO_WritePin(TM1637_SCL_GPIO_Port,TM1637_SCL_Pin,GPIO_PIN_SET)
#define TM1637_SCL_L()     HAL_GPIO_WritePin(TM1637_SCL_GPIO_Port,TM1637_SCL_Pin,GPIO_PIN_RESET)
#define TM1637_SDA_H()     HAL_GPIO_WritePin(TM1637_SDA_GPIO_Port,TM1637_SDA_Pin,GPIO_PIN_SET)
#define TM1637_SDA_L()     HAL_GPIO_WritePin(TM1637_SDA_GPIO_Port,TM1637_SDA_Pin,GPIO_PIN_RESET)
/**********************************************************************************************************/
void TM1637_ShowNum(uint16_t num, uint8_t brightness); // brihtness: 0 ~ 8;

#endif


