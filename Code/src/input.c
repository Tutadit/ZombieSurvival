#include <osbind.h>
#include "global.h"
#include "input.h"

volatile UINT8 * const MIDI_CONTROL = 0xFFFC04;
volatile UINT8 * const IKBD_control = 0xFFFC00;
volatile const UINT8 * const IKBD_status = 0xFFFC00;
volatile const UINT8 * const IKBD_RDR = 0xFFFC02;

UINT8 * MFP_in_service_b = 0xFFFA11;

SCANCODE scan_buffer[ZS_BUFFER_SIZE] = {0};
int sb_front = 0;
int sb_rear = -1;
int sb_fill_level = 0;

bool w_down = false;
bool a_down = false;
bool s_down = false;
bool d_down = false;
bool m_left_pressed = false;

int cursor_position_x = 0;
int cursor_position_y = 0;
bool mouse_left_button = false;

bool mouse_packet = false;
int mouse_state = 0;

bool sb_isEmpty() {
   return sb_fill_level == 0;
}

bool sb_isFull() {
   return sb_fill_level == ZS_BUFFER_SIZE;
}

int sb_size() {
   return sb_fill_level;
}

void sb_push(SCANCODE code) {
   if(!sb_isFull()) {

      if(sb_rear == ZS_BUFFER_SIZE-1) {
         sb_rear = -1;
      }

      scan_buffer[++sb_rear] = code;
      sb_fill_level++;
   }
}

SCANCODE sb_pop() {
    SCANCODE code = scan_buffer[sb_front++];
    int old_mask;
    long old_ssp;
    old_ssp = Super(0);
    old_mask = set_ipl(IKBD_MASK);
    Super(old_ssp);
    if(sb_front == ZS_BUFFER_SIZE) {
        sb_front = 0;
    }

    sb_fill_level--;
    old_ssp = Super(0);
    set_ipl(old_mask);
    Super(old_ssp);
    return code;
}

bool mouse_left_status() {
    return mouse_left_button;
}

int cursor_x() {
    if (cursor_position_x < 0 ) {
        cursor_position_x = 0;
    } else if (cursor_position_x > 640) {
        cursor_position_x = 640;
    }
    return cursor_position_x;
}

int cursor_y() {
    if (cursor_position_y < 0 ) {
        cursor_position_y = 0;
    } else if (cursor_position_y > 400) {
        cursor_position_y = 400;
    }
    return cursor_position_y;
}

bool keys_to_read() {
    return !sb_isEmpty();
}

SCANCODE read_key() {
    return sb_pop();
}

void disable_midi() {
    long old_ssp = Super(0);
    *MIDI_CONTROL = DISABLE_INTERRUPT;
    Super(old_ssp);
}

void do_kbd_isr() {
    SCANCODE scancode;
    M_POS pos;
    if ( *IKBD_status & RDR_FULL ) {
        if(mouse_packet) {
            pos = *(M_POS *) IKBD_RDR;
            if (mouse_state) {
                cursor_position_y += (int) pos;
                mouse_state = 0;
                mouse_packet = false;
            } else {
                cursor_position_x += (int) pos;
                mouse_state = 1;
            }
        } else {
            scancode = *IKBD_RDR;
            if ((scancode >> 3) == 0x1F) {
                mouse_packet = true;
                mouse_left_button = scancode & M_LEFT;
            } else {
                sb_push(scancode);
            }
        }
    }
    *MFP_in_service_b &= MFP_CLEAR;
}
