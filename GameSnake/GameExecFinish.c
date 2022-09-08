#include "GameExecFinish.h"

//// INTERNAL VARIABLE

static int g_final_score;
static int g_elapsed_time;

//// FUNCTION IMPLEMENTATION

void reset_game_exec_finish() {

}

APP_NAV_STATE handle_game_exec_finish_event(GAME_EXEC_FINISH_USER_ACTION action) {
    APP_NAV_STATE next_state = APP_NAV_STATE_GAME_EXEC_FINISH;
    
    switch (action) {
    case GAME_EXEC_FINISH_USER_ACTION_EXIT:
        next_state = APP_NAV_STATE_MENU;
        break;
    default:
        break;
    }

    return next_state;
}

void set_game_finish_params(int final_score, int elapsed_time) {
    g_final_score = final_score;
    g_elapsed_time = elapsed_time;
}

int get_final_score() {
    return g_final_score;
}

int get_total_elapsed_time() {
    return g_elapsed_time;
}

void finish_game_exec_finish() {

}
