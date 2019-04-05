#ifndef MAIN_GAME_ZS
#define MAIN_GAME_ZS

#include "global.h"
#include "model.h"
/* Default frequency values. */
#define PLAYER_UPDATE_FREQUENCY 1
#define ZOMBIE_UPDATE_FREQUENCY 10
#define BULLET_UPDATE_FREQUENCY 0

/* Buffer size. */
#define BUFFER_SPACE 32256

extern bool render_request;

extern int player_timer;
extern int zombie_timer;
extern int bullet_timer;

extern UINT32 *back_buffer;
extern UINT32 *tmp;
extern UINT8 buffer_space[BUFFER_SPACE];

/* This function initializes the system, sets the ,
*  video base, MFP, etc.
*
*  @param: none.
*
*  @return: none
*/
void initital_setup();

/* This function handles the synchronous events
*  through the timer.
*
*  @param: none.
*
*  @return: none
*/
void do_vbl_isr();

/* This function handles all input functions.
*
*  @param: none.
*
* @ return: none.
*/
void handle_input();

/* This function handles the keyboard input.
*
*  @param: none.
*
* @ return: none.
*/
void handle_keyboard_input();

/* This function handles the mouse input.
*
*  @param: none.
*
* @ return: none.
*/
void handle_mouse_input();

/* This function displays the menu of the game.
*
*  @param: none.
*
* @ return: none.
*/
void main_menu();

/* This function resets the timer to 0
*
*  @param: none.
*
* @ return: none.
*/
void reset_timer(int *timer);

/* This is the main function of the game. This functions calls
*  Player and zombie frequency.
*  @param: none.
*
* @ return: none.
*/
void game();

/* This function updates the x and y coordinates of
*  the mouse cursor
*
*  @param: none.
*
* @ return: none.
*/
void update_cursor();

/* This function updates the x and y coordinates of
*  the bullet.
*
*  @param: none.
*
* @ return: none.
*/
void update_bullets();

/* This function updates the x and y coordinates of
*  the player.
*
*  @param: none.
*
* @ return: none.
*/
bool update_player();

/* This function updates the x and y coordinates of
*  the zombies.
*
*  @param: none.
*
* @ return: none.
*/
bool update_zombies();

/* This function updates the x and y coordinates of
*  the player based on synchronous events.
*
*  @param: none.
*
* @ return: none.
*/
void update_player_timed();

/* This function updates the x and y coordinates of
*  the zombie based on synchronous events.
*
*  @param: none.
*
* @ return: none.
*/
void update_zombies_timed();

/* This function shoots a bullet.
*
*  @param: none.
*
* @ return: none.
*/
void shoot();

/* This function renders the game to the screen.
*
*  @param: none.
*
* @ return: none.
*/
void render_game();

/* This function renders zombies to the screen.
*
*  @param: none.
*
* @ return: none.
*/
void render_zombies();

/* This function renders bullets to the screen.
*
*  @param: none.
*
* @ return: none.
*/
void render_bullets();

#endif
