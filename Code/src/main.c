#include <osbind.h>
#include "global.h"
#include "raster.h"
#include "model.h"
#include "renderer.h"
#include "zombie_b.h"
#include "player_b.h"
#include "t_render.h"
#include "misc_b.h"
#include "input.h"
#include "music.h"
#include "zs_math.h"
#include "main.h"

volatile UINT8 * const MFP_PDR_P = MFP_PDR_ADR;
volatile UINT8 * const MFP_AER_P = MFP_AER_ADR;
volatile UINT8 * const MFP_DIR_P = MFP_DIR_ADR;
volatile UINT8 * const MFP_IEA_P = MFP_IEA_ADR;
volatile UINT8 * const MFP_IEB_P = MFP_IEB_ADR;
volatile UINT8 * const MFP_IPA_P = MFP_IPA_ADR;
volatile UINT8 * const MFP_IPB_P = MFP_IPB_ADR;
volatile UINT8 * const MFP_ISA_P = MFP_ISA_ADR;
volatile UINT8 * const MFP_ISB_P = MFP_ISB_ADR;
volatile UINT8 * const MFP_IMA_P = MFP_IMA_ADR;
volatile UINT8 * const MFP_IMB_P = MFP_IMB_ADR;
volatile UINT8 * const MFP_VCR_P = MFP_VCR_ADR;
volatile UINT8 * const MFP_TAC_P = MFP_TAC_ADR;
volatile UINT8 * const MFP_TBC_P = MFP_TBC_ADR;
volatile UINT8 * const MFP_TDC_P = MFP_TDC_ADR;
volatile UINT8 * const MFP_TAD_P = MFP_TAD_ADR;
volatile UINT8 * const MFP_TBD_P = MFP_TBD_ADR;
volatile UINT8 * const MFP_TCD_P = MFP_TCD_ADR;
volatile UINT8 * const MFP_TDD_P = MFP_TDD_ADR;
volatile UINT8 * const MFP_SYC_P = MFP_SYC_ADR;
volatile UINT8 * const MFP_UCR_P = MFP_UCR_ADR;
volatile UINT8 * const MFP_RES_P = MFP_RES_ADR;
volatile UINT8 * const MFP_TRS_P = MFP_TRS_ADR;
volatile UINT8 * const MFP_UAD_P = MFP_UAD_ADR;

UINT32 *back_buffer = 0;
UINT32 *tmp = 0;
UINT8 buffer_space[BUFFER_SPACE] = {0};
bool render_request = false;

int main() {
    UINT32 timeThen,
        timeNow,
        timeElapsed;
    int offset;
    char choice = 'm';
    struct MainMenu menu;

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

    menu = generate_main_menu();

    while ( choice != 'q' ) {
        update_music();
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
    return 0;
}

void set_up_mfp() {
    long old_ssp = Super(0);
    *MFP_PDR_P = MFP_PDR_DEF;
    *MFP_AER_P = MFP_AER_DEF;
    *MFP_DIR_P = MFP_DIR_DEF;
    *MFP_IEA_P = MFP_IEA_DEF;
    *MFP_IEB_P = MFP_IEB_DEF;
    *MFP_IPA_P = MFP_IPA_DEF;
    *MFP_IPB_P = MFP_IPB_DEF;
    *MFP_ISA_P = MFP_ISA_DEF;
    *MFP_ISB_P = MFP_ISB_DEF;
    *MFP_IMA_P = MFP_IMA_DEF;
    *MFP_IMB_P = MFP_IMB_DEF;
    *MFP_VCR_P = MFP_VCR_DEF;
    *MFP_TAC_P = MFP_TAC_DEF;
    *MFP_TBC_P = MFP_TBC_DEF;

    *MFP_TAD_P = MFP_TAD_DEF;
    *MFP_TBD_P = MFP_TBD_DEF;
    *MFP_TCD_P = MFP_TCD_DEF;

    *MFP_TDD_P = MFP_TDD_DEF;
    *MFP_SYC_P = MFP_SYC_DEF;
    *MFP_UCR_P = MFP_UCR_DEF;
    *MFP_RES_P = MFP_RES_DEF;
    *MFP_TRS_P = MFP_TRS_DEF;
    *MFP_UAD_P = MFP_UAD_DEF;
    Super(old_ssp);
}

void enable_ikbd_irq() {
    long old_ssp = Super(0);
    *IKBD_control = IKBD_CTL_DEF;
    set_ipl(0);
    Super(old_ssp);
}

void install_isrs() {
    install_vector(VECTOR_VBL, vbl_isr);
    install_vector(VECTOR_HBL, hbl_isr);
    install_vector(VECTOR_KBD, kbd_isr);
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
        }
    }
    button_cross_collision(&menu->survive, &game_model.cross);

    render_button(&menu->survive, back_buffer);
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

void install_vector(int num, Vector vector) {
    Vector *vectp = (Vector *)((long)num << 2);
    long old_ssp = Super(0);
    *vectp = vector;
    Super(old_ssp);
}

void do_vbl_isr() {
    note++;
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
