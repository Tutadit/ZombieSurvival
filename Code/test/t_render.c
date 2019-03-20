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

#define TOTAL_ZOMBIES 7

void test_renderer(UINT32 *base) {
    struct Player player;
    struct Zombie zombies[TOTAL_ZOMBIES];
    struct Cross cross;
    UINT32 *base_back = (UINT32 *) malloc(32255);
    int offset = (int) base_back % 256;
    UINT32 *tmp;
    UINT32 *og = base;
    int positions[TOTAL_ZOMBIES][2] = {
                                       30,30,
                                       200,30,
                                       400,30,
                                       30,200,
                                       30,350,
                                       200,350,
                                       400,350
    };
    int m_x;
    int m_y;
    int key;
    int i;
    bool loop = true;
    if ( offset !=0 ) {
        base_back += 256 - offset;
    }
    linea0();
    player_spawn(&player);
    for(i = 0; i < TOTAL_ZOMBIES; i++) {
        zombie_spawn(&zombies[i],positions[i][0],positions[i][1]);
        zombie_set_direction(&zombies[i],&player);
    }

    while(loop) {
        m_x = GCURX;
        m_y = GCURY;
        cross_set_position(&cross,m_x,m_y);
        if( Cconis()) {
            key = Cnecin();
            switch ( key ) {
            case 119:
                player_set_speed(&player,1);
                player_set_move_direction(&player,MOVE_N);
                break;
            case 115:
                player_set_speed(&player,1);
                player_set_move_direction(&player,MOVE_S);
                break;
            case 97:
                player_set_speed(&player,1);
                player_set_move_direction(&player,MOVE_W);
                break;
            case 100:
                player_set_speed(&player,1);
                player_set_move_direction(&player,MOVE_E);
                break;
            default:
                loop = false;
                break;
            }
        }
        /*player_set_speed(&player,0);*/
        player_update_postion(&player);
        player_set_aim_direction(&player,&cross);
        player_set_step(&player);


        Vsync();
        clear_screen(base_back);
        render_player(&player,base_back);
        render_cross(&cross,base_back);
        for(i = 0; i < TOTAL_ZOMBIES; i++) {
            zombie_set_direction(&zombies[i],&player);
            zombie_update_position(&zombies[i]);
            zombie_set_step(&zombies[i]);
            render_zombie(&zombies[i],base_back);
        }
        tmp = Physbase();
        Setscreen(-1,base_back,-1);
        base_back = tmp;
    }
    Setscreen(-1,og,-1);
}
