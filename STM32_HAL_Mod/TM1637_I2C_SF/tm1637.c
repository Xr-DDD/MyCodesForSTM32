#include "tm1637.h"

#define waitack_delayus (10)

static const uint8_t Mode[]=
{
    0x40,//mode0 addr auto add
    0x44,//mode1 addr manu add
};
static const uint8_t Addr[]=
{
    0xC0,//adress0
    0xC1,//adress1
    0xC2,//daress2
    0xC3,//adress3
    0xC4,//adress4
    0xC5,//adress5
};
static const uint8_t Data[]=
{
    0x3F,//0
    0x06,//1
    0x5B,//2
    0x4F,//3
    0x66,//4
    0x6D,//5
    0x7D,//6
    0x07,//7
    0x7F,//8
    0x6F,//9
    0x00,//dark
};

//TM1637_SendByte(Data[x]);
static const uint8_t DisplayCtrl[]=
{
    0x80,//display0
    0x88,//display1
    0x89,//display2
    0x8A,//display3
    0x8B,//display4
    0x8C,//display5
    0x8D,//display6
    0x8E,//display7
    0x8F,//display8
};

static void tm1637_delayus(uint16_t nus)//72MHz
{
    while(nus--)
    {
        for(uint8_t i = 0; i < 8; i++);
    }
}

static void TM1637_Start()
{
    TM1637_SCL_H();
    TM1637_SDA_H();
    TM1637_SDA_L();
    TM1637_SCL_L();
}

static void TM1637_Stop()
{
    TM1637_SCL_L();
    TM1637_SDA_L();
    TM1637_SCL_H();
    TM1637_SDA_H();
}

static void TM1637_WaitAck()
{
  TM1637_SCL_L();
  tm1637_delayus(waitack_delayus);
  TM1637_SCL_H();
  TM1637_SCL_L();    
}

static void TM1637_SendByte(uint8_t byte)
{
    for(uint8_t i = 0; i < 8; i++)
  {
    TM1637_SCL_L();
    if(byte & 0x01) // 低位在前,与普通IIC的高位在前的传输顺序不同
    {
      TM1637_SDA_H();
    }else{
      TM1637_SDA_L();
    }
    byte >>= 1;
    TM1637_SCL_H();
  }
}

void TM1637_ShowNum(uint16_t num, uint8_t brigthness)
{
  TM1637_Start();
  TM1637_SendByte(Mode[0]);
  TM1637_WaitAck();
  TM1637_Stop();

  TM1637_Start();
  TM1637_SendByte(Addr[0]);
  TM1637_WaitAck();
  TM1637_SendByte(Data[num/1000%10]);
  TM1637_WaitAck();
  TM1637_SendByte(Data[num/100%10]);
  TM1637_WaitAck();
  TM1637_SendByte(Data[num/10%10]);
  TM1637_WaitAck();
  TM1637_SendByte(Data[num/1%10]);
  TM1637_WaitAck();
  TM1637_SendByte(Data[0]);
  TM1637_WaitAck();
  TM1637_SendByte(Data[0]);
  TM1637_WaitAck();
  TM1637_Stop();

  TM1637_Start();
  TM1637_SendByte(DisplayCtrl[brigthness]);
  TM1637_WaitAck();
  TM1637_Stop();
}




