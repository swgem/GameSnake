#ifndef GAME_EXEC_FINISH_H
#define GAME_EXEC_FINISH_H

#include "AppNav.h"

//// ENUM

typedef enum {
    GAME_EXEC_FINISH_USER_ACTION_NONE = 0,
    GAME_EXEC_FINISH_USER_ACTION_EXIT
} GAME_EXEC_FINISH_USER_ACTION;

//// EXTERNAL FUNCTION DECLARATION

void reset_game_exec_finish();
APP_NAV_STATE handle_game_exec_finish_event(GAME_EXEC_FINISH_USER_ACTION action);
void set_game_finish_params(int final_score, int elapsed_time);
int get_final_score();
int get_total_elapsed_time();
void finish_game_exec_finish();

#endif
