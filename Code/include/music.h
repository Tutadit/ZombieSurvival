#ifndef ZS_MUSIC
#define ZS_MUSIC
#include "global.h"

#define SONG_SIZE 5

extern const UINT8 song[SONG_SIZE];
extern int tempo;
extern int note;

void start_music();
void update_music();
#endif
