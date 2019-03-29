#include <stdio.h>
#include <linea.h>
#include <osbind.h>
#include <stdlib.h>

#include "global.h"
#include "model.h"
#include "renderer.h"
#include "zombie_b.h"
#include "player_b.h"
#include "t_render.h"
#include "zs.h"

#define CLOCK 0x462
#define MAX_ZOMBIES 200
#define MAX_BULLETS 50

UINT32 *base;
UINT32 *base_back;
UINT32 *back_buffer;
UINT32 *tmp;
UINT32 *og;

int main() {

    UINT32 timeThen,
        timeNow,
        timeElapsed;
    int offset;
    struct GameModel game_model;

    int i;
    int mouse_status;
    int zombie_timer = 0;
    int player_timer = 0;

    base_back = (UINT32 *) malloc(32255);
    base = Physbase();
    back_buffer = base_back;
    offset = (int) base_back % 256;
    og = base;
    if ( offset !=0 ) {
        base_back += 256 - offset;
    }

    linea0();

    initialize_game(&game_model);

    timeThen = get_time();
    timeNow = get_time();

    while ( !is_game_over(&game_model) ) {

        timeNow = get_time();
        timeElapsed = timeNow - timeThen;

        if ( timeElapsed > 0 ) {
            mouse_status = MOUSE_BT;
            if ( mouse_status << 15 ) {
                shoot(&game_model);
            }

            if ( update_player(&game_model) ){
                game_over(&game_model);
            }

            player_timer++;
            if ( player_timer  > 1 ) {
                update_player_timed(&game_model);
                player_timer = 0;
            }

            zombie_timer++;
            if ( zombie_timer  > 2 ) {
                update_zombies_timed(&game_model);
                zombie_timer = 0;
            }

            detect_collisions(&game_model);

            clear_screen(base_back);
            render_game(&game_model,base_back);

            tmp = Physbase();
            Setscreen(-1,base_back,-1);
            base_back = tmp;
            timeThen = get_time();
        }
    }

    end_game(&game_model);

    Setscreen(-1,og,-1);
    free(back_buffer);
    return 0;
}

void initialize_game(struct GameModel *game_model) {
    game_model->game = (struct Game *) malloc(sizeof(struct Game));
    game_model->player = (struct Player *) malloc(sizeof(struct Player));
    game_model->cross = (struct Cross *) malloc(sizeof(struct Cross));
    game_model->current_zombie_index = 0;
    game_model->current_bullet_index = 0;

    start_game(game_model);
    player_spawn(game_model->player);
    spawn_zombies(game_model);
}

void end_game(struct GameModel *game_model) {
    int i;
    free(game_model->game);
    game_model->game = NULL;
    free(game_model->player);
    game_model->player = NULL;
    free(game_model->cross);
    game_model->cross = NULL;

    for( i = 0; i < ABSOLUTE_MAX_ZOMBIES; i++ ) {
        if(game_model->zombies[i] != NULL) {
            free(game_model->zombies[i]);
            game_model->zombies[i] = NULL;
        }
    }

    for( i = 0; i < ABSOLUTE_MAX_BULLETS; i++ ) {
        if(game_model->bullets[i] != NULL) {
            free(game_model->bullets[i]);
            game_model->bullets[i] = NULL;
        }
    }
}

void spawn_zombies(struct GameModel *game_model) {
    int i;
    int total_zombies = game_wave(game_model) * ZOMBIES_PER_WAVE_NUMBER;
    game_model->current_zombie_index = 0;
    for(i = 0; i < total_zombies; i++) {
        game_model->zombies[i] = (struct Zombie*) malloc(sizeof(struct Zombie));
        zombie_spawn(game_model->zombies[i]);
        game_model->current_zombie_index = game_model->current_zombie_index + 1;
    }
}

bool update_zombies(struct GameModel *game_model) {
    int up_by = rand() % 2 + 1;
    int i;
    bool all_dead = true;
    for(i = 0; i < game_model->current_zombie_index; i+= up_by) {
        if (game_model->zombies[i] != NULL) {
            if ( zombie_alive(game_model->zombies[i]) ) {
                zombie_set_direction(game_model->zombies[i],
                                     game_model->player);
                zombie_update_position(game_model->zombies[i]);
                zombie_set_step(game_model->zombies[i]);
                all_dead = false;
            } else {
                player_score(game_model);
                free(game_model->zombies[i]);
                game_model->zombies[i] = NULL;
            }
        }
    }
    return all_dead;
}
bool update_player(struct GameModel *game_model) {
    int m_x;
    int m_y;
    int key;
    if( Cconis()) {
        key = Cnecin();
        switch ( key ) {
        case 119:
            player_set_speed(game_model,1);
            player_set_move_direction(game_model,MOVE_N);
            break;
        case 115:
            player_set_speed(game_model,1);
            player_set_move_direction(game_model,MOVE_S);
            break;
        case 97:
            player_set_speed(game_model,1);
            player_set_move_direction(game_model,MOVE_W);
            break;
        case 100:
            player_set_speed(game_model,1);
            player_set_move_direction(game_model,MOVE_E);
            break;
        case 32:
            player_reload(game_model);
            break;
        default:

            break;
        }
    }

    m_x = GCURX;
    m_y = GCURY;
    cross_set_position(game_model->cross,m_x,m_y);
    player_set_aim_direction(game_model);;
    return !player_alive(game_model);
}

void update_player_timed(struct GameModel *game_model) {
    player_update_postion(game_model);
    player_set_step(game_model);
}

void update_zombies_timed(struct GameModel *game_model) {
    if ( update_zombies(game_model) ) {
        game_next_wave(game_model);
        player_max_ammo(game_model);
        spawn_zombies(game_model);
    }
}

void shoot(struct GameModel *game_model) {
    game_model->bullets[game_model->current_bullet_index] =
        (struct Bullet *) malloc(sizeof(struct Bullet));
    bullet_shoot(
                 game_model->bullets[game_model->current_bullet_index],
                 game_model->player);
    game_model->current_bullet_index++;
    if ( game_model->current_bullet_index == MAX_BULLETS ) {
        game_model->current_bullet_index = 0;
    }

}

void render_game(struct GameModel *game_model, UINT32 *base) {
    render_player(game_model->player,base);
    render_stats(game_model->player,game_model->game,base);
    render_cross(game_model->cross,base);
    render_zombies(game_model,base);
    render_bullets(game_model,base);
}

void render_zombies(struct GameModel *game_model, UINT32 *base) {
    int i;
    for (i = 0; i < game_model->current_zombie_index; i++) {
        if(game_model->zombies[i] != NULL) {
            render_zombie(game_model->zombies[i],base);
        }
    }

}

void render_bullets(struct GameModel *game_model, UINT32 *base) {
    int i;
    for(i = 0; i < game_model->current_bullet_index; i++ ) {
        if(game_model->bullets[i] != NULL) {
            if ( !bullet_update_position(game_model->bullets[i]) ) {
                render_bullet(game_model->bullets[i],base);
            } else {
                free(game_model->bullets[i]);
                game_model->bullets[i] = NULL;
            }
        }
    }

}

UINT32 get_time() {
    UINT32 old_ssp;
    UINT32 *timer = (UINT32 *) CLOCK;
    UINT32 time;
    old_ssp = Super(0);
    time = (UINT32) *timer;
    Super(old_ssp);
    return (UINT32) time;
}
