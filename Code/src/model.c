#include "global.h"
#include "model.h"

void player_set_aim_direction(struct Player *player, int direction) {
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
}
