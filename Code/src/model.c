#include "global.h"
#include "player_b.h"
#include "model.h"

#include <stdlib.h>
#include <math.h>

void player_set_postion(struct Player *player, int x, int y) {
    player->position_x = x;
    player->position_y = y;
}
void player_set_aim_direction(struct Player *player,
                              int mouse_x,
                              int mouse_y) {
    double delta_x = mouse_x - player->position_x;
    double delta_y = player->position_y - mouse_y;
    double theta_radians = atan2(delta_y,delta_x);
    int direction;
     if (theta_radians <= 0.3926991) {
         direction = LOOK_N;
     } else if (theta_radians < 1.178097) {
         direction = LOOK_NE;
     } else if (theta_radians <= 1.9634954) {
         direction = LOOK_E;
     } else if (theta_radians < 2.7488936) {
         direction = LOOK_SE;
     } else if (theta_radians <= 3.5342917) {
         direction = LOOK_S;
     } else if (theta_radians < 4.3196899) {
         direction = LOOK_SW;
     } else if (theta_radians <= 5.1050881) {
         direction = LOOK_W;
     } else if (theta_radians < 5.8904862) {
         direction = LOOK_NW;
     } else {
         direction = LOOK_N;
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

void zombie_set_speed(struct Zombie *zombie, int speed){
    if(speed <= zombie->max_speed){
      zombie->speed = speed;
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
