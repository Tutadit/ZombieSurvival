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

#endif
