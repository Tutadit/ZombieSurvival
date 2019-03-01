#include "global.h"
#include "player.h"
#include "zombie.h"
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
                   player->position_y+14,
                   PLAYER_STEP[player->move_direction][player->step],
                   PLAYER_LEGS_HEIGHT);
}

void render_zombie(const struct Zombie *zombie, UINT32 *base) {

}
