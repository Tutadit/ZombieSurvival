#include "global.h"
#include "music.h"
#inlude "sound.h"
#include "psg.h"


const int song[SONG_SIZE] = {
                               G_NOTE,
                               C_NOTE,
                               C_NOTE,
                               C_NOTE,
                               D_NOTE,
                               E_NOTE,
                               E_NOTE,
                               E_NOTE,
                               D_NOTE
};
int tempo = 0;
int note = 0;
void start_music() {
    enable_channel(CHANNEL_A,true,false);
    set_tone(CHANNEL_A,song[note]);
    set_volume(CHANNEL_A,11);
}

void update_music() {
    if ( tempo >= 25 ) {
        note++;
        if ( note >= SONG_SIZE ) {
            note = 0;
        }

        set_tone(CHANNEL_A,song[note]);
        tempo = 0;
    }

    set_tone(CHANNEL_A,song[note]);
}
