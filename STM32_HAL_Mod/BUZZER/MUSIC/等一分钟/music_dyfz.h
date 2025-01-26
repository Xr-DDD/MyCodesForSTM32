#ifndef MUSIC_DYFZ_H
#define MUSIC_DYFZ_H
#include "stm32f1xx_hal.h"

#define dyfz_PATH_TIME (60*1000/80) //80 path per min
#define dyfz_pTIME (dyfz_PATH_TIME/4)

extern uint8_t music_dyfz_tone_level[];

extern uint8_t music_dyfz_tone_name[];

extern uint8_t music_dyfz_time_path[];//dyfz_pTIME*music_dyfz_time_path[i]

#endif
