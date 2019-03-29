#ifndef MODEL_ZS
#define MODEL_ZS

#define PLAYER_START_X 200
#define PLAYER_START_Y 200
#define PLAYER_START_HEALTH 70
#define PLAYER_START_SPEED 0
#define PLAYER_START_MAX_SPEED 3
#define PLAYER_START_MAGAZINE 4
#define PLAYER_START_MAX_MAGAZINE 8
#define PLAYER_START_MAX_AMMO 40
#define PLAYER_START_AIM_DIRECTION 0
#define PLAYER_START_MOVE_DIRECTION 0
#define PLAYER_START_STEP 0
#define PLAYER_START_SCORE 0;

#define ZOMBIE_START_HEALTH 1
#define ZOMBIE_START_SPEED 1
#define ZOMBIE_START_MAX_SPEED 3
#define ZOMBIE_START_STRENGTH 3
#define ZOMBIE_START_DIRECTION 0
#define ZOMBIE_START_STEP 0

#define GAME_START_WAVE 1
#define GAME_START_OVER false

#define ZOMBIES_PER_WAVE_NUMBER 2

#define ABSOLUTE_MAX_ZOMBIES 400
#define ABSOLUTE_MAX_BULLETS 100

extern const int bullet_shooting_pos[8][2];

struct Game {
    int wave;
    bool over;
};


struct Player {
    int position_x;
    int position_y;
    int health;
    unsigned int speed;
    unsigned int max_speed;
    int magazine;
    int ammo;
    int max_ammo;
    int max_magazine;
    unsigned int aim_direction;
    unsigned int move_direction;
    unsigned int step;
    int score;
};


struct Bullet {
    int position_x;
    int position_y;
    unsigned int direction;
    bool hit;
};

struct Cross {
    int position_x;
    int position_y;
};

struct Zombie {
    int position_x;
    int position_y;
    unsigned int health;
    unsigned int speed;
    unsigned int max_speed;
    int strength;
    unsigned int direction;
    unsigned int step;
};

struct GameModel {
    struct Game *game;
    struct Player *player;
    struct Cross *cross;
    struct Zombies *zombies[ABSOLUTE_MAX_ZOMBIES];
    struct Bullets *bullets[ABSOLUTE_MAX_BULLETS];
    int current_zombie_index;
    int current_bullet_index;

};

void start_game(struct GameModel *game_model);
int game_wave(struct GameModel *game_model);
void game_next_wave(struct GameModel *game_model);
void game_over(struct GameModel *game_model);
bool is_game_over(struct GameModel *game_model);

void player_spawn(struct Player *player);
void zombie_spawn(struct Zombie *zombie);

void player_update_postion(struct GameModel *game_model);
void player_set_aim_direction(struct GameModel *game_model);
void player_set_move_direction(struct GameModel *game_model, int direction);
void player_set_step(struct GameModel *game_model);
void player_set_speed(struct GameModel *game_model, int speed);
void player_take_damage(struct GameModel *game_model, int damage);
void player_reload(struct GameModel *game_model);
void player_max_ammo(struct GameModel *game_model);
void player_score(struct GameModel *game_model);
bool player_alive(struct GameModel *game_model);

void zombie_update_position(struct Zombie *zombie);
void zombie_set_speed(struct Zombie *zombie, int speed);
void zombie_set_strength(struct Zombie *zombie, int strength);
void zombie_take_damage(struct Zombie * zombie, int damage );
void zombie_set_direction(struct Zombie * zombie, struct Player *player);
bool zombie_alive(struct Zombie *zombie);
void zombie_set_step(struct Zombie *zombie);

void bullet_shoot(struct Bullet *bullet, struct Player *player);
bool bullet_update_position(struct Bullet *bullet);
void cross_set_position(struct Cross *cross, int x, int y);
void detect_collisions(struct GameModel *game_model);
bool collided (int x1, int y1, int h1, int w1, int x2, int y2, int h2, int w2);
#endif
