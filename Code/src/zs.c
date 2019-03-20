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
#define TOTAL_ZOMBIES 15


int main() {
    UINT32
        timeThen,
        timeNow,
        timeElapsed;
    bool quit = false;
    struct Player player;
    struct Zombie zombies[TOTAL_ZOMBIES];
    struct Cross cross;
    struct Misc_Obj misc_obs[2];
    struct Bullet bullet;

    UINT32 *base = Physbase();
    UINT32 *base_back = (UINT32 *) malloc(32255);
    int offset = (int) base_back % 256;
    UINT32 *tmp;
    UINT32 *og = base;
    int key;
    int i;
    if ( offset !=0 ) {
        base_back += 256 - offset;
    }

    linea0();
    initialize_game(&player,
                    zombies,
                    TOTAL_ZOMBIES,
                    misc_obs,
                    2);
    while ( !quit ) {

        if ( MOUSE_BT ) {
            bullet_shoot(&bullet,&player);
        }
        bullet_update_position(&bullet);

        Vsync();

        clear_screen(base_back);

        render_player(&player,base_back);
        render_bullet(&bullet,base);
        render_cross(&cross,base_back);
        for (i = 0; i < TOTAL_ZOMBIES; i++) {
            render_zombie(&zombies[i],base_back);
        }

        tmp = Physbase();
        Setscreen(-1,base_back,-1);
        base_back = tmp;

        timeNow = get_time();
        timeElapsed = timeNow - timeThen;
        if ( timeElapsed > 10 ) {
            update_player(&player,&cross, &quit);
            update_zombies(zombies,&player);
            timeThen = timeNow;
        }
    }
    Setscreen(-1,og,-1);
    return 0;
}

void initialize_game(struct Player *player,
                     struct Zombie *zombies,
                     int total_zombies,
                     struct Misc_Obj *misc_objs,
                     int total_misc) {
    int i;
    player_spawn(player);
    for(i = 0; i < total_zombies; i++) {
        zombie_spawn(&zombies[i]);
    }
}

void update_zombies(struct Zombie *zombies, struct Player *player) {
    int i;
    for(i = 0; i < TOTAL_ZOMBIES; i++) {
        zombie_set_direction(&zombies[i],player);
        zombie_update_position(&zombies[i]);
        zombie_set_step(&zombies[i]);
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
        default:
            *quit = true;
            break;
        }
    }

    m_x = GCURX;
    m_y = GCURY;
    cross_set_position(cross,m_x,m_y);
    player_update_postion(player);
    player_set_aim_direction(player,cross);
    player_set_step(player);

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
