#ifndef GAME_OVER_H
#define GAME_OVER_H

#include <stdbool.h>
#include "AppNav.h"

//// ENUM

typedef enum {
    GAME_OVER_USER_ACTION_NONE = 0,
    GAME_OVER_USER_ACTION_SELECT,
    GAME_OVER_USER_ACTION_SAVE_RECORD_YES,
    GAME_OVER_USER_ACTION_SAVE_RECORD_NO
} GAME_OVER_USER_ACTION;

typedef enum {
    GAME_OVER_MODE_DISPLAY_ONLY = 0,
    GAME_OVER_MODE_SAVE_RECORD_QUESTION,
    GAME_OVER_MODE_SAVE_RECORD_INPUT,
    GAME_OVER_MODE_WON
} GAME_OVER_MODE;

//// EXTERNAL FUNCTION DECLARATION

void reset_game_over();
APP_NAV_STATE handle_game_over_timer();
APP_NAV_STATE handle_game_over_event(GAME_OVER_USER_ACTION action);
APP_NAV_STATE handle_game_over_event_keychar(char unichar);
void set_game_over_params(int final_score, int elapsed_time);
int get_final_score();
int get_total_elapsed_time();
GAME_OVER_MODE get_game_over_mode();
bool get_save_record_state();
char* get_new_record_name();
void finish_game_over();

#endif
