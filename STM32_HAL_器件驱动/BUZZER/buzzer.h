#ifndef BUZZER_H
#define BUZZER_H

#include "stm32f1xx_hal.h"
#include "tim.h"

#define BUZZER_PWM_TIM_HANDLE  &htim2
#define BUZZER_PWM_TIM_CHANNEL TIM_CHANNEL_2

void BUZZER_Start(void);
void BUZZER_Tone(uint8_t tone_level, uint8_t tone_name, uint16_t time_ms);
void BUZZER_Stop(void);

#endif

/* USER CODE BEGIN 2 */
/*
BUZZER_Start();
for(int i = 0 ; music_tone_level[i] != -1 ; i++)
{
	BUZZER_Tone(music_pitch[i], music_note[i], pTIME*music_duration[i]);
}
BUZZER_Stop();
*/
/* USER CODE END 2 */

