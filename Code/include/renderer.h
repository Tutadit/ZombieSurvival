/*
 * Render helper functions for
 * the game.
 *
 * Each function takes in the address of
 * the frame buffer to render it at.
 */
#ifndef RENDERER_ZS
#define RENDERER_ZS
#include "global.h"
#include "model.h"

void render_button(const struct Button *button, UINT32 *base);
void render_player(const struct Player *player, UINT32 *base);
void render_stats(const struct Player *player,
                  const struct Game *game,
                  UINT32 *base);
void render_cursor(const struct Cursor *cross, UINT32 *base);
void render_zombie(const struct Zombie *zombie, UINT32 *base);
void render_bullet(const struct Bullet *obj, UINT32 *base);

#endif
