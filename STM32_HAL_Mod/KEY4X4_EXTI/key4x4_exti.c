#include "key4x4_exti.h"

void KEY4X4_EXTI_Loop_Delayms(uint32_t nms)
{
  uint32_t i=8000*nms;
  while(i--);
}

uint8_t KEY4X4_EXTI_GetValue(uint16_t GPIO_Pin)
{
    uint8_t key_value=0;
    if(GPIO_Pin==Raw1_Pin)
    {
        KEY4X4_EXTI_Loop_Delayms(20);
        if(HAL_GPIO_ReadPin(Raw1_GPIO_Port,Raw1_Pin)==GPIO_PIN_RESET){
            
            HAL_GPIO_WritePin(Column1_GPIO_Port,Column1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(Column2_GPIO_Port,Column2_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(Column3_GPIO_Port,Column3_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(Column4_GPIO_Port,Column4_Pin,GPIO_PIN_SET);
            
            HAL_GPIO_WritePin(Column1_GPIO_Port,Column1_Pin,GPIO_PIN_RESET);
            if(HAL_GPIO_ReadPin(Raw1_GPIO_Port,Raw1_Pin)==GPIO_PIN_RESET){

                key_value=1;
            }
            HAL_GPIO_WritePin(Column2_GPIO_Port,Column2_Pin,GPIO_PIN_RESET);
            if(HAL_GPIO_ReadPin(Raw1_GPIO_Port,Raw1_Pin)==GPIO_PIN_RESET){

                key_value=2;
            }
            HAL_GPIO_WritePin(Column3_GPIO_Port,Column3_Pin,GPIO_PIN_RESET);
            if(HAL_GPIO_ReadPin(Raw1_GPIO_Port,Raw1_Pin)==GPIO_PIN_RESET){

                key_value=3;
            }
            HAL_GPIO_WritePin(Column4_GPIO_Port,Column4_Pin,GPIO_PIN_RESET);
            if(HAL_GPIO_ReadPin(Raw1_GPIO_Port,Raw1_Pin)==GPIO_PIN_RESET){

                key_value=4;
            }
            
        while(HAL_GPIO_ReadPin(Raw1_GPIO_Port,Raw1_Pin)==GPIO_PIN_RESET);
        }
    }
        
    if(GPIO_Pin==Raw2_Pin)
    {
        KEY4X4_EXTI_Loop_Delayms(20);
        if(HAL_GPIO_ReadPin(Raw2_GPIO_Port,Raw2_Pin)==GPIO_PIN_RESET){
            
            HAL_GPIO_WritePin(Column1_GPIO_Port,Column1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(Column2_GPIO_Port,Column2_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(Column3_GPIO_Port,Column3_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(Column4_GPIO_Port,Column4_Pin,GPIO_PIN_SET);
            
            HAL_GPIO_WritePin(Column1_GPIO_Port,Column1_Pin,GPIO_PIN_RESET);
            if(HAL_GPIO_ReadPin(Raw2_GPIO_Port,Raw2_Pin)==GPIO_PIN_RESET){

                key_value=5;
            }
            HAL_GPIO_WritePin(Column2_GPIO_Port,Column2_Pin,GPIO_PIN_RESET);
            if(HAL_GPIO_ReadPin(Raw2_GPIO_Port,Raw2_Pin)==GPIO_PIN_RESET){

                key_value=6;
            }
            HAL_GPIO_WritePin(Column3_GPIO_Port,Column3_Pin,GPIO_PIN_RESET);
            if(HAL_GPIO_ReadPin(Raw2_GPIO_Port,Raw2_Pin)==GPIO_PIN_RESET){

                key_value=7;
            }
            HAL_GPIO_WritePin(Column4_GPIO_Port,Column4_Pin,GPIO_PIN_RESET);
            if(HAL_GPIO_ReadPin(Raw2_GPIO_Port,Raw2_Pin)==GPIO_PIN_RESET){

                key_value=8;
            }
            
        while(HAL_GPIO_ReadPin(Raw2_GPIO_Port,Raw2_Pin)==GPIO_PIN_RESET);
        }
    }
        
    if(GPIO_Pin==Raw3_Pin)
    {
        KEY4X4_EXTI_Loop_Delayms(20);
        if(HAL_GPIO_ReadPin(Raw3_GPIO_Port,Raw3_Pin)==GPIO_PIN_RESET){
            
            HAL_GPIO_WritePin(Column1_GPIO_Port,Column1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(Column2_GPIO_Port,Column2_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(Column3_GPIO_Port,Column3_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(Column4_GPIO_Port,Column4_Pin,GPIO_PIN_SET);
            
            HAL_GPIO_WritePin(Column1_GPIO_Port,Column1_Pin,GPIO_PIN_RESET);
            if(HAL_GPIO_ReadPin(Raw3_GPIO_Port,Raw3_Pin)==GPIO_PIN_RESET){

                key_value=9;
            }
            HAL_GPIO_WritePin(Column2_GPIO_Port,Column2_Pin,GPIO_PIN_RESET);
            if(HAL_GPIO_ReadPin(Raw3_GPIO_Port,Raw3_Pin)==GPIO_PIN_RESET){

                key_value=10;
            }
            HAL_GPIO_WritePin(Column3_GPIO_Port,Column3_Pin,GPIO_PIN_RESET);
            if(HAL_GPIO_ReadPin(Raw3_GPIO_Port,Raw3_Pin)==GPIO_PIN_RESET){

                key_value=11;
            }
            HAL_GPIO_WritePin(Column4_GPIO_Port,Column4_Pin,GPIO_PIN_RESET);
            if(HAL_GPIO_ReadPin(Raw3_GPIO_Port,Raw3_Pin)==GPIO_PIN_RESET){

                key_value=12;
            }
            
        while(HAL_GPIO_ReadPin(Raw3_GPIO_Port,Raw3_Pin)==GPIO_PIN_RESET);
        }
    }
        
    if(GPIO_Pin==Raw4_Pin)
    {
        KEY4X4_EXTI_Loop_Delayms(20);
        if(HAL_GPIO_ReadPin(Raw4_GPIO_Port,Raw4_Pin)==GPIO_PIN_RESET){
            
            HAL_GPIO_WritePin(Column1_GPIO_Port,Column1_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(Column2_GPIO_Port,Column2_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(Column3_GPIO_Port,Column3_Pin,GPIO_PIN_SET);
            HAL_GPIO_WritePin(Column4_GPIO_Port,Column4_Pin,GPIO_PIN_SET);
            
            HAL_GPIO_WritePin(Column1_GPIO_Port,Column1_Pin,GPIO_PIN_RESET);
            if(HAL_GPIO_ReadPin(Raw4_GPIO_Port,Raw4_Pin)==GPIO_PIN_RESET){

                key_value=13;
            }
            HAL_GPIO_WritePin(Column2_GPIO_Port,Column2_Pin,GPIO_PIN_RESET);
            if(HAL_GPIO_ReadPin(Raw4_GPIO_Port,Raw4_Pin)==GPIO_PIN_RESET){

                key_value=14;
            }
            HAL_GPIO_WritePin(Column3_GPIO_Port,Column3_Pin,GPIO_PIN_RESET);
            if(HAL_GPIO_ReadPin(Raw4_GPIO_Port,Raw4_Pin)==GPIO_PIN_RESET){

                key_value=15;
            }
            HAL_GPIO_WritePin(Column4_GPIO_Port,Column4_Pin,GPIO_PIN_RESET);
            if(HAL_GPIO_ReadPin(Raw4_GPIO_Port,Raw4_Pin)==GPIO_PIN_RESET){

                key_value=16;
            }
            
        while(HAL_GPIO_ReadPin(Raw4_GPIO_Port,Raw4_Pin)==GPIO_PIN_RESET);
        }
    }
    return key_value;
}
	

