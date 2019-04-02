#ifndef ZS_MUSIC
#define ZS_MUSIC
#include "global.h"

#define SONG_SIZE 9

#define c_NOTE 478
#define C_NOTE 451
#define d_NOTE 426
#define D_NOTE 402
#define E_NOTE 379
#define f_NOTE 358
#define F_NOTE 338
#define g_NOTE 319
#define G_NOTE 301
#define a_NOTE 284
#define A_NOTE 268
#define b_NOTE 253

extern const int song[SONG_SIZE];
extern int tempo;
extern int note;

void start_music();
void update_music();
#endif
