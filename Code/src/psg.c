#include "psg.h"

volatile char *PSG_reg_select = 0xFF8800;
volatile char *PSG_reg_write  = 0xFF8802;

void write_psg(int reg, UINT8 val){
  *PSG_reg_select = reg;
  *PSG_reg_write  = val;
}

UINT8 read_psg(int reg){
  reg = (int) *PSG_reg_write;
  return reg;
}

void set_tone(int channel, int tuning){
  write_psg(channel,tuning);
}

void set_volume(int channel, int volume) {
  write_psg(channel, volume);
}

void enable_channel (int channel, int tone_on, int noise_on){
  write_psg(channel,tone_on);
  write_psg(channel,noise_on);
}

void stop_sound(){

}
void set_noise(int tuning){
  *PSG_reg_select = 6;
  *PSG_reg_write  = tuning;
}
void set_envelope(int shape, unsigned int sustain){
  *PSG_reg_select = 0xD;
  *PSG_reg_write  = sustain;
}
