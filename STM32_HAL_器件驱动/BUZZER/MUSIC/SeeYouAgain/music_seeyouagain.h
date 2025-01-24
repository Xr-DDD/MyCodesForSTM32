#ifndef MUSIC_SEEYOUAGAIN_H
#define MUSIC_SEEYOUAGAIN_H
#include "stm32f1xx_hal.h"

#define seeyouagain_PATH_TIME (60*1000/96) //96 path per min
#define seeyouagain_pTIME (seeyouagain_PATH_TIME/4)

extern uint8_t music_seeyouagain_tone_level[];

extern uint8_t music_seeyouagain_tone_name[];

extern uint8_t music_seeyouagain_time_path[];//seeyouagain_pTIME*music_seeyouagain_time_path[i]

#endif
