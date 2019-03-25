#include "global.h"
#include "player_b.h"
#include "zombie_b.h"
#include "misc_b.h"
#include "raster.h"
#include "model.h"
#include "font.h"

void render_stats(const struct Player *player,
                  const struct Game *game,
                  UINT32 *base) {

    UINT8 *base8 = (UINT8 *)base;
    plot_number(base8, 10, 10, player->health);
    plot_number(base8, 598, 382, player->magazine);
    plot_chars(base8, 606, 382, "/",1);
    plot_number(base8, 614, 382, player->ammo);
    plot_number(base8, 614,10,player->score);
    plot_number(base8, 10,382,game->wave);
}

void render_player(const struct Player *player, UINT32 *base) {
    if (player->health > 0) {
        plot_bitmap_32(base,
                       player->position_x,
                       player->position_y,
                       PLAYER_BODY[player->aim_direction],
                       PLAYER_BODY_HEIGHT);
        plot_bitmap_32(base,
                       player->position_x,
                       player->position_y+PLAYER_BODY_HEIGHT,
                       PLAYER_STEP[player->move_direction][player->step],
                       PLAYER_LEGS_HEIGHT);
    } else {
        plot_bitmap_32(base,
                       player->position_x,
                       player->position_y,
                       PLAYER_DEAD,
                       10);
    }
}

void render_zombie(const struct Zombie *zombie, UINT32 *base) {
    if (zombie->health > 0){
        plot_bitmap_32(base,
                       zombie->position_x,
                       zombie->position_y,
                       ZOMBIE_DIRECTION_STEP[zombie->direction][zombie->step],
                       ZOMBIE_HEIGHT);
    }
}

void render_cross(const struct Cross *cross, UINT32 *base) {
    plot_bitmap_8((UINT8 *)base,
                  cross->position_x - 1,
                  cross->position_y + 1,
                  CROSS,
                  CROSS_HEIGHT);
}

void render_bullet(const struct Bullet *bullet, UINT32 *base) {
    plot_pixel((UINT8 *)base,
               bullet->position_x,
               bullet->position_y);
}
