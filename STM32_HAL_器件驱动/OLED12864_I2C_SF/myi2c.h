#ifndef _MY_I2C_H_
#define _MY_I2C_H_

#include "stm32f1xx_hal.h"
/**修改引脚配置*********************************************************************************************/
#define M_I2C_SCL_GPIO_Port    GPIOA
#define M_I2C_SCL_Pin     GPIO_PIN_2
#define M_I2C_SDA_GPIO_Port    GPIOA
#define M_I2C_SDA_Pin     GPIO_PIN_3
/**********************************************************************************************************/
#define M_I2C_SCL_H()     HAL_GPIO_WritePin(M_I2C_SCL_GPIO_Port,M_I2C_SCL_Pin,GPIO_PIN_SET)
#define M_I2C_SCL_L()     HAL_GPIO_WritePin(M_I2C_SCL_GPIO_Port,M_I2C_SCL_Pin,GPIO_PIN_RESET)
#define M_I2C_SDA_H()     HAL_GPIO_WritePin(M_I2C_SDA_GPIO_Port,M_I2C_SDA_Pin,GPIO_PIN_SET)
#define M_I2C_SDA_L()     HAL_GPIO_WritePin(M_I2C_SDA_GPIO_Port,M_I2C_SDA_Pin,GPIO_PIN_RESET)
#define M_I2C_SDA_RD()    HAL_GPIO_ReadPin(M_I2C_SDA_GPIO_Port,M_I2C_SDA_Pin)
/**********************************************************************************************************/
void M_I2C_Start(void);
void M_I2C_Stop(void);
//void M_I2C_WaitAck(void);
void M_I2C_SendByte(uint8_t byte);
void M_I2C_SendAck(uint8_t ack);
uint8_t M_I2C_ReceiveByte(void);
uint8_t M_I2C_ReceiveAck(void);
/**********************************************************************************************************/
void M_I2C_Master_Transimt(uint8_t addr, uint16_t* p_bytes, uint16_t bytes_size);
void M_I2C_Master_Receive(uint8_t addr, uint16_t* p_bytes, uint16_t bytes_size);
void M_I2C_Mem_Write(uint8_t dev_addr, uint8_t mem_addr, uint8_t* p_bytes, uint16_t bytes_size);
void M_I2C_Mem_Read(uint8_t dev_addr, uint8_t mem_addr, uint8_t* p_bytes, uint16_t bytes_size);
#endif


