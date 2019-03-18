#ifndef RENDERER_ZS
#define RENDERER_ZS

void render_player(const struct Player *player, UINT32 *base);
void render_cross(const struct Cross *cross, UINT32 *base);
void render_zombie(const struct Zombie *zombie, UINT32 *base);
void render_misc(const struct Misc_Obj *obj, UINT32 *base);

#endif
