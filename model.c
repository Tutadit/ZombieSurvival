#include "model.h"

void player_set_direction(struct Player *player, int direction) {
    player->direction = direction;
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

void player_max_ammo(strcut Player *player) {
    player->ammo = player->max_ammo;
}
