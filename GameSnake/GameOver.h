#ifndef GAME_OVER_H
#define GAME_OVER_H

#include "AppNav.h"

//// ENUM

typedef enum {
    GAME_OVER_USER_ACTION_NONE = 0,
    GAME_OVER_USER_ACTION_EXIT
} GAME_OVER_USER_ACTION;

//// EXTERNAL FUNCTION DECLARATION

void reset_game_over();
APP_NAV_STATE handle_game_over_event(GAME_OVER_USER_ACTION action);
void set_game_over_params(int final_score, int elapsed_time);
int get_final_score();
int get_total_elapsed_time();
void finish_game_over();

#endif
