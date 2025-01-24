#ifndef _MPU6050_H_
#define _MPU6050_H_

#include "stm32f1xx_hal.h"
/* 移植时需要修改的I2C接口 ***************************************************************************************************/
#define MPU6050_I2C_HANDLE             (&hi2c1)
extern I2C_HandleTypeDef                hi2c1;
/*********************************************************************************************************/
#define MPU6050_SAMPLE_INTERVAL         (0.005)
/* MPU6050 REG MAP ******************************************************************************************/
#define MPU6050_SLAVE_ADDR          (0xd0)

#define MPU6050_SMPLRT_DIV          (0x19) //设置ADC采样率 采样率分频器 采样率=1000/(采样率分频系数+1)
#define MPU6050_CONFIG              (0x1a)
#define MPU6050_GYRO_CONFIG         (0x1b) //设置陀螺仪量程
#define MPU6050_ACCEL_CONFIG        (0x1c) //设置加速度计量程
#define MPU6050_FIFO_EN             (0x23)

#define MPU6050_ACCEL_XOUT_H        (0x3b)
#define MPU6050_ACCEL_XOUT_L        (0x3c)
#define MPU6050_ACCEL_YOUT_H        (0x3d)
#define MPU6050_ACCEL_YOUT_L        (0x3e)
#define MPU6050_ACCEL_ZOUT_H        (0x3f)
#define MPU6050_ACCEL_ZOUT_L        (0x40)
#define MPU6050_TEMP_OUT_H          (0x41)
#define MPU6050_TEMP_OUT_L          (0x42)
#define MPU6050_GYRO_XOUT_H         (0x43)
#define MPU6050_GYRO_XOUT_L         (0x44)
#define MPU6050_GYRO_YOUT_H         (0x45)
#define MPU6050_GYRO_YOUT_L         (0x46)
#define MPU6050_GYRO_ZOUT_H         (0x47)
#define MPU6050_GYRO_ZOUT_L         (0x48)

#define MPU6050_USER_CTRL           (0x6a)
#define MPU6050_PWR_MGMT_1          (0x6b) //PowerManagement1 电源管理寄存器1 管理复位和唤醒等
#define MPU6050_PWR_MGMT_2          (0x6c) //PowerManagement2 电源管理寄存器2 管理加速度计和陀螺仪是否启用等
#define MPU6050_FIFO_COUNT_H        (0x72)
#define MPU6050_FIFO_COUNT_L        (0x73)
#define MPU6050_FIFO_R_W            (0x74)
#define MPU6050_WHO_AM_I            (0x75) //从该寄存器读到的值应该是ox70
/* MPU6050 STRUCT ****************************************************************************************/
/*加速度计(accel)参数：测量沿xyz轴方向上的加速度*/
typedef struct{
    float x;
    float y;
    float z;
    int16_t ox;
    int16_t oy;
    int16_t oz;
}_accel;
/*陀螺仪(gyro)参数：测量绕xyz轴转动的角速度*/
typedef struct{
    float x;
    float y;
    float z;
    int16_t ox;
    int16_t oy;
    int16_t oz;
}_gyro;
/*MPU6050检测值包括：加速度计，陀螺仪，温度传感器，最后算出欧拉角*/
typedef struct{
    _accel accel;
    _gyro gyro;
    float temp;
    uint16_t otemp;
    float pitch;
    float roll;
    float yaw;
}MPU6050_ValueStructure;
/* 移植时需要修改的通信函数 *******************************************************************************/
void MPU6050_WriteReg(uint8_t reg_addr, uint8_t byte);
uint8_t MPU6050_ReadReg(uint8_t reg_addr);
void MPU6050_WriteMultiReg(uint8_t fst_reg_addr, uint8_t* p_byte, uint8_t byte_size);
void MPU6050_ReadMultiReg(uint8_t fst_reg_addr, uint8_t* p_byte, uint8_t byte_size);
void MPU6050_Delay(uint8_t delayms);
/****************************************************************************************************/
void MPU6050_Init(void);
uint8_t MPU6050_Check(void);
void MPU6050_GetOriginData(MPU6050_ValueStructure* p_mpu6050_value);
void MPU6050_GetResult(MPU6050_ValueStructure* p_mpu6050_value);

#endif


