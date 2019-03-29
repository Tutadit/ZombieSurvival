#ifndef MAIN_GAME_ZS
#define MAIN_GAME_ZS
#include "global.h"
#include "model.h"
#define BUFFER_SPACE 32256

#define VECTOR_VBL 28

typedef void (*Vector)();

extern bool render_request;

extern UINT32 *back_buffer;
extern UINT32 *tmp;
extern UINT32 *og_base;
extern UINT8 buffer_space[BUFFER_SPACE];


Vector install_vector(int num, Vector vector);
void vbl_isr();
void do_vbl_isr();

void main_menu(struct MainMenu *menu);
void game();
void end_game();

void update_cursor(struct Cross *cross);
void update_bullets();
bool update_player();
bool update_zombies();

void update_player_timed();
void update_zombies_timed();

void shoot();
void render_game(UINT32 *base);
void render_zombies(UINT32 *base);
void render_bullets(UINT32 *base);
#endif
