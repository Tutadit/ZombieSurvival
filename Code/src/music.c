#include "global.h"
#include "music.h"
#include "psg.h"
#include "main.h"

/* Music By Ernesto Lozano */
const int song[SONG_SIZE] = {
                             a_NOTE,
                             C_NOTE,
                             F_NOTE,
                             C_NOTE,
                             a_NOTE,
                             E_NOTE,
                             F_NOTE,
                             G_NOTE};

const int song_note_length[SONG_SIZE] = {
                                                QUARTER_NOTE,
                                                HALF_NOTE,
                                                QUARTER_NOTE,
                                                HALF_NOTE,
                                                QUARTER_NOTE,
                                                HALF_NOTE,
                                                QUARTER_NOTE,
                                                HALF_NOTE
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
    if (volume_down >= VOLUME_DOWN_FREQUENCY) {
        volume--;
        set_volume(CHANNEL_A,volume);
        reset_timer(&volume_down);
    }
    if ( tempo >= song_note_length[note] ) {
        volume = 0xF;
        note++;
        if ( note >= SONG_SIZE ) {
            note = 0;
        }
        set_volume(CHANNEL_A,volume);
        set_tone(CHANNEL_A,song[note]);
        reset_timer(&tempo);
    }

    set_tone(CHANNEL_A,song[note]);
}
