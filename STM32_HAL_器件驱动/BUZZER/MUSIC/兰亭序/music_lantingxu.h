#ifndef MUSIC_LANTINGXU_H
#define MUSIC_LANTINGXU_H
#include "stm32f1xx_hal.h"

#define lantingxu_PATH_TIME (60*1000/80) //80 path per min
#define lantingxu_pTIME (lantingxu_PATH_TIME/4)

extern uint8_t music_lantingxu_tone_level[];

extern uint8_t music_lantingxu_tone_name[];

extern uint8_t music_lantingxu_time_path[];//lantingxu_pTIME*music_lantingxu_time_path[i]

#endif
