#ifndef MUSIC_QIMEIDI_H
#define MUSIC_QIMEIDI_H
#include "stm32f1xx_hal.h"

#define qimeidi_PATH_TIME (60*1000/125) //125 path per min
#define qimeidi_pTIME (qimeidi_PATH_TIME/4)

extern uint8_t music_qimeidi_tone_level[];

extern uint8_t music_qimeidi_tone_name[];

extern uint8_t music_qimeidi_time_path[];//qimeidi_pTIME*music_qimeidi_time_path[i]

#endif
