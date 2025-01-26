#include "music_maibaoge.h"

uint8_t music_maibaoge_tone_level[]=
{
    2,2,2,
    2,2,2,
    2,2,2,2,2,
    2,2,2,
    2,2,2,2,2,
    2,2,2,
    2,2,2,
    1,2,2,
    2,2,2,
    2,2,2,
    2,2,2,2,
    2,
    2,2,2,2,
    2,2,2,2,
    1,2,2,2,
    2,
    99
};

uint8_t music_maibaoge_tone_name[]=
{
    5,5,5,
    5,5,5,
    3,5,6,5,3,
    2,3,5,
    5,3,5,3,2,
    1,3,2,
    3,3,2,
    6,1,2,
    6,6,5,
    3,6,5,
    5,3,2,3,
    5,
    5,3,2,3,
    5,3,2,3,
    6,1,2,3,
    1,
    99
};

uint8_t music_maibaoge_time_path[]=
{
    2,2,4,
    2,2,4,
    2,2,2,1,1,
    2,2,4,
    2,2,2,1,1,
    2,2,4,
    2,2,4,
    2,2,4,
    4,2,2,
    2,2,4,
    2,2,2,2,
    8,
    2,2,2,2,
    2,2,2,2,
    2,2,2,2,
    8,
    99
};

/*
buzzer_start();
for(uint16_t i = 0; music_maibaoge_tone_level[i] != 99; i++)
{
    buzzer_tone(music_maibaoge_tone_level[i], music_maibaoge_tone_name[i], pTIME*music_maibaoge_time_path[i]);
}
buzzer_stop();
*/


