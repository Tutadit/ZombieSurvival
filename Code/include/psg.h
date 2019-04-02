#ifndef ZS_PSG
#define ZS_PSG
#include "global.h"

#define PSG_SEL_ADR 0xFF8800
#define PSG_DAT_ADR 0xFF8802

#define CHANNEL_A 0
#define CHANNEL_B 1
#define CHANNEL_C 2

#define PSG_SHAPE_A 0x0
#define PSG_SHAPE_B 0x4
#define PSG_SHAPE_C 0x8
#define PSG_SHAPE_D 0x9
#define PSG_SHAPE_E 0xA
#define PSG_SHAPE_F 0xB
#define PSG_SHAPE_G 0xC
#define PSG_SHAPE_H 0xD
#define PSG_SHAPE_I 0xE
#define PSG_SHAPE_J 0xF


extern volatile  UINT8 * const PSG_SEL_P;
extern volatile  UINT8 * const PSG_DAT_P;

void write_psg(int reg, UINT8 val);
UINT8 read_psg(int reg);
void set_tone(int channel, int tuning);
void set_volume(int channel, int volume);
void enable_channel(int channel, bool tone_on, bool noise_on);
void stop_sound();
void set_noise(int tuning);
void set_envelope(int shape, unsigned int sustain);
#endif
