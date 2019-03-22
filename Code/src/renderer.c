#include "global.h"
#include "player_b.h"
#include "zombie_b.h"
#include "misc_b.h"
#include "raster.h"
#include "model.h"
#include "font.h"

void render_stats(const struct Player *player, UINT32 *base) {
    int health_lsb;
    int health_msb;
    int ammo_lsb;
    int ammo_msb;
    int magazine;
    UINT8 *health_lsb_char;
    UINT8 *health_msb_char;
    UINT8 *ammo_lsb_char;
    UINT8 *ammo_msb_char;
    UINT8 *magazine_char;
    UINT8 *slash_char;

    health_lsb = player->health % 10;
    health_msb = ( player->health / 10 ) % 10;

    ammo_lsb = player->ammo %10;
    ammo_msb = ( player->ammo / 10 ) % 10;

    magazine = player->magazine;
    health_lsb_char = GLYPH_START(health_lsb + '0');
    health_msb_char = GLYPH_START(health_msb + '0');
    ammo_lsb_char = GLYPH_START(ammo_lsb + '0');
    ammo_msb_char = GLYPH_START(ammo_msb + '0');
    magazine_char = GLYPH_START(magazine + '0');
    slash_char = GLYPH_START('/');


    plot_bitmap_8((UINT8 *)base,
                  10,10,
                  health_msb_char,
                  8);
    plot_bitmap_8((UINT8 *)base,
                  18,10,
                  health_lsb_char,
                  8);
    plot_bitmap_8((UINT8 *)base,
                  598,382,
                  magazine_char,
                  8);
    plot_bitmap_8((UINT8 *)base,
                  606,382,
                  slash_char,
                  8);
    plot_bitmap_8((UINT8 *)base,
                  614,382,
                  ammo_msb_char,
                  8);
    plot_bitmap_8((UINT8 *)base,
                  622,382,
                  ammo_lsb_char,
                  8);
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
