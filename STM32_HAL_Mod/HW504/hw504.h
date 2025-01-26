#ifndef HW504_H
#define HW504_H

#include "stm32f1xx_hal.h"
#include "adc.h"

#define HW504_XY_ADC_HANDLE     (&hadc1)
#define HW504_Z_GPIO_Port       (GPIOA)
#define HW504_Z_Pin             (GPIO_PIN_4)
/********************************************************************** */
typedef struct
{
    uint16_t x;
    uint16_t y;
    uint8_t z;

}HW504_ValueStructure;
/********************************************************************** */
void HW504_GetValue(HW504_ValueStructure* hw504);

#endif


