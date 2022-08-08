#ifndef GAME_EXEC_H
#define GAME_EXEC_H

#include "AppNav.h"
#include "Snake.h"

//// ENUM

typedef enum {
    GAME_EXEC_USER_ACTION_NONE = 0,
    GAME_EXEC_USER_ACTION_DOWN,
    GAME_EXEC_USER_ACTION_UP,
    GAME_EXEC_USER_ACTION_LEFT,
    GAME_EXEC_USER_ACTION_RIGHT
} GAME_EXEC_USER_ACTION;

//// EXTERNAL FUNCTION DECLARATION

void reset_game_exec();

APP_NAV_STATE handle_game_exec_timer();

APP_NAV_STATE handle_game_exec_event(GAME_EXEC_USER_ACTION action);

const SNAKE* get_snake();

#endif
