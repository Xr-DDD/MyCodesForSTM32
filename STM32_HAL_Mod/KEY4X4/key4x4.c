#include "key4x4.h"

uint8_t KEY4X4_GetValue(void)
{
    uint8_t key_value=0;
    HAL_GPIO_WritePin(Raw1_GPIO_Port,Raw1_Pin,GPIO_PIN_RESET);

        if(HAL_GPIO_ReadPin(Column1_GPIO_Port,Column1_Pin)==GPIO_PIN_RESET){
        HAL_Delay(20);
        if(HAL_GPIO_ReadPin(Column1_GPIO_Port,Column1_Pin)==GPIO_PIN_RESET){
        
            key_value=1;

        while(HAL_GPIO_ReadPin(Column1_GPIO_Port,Column1_Pin)==GPIO_PIN_RESET);
        }
        }

        if(HAL_GPIO_ReadPin(Column2_GPIO_Port,Column2_Pin)==GPIO_PIN_RESET){
        HAL_Delay(20);
        if(HAL_GPIO_ReadPin(Column2_GPIO_Port,Column2_Pin)==GPIO_PIN_RESET){
            
            key_value=2;
            
        while(HAL_GPIO_ReadPin(Column2_GPIO_Port,Column2_Pin)==GPIO_PIN_RESET);
        }
        }

        if(HAL_GPIO_ReadPin(Column3_GPIO_Port,Column3_Pin)==GPIO_PIN_RESET){
        HAL_Delay(20);
        if(HAL_GPIO_ReadPin(Column3_GPIO_Port,Column3_Pin)==GPIO_PIN_RESET){
            
            key_value=3;
            
        while(HAL_GPIO_ReadPin(Column3_GPIO_Port,Column3_Pin)==GPIO_PIN_RESET);
        }
        }

        if(HAL_GPIO_ReadPin(Column4_GPIO_Port,Column4_Pin)==GPIO_PIN_RESET){
        HAL_Delay(20);
        if(HAL_GPIO_ReadPin(Column4_GPIO_Port,Column4_Pin)==GPIO_PIN_RESET){
            
            key_value=4;
            
        while(HAL_GPIO_ReadPin(Column4_GPIO_Port,Column4_Pin)==GPIO_PIN_RESET);
        }
        }

    HAL_GPIO_WritePin(Raw1_GPIO_Port,Raw1_Pin,GPIO_PIN_SET);

    HAL_GPIO_WritePin(Raw2_GPIO_Port,Raw2_Pin,GPIO_PIN_RESET);

        if(HAL_GPIO_ReadPin(Column1_GPIO_Port,Column1_Pin)==GPIO_PIN_RESET){
        HAL_Delay(20);
        if(HAL_GPIO_ReadPin(Column1_GPIO_Port,Column1_Pin)==GPIO_PIN_RESET){
        
            key_value=5;

        while(HAL_GPIO_ReadPin(Column1_GPIO_Port,Column1_Pin)==GPIO_PIN_RESET);
        }
        }

        if(HAL_GPIO_ReadPin(Column2_GPIO_Port,Column2_Pin)==GPIO_PIN_RESET){
        HAL_Delay(20);
        if(HAL_GPIO_ReadPin(Column2_GPIO_Port,Column2_Pin)==GPIO_PIN_RESET){
            
            key_value=6;
            
        while(HAL_GPIO_ReadPin(Column2_GPIO_Port,Column2_Pin)==GPIO_PIN_RESET);
        }
        }

        if(HAL_GPIO_ReadPin(Column3_GPIO_Port,Column3_Pin)==GPIO_PIN_RESET){
        HAL_Delay(20);
        if(HAL_GPIO_ReadPin(Column3_GPIO_Port,Column3_Pin)==GPIO_PIN_RESET){
            
            key_value=7;
            
        while(HAL_GPIO_ReadPin(Column3_GPIO_Port,Column3_Pin)==GPIO_PIN_RESET);
        }
        }

        if(HAL_GPIO_ReadPin(Column4_GPIO_Port,Column4_Pin)==GPIO_PIN_RESET){
        HAL_Delay(20);
        if(HAL_GPIO_ReadPin(Column4_GPIO_Port,Column4_Pin)==GPIO_PIN_RESET){
            
            key_value=8;
            
        while(HAL_GPIO_ReadPin(Column4_GPIO_Port,Column4_Pin)==GPIO_PIN_RESET);
        }
        }

    HAL_GPIO_WritePin(Raw2_GPIO_Port,Raw2_Pin,GPIO_PIN_SET);

    HAL_GPIO_WritePin(Raw3_GPIO_Port,Raw3_Pin,GPIO_PIN_RESET);

        if(HAL_GPIO_ReadPin(Column1_GPIO_Port,Column1_Pin)==GPIO_PIN_RESET){
        HAL_Delay(20);
        if(HAL_GPIO_ReadPin(Column1_GPIO_Port,Column1_Pin)==GPIO_PIN_RESET){
        
            key_value=9;

        while(HAL_GPIO_ReadPin(Column1_GPIO_Port,Column1_Pin)==GPIO_PIN_RESET);
        }
        }

        if(HAL_GPIO_ReadPin(Column2_GPIO_Port,Column2_Pin)==GPIO_PIN_RESET){
        HAL_Delay(20);
        if(HAL_GPIO_ReadPin(Column2_GPIO_Port,Column2_Pin)==GPIO_PIN_RESET){
            
            key_value=10;
            
        while(HAL_GPIO_ReadPin(Column2_GPIO_Port,Column2_Pin)==GPIO_PIN_RESET);
        }
        }

        if(HAL_GPIO_ReadPin(Column3_GPIO_Port,Column3_Pin)==GPIO_PIN_RESET){
        HAL_Delay(20);
        if(HAL_GPIO_ReadPin(Column3_GPIO_Port,Column3_Pin)==GPIO_PIN_RESET){
            
            key_value=11;
            
        while(HAL_GPIO_ReadPin(Column3_GPIO_Port,Column3_Pin)==GPIO_PIN_RESET);
        }
        }

        if(HAL_GPIO_ReadPin(Column4_GPIO_Port,Column4_Pin)==GPIO_PIN_RESET){
        HAL_Delay(20);
        if(HAL_GPIO_ReadPin(Column4_GPIO_Port,Column4_Pin)==GPIO_PIN_RESET){
            
            key_value=12;
            
        while(HAL_GPIO_ReadPin(Column4_GPIO_Port,Column4_Pin)==GPIO_PIN_RESET);
        }
        }

    HAL_GPIO_WritePin(Raw3_GPIO_Port,Raw3_Pin,GPIO_PIN_SET);

    HAL_GPIO_WritePin(Raw4_GPIO_Port,Raw4_Pin,GPIO_PIN_RESET);

        if(HAL_GPIO_ReadPin(Column1_GPIO_Port,Column1_Pin)==GPIO_PIN_RESET){
        HAL_Delay(20);
        if(HAL_GPIO_ReadPin(Column1_GPIO_Port,Column1_Pin)==GPIO_PIN_RESET){
        
            key_value=13;

        while(HAL_GPIO_ReadPin(Column1_GPIO_Port,Column1_Pin)==GPIO_PIN_RESET);
        }
        }

        if(HAL_GPIO_ReadPin(Column2_GPIO_Port,Column2_Pin)==GPIO_PIN_RESET){
        HAL_Delay(20);
        if(HAL_GPIO_ReadPin(Column2_GPIO_Port,Column2_Pin)==GPIO_PIN_RESET){
            
            key_value=14;
            
        while(HAL_GPIO_ReadPin(Column2_GPIO_Port,Column2_Pin)==GPIO_PIN_RESET);
        }
        }

        if(HAL_GPIO_ReadPin(Column3_GPIO_Port,Column3_Pin)==GPIO_PIN_RESET){
        HAL_Delay(20);
        if(HAL_GPIO_ReadPin(Column3_GPIO_Port,Column3_Pin)==GPIO_PIN_RESET){
            
            key_value=15;
            
        while(HAL_GPIO_ReadPin(Column3_GPIO_Port,Column3_Pin)==GPIO_PIN_RESET);
        }
        }

        if(HAL_GPIO_ReadPin(Column4_GPIO_Port,Column4_Pin)==GPIO_PIN_RESET){
        HAL_Delay(20);
        if(HAL_GPIO_ReadPin(Column4_GPIO_Port,Column4_Pin)==GPIO_PIN_RESET){
            
            key_value=16;
            
        while(HAL_GPIO_ReadPin(Column4_GPIO_Port,Column4_Pin)==GPIO_PIN_RESET);
        }
        }

    HAL_GPIO_WritePin(Raw4_GPIO_Port,Raw4_Pin,GPIO_PIN_SET);
    return key_value;
}

