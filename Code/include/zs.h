#ifndef MAIN_GAME
#define MAIN_GAME

UINT32 get_time();
void clear_screen(UINT32 *base);

void initialize_game(struct GameModel *game_model);
void end_game(struct GameModel *game_model);

void spawn_zombies(struct GameModel *game_model);
bool update_player(struct GameModel *game_model);
bool update_zombies(struct GameModel *game_model);

void update_player_timed(struct GameModel *game_model);
void update_zombies_timed(struct GameModel *game_model);

void shoot(struct GameModel *game_model);
void render_game(struct GameModel *game_model, UINT32 *base);
void render_zombies(struct GameModel *game_model, UINT32 *base);
void render_bullets(struct GameModel *game_model, UINT32 *base);

#endif
