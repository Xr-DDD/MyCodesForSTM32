#ifndef MUSIC_H
#define MUSIC_H

#define MAX_NOTE_NUMBER (1024)

typedef struct _Muisc
{
	char* name;
    char* author;
    unsigned char bpm;
	char note[MAX_NOTE_NUMBER];
	char pitch[MAX_NOTE_NUMBER];
	char duration[MAX_NOTE_NUMBER];
} Music;

/*
***about note***
note == 1(do) or 2(re) or 3(mi) or ...;
***about pitch***
pitch == 1(-1 octave) or 2(normal) or 3(+1 octave) or 4(+2 octave);
***about duration***
60000/bpm == a_beat; a_beat/4*duration[note_position];
duration == 4(a_beat) or 2(half_beat) or 1(quarter_beat) or ...;
*/

#endif

