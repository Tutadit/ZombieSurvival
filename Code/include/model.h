/*
 * Model Data for Zombie Survival
 *
 */
#ifndef MODEL_ZS
#define MODEL_ZS

#include "misc_b.h"
#include "global.h"

/* Default Player Values */
#define PLAYER_START_X 200
#define PLAYER_START_Y 200
#define PLAYER_START_HEALTH 70
#define PLAYER_START_MOVING false
#define PLAYER_START_MAGAZINE 4
#define PLAYER_START_MAX_MAGAZINE 8
#define PLAYER_START_MAX_AMMO 40
#define PLAYER_START_AIM_DIRECTION 0
#define PLAYER_START_MOVE_DIRECTION 0
#define PLAYER_START_STEP 0
#define PLAYER_START_SCORE 0

/* Default Zombie Values */
#define ZOMBIE_START_HEALTH 1
#define ZOMBIE_START_MOVING true
#define ZOMBIE_START_MAX_SPEED 3
#define ZOMBIE_START_STRENGTH 3
#define ZOMBIE_START_DIRECTION 0
#define ZOMBIE_START_STEP 0

/* Default Game value */
#define GAME_START_WAVE 1
#define GAME_START_OVER false
#define ZOMBIES_PER_WAVE_NUMBER 2 /* Dificulty Level */

/* Max numbers for static arrays */
#define ABSOLUTE_MAX_ZOMBIES 100
#define ABSOLUTE_MAX_BULLETS 30

/* Location for survive button */
#define MM_SURVIVE_X 288
#define MM_SURVIVE_Y 190

/* Bullet position offsets, based on shooting direction */
extern const int bullet_shooting_pos[8][2];

struct Game {
    int wave;
    bool over;
};

/* Player Structure:
 *
 * Ammo and Magazine:
 *     The player magazine is the amount of ammunition currently
 *     in the gun. max_magazine is the capacity of ammunition of
 *     the gun. Ammo is the total ammunition the player is holding
 *     that is not in the gun. max_ammo is the maximum amount of
 *     ammunition that the player can hold.
 *
 * Aim and move direction and ste:
 *     The player graphics consist of two bitmaps: upper body
 *     and lower body. The upper body is set by aim_direction and
 *     lower body is set by move direction and step. See player_b.h
 *     for more details.
 */
struct Player {
    int position_x;
    int position_y;
    int health;
    int magazine;
    int score;
    int ammo;
    int max_ammo;
    int max_magazine;
    bool moving;
    unsigned int aim_direction;
    unsigned int move_direction;
    unsigned int step;
};

struct Zombie {
    int position_x;
    int position_y;
    unsigned int health;
    bool moving;
    int strength;
    unsigned int direction;
    unsigned int step;
};

struct Bullet {
    int position_x;
    int position_y;
    unsigned int direction;
    bool hit;
};

struct Cursor {
    int position_x;
    int position_y;
};

/*
 * A button is a 64-bit bitmap and so it must be
 * divided into 2 32-bit bitmaps.
 */
struct Button {
    const UINT32 *bitmap_a;
    const UINT32 *bitmap_b;
    int position_x;
    int position_y;
    int height;
    bool hover;
};
/*
 * The global game model consisting of all
 * structures required by the game.
 */
struct GameModel {
    struct Button survive;
    struct Game game;
    struct Player player;
    struct Cursor cursor;
    struct Zombie zombies[ABSOLUTE_MAX_ZOMBIES];
    struct Bullet bullets[ABSOLUTE_MAX_BULLETS];
    int current_zombie_index;
    int current_bullet_index;
};

extern struct GameModel game_model;

/*
 * Generates a new button with the provided specs.
 */
void spawn_button(struct Button *button,
                  UINT32 *bitmap_a,
                  UINT32 *bitmap_b,
                  int x, int y);
/*
 * Returns true if the button's hover flag is on.
 */
bool button_hover(struct Button *button);
/*
 * Given the cursor it detects if it collides with the
 * provided button and if so it sets the buttons hover
 * flag. Otherwise it unsets it.
 */
void button_cursor_collision(struct Button *button, struct Cursor *cursor);
/*
 *
 */
void start_game();
/*
 *
 */
int game_wave();
/*
 *
 */
void game_next_wave();
/*
 *
 */
void game_over();
/*
 *
 */
bool is_game_over();
/*
 *
 */
void player_spawn(struct Player *player);
/*
 *
 */
void zombie_spawn(struct Zombie *zombie);
/*
 *
 */
void spawn_zombies();
/*
 *
 */
void player_update_postion();
/*
 *
 */
void player_set_aim_direction();
/*
 *
 */
void player_set_move_direction(int direction);
/*
 *
 */
void player_set_step();
/*
 *
 */
void player_set_moving(bool moving);
/*
 *
 */
void player_take_damage(int damage);
/*
 *
 */
void player_reload();
/*
 *
 */
void player_max_ammo();
/*
 *
 */
void player_score();
/*
 *
 */
bool player_alive();
/*
 *
 */
void zombie_update_position(struct Zombie *zombie);
/*
 *
 */
void zombie_set_moving(struct Zombie *zombie, bool moving);
/*
 *
 */
void zombie_set_strength(struct Zombie *zombie, int strength);
void zombie_take_damage(struct Zombie * zombie, int damage );
void zombie_set_direction(struct Zombie * zombie, struct Player *player);
bool zombie_alive(struct Zombie *zombie);
void zombie_set_step(struct Zombie *zombie);

bool bullet_hit(struct Bullet *bullet);
bool bullet_shoot(struct Bullet *bullet, struct Player *player);
void bullet_update_position(struct Bullet *bullet);
void cursor_set_position(struct Cursor *cursor, int x, int y);
void detect_collisions();
#endif
