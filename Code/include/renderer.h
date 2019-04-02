#ifndef RENDERER_ZS
#define RENDERER_ZS
#include "global.h"
#include "model.h"
void render_button(const struct Button *button, UINT32 *base);
void render_player(const struct Player *player, UINT32 *base);
void render_stats(const struct Player *player,
                  const struct Game *game,
                  UINT32 *base);
void render_cross(const struct Cross *cross, UINT32 *base);
void render_zombie(const struct Zombie *zombie, UINT32 *base);
void render_bullet(const struct Bullet *obj, UINT32 *base);

#endif
