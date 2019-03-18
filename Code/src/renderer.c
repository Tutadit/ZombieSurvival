#include "global.h"
#include "player_b.h"
#include "zombie_b.h"
#include "raster.h"
#include "model.h"

void render_player(const struct Player *player, UINT32 *base) {
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
}

void render_zombie(const struct Zombie *zombie, UINT32 *base) {
    plot_bitmap_32(base,
                   zombie->position_x,
                   zombie->position_y,
                   ZOMBIE_DIRECTION_STEP[zombie->direction][zombie->step],
                   ZOMBIE_HEIGHT);
}

void render_cross(const struct Cross *cross, UINT32 *base) {
    plot_bitmap_8((UINT8 *)base,
                  cross->position_x,
                  cross->position_y,
                  CROSS,
                  CROSS_HEIGHT);
}

void render_misc(const struct Misc_Obj *obj, UINT32 *base) {
    plot_bitmap_32(base,
                   zombie->position_x,
                   zombie->position_y,
                   ZOMBIE_DIRECTION_STEP[zombie->direction][zombie->step],
                   ZOMBIE_HEIGHT);
}
