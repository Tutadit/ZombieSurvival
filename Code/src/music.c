#include "music.h"
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

}
