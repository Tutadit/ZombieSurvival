#ifndef MODEL_ZS
#define MODEL_ZS

struct Player {
    unsigned int position_x;
    unsigned int position_y;
    unsigned int health;
    unsigned int speed;
    unsigned int max_speed;
    unsigned int magazine;
    unsigned int ammo;
    unsigned int max_ammo;
    unsigned int max_magazine;
    unsigned int aim_direction;
    unsigned int move_direction;
    unsigned int step;
};

struct Bullet {
    unsigned int position_x;
    unsigned int position_y;
};

struct Zombie {
    unsigned int position_x;
    unsigned int position_y;
    unsigned int health;
    unsigned int speed;
    unsigned int max_speed;
    unsigned int strength;
    unsigned int direction;
};

void player_set_postion(struct Player *player, int x, int y);
void player_set_aim_direction(struct Player *player,
                              int mouse_x,
                             int mouse_y);

void player_set_move_direction(struct Player *player, int direction);
void player_set_speed(struct Player *player, int speed);
bool player_take_damage(struct Player *player, int damage);
void player_reload(struct Player *player);
void player_max_ammo(struct Player *player);
void zombie_set_speed(struct Zombie *zombie, int speed);
void zombie_strength(struct Zombie *zombie, int strength);
bool zombie_take_damage(struct Zombie * zombie, int damage );

#endif
