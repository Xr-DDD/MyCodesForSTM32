#include "mpu6050.h"
#include "math.h"

static void MPU6050_Delay(uint8_t delayms)
{
    HAL_Delay(delayms);
}
/*********************************************************************************************************/
void MPU6050_WriteReg(uint8_t reg_addr, uint8_t byte)
{
    HAL_I2C_Mem_Write(MPU6050_I2C_HANDLE, MPU6050_SLAVE_ADDR, reg_addr, I2C_MEMADD_SIZE_8BIT, &byte, 1, 1000);
}

uint8_t MPU6050_ReadReg(uint8_t reg_addr)
{
    uint8_t byte;
    HAL_I2C_Mem_Read(MPU6050_I2C_HANDLE, MPU6050_SLAVE_ADDR, reg_addr, I2C_MEMADD_SIZE_8BIT, &byte, 1, 1000);
    return byte;
}

void MPU6050_WriteMultiReg(uint8_t fst_reg_addr, uint8_t* p_byte, uint8_t byte_size)
{
    HAL_I2C_Mem_Write(MPU6050_I2C_HANDLE, MPU6050_SLAVE_ADDR, fst_reg_addr,I2C_MEMADD_SIZE_8BIT, p_byte, byte_size, 1000);
}

void MPU6050_ReadMultiReg(uint8_t fst_reg_addr, uint8_t* p_byte, uint8_t byte_size)
{
    HAL_I2C_Mem_Read(MPU6050_I2C_HANDLE, MPU6050_SLAVE_ADDR, fst_reg_addr,I2C_MEMADD_SIZE_8BIT, p_byte, byte_size, 1000);
}
/*********************************************************************************************************/
void MPU6050_Init(void)
{
    MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x80); //复位
    MPU6050_Delay(100);
    MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x00); //唤醒
    MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x04); //设置采样率为5ms
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x00); //设置加速度计量程为±2g
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18); //设置陀螺仪量程为200°/s
}


uint8_t MPU6050_Check(void)
{
    if(MPU6050_ReadReg(MPU6050_WHO_AM_I) == 0x70)
        return 0;
    else
        return 1;
}


void MPU6050_GetOriginData(MPU6050_ValueStructure* p_mpu6050_value)
{
    uint8_t read_value[14];
    MPU6050_ReadMultiReg(MPU6050_ACCEL_XOUT_H, read_value, 14);
    (*p_mpu6050_value).accel.ox = (((uint16_t)read_value[0] << 8) | read_value[1]);
    (*p_mpu6050_value).accel.oy = (((uint16_t)read_value[2] << 8) | read_value[3]);
    (*p_mpu6050_value).accel.oz = (((uint16_t)read_value[4] << 8) | read_value[5]);
    (*p_mpu6050_value).otemp    = ((uint16_t)(read_value[6] << 8) | read_value[7]);
    (*p_mpu6050_value).gyro.ox  = (((uint16_t)read_value[8] << 8) | read_value[9]);
    (*p_mpu6050_value).gyro.oy  = (((uint16_t)read_value[10] << 8) | read_value[11]);
    (*p_mpu6050_value).gyro.oz  = (((uint16_t)read_value[12] << 8) | read_value[13]);
}

void MPU6050_GetResult(MPU6050_ValueStructure* p_mpu6050_value)
{
    MPU6050_GetOriginData(p_mpu6050_value); //得到原始数据

    (*p_mpu6050_value).accel.x = (*p_mpu6050_value).accel.ox / 16384.0f;
    (*p_mpu6050_value).accel.y = (*p_mpu6050_value).accel.oy / 16384.0f;
    (*p_mpu6050_value).accel.z = (*p_mpu6050_value).accel.oz / 16384.0f;
    (*p_mpu6050_value).temp = (*p_mpu6050_value).otemp / 340.f + 36.53f;
    (*p_mpu6050_value).gyro.x = (*p_mpu6050_value).gyro.ox / 16.4f;
    (*p_mpu6050_value).gyro.y = (*p_mpu6050_value).gyro.oy / 16.4f;
    (*p_mpu6050_value).gyro.z = (*p_mpu6050_value).gyro.oz / 16.4f;

    float pitch_a = -atan2((*p_mpu6050_value).accel.x, (*p_mpu6050_value).accel.z) / 3.141593f *180.0f;
    float roll_a = atan2((*p_mpu6050_value).accel.y, (*p_mpu6050_value).accel.z) / 3.141593f *180.0f;
    float pitch_g = (*p_mpu6050_value).pitch + (*p_mpu6050_value).gyro.y * 0.005f;
    float roll_g = (*p_mpu6050_value).roll + (*p_mpu6050_value).gyro.x * 0.005f;
    float yaw_g = (*p_mpu6050_value).yaw + (*p_mpu6050_value).gyro.z * 0.005f;
    (*p_mpu6050_value).pitch = pitch_g * 0.95238f + pitch_a * (1.0f - 0.95238f);
    (*p_mpu6050_value).roll = roll_g * 0.95238f + roll_a * (1.0f - 0.95238f);
    (*p_mpu6050_value).yaw = yaw_g;

    MPU6050_Delay(MPU6050_SAMPLE_INTERVAL * 1000); //对应选择的采样率
}

/*example*/
/*
    while(1)
    {
        MPU6050_GetResult(&mpu6050_value);
    }
*/
