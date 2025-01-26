#include "myi2c.h"

/******************************************************************************************************/
void M_I2C_Start()
{
    M_I2C_SDA_H();
    M_I2C_SCL_H();
    M_I2C_SDA_L();
    M_I2C_SCL_L();
}

void M_I2C_Stop()
{
    M_I2C_SDA_L();
    M_I2C_SCL_H();
    M_I2C_SDA_H();
}

// void M_I2C_WaitAck()
// {
//     M_I2C_SCL_H();
//     M_I2C_SCL_L();
// }

void M_I2C_SendByte(uint8_t byte)
{
    for(uint8_t i = 0; i < 8; i++)
    {
        if(byte & 0x80)
        {
            M_I2C_SDA_H();
        }else{
            M_I2C_SDA_L();
        }
        byte <<= 1;
        M_I2C_SCL_H();
        M_I2C_SCL_L();
    }
    M_I2C_SDA_L();
}

void M_I2C_SendAck(uint8_t ack)
{
    if(ack)
    {
        M_I2C_SDA_H();
    }
    else
    {
        M_I2C_SDA_L();
    }
    M_I2C_SCL_H();
    M_I2C_SCL_L();
    M_I2C_SDA_L();
}

uint8_t M_I2C_ReceiveByte(void)
{
    uint8_t byte = 0x00;
    M_I2C_SDA_H();
    for(uint8_t i = 0; i < 8; i++)
    {
        M_I2C_SCL_H();
        if(M_I2C_SDA_RD())
        {
            byte |= 0x01;
        }
        byte <<= 1;
        M_I2C_SCL_L();
    }
    M_I2C_SDA_L();
    return byte;
}

uint8_t M_I2C_ReceiveAck(void)
{
    uint8_t ack = 1;
    M_I2C_SDA_H();
    M_I2C_SCL_H();
    if(M_I2C_SDA_RD())
    {
        ack = 1;
    }
    else
    {
        ack = 0;
    }
    M_I2C_SCL_L();
    M_I2C_SDA_L();
    return ack;
}
/*********************************************************************************************************/
void M_I2C_Master_Transimt(uint8_t addr, uint16_t* p_bytes, uint16_t bytes_size)
{
    M_I2C_Start();
    M_I2C_SendByte(addr);
    //M_I2C_WaitAck();
    if(M_I2C_ReceiveAck())
    {
        M_I2C_Stop();
    }
    uint16_t i;
    for(i = 0; i < bytes_size; i++)
    {    
        M_I2C_SendByte(p_bytes[i]);
        //M_I2C_WaitAck();
        if(M_I2C_ReceiveAck())
        {
            M_I2C_Stop();
        }
    }
    M_I2C_Stop();
}

void M_I2C_Master_Receive(uint8_t addr, uint16_t* p_bytes, uint16_t bytes_size)
{
    M_I2C_Start();
    M_I2C_SendByte(addr);
    //M_I2C_WaitAck();
    if(M_I2C_ReceiveAck())
    {
        M_I2C_Stop();
    }

    M_I2C_Start();
    M_I2C_SendByte(addr | 0x01);
    //M_I2C_WaitAck();
    if(M_I2C_ReceiveAck())
    {
        M_I2C_Stop();
    }
    uint16_t i;
    for(i = 0; i < bytes_size; i++)
    {    
        p_bytes[i] = M_I2C_ReceiveByte();
        //M_I2C_WaitAck();
        if(i < bytes_size - 1)
        {
            M_I2C_SendAck(0);
        }
        else
        {
            M_I2C_SendAck(1);
        }
    }
    M_I2C_Stop();
}

void M_I2C_Mem_Write(uint8_t dev_addr, uint8_t mem_addr, uint8_t* p_bytes, uint16_t bytes_size)
{
    M_I2C_Start();
    M_I2C_SendByte(dev_addr);
    //M_I2C_WaitAck();
    if(M_I2C_ReceiveAck())
    {
        M_I2C_Stop();
    }
    M_I2C_SendByte(mem_addr);
    //M_I2C_WaitAck();
    if(M_I2C_ReceiveAck())
    {
        M_I2C_Stop();
    }
    uint16_t i;
    for(i = 0; i < bytes_size; i++)
    {    
        M_I2C_SendByte(p_bytes[i]);
        //M_I2C_WaitAck();
        if(M_I2C_ReceiveAck())
        {
            M_I2C_Stop();
        }
    }
    M_I2C_Stop();
}

void M_I2C_Mem_Read(uint8_t dev_addr, uint8_t mem_addr, uint8_t* p_bytes, uint16_t bytes_size)
{
    M_I2C_Start();
    M_I2C_SendByte(dev_addr);
    //M_I2C_WaitAck();
    if(M_I2C_ReceiveAck())
    {
        M_I2C_Stop();
    }
    M_I2C_SendByte(mem_addr);
    //M_I2C_WaitAck();
    if(M_I2C_ReceiveAck())
    {
        M_I2C_Stop();
    }

    M_I2C_Start();
    M_I2C_SendByte(dev_addr | 0x01);
    //M_I2C_WaitAck();
    if(M_I2C_ReceiveAck())
    {
        M_I2C_Stop();
    }
    uint16_t i;
    for(i = 0; i < bytes_size; i++)
    {
        p_bytes[i] = M_I2C_ReceiveByte();
        //M_I2C_WaitAck();
        if(i < bytes_size - 1)
        {
            M_I2C_SendAck(0);
        }
        else
        {
            M_I2C_SendAck(1);
        }
    }
    M_I2C_Stop();
}


