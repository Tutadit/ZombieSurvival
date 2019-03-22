#ifndef MAIN_GAME
#define MAIN_GAME

UINT32 get_time();
void initialize_game(struct Player *player,
                     struct Zombie *zombies[],
                     int total_zombies,
                     struct Misc_Obj *misc_objs,
                     int total_misc);
void update_player(struct Player *player, struct Cross *cross, bool *quit);
void update_zombies(struct Zombie *zombies[], struct Player *player);
#endif
