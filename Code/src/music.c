#include "global.h"
#include "music.h"
<<<<<<< HEAD
#inlude "sound.h"

int notes[12] = {
  478,  // c Flat
  451,  // C Sharp
  426,  // d Flat
  402,  // D Sharp
  379,  // e Flat
  358,  // f Flat
  338,  // F Sharp
  319,  // g Flat
  301,  // G Sharp
  284,  // a Flat
  268,  // D Sharp
  253   // b Flat
}
void start_music(){
  UINT8 data = 0xD5D;
  write_psg(0,data);
}
void update_music(UINT32 time_elapsed){

=======
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
>>>>>>> 4817757ff4351ca69ef375dc288a3f9e69b69911
}
