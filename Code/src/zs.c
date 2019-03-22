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
#define MAX_ZOMBIES 15
#define MAX_BULLETS 50

int main() {
    UINT32
        timeThen,
        timeNow,
        timeElapsed;
    bool quit = false;
    struct Player player;
    struct Zombie *zombies[MAX_ZOMBIES];
    struct Cross cross;
    struct Misc_Obj misc_obs[2];
    struct Bullet *bullets[MAX_BULLETS];
    int current_bullet_index = 0;
    UINT32 *base = Physbase();
    UINT32 *base_back = (UINT32 *) malloc(32255);
    UINT32 *back_buffer;
    int offset = (int) base_back % 256;
    UINT32 *tmp;
    UINT32 *og = base;
    int key;
    int zombie_time = 0;
    int i;
    if ( offset !=0 ) {
        base_back += 256 - offset;
    }

    for(i = 0; i < MAX_BULLETS; i++) {
        bullets[i] = NULL;
    }
    linea0();
    initialize_game(&player,
                    zombies,
                    MAX_ZOMBIES,
                    misc_obs,
                    2);
    while ( !quit ) {

        if ( MOUSE_BT ) {
            bullets[current_bullet_index] =
                (struct Bullet *) malloc(sizeof(struct Bullet));
            bullet_shoot(bullets[current_bullet_index],&player);
            current_bullet_index++;
            if ( current_bullet_index == MAX_BULLETS ) {
                current_bullet_index = 0;
            }
        }


        Vsync();

        clear_screen(base_back);

        render_player(&player,base_back);
        render_stats(&player,base_back);
        for(i = 0; i < MAX_BULLETS; i++ ) {
            if(bullets[i] != NULL) {
                if ( !bullet_update_position(bullets[i]) ) {
                    render_bullet(bullets[i],base);
                } else {
                    free(bullets[i]);
                    bullets[i] = NULL;
                }
            }
        }
        render_cross(&cross,base_back);
        for (i = 0; i < MAX_ZOMBIES; i++) {
            if(zombies[i] != NULL) {
                render_zombie(zombies[i],base_back);
            }
        }

        detect_collisions(bullets,zombies,&player,
                          MAX_BULLETS,
                          MAX_ZOMBIES);

        tmp = Physbase();
        Setscreen(-1,base_back,-1);
        base_back = tmp;
        update_player(&player,&cross, &quit);

        timeNow = get_time();
        timeElapsed = timeNow - timeThen;
        if ( timeElapsed > 5 ) {
            player_update_postion(&player);
            player_set_step(&player);
            timeThen = timeNow;
            zombie_time = ~zombie_time;
            if ( zombie_time ) {
                update_zombies(zombies,&player);
            }
        }
    }
    Setscreen(-1,og,-1);
    free(back_buffer);
    return 0;
}

void initialize_game(struct Player *player,
                     struct Zombie *zombies[],
                     int total_zombies,
                     struct Misc_Obj *misc_objs,
                     int total_misc) {
    int i;
    player_spawn(player);
    for(i = 0; i < total_zombies; i++) {
        zombies[i] = (struct Zombie*) malloc(sizeof(struct Zombie));
        zombie_spawn(zombies[i]);
    }
}

void update_zombies(struct Zombie *zombies[], struct Player *player) {
    int i;
    for(i = 0; i < MAX_ZOMBIES; i++) {
        if (zombies[i] != NULL) {
            if (zombies[i]->health > 0 ) {
                zombie_set_direction(zombies[i],player);
                zombie_update_position(zombies[i]);
                zombie_set_step(zombies[i]);
            } else {
                free(zombies[i]);
                zombies[i] = NULL;
            }
        }
    }
}
void update_player(struct Player *player, struct Cross *cross,
                   bool *quit) {
    int m_x;
    int m_y;
    int key;
    if( Cconis()) {
        key = Cnecin();
        switch ( key ) {
        case 119:
            player_set_speed(player,1);
            player_set_move_direction(player,MOVE_N);
            break;
        case 115:
            player_set_speed(player,1);
            player_set_move_direction(player,MOVE_S);
            break;
        case 97:
            player_set_speed(player,1);
            player_set_move_direction(player,MOVE_W);
            break;
        case 100:
            player_set_speed(player,1);
            player_set_move_direction(player,MOVE_E);
            break;
        case 32:
            player_reload(player);
            break;
        default:
            *quit = true;
            break;
        }
    }

    m_x = GCURX;
    m_y = GCURY;
    cross_set_position(cross,m_x,m_y);
    player_set_aim_direction(player,cross);

}
UINT32 get_time() {
    long old_ssp;
    UINT32 *timer = (UINT32 *) CLOCK;
    UINT32 time;
    old_ssp = Super(0);
    time = *timer;
    Super(old_ssp);
    return time;
}
