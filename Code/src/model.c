#include "global.h"
#include "player_b.h"
#include "zombie_b.h"
#include "model.h"

#include <stdio.h>
#include <osbind.h>
#include <linea.h>

#include <math.h>
#include <stdlib.h>

const int bullet_shooting_pos[8][2] = {
                       15,0, /* N  */
                       9,2,  /* NW */
                       8,8,  /* W  */
                       10,13,/* SW */
                       15,10,/* S  */
                       18,13,/* SE */
                       21,8, /* E  */
                       20,2  /* NE */
    };

void player_spawn(struct Player *player) {
    player->position_x = PLAYER_START_X;
    player->position_y = PLAYER_START_Y;
    player->health = PLAYER_START_HEALTH;
    player->speed = PLAYER_START_SPEED;
    player->max_speed = PLAYER_START_MAX_SPEED;
    player->magazine = PLAYER_START_MAGAZINE;
    player->max_magazine = PLAYER_START_MAX_MAGAZINE;
    player->aim_direction = PLAYER_START_AIM_DIRECTION;
    player->move_direction = PLAYER_START_MOVE_DIRECTION;
    player->step = PLAYER_START_STEP;
}

void zombie_spawn(struct Zombie *zombie) {
    zombie->position_x = (rand() % 640);
    zombie->position_y = -32;
    zombie->health = ZOMBIE_START_HEALTH;
    zombie->speed = ZOMBIE_START_SPEED;
    zombie->max_speed = ZOMBIE_START_MAX_SPEED;
    zombie->strength = ZOMBIE_START_STRENGTH;
    zombie->direction = ZOMBIE_START_DIRECTION;
    zombie->step = ZOMBIE_START_STEP;
}

void player_update_postion(struct Player *player) {
    if (player->speed > 0) {
        switch ( player->move_direction ) {
        case MOVE_W:
            player->position_x--;
            break;
        case MOVE_N:
            player->position_y--;
            break;
        case MOVE_E:
            player->position_x++;
            break;
        case MOVE_S:
            player->position_y++;
            break;
        }
    }
}
void player_set_aim_direction(struct Player *player, struct Cross *cross) {
    int delta_x = cross->position_x - player->position_x;
    int delta_y = player->position_y - cross->position_y;
    int direction = LOOK_E;

    bool steep = abs(delta_y) > abs(delta_x * 2);
    bool shallow = abs(delta_x) > abs(delta_y * 2);
    bool upwards = delta_y > 0;
    bool right = delta_x > 0;
    bool dy_gt_0 = delta_y > 0;
    bool dx_gt_0 = delta_x > 0;
    if ( steep ) {
        if (upwards)
            direction = LOOK_N;
        else {
            direction = LOOK_S;
        }
    } else if (shallow) {
        if (right) {
            direction = LOOK_E;
        } else {
            direction = LOOK_W;
        }
    } else {
        if ( delta_x < 0 && delta_y < 0 ) {
            direction = LOOK_SW;
        } else if ( delta_x < 0 && delta_y > 0 ) {
            direction = LOOK_NW;
        } else if ( delta_x > 0 && delta_y > 0 ) {
            direction = LOOK_NE;
        } else {
            direction = LOOK_SE;
        }
    }

    player->aim_direction = direction;
}

void player_set_move_direction(struct Player *player, int direction) {
    player->move_direction = direction;
}

void player_set_speed(struct Player *player, int speed) {
    if( speed <= player->max_speed ) {
        player->speed = speed;
    }
}

bool player_take_damage(struct Player *player, int damage) {
    bool dead = false;
    if ( player->health <= damage ) {
        dead = true;
        player->health = 0;
    } else {
        player->health =- damage;
    }
    return dead;
}

void player_reload(struct Player *player) {
    unsigned int ammo_needed;
    ammo_needed = player->max_magazine - player->magazine;
    if ( ammo_needed > 0 ) {
        player->magazine += ammo_needed;
        player->ammo =- ammo_needed;
    }
}

void player_max_ammo(struct Player *player) {
    player->ammo = player->max_ammo;
}

void player_set_step(struct Player *player) {
    if(player->speed > 0) {
        if(player->step == PLAYER_TOTAL_STEPS - 1) {
            player->step = 0;
        } else {
            player->step = player->step + 1;
        }
    } else {
        player->step = PLAYER_STEPS_STOP_NUMBER;
    }
}

void zombie_set_speed(struct Zombie *zombie, int speed){
    if(speed <= zombie->max_speed){
      zombie->speed = speed;
    }
}

void zombie_update_position(struct Zombie *zombie) {
    if (zombie->speed > 0) {
        switch ( zombie->direction ) {
        case Z_MOVE_W:
            zombie->position_x = zombie->position_x - 1;
            break;
        case Z_MOVE_N:
            zombie->position_y = zombie->position_y - 1;
            break;
        case Z_MOVE_E:
            zombie->position_x = zombie->position_x + 1;
            break;
        case Z_MOVE_S:
            zombie->position_y = zombie->position_y + 1;
            break;
        }
    }
}
void zombie_strength(struct Zombie *zombie, int strength){
    zombie->strength = strength;
}

bool zombie_take_damage(struct Zombie * zombie, int damage ){
  bool dead = false;
    if(zombie->health <= damage){
        dead = true;
        zombie->health = 0;
    } else {
        zombie->health -= damage;
    }
    return dead;
}

void zombie_set_direction(struct Zombie * zombie, struct Player *player) {
    int delta_x = player->position_x - zombie->position_x;
    int delta_y = zombie->position_y - player->position_y;
    int direction = LOOK_E;

    bool steep = abs(delta_y) > abs(delta_x * 2);
    bool shallow = abs(delta_x) > abs(delta_y * 2);
    bool upwards = delta_y > 0;
    bool right = delta_x > 0;
    bool dy_gt_0 = delta_y > 0;
    bool dx_gt_0 = delta_x > 0;
    if ( steep ) {
        if (upwards)
            direction = Z_MOVE_N;
        else {
            direction = Z_MOVE_S;
        }
    } else {
        if (right) {
            direction = Z_MOVE_E;
        } else {
            direction = Z_MOVE_W;
        }
    }

    zombie->direction = direction;
}

void zombie_set_step(struct Zombie *zombie) {
    if(zombie->speed > 0) {
        if(zombie->step == ZOMBIE_TOTAL_STEPS - 1) {
            zombie->step = 0;
        } else {
            zombie->step = zombie->step + 1;
        }
    } else {
        zombie->step = ZOMBIE_STEPS_STOP_NUMBER;
    }
}

void misc_set_postion(struct Misc_Obj *obj, int x, int y) {
    obj->position_x = x;
    obj->position_y = y;
}

void misc_set_index(struct Misc_Obj *obj, int index) {
    obj->index = index;
}

void cross_set_position(struct Cross *cross, int x, int y) {
    cross->position_x = x;
    cross->position_y = y;
}

void bullet_shoot(struct Bullet *bullet, struct Player *player) {
    if(player->magazine > 0 ) {
        bullet->position_x =
            player->position_x
            + bullet_shooting_pos[player->aim_direction][0];
        bullet->position_y =
            player->position_y
            + bullet_shooting_pos[player->aim_direction][1];
        bullet->direction = player->aim_direction;
        bullet->hit = false;
        player->magazine = player->magazine - 1;
    }
}
bool bullet_update_position(struct Bullet *bullet) {
    switch ( bullet->direction ) {
    case LOOK_N:
        bullet->position_y = bullet->position_y - 1;
        break;
    case LOOK_NW:
        bullet->position_x = bullet->position_x - 1;
        bullet->position_y = bullet->position_y - 1;
        break;
    case LOOK_W:
        bullet->position_x = bullet->position_x - 1;
        break;
    case LOOK_SW:
        bullet->position_x = bullet->position_x - 1;
        bullet->position_y = bullet->position_y + 1;
        break;
    case LOOK_S:
        bullet->position_y = bullet->position_y + 1;
        break;
    case LOOK_SE:
        bullet->position_x = bullet->position_x + 1;
        bullet->position_y = bullet->position_y + 1;
        break;
    case LOOK_E:
        bullet->position_x = bullet->position_x + 1;
        break;
    case LOOK_NE:
        bullet->position_x = bullet->position_x + 1;
        bullet->position_y = bullet->position_y - 1;
        break;
    }
    return ( bullet->position_y < 0 || bullet->position_x < 0 || bullet->hit );
}

void detect_collisions(struct Bullet *bullets[],
                       struct Zombie *zombies[],
                       struct Player *player,
                       int total_b, int total_z) {
    int i;
    int j;

    for ( i = 0; i < total_z; i++ ) {
        if (player->position_x <= zombies[i]->position_x + 20 &&
            player->position_x + 18 >= zombies[i]->position_x &&
            player->position_y <= zombies[i]->position_y + 24 &&
            19 + player->position_y >= zombies[i]->position_y) {
            player_take_damage(player,zombies[i]->strength);
        }

        for (j = 0; j < total_b; j++ ) {
            if (bullets[j] != NULL) {
                if (bullets[j]->position_x <= zombies[i]->position_x + 20 &&
                    bullets[j]->position_x + 1 >= zombies[i]->position_x &&
                    bullets[j]->position_y <= zombies[i]->position_y + 24 &&
                    1 + bullets[j]->position_y >= zombies[i]->position_y) {
                    zombie_take_damage(zombies[i],1);
                    bullets[j]->hit = true;
                }
            }
        }
    }
}
