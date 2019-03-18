#include <stdio.h>
#include <linea.h>
#include <osbind.h>
#include <stdlib.h>

#include "global.h"
#include "model.h"
#include "renderer.h"
#include "zombie_b.h"
#include "t_render.h"

#define TOTAL_ZOMBIES 7
void test_renderer(UINT32 *base) {
    struct Player player;
    struct Zombie zombies[TOTAL_ZOMBIES];
    int positions[TOTAL_ZOMBIES][2] = {
                                       30,30,
                                       200,30,
                                       400,30,
                                       30,200,
                                       30,350,
                                       200,350,
                                       400,350
    };
    int i = 0;
    clear_screen(base);
    player_spawn(&player);
    render_player(&player,base);
    for(; i < TOTAL_ZOMBIES; i++) {
        zombie_spawn(&zombies[i],positions[i][0],positions[i][1]);
        zombie_set_direction(&zombies[i],&player);
        render_zombie(&zombies[i],base);
    }

    while(true) {
        Vsync();
        player_update_postion(&player);
        render_player(&player,base);
        for(i = 0; i < TOTAL_ZOMBIES; i++) {
            zombie_set_direction(&zombies[i],&player);
            zombie_update_position(&zombies[i]);
            zombie_set_step(&zombies[i]);
            render_zombie(&zombies[i],base);
        }
        Cnecin();
        clear_screen(base);
    }

}
