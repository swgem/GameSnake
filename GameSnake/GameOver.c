#include "GameOver.h"
#include "Audio.h"
#include "RecordsController.h"

//// INTERNAL VARIABLE

static int g_final_score;
static int g_elapsed_time;

//// FUNCTION IMPLEMENTATION

void reset_game_over() {
    play_death_audio();
}

APP_NAV_STATE handle_game_over_event(GAME_OVER_USER_ACTION action) {
    APP_NAV_STATE next_state = APP_NAV_STATE_GAME_OVER;
    
    switch (action) {
    case GAME_OVER_USER_ACTION_EXIT:
        next_state = APP_NAV_STATE_MENU;
        break;
    default:
        break;
    }

    return next_state;
}

void set_game_over_params(int final_score, int elapsed_time) {
    g_final_score = final_score;
    g_elapsed_time = elapsed_time;
}

int get_final_score() {
    return g_final_score;
}

int get_total_elapsed_time() {
    return g_elapsed_time;
}

void finish_game_over() {
    reset_audio();
}
