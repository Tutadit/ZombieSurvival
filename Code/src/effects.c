#include "effects.h"
#include "psg.h"

void play_shoot() {
    write_psg(9,0x10);
    enable_channel(CHANNEL_B,false,true);
    set_envelope(PSG_SHAPE_A,0x15);
    set_noise(0x1F);
}

void play_empty() {
    write_psg(9,0x10);
    enable_channel(CHANNEL_B,false,true);
    set_envelope(PSG_SHAPE_A,0x04);
    set_noise(0x1F);
}

void play_bite() {
    write_psg(9,0x10);
    enable_channel(CHANNEL_B,false,true);
    set_noise(0x07);
    set_envelope(PSG_SHAPE_B,0x04);
}
