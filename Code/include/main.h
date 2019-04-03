#ifndef MAIN_GAME_ZS
#define MAIN_GAME_ZS

#include "global.h"
#include "model.h"

#define PLAYER_UPDATE_FREQUENCY 1
#define ZOMBIE_UPDATE_FREQUENCY 10
#define BULLET_UPDATE_FREQUENCY 0


#define BUFFER_SPACE 32256

extern bool render_request;

extern int player_timer;
extern int zombie_timer;
extern int bullet_timer;

extern UINT32 *back_buffer;
extern UINT32 *tmp;
extern UINT8 buffer_space[BUFFER_SPACE];

void initital_setup();
void do_vbl_isr();

void handle_input();
void handle_keyboard_input();
void handle_mouse_input();

void main_menu();
void reset_timer(int *timer);
void game();
void update_cursor();
void update_bullets();
bool update_player();
bool update_zombies();


void update_player_timed();
void update_zombies_timed();

void shoot();
void render_game();
void render_zombies();
void render_bullets();

#endif
