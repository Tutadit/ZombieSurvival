#include <stdio.h>
#include <linea.h>
#include <osbind.h>
#include <stdlib.h>

#include "global.h"
#include "raster.h"
#include "player.h"
#include "model.h"
#include "renderer.h"
#include "t_player.h"

void test_player(UINT32 *base) {
    test_player_render(base);
}

void test_player_render(UINT32 *base) {
    struct Player player;

    player.position_x = 100;
    player.position_y = 200;
    player.aim_direction = 2;
    player.move_direction = 3;
    player.step = 0;

    while(true) {
        Vsync();
        clear_screen(base);
        render_player(&player,base);
        Cnecin();
    }

}
