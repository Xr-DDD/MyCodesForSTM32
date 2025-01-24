#ifndef _HC05_H_
#define _HC05_H_

#include "stm32f1xx_hal.h"

#define HC05_UART_HANDLE    (&huart1)
extern UART_HandleTypeDef   (huart1);

void HC05_Transmit(uint8_t* p_tx_buf, uint16_t size);
void HC05_Receive(uint8_t* p_rx_buf, uint16_t size);
void HC05_Transmit_IT(uint8_t* p_tx_buf, uint16_t size);
void HC05_Receive_IT(uint8_t* p_rx_buf, uint16_t size);

#endif

/*
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
	}
}
*/


