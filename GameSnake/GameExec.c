#include "GameExec.h"
#include <stdlib.h>
#include "Snake.h"
#include "DefaultConfig.h"

//// INTERNAL VARIABLE 

SNAKE g_snake = {.head = {.next_seg = NULL}, .length = 1};

//// FUNCTION IMPLEMENTATION

void reset_game_exec() {
    reset_snake(&g_snake, GAME_SNAKE_INITIAL_LENGTH,
        GAME_SNAKE_INITIAL_POS_X, GAME_SNAKE_INITIAL_POS_Y,
        GAME_SNAKE_SPEED, GAME_SNAKE_INITIAL_DIRECTION);
}

APP_NAV_STATE handle_game_exec_timer() {
    move_snake(&g_snake);
    return APP_NAV_STATE_GAME_EXEC;
}
