#include "buzzer.h"

void BUZZER_Start(void)
{
	HAL_TIM_PWM_Start(BUZZER_PWM_TIM_HANDLE, BUZZER_PWM_TIM_CHANNEL);
}

void BUZZER_Stop(void)
{
	HAL_TIM_PWM_Stop(BUZZER_PWM_TIM_HANDLE, BUZZER_PWM_TIM_CHANNEL);
}

void BUZZER_Tone(uint8_t tone_level, uint8_t tone_name, uint16_t time_ms)
{
	uint16_t Hz=0;
	switch(tone_name)
	{
		case 1 : Hz=524;break;
		case 2 : Hz=588;break;
		case 3 : Hz=660;break;
		case 4 : Hz=698;break;
		case 5 : Hz=784;break;
		case 6 : Hz=880;break;
		case 7 : Hz=988;break;
		default : Hz=0;break;
	}
	
	switch(tone_level)
	{
		case 1 : Hz/=4;break;
		case 2 : Hz/=2;break;
		case 3 : break;
		case 4 : Hz*=2;break;
		default : Hz=0;break;
	}

	__HAL_TIM_SetCompare(BUZZER_PWM_TIM_HANDLE, BUZZER_PWM_TIM_CHANNEL, (1+1000000/Hz)/2);//volume
	__HAL_TIM_SetAutoreload(BUZZER_PWM_TIM_HANDLE, 1+1000000/Hz);//tune
	HAL_Delay(time_ms);
}
