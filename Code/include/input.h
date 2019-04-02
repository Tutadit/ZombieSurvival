#ifndef INPUT_ZS
#define INPUT_ZS
#include "global.h"

#define ZS_BUFFER_SIZE 20
#define IKBD_MASK 6

#define VECTOR_KBD 70

#define RDR_FULL 0x01
#define DISABLE_INTERRUPT 0x16
#define BACK_TO_DEF 0x96

#define MFP_CLEAR 0xBF
#define M_LEFT 0x2;

#define W_DOWN 0x11
#define W_UP 0x91
#define A_DOWN 0x1e
#define A_UP 0x9e
#define S_DOWN 0x1F
#define S_UP 0x9F
#define D_DOWN 0x20
#define D_UP 0xA0
#define SP_DOWN 0x39
#define SP_UP 0xB9

typedef UINT8 SCANCODE;
typedef signed char M_POS;

extern bool w_down;
extern bool a_down;
extern bool s_down;
extern bool d_down;
extern bool m_left_pressed;

extern SCANCODE scan_buffer[ZS_BUFFER_SIZE];
extern int sb_front;
extern int sb_rear;
extern int sb_fill_level;

extern int cursor_position_x;
extern int cursor_position_y;
extern bool mouse_left_button;

extern volatile UINT8 * const MIDI_CONTROL;
extern volatile UINT8 * const IKBD_control;
extern volatile const UINT8 * const IKBD_status;
extern volatile const UINT8 * const IKBD_RDR;
extern UINT8 * MFP_in_service_b;

int set_ipl(int mask);
void enable_midi();
void disable_midi();


void kbd_isr();
void do_kbd_isr();

bool sb_isEmpty();
bool sb_isFull();
int sb_size();
void sb_push(SCANCODE code);
SCANCODE sb_pop();
bool keys_to_read();
bool mouse_left_status();
int cursor_x();
int cursor_y();
#endif
