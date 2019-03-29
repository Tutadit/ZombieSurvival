#include <osbind.h>
#include <stdio.h>
#include "global.h"
#include "raster.h"
#include "model.h"
#include "renderer.h"
#include "zombie_b.h"
#include "player_b.h"
#include "t_render.h"
#include "misc_b.h"
#include "input.h"
#include "zs_math.h"
#include "zs.h"

UINT32 *back_buffer = 0;
UINT32 *tmp = 0;
UINT32 *og_base = 0;
UINT8 buffer_space[BUFFER_SPACE] = {0};

int main() {
    UINT32 timeThen,
        timeNow,
        timeElapsed;
    int offset;
    char choice = 'm';
    Vector orig_vbl_vector = install_vector(VECTOR_VBL, vbl_isr);
    Vector orig_kbd_vector = install_vector(VECTOR_KBD, kbd_isr);
    struct MainMenu menu;
    disable_midi();
    og_base = get_video_base();
    back_buffer = (UINT32 *) buffer_space;
    offset = (int) buffer_space % 256;
    if ( offset !=0 ) {
       back_buffer += 256 - offset;
    }
    random_init();
    menu = generate_main_menu();
    while ( choice != 'q' ) {
        if ( render_request ) {
            clear_screen(back_buffer);
            if (is_game_over()) {
                main_menu(&menu);
            } else {
                game();
            }
            cross_set_position(&game_model.cross,cursor_x(),cursor_y());
            render_cross(&game_model.cross,back_buffer);
            tmp = get_video_base();
            set_video_base(back_buffer);
            back_buffer = tmp;
            render_request = false;
        }
    }
    set_video_base(og_base);
    install_vector(VECTOR_VBL, orig_vbl_vector);
    install_vector(VECTOR_KBD, orig_kbd_vector);
    enable_midi();
    return 0;
}

void game() {
    if ( mouse_left_status() ) {
        if (!m_left_pressed) {
            shoot();
            m_left_pressed = true;
        }
    } else {
        m_left_pressed = false;
    }
    if ( update_player() ){
        game_over();
    }
    detect_collisions();
    render_game(back_buffer);
}

void main_menu(struct MainMenu *menu) {
    if ( mouse_left_status() ) {
        if (button_hover(&menu->survive)) {
            start_game();
        } else if (button_hover(&menu->quit)) {
            ;
        }
    }
    button_cross_collision(&menu->survive, &game_model.cross);
    button_cross_collision(&menu->quit, &game_model.cross);

    render_button(&menu->survive, back_buffer);
    render_button(&menu->quit, back_buffer);
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

bool update_player() {
    int m_x;
    int m_y;
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
    if ( w_down || a_down || s_down || d_down ) {
        player_set_speed(1);
    } else {
        player_set_speed(0);
    }
    player_set_aim_direction();
    return !player_alive();
}

void update_player_timed() {
    player_set_step();
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
    bullet_shoot(&game_model.bullets[game_model.current_bullet_index],
                 &game_model.player);
    game_model.current_bullet_index++;
    if ( game_model.current_bullet_index == ABSOLUTE_MAX_BULLETS ) {
        game_model.current_bullet_index = 0;
    }
}

void render_game(UINT32 *base) {
    render_player(&game_model.player,base);
    render_stats(&game_model.player,&game_model.game,base);
    render_zombies(base);
    render_bullets(base);
}

void render_zombies(UINT32 *base) {
    int i;
    for (i = 0; i < game_model.current_zombie_index; i++) {
        if(zombie_alive(&game_model.zombies[i])) {
            render_zombie(&game_model.zombies[i],base);
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
void render_bullets(UINT32 *base) {
    int i;
    for(i = 0; i < game_model.current_bullet_index; i++ ) {
        if(!bullet_hit(&game_model.bullets[i])) {
            if ( !bullet_hit(&game_model.bullets[i]) ) {
                render_bullet(&game_model.bullets[i],base);
            }
        }
    }

}

Vector install_vector(int num, Vector vector) {
    Vector orig;
    Vector *vectp = (Vector *)((long)num << 2);
    long old_ssp = Super(0);
    orig = *vectp;
    *vectp = vector;
    Super(old_ssp);
    return orig;
}

void do_vbl_isr() {
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
    if ( game_model.zombie_timer  > 7 ) {
        update_zombies_timed();
        game_model.zombie_timer = 0;
    }
    render_request = true;
}
