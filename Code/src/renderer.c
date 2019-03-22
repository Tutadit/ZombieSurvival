#include "global.h"
#include "player_b.h"
#include "zombie_b.h"
#include "misc_b.h"
#include "raster.h"
#include "model.h"

UINT32 border_wall[32] = {
                      0xFFFFFFFF,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0x80000001,
                      0xFFFFFFFF
};
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
                       8);
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

void render_misc(const struct Misc_Obj *obj, UINT32 *base) {
    plot_bitmap_32(base,
                   obj->position_x,
                   obj->position_y,
                   TREE_01,
                   TREE_01_HEIGHT);
}

void render_bullet(const struct Bullet *bullet, UINT32 *base) {
    plot_pixel((UINT8 *)base,
               bullet->position_x,
               bullet->position_y);
}
