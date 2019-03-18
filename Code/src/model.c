#include "global.h"
#include "player_b.h"
#include "model.h"

#include <stdio.h>
#include <osbind.h>
#include <linea.h>

#include <math.h>

void player_update_postion(struct Player *player) {
    if (player_speed > 0) {
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
    int mouse_x = cross->position_x;
    int mouse_y = cross->position_y;

    double delta_x = mouse_x - player->position_x + 15;
    double delta_y = player->position_y - mouse_y;

    double angle;
    int direction;

    angle = atan2(delta_y , delta_x);
    if(angle < 0 ) {
        angle+=6.28319;
    }

     if (angle <= 0.3926991) {
         direction = LOOK_E;
     } else if (angle < 1.178097) {
         direction = LOOK_NE;
     } else if (angle <= 1.9634954) {
         direction = LOOK_N;
     } else if (angle < 2.7488936) {
         direction = LOOK_NW;
     } else if (angle <= 3.5342917) {
         direction = LOOK_W;
     } else if (angle < 4.3196899) {
         direction = LOOK_SW;
     } else if (angle <= 5.1050881) {
         direction = LOOK_S;
     } else if (angle < 5.8904862) {
         direction = LOOK_SE;
     } else {
         direction = LOOK_E;
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
    }
    player->health =- damage;
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
    if (zombie_speed > 0) {
        switch ( zombie->direction ) {
        case Z_MOVE_W:
            zombie->position_x--;
            break;
        case Z_MOVE_N:
            zombie->position_y--;
            break;
        case Z_MOVE_E:
            zombie->position_x++;
            break;
        case Z_MOVE_S:
            zombie->position_y++;
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
    }
    zombie->health -= damage;
    return dead;
}

void zombie_set_direction(struct Zombie * zombie, struct Player *player) {
    int player_x = player->position_x;
    int player_y = player->position_y;

    double delta_x = player_x - zombie->position_x + 15;
    double delta_y = zombie->position_y - player_y;

    double angle;
    int direction;
    angle = atan2(delta_y , delta_x);
    if(angle < 0 ) {
        angle+=6.28319;
    }

    if (angle <= 0.3926991) {
        direction = Z_MOVE_E;
    } else if (angle <= 1.9634954) {
        direction = Z_MOVE_N;
    } else if (angle <= 3.5342917) {
        direction = Z_MOVE_W;
    } else if (angle <= 5.1050881) {
        direction = Z_MOVE_S;
    } else {
        direction = Z_MOVE_E;
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

void bullet_set_position(struct Bullet *bullet, int x, int y) {
    bullet->position_x = x;
    bullet->position_y = y;
}
