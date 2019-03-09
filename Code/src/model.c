#include "global.h"
#include "player_b.h"
#include "model.h"

#include <stdio.h>
#include <osbind.h>
#include <linea.h>

#include <math.h>

void player_set_postion(struct Player *player, int x, int y) {
    player->position_x = x;
    player->position_y = y;
}
void player_set_aim_direction(struct Player *player,
                              int mouse_x,
                              int mouse_y) {

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
        if(player->step == 2) {
            player->step = 0;
        } else {
            player->step = player->step + 1;
        }
    } else {
        player->step = 0;
    }
}

void zombie_set_speed(struct Zombie *zombie, int speed){
    if(speed <= zombie->max_speed){
      zombie->speed = speed;
    }
}

void zombie_set_position(struct Zombie *zombie, int x, int y) {
    zombie->position_x = x;
    zombie->position_y = y;
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

void zombie_set_direction(struct Zombie * zombie, int direction) {
    zombie->direction = direction;
}

void zombie_set_step(struct Zombie *zombie) {
    zombie->step = 0;
}

void misc_set_postion(struct Misc_Obj *obj, int x, int y) {
    obj->position_x = x;
    obj->position_y = y;
}

void misc_set_index(struct Misc_Obj *obj, int index) {
    obj->index = index;
}
