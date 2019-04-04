#include <osbind.h>
#include "global.h"
#include "psg.h"

volatile  UINT8 * const PSG_SEL_P = PSG_SEL_ADR;
volatile  UINT8 * const PSG_DAT_P = PSG_DAT_ADR;

void write_psg(int reg, UINT8 val) {
    long old_ssp;
    old_ssp = Super(0);
    *PSG_SEL_P = reg;
    *PSG_DAT_P = val;
    Super(old_ssp);
}

UINT8 read_psg(int reg) {
    long old_ssp = Super(0);
    UINT8 data;
    *PSG_SEL_P = reg;
    data = *PSG_SEL_P;
    Super(old_ssp);
    return data;
}

void set_tone(int channel, UINT tuning) {
    UINT8 fine_tone = (UINT8) tuning;
    UINT8 rough_tone = (tuning >> 8);
    switch(channel) {
    case CHANNEL_A:
        write_psg(0x0, (UINT8) fine_tone);
        write_psg(0x1, (UINT8) rough_tone);
        break;
    case CHANNEL_B:
        write_psg(0x2, (UINT8) fine_tone);
        write_psg(0x3, (UINT8) rough_tone);
        break;
    case CHANNEL_C:
        write_psg(0x4, (UINT8) fine_tone);
        write_psg(0x5, (UINT8) rough_tone);
        break;
    }
}

void set_volume(int channel, int volume) {
    if ( volume >= 0 && volume <= 15 ) {
        switch(channel) {
        case CHANNEL_A:
            write_psg(0x8, volume);
        break;
        case CHANNEL_B:
            write_psg(0x9, volume);
            break;
        case CHANNEL_C:
            write_psg(0xA, volume);
            break;
        }
    }
}

void enable_channel(int channel, bool tone_on, bool noise_on) {
    UINT8 new_setup = read_psg(0x7);
    int tone_bit = 0;
    int noise_bit = 0;
    switch(channel) {
    case CHANNEL_A:
        tone_bit = 3;
        noise_bit = 0;
        break;
    case CHANNEL_B:
        tone_bit = 4;
        noise_bit = 1;
        break;
    case CHANNEL_C:
        tone_bit = 5;
        noise_bit = 2;
        break;
    }
    if ( tone_on ) {
        new_setup |= ( 1UL << tone_bit);
    } else {
        new_setup &= ~( 1UL << tone_bit);
    }
    if ( noise_on ) {
        new_setup |= ( 1UL << noise_bit );
    } else {
        new_setup &= ~( 1UL << noise_bit);
    }
    write_psg(0x7, new_setup);
}

void stop_sound() {
    set_volume(CHANNEL_A,0);
    set_volume(CHANNEL_B,0);
    set_volume(CHANNEL_C,0);
}

void set_noise(int tuning) {
    write_psg(0x6,tuning);
}

void set_envelope(int shape, unsigned int sustain) {
    write_psg(0xC,sustain);
    write_psg(0xD,0x0);
    write_psg(0xD,shape);
}
