#include "hc05.h"

void HC05_Transmit(uint8_t* p_tx_buf, uint16_t size)
{
    HAL_UART_Transmit(HC05_UART_HANDLE, p_tx_buf, size, 1000);
}

void HC05_Receive(uint8_t* p_rx_buf, uint16_t size)
{
    HAL_UART_Receive(HC05_UART_HANDLE, p_rx_buf, size, 1000);
}

void HC05_Transmit_IT(uint8_t* p_tx_buf, uint16_t size)
{
    HAL_UART_Transmit_IT(HC05_UART_HANDLE, p_tx_buf, size);
}

void HC05_Receive_IT(uint8_t* p_rx_buf, uint16_t size)
{
    HAL_UART_Receive_IT(HC05_UART_HANDLE, p_rx_buf, size);
}


