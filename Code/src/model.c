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

int game_wave(struct Game *game) {
    return game->wave;
}
void game_next_wave(struct Game *game) {
    game->wave = game->wave + 1;
}
void game_over(struct Game *game) {
    game->over = true;
}
bool is_game_over(struct Game *game) {
    return game->over;
}

void start_game(struct Game *game) {
    game->wave = GAME_START_WAVE;
    game->over = GAME_START_OVER;
}

void player_spawn(struct Player *player) {
    player->position_x = PLAYER_START_X;
    player->position_y = PLAYER_START_Y;
    player->health = PLAYER_START_HEALTH;
    player->speed = PLAYER_START_SPEED;
    player->max_speed = PLAYER_START_MAX_SPEED;
    player->magazine = PLAYER_START_MAGAZINE;
    player->max_ammo = PLAYER_START_MAX_AMMO;
    player->ammo = PLAYER_START_MAX_AMMO;
    player->max_magazine = PLAYER_START_MAX_MAGAZINE;
    player->aim_direction = PLAYER_START_AIM_DIRECTION;
    player->move_direction = PLAYER_START_MOVE_DIRECTION;
    player->step = PLAYER_START_STEP;
    player->score = PLAYER_START_SCORE;
}

void zombie_spawn(struct Zombie *zombie) {
    if ( (rand() % 2) == 1 ) {
        zombie->position_x = (rand() % 640);
        zombie->position_y = -32;
    } else {
        zombie->position_x = -32;
        zombie->position_y = (rand() % 400);
    }
    zombie->health = ZOMBIE_START_HEALTH;
    zombie->speed = ZOMBIE_START_SPEED;
    zombie->max_speed = ZOMBIE_START_MAX_SPEED;
    zombie->strength = ZOMBIE_START_STRENGTH;
    zombie->direction = ZOMBIE_START_DIRECTION;
    zombie->step = ZOMBIE_START_STEP;
}

void player_update_postion(struct Player *player) {
    if (player->speed > 0 && player->health > 0) {
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
        if(player->position_x < 0) {
            player->position_x = 0;
        }
        if(player->position_y < 0) {
            player->position_y = 0;
        }
        if(player->position_x > 640) {
            player->position_x = 640;
        }
        if(player->position_y > 400) {
            player->position_y = 400;
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

void player_take_damage(struct Player *player, unsigned int damage) {
    if ( player->health <= damage ) {
        player->health = 0;
    } else {
        player->health -= damage;
    }
}

void player_reload(struct Player *player) {
    int ammo_needed;
    ammo_needed = player->max_magazine - player->magazine;
    if ( ammo_needed > 0 && player->ammo > 0) {
        if ( ammo_needed < player->ammo ) {
            player->magazine += ammo_needed;
            player->ammo -= ammo_needed;
        } else {
            player->magazine += player->ammo;
            player->ammo = 0;
        }
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

void player_score(struct Player *player) {
    player->score = player->score + 1;
}

bool player_alive(struct Player *player) {
    return player->health > 0;
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

void zombie_take_damage(struct Zombie * zombie, int damage ){
    if(zombie->health <= damage){
        zombie->health = 0;
    } else {
        zombie->health -= damage;
    }
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
    if(player->health > 0) {
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
    } else {
        direction = (rand() % 4);
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

bool zombie_alive(struct Zombie *zombie) {
    return zombie->health > 0;
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

void detect_collisions(struct GameModel *game_model) {
    int i;
    int j;
    struct Player *player = game_model->player;
    struct Zombie *zombies[ABSOLUTE_MAX_ZOMBIES] = game_model->zombies;
    struct Bullet *bullets[ABSOLUTE_MAX_BULLETS] = game_model->bullets;
    for ( i = 0; i < game_model->current_zombie_index; i++ ) {
        if (zombies[i] != NULL) {
            if (player->position_x <= zombies[i]->position_x + 20 &&
                player->position_x + 18 >= zombies[i]->position_x &&
                player->position_y <= zombies[i]->position_y + 24 &&
                19 + player->position_y >= zombies[i]->position_y) {
                player_take_damage(player,zombies[i]->strength);
            }

            for (j = 0; j < game_model->current_bullet_index; j++ ) {
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
}
