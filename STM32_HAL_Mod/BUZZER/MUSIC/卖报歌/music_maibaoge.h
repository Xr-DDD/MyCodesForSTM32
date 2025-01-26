#ifndef MUSIC_TEST_H
#define MUSIC_TEST_H
#include "stm32f1xx_hal.h"

#define maibaoge_PATH_TIME (60*1000/120) //120 path per min
#define maibaoge_pTIME (PATH_TIME/4)

extern uint8_t music_maibaoge_tone_level[];

extern uint8_t music_maibaoge_tone_name[];

extern uint8_t music_maibaoge_time_path[];//maibaoge_pTIME*music_lantingxu_time_path[i]

#endif
