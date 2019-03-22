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

void plot_pixel(char *base, int x, int y)
{
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
        *(base + y * 80 + (x >> 3)) |= 1 << 7 - (x & 7);
}
void test_player_render(UINT32 *base) {
    struct Player player;
    int x = 100;
    int y = 100;
    int m_x;
    int m_y;
    int ai = 0;
    int key;
    linea0();

    player.step = 0;
    player.move_direction = 0;
    /*!Cconis()*/
    while(true) {
        m_x = GCURX;
        m_y = GCURY;
        key = Cnecin();
        if (key == 119) {
            player.speed = 1;
            player_set_move_direction(&player,MOVE_S);
            y--;
        } else if (key == 115) {
            player.speed = 1;
            player_set_move_direction(&player,MOVE_N);
            y++;
        } else if (key == 97) {
            player.speed = 1;
            player_set_move_direction(&player,MOVE_W);
            x--;
        } else if (key == 100) {
            player.speed = 1;
            player_set_move_direction(&player,MOVE_E);
            x++;
        }
        fflush(stdout);
        player_update_postion(&player,x,y);
        player_set_aim_direction(&player, m_x,m_y);
        player.speed = 1;
        player_set_step(&player);
        Vsync();
        clear_screen(base);
        render_player(&player,base);
        plot_pixel((char *)base, m_x,m_y);
    }

}
