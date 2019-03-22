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

#define ZOMBIE_START_HEALTH 1
#define ZOMBIE_START_SPEED 1
#define ZOMBIE_START_MAX_SPEED 3
#define ZOMBIE_START_STRENGTH 3
#define ZOMBIE_START_DIRECTION 0
#define ZOMBIE_START_STEP 0

extern const int bullet_shooting_pos[8][2];
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

struct Misc_Obj {
    int position_x;
    int position_y;
    unsigned int index;
    unsigned int;
};

void player_spawn(struct Player *player);
void zombie_spawn(struct Zombie *zombie);
void player_update_postion(struct Player *player);
void player_set_aim_direction(struct Player *player, struct Cross *cross);
void player_set_move_direction(struct Player *player, int direction);
void player_set_step(struct Player *player);
void player_set_speed(struct Player *player, int speed);
bool player_take_damage(struct Player *player, unsigned int damage);
void player_reload(struct Player *player);
void player_max_ammo(struct Player *player);
void zombie_update_position(struct Zombie *zombie);
void zombie_set_speed(struct Zombie *zombie, int speed);
void zombie_strength(struct Zombie *zombie, int strength);
bool zombie_take_damage(struct Zombie * zombie, int damage );
void zombie_set_direction(struct Zombie * zombie, struct Player *player
                          );
void zombie_set_step(struct Zombie *zombie);
void misc_set_postion(struct Misc_Obj *obj, int x, int y);
void misc_set_index(struct Misc_Obj *obj, int index);
void bullet_shoot(struct Bullet *bullet, struct Player *player);
bool bullet_update_position(struct Bullet *bullet);
void cross_set_position(struct Cross *cross, int x, int y);
void detect_collisions(struct Bullet *bullets[],
                       struct Zombie *zombies[],
                       struct Player *player,
                       int total_b, int total_z);
#endif
