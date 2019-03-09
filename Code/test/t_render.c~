#include <stdio.h>
#include <linea.h>
#include <osbind.h>
#include <stdlib.h>

#include "global.h"
#include "model.h"
#include "renderer.h"
#include "zombie_b.h"
#include "t_render.h"

void test_renderer(UINT32 *base) {
    struct Player player;
    struct Zombie zombie01;
    struct Zombie zombie02;
    struct Zombie zombie03;

    clear_screen(base);
    player_set_postion(&player, 100,200);
    player_set_aim_direction(&player, 1,1);
    player_set_move_direction(&player,0);
    player.speed = 0;
    player_set_step(&player);

    zombie_set_position(&zombie01, 50, 200);
    zombie_set_direction(&zombie01, Z_MOVE_E);
    zombie_set_step(&zombie01);

    zombie_set_position(&zombie02, 200, 200);
    zombie_set_direction(&zombie02, Z_MOVE_W);
    zombie_set_step(&zombie02);

    zombie_set_position(&zombie03, 80, 300);
    zombie_set_direction(&zombie03, Z_MOVE_N);
    zombie_set_step(&zombie03);

    render_player(&player,base);
    render_zombie(&zombie01,base);
    render_zombie(&zombie02,base);
    render_zombie(&zombie03,base);

    Cnecin();

}
