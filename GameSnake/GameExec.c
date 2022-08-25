#include "GameExec.h"
#include <stdlib.h>
#include "Snake.h"
#include "DefaultConfig.h"
#include <time.h>

//// INTERNAL VARIABLE 

SNAKE g_snake = {.head = {.next_seg = NULL}, .length = 1};
FOOD g_food;
bool g_can_change_direction = true;
int g_score = 0;

static int g_timestamp_old = 0;

//// INTERNAL FUNCTION DECLARATION

void refresh_score(int snake_length, int period);

//// FUNCTION IMPLEMENTATION

void refresh_score(int snake_length, int period) {
    int add_score = (int)(((float)GAME_MAX_SCORE - (2.0f * (float)period) * (1.0f + 0.1f) * ((float)snake_length - ((float)GAME_SNAKE_INITIAL_LENGTH - 1.0f))));
    if (add_score < 10) {
        add_score = 10;
    }
    g_score += add_score;
}

void reset_game_exec() {
    reset_snake(&g_snake, GAME_SNAKE_INITIAL_LENGTH,
        GAME_SNAKE_INITIAL_POS_X, GAME_SNAKE_INITIAL_POS_Y,
        GAME_SNAKE_SPEED, GAME_SNAKE_INITIAL_DIRECTION);

    refresh_food_position(&g_food, &g_snake, (GAME_MAP_SIZE_X - 1), (GAME_MAP_SIZE_Y - 1));

    g_timestamp_old = (int)time(NULL);
}

APP_NAV_STATE handle_game_exec_timer() {
    APP_NAV_STATE next_state = APP_NAV_STATE_GAME_EXEC;
    static int count = 0; // each counted time, a DISPLAY_FRAME_RATE has passed
    
    if (count < (DISPLAY_FRAME_RATE/g_snake.speed - 1)) {
        count++;
    }
    else {
        // A full second has passed
        count = 0;
        move_snake(&g_snake, (GAME_MAP_SIZE_X - 1), (GAME_MAP_SIZE_Y - 1));
        
        //Check collision with itself
        if (check_snake_collision(&g_snake)) {
            next_state = APP_NAV_STATE_MENU;
        }

        //Check colision of the head with food
        if (g_food.pos_x == g_snake.head.pos_x && g_food.pos_y == g_snake.head.pos_y) {
            add_snake_seg(&g_snake);
            refresh_food_position(&g_food, &g_snake, (GAME_MAP_SIZE_X - 1), (GAME_MAP_SIZE_Y - 1));
            
            int timestamp_curr = (int)time(NULL);
            int diff = timestamp_curr - g_timestamp_old;

            refresh_score(g_snake.length, diff);

            g_timestamp_old = timestamp_curr;
        }
        g_can_change_direction = true;
    }
    return next_state;
}

APP_NAV_STATE handle_game_exec_event(GAME_EXEC_USER_ACTION action) {
    APP_NAV_STATE next_state = APP_NAV_STATE_GAME_EXEC;

    switch (action) {
    case GAME_EXEC_USER_ACTION_DOWN:
        if (g_can_change_direction && g_snake.direction != MOVEMENT_DIRECTION_UP) {
            g_snake.direction = MOVEMENT_DIRECTION_DOWN;
            g_can_change_direction = false;
        }
        break;
    case GAME_EXEC_USER_ACTION_UP:
        if (g_can_change_direction && g_snake.direction != MOVEMENT_DIRECTION_DOWN) {
            g_snake.direction = MOVEMENT_DIRECTION_UP;
            g_can_change_direction = false;
        }
        break;
    case GAME_EXEC_USER_ACTION_LEFT:
        if (g_can_change_direction && g_snake.direction != MOVEMENT_DIRECTION_RIGHT) {
            g_snake.direction = MOVEMENT_DIRECTION_LEFT;
            g_can_change_direction = false;
        }
        break;
    case GAME_EXEC_USER_ACTION_RIGHT:
        if (g_can_change_direction && g_snake.direction != MOVEMENT_DIRECTION_LEFT) {
            g_snake.direction = MOVEMENT_DIRECTION_RIGHT;
            g_can_change_direction = false;
        }
        break;
    case GAME_EXEC_USER_ACTION_SPACEBAR_KEYUP:
        g_snake.speed = GAME_SNAKE_SPEED;
        break;
    case GAME_EXEC_USER_ACTION_SPACEBAR_KEYDOWN:
        g_snake.speed = GAME_SNAKE_SPEED_FAST;
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
