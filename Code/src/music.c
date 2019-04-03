#include "global.h"
#include "music.h"
#include "psg.h"

const int song[SONG_SIZE] = {
                             F_NOTE,
                             a_NOTE,
                             F_NOTE,
                             G_NOTE,
                             C_NOTE,
                             G_NOTE,
                             F_NOTE,
                             a_NOTE,
                             G_NOTE,
                             G_NOTE,
                             F_NOTE,
                             F_NOTE,
                             C_NOTE,
                             G_NOTE,
                             C_NOTE,
                             C_NOTE
};



int tempo = 0;
int volume_down = 0;
int note = 0;
int volume = 0xF;
void start_music() {
    enable_channel(CHANNEL_A,true,false);
    set_tone(CHANNEL_A,song[note]);
    set_volume(CHANNEL_A,volume);
}

void update_music() {
    if (volume_down >= 5) {
        volume--;
        set_volume(CHANNEL_A,volume);
        volume_down = 0;
    }
    if ( tempo >= 20 ) {
        volume = 0xF;
        note++;
        if ( note >= SONG_SIZE ) {
            note = 0;
        }
        set_volume(CHANNEL_A,volume);
        set_tone(CHANNEL_A,song[note]);
        tempo = 0;
    }
}
