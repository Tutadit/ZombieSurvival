#include <stdio.h>
#include <linea.h>
#include <osbind.h>
#include <stdlib.h>

#include "global.h"
#include "raster.h"
#include "player_b.h"
#include "model.h"
#include "renderer.h"
#include "t_player.h"

void test_player(UINT32 *base) {
    test_player_render(base);
}

void test_player_render(UINT32 *base) {
    struct Player player;
    int x = 100;
    int y = 100;

    while(true) {
        player_set_postion(&player,x,y);
        player_set_aim_direction(&player, 40,40);
        player_set_move_direction(&player,1);
        player.step = 0;
        Vsync();
        clear_screen(base);
        render_player(&player,base);
        Cnecin();
    }

}
