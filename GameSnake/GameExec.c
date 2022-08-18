#include "GameExec.h"
#include <stdlib.h>
#include "Snake.h"
#include "DefaultConfig.h"

//// INTERNAL VARIABLE 

SNAKE g_snake = {.head = {.next_seg = NULL}, .length = 1};
FOOD g_food;

//// FUNCTION IMPLEMENTATION

void reset_game_exec() {
    reset_snake(&g_snake, GAME_SNAKE_INITIAL_LENGTH,
        GAME_SNAKE_INITIAL_POS_X, GAME_SNAKE_INITIAL_POS_Y,
        GAME_SNAKE_SPEED, GAME_SNAKE_INITIAL_DIRECTION);

    refresh_food_position(&g_food, &g_snake, (GAME_MAP_SIZE_X - 1), (GAME_MAP_SIZE_Y - 1));
}

APP_NAV_STATE handle_game_exec_timer() {
    APP_NAV_STATE next_state = APP_NAV_STATE_GAME_EXEC;
    static int count = 0; // each counted time, a DISPLAY_FRAME_RATE has passed
    
    if (count < (DISPLAY_FRAME_RATE/2 - 1)) {
        count++;
    }
    else {
        // A full second has passed
        count = 0;
        move_snake(&g_snake, (GAME_MAP_SIZE_X - 1), (GAME_MAP_SIZE_Y - 1));
        if (check_snake_collision(&g_snake)) {
            next_state = APP_NAV_STATE_MENU;
        }
    }
    return next_state;
}

APP_NAV_STATE handle_game_exec_event(GAME_EXEC_USER_ACTION action) {
    APP_NAV_STATE next_state = APP_NAV_STATE_GAME_EXEC;

    switch (action) {
    case GAME_EXEC_USER_ACTION_DOWN:
        if (g_snake.direction != MOVEMENT_DIRECTION_UP) {
            g_snake.direction = MOVEMENT_DIRECTION_DOWN;
        }
        break;
    case GAME_EXEC_USER_ACTION_UP:
        if (g_snake.direction != MOVEMENT_DIRECTION_DOWN) {
            g_snake.direction = MOVEMENT_DIRECTION_UP;
        }
        break;
    case GAME_EXEC_USER_ACTION_LEFT:
        if (g_snake.direction != MOVEMENT_DIRECTION_RIGHT) {
            g_snake.direction = MOVEMENT_DIRECTION_LEFT;
        }
        break;
    case GAME_EXEC_USER_ACTION_RIGHT:
        if (g_snake.direction != MOVEMENT_DIRECTION_LEFT) {
            g_snake.direction = MOVEMENT_DIRECTION_RIGHT;
        }
        break;
    default:
        break;
    }

    return next_state;
}

const SNAKE* get_snake() {
    return &g_snake;
}

const FOOD* get_food() {
    return &g_food;
}
