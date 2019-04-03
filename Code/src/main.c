#include <osbind.h>
#include "global.h"
#include "zs_math.h"
#include "zombie_b.h"
#include "player_b.h"
#include "misc_b.h"
#include "raster.h"
#include "model.h"
#include "renderer.h"
#include "input.h"
#include "music.h"
#include "effects.h"
#include "setup.h"
#include "main.h"


UINT32 *back_buffer = 0;
UINT32 *tmp = 0;
UINT8 buffer_space[BUFFER_SPACE] = {0};
bool render_request = false;

int player_timer = 0;
int zombie_timer = 0;
int bullet_timer = 0;

int main() {
    initital_setup();
    while ( true ) {
        if ( render_request ) {
            update_music();
            handle_input();
            clear_screen(back_buffer);
            if (is_game_over()) {
                main_menu();
            } else {
                game();
            }
            update_cursor();
            tmp = get_video_base();
            set_video_base(back_buffer);
            back_buffer = tmp;
            render_request = false;
        }
    }
    return 0;
}

void handle_input() {
    handle_mouse_input();
    handle_keyboard_input();
}

void update_cursor() {
    cursor_set_position(&game_model.cursor,cursor_x(),cursor_y());
    render_cursor(&game_model.cursor,back_buffer);
}

void initital_setup() {
    int offset;
    set_video_base((UINT32 *)VIDEO_BASE);
    set_up_mfp();
    install_isrs();
    random_init();
    disable_midi();
    enable_ikbd_irq();
    start_music();
    back_buffer = (UINT32 *) buffer_space;
    offset = (int) ( (UINT32) buffer_space % 256 );
    if ( offset !=0 ) {
       back_buffer += 256 - offset;
    }
    spawn_button(&game_model.survive,
                 SURVIVE_A,
                 SURVIVE_B,
                 MM_SURVIVE_X,
                 MM_SURVIVE_Y);
}

void game() {
    if ( update_player() ){
        game_over();
    }
    detect_collisions();
    render_game();
}

void handle_mouse_input() {
    if ( mouse_left_status() ) {
        if ( is_game_over() ) {
            if (button_hover(&game_model.survive)) {
                start_game();
            }
        } else {
            if (!m_left_pressed) {
                shoot();
                m_left_pressed = true;
            }
        }
    } else {
        m_left_pressed = false;
    }

}

void main_menu() {
    button_cursor_collision(&game_model.survive, &game_model.cursor);
    render_button(&game_model.survive, back_buffer);
}

bool update_zombies() {
    int i;
    bool all_dead = true;
    for(i = 0; i < game_model.current_zombie_index; i++) {
        if ( zombie_alive(&game_model.zombies[i]) ) {
            zombie_set_direction(&game_model.zombies[i],
                                 &game_model.player);
            zombie_update_position(&game_model.zombies[i]);
            zombie_set_step(&game_model.zombies[i]);
            all_dead = false;
        }
    }
    return all_dead;
}

void handle_keyboard_input() {
    SCANCODE key;
    if( keys_to_read()) {
        key = sb_pop();
        switch ( key ) {
        case W_DOWN:
            w_down = true;
            player_set_move_direction(MOVE_N);
            break;
        case S_DOWN:
            s_down = true;
            player_set_move_direction(MOVE_S);
            break;
        case A_DOWN:
            a_down = true;
            player_set_move_direction(MOVE_W);
            break;
        case D_DOWN:
            d_down = true;
            player_set_move_direction(MOVE_E);
            break;
        case SP_UP:
            player_reload();
            break;
        case W_UP:
            w_down = false;
            break;
        case A_UP:
            a_down = false;
            break;
        case S_UP:
            s_down = false;
            break;
        case D_UP:
            d_down = false;
            break;
        default:
            break;
        }
    }
}
bool update_player() {
    if ( w_down || a_down || s_down || d_down ) {
        player_set_moving(true);
    } else {
        player_set_moving(false);
    }
    player_set_step();
    player_set_aim_direction();
    return !player_alive();
}

void update_player_timed() {
    player_update_postion();
}

void update_zombies_timed() {
    if ( update_zombies() ) {
        game_next_wave();
        player_max_ammo();
        spawn_zombies();
    }
}

void shoot() {
    if ( bullet_shoot(&game_model.bullets[game_model.current_bullet_index],
                      &game_model.player)) {
        game_model.current_bullet_index++;
        play_shoot();
    } else {
        play_empty();
    }
    if ( game_model.current_bullet_index == ABSOLUTE_MAX_BULLETS ) {
        game_model.current_bullet_index = 0;
    }
}

void render_game() {
    render_player(&game_model.player,back_buffer);
    render_stats(&game_model.player,&game_model.game,back_buffer);
    render_zombies(back_buffer);
    render_bullets(back_buffer);
}

void render_zombies() {
    int i;
    for (i = 0; i < game_model.current_zombie_index; i++) {

        if(zombie_alive(&game_model.zombies[i])) {
            render_zombie(&game_model.zombies[i],back_buffer);
        }
    }

}

void update_bullets() {
    int i;
    for(i = 0; i < game_model.current_bullet_index; i++ ) {
        if(!bullet_hit(&game_model.bullets[i])) {
            bullet_update_position(&game_model.bullets[i]);
        }
    }
}
void render_bullets() {
    int i;
    for(i = 0; i < game_model.current_bullet_index; i++ ) {
        if(!bullet_hit(&game_model.bullets[i])) {
            if ( !bullet_hit(&game_model.bullets[i]) ) {
                render_bullet(&game_model.bullets[i],back_buffer);
            }
        }
    }

}

void do_vbl_isr() {
    tempo++;
    volume_down++;
    update_bullets();
    random_update();
    if(!is_game_over()) {
        game_model.player_timer++;
        if ( game_model.player_timer  > 1 ) {
            update_player_timed();
            game_model.player_timer = 0;
        }
    }

    game_model.zombie_timer++;
    if ( game_model.zombie_timer  > 15 ) {
        update_zombies_timed();
        game_model.zombie_timer = 0;
    }
    render_request = true;
}
