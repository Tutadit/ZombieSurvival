#include "global.h"
#include "music.h"
#include "psg.h"

const UINT8 song[SONG_SIZE] = {
                                  248,
                                  451,
                                  379,
                                  253,
                                  379
};
int tempo = 0;
int note = 0;
void start_music() {
    enable_channel(CHANNEL_A,true,false);
    set_tone(CHANNEL_A,song[note]);
    set_volume(CHANNEL_A,11);
}

void update_music() {
    if ( note == SONG_SIZE ) {
        note = 0;
    }
    set_tone(CHANNEL_A,song[note]);
}
