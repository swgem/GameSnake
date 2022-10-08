#include "GameExec.h"
#include <stdbool.h>
#include "DefaultConfig.h"
#include "Logger.h"
#include "GameOver.h"
#include "Audio.h"

//// INTERNAL VARIABLE

static bool g_up_key_down = false;
static bool g_down_key_down = false;
static bool g_left_key_down = false;
static bool g_right_key_down = false;
static bool g_any_key_down = false;
static bool g_is_paused = false;
static float g_time_to_speed = 0;
static bool g_won_game = false;

//// INTERNAL FUNCTION DECLARATION

static MOVEMENT_DIRECTION actual_curr_snake_direction(const SNAKE* snake);

//// FUNCTION IMPLEMENTATION

bool is_game_won() {
    return g_won_game;
}

static MOVEMENT_DIRECTION actual_curr_snake_direction(const SNAKE* snake) {
    MOVEMENT_DIRECTION ret = snake->direction;
    if (snake->head.next_seg != (void*)0) {
        if (snake->head.pos_x == snake->head.next_seg->pos_x) {
            if (snake->head.pos_y > snake->head.next_seg->pos_y) {
                ret = MOVEMENT_DIRECTION_DOWN;
            }
            else {
                ret = MOVEMENT_DIRECTION_UP;
            }
        }
        else if (snake->head.pos_y == snake->head.next_seg->pos_y) {
            if (snake->head.pos_x > snake->head.next_seg->pos_x) {
                ret = MOVEMENT_DIRECTION_RIGHT;
            }
            else {
                ret = MOVEMENT_DIRECTION_LEFT;
            }
        }
        else {
            log_msg("Something is really wrong with snake segments position...", LOG_TYPE_ERROR);
        }
    }
    return ret;
}

bool is_game_paused() {
    return g_is_paused;

}

void reset_game_exec() {
    play_game_exec_audio();
    game_restart();
    g_won_game = false;
    g_up_key_down = false;
    g_down_key_down = false;
    g_left_key_down = false;
    g_right_key_down = false;
    g_any_key_down = false;
    g_is_paused = false;
}

void finish_game_exec() {
    set_game_over_params(get_score(), (int)get_elapsed_time());
    reset_audio();
}

APP_NAV_STATE handle_game_exec_timer() {
    APP_NAV_STATE next_state = APP_NAV_STATE_GAME_EXEC;
    
    if (g_up_key_down || g_down_key_down || g_left_key_down || g_right_key_down) {
        g_any_key_down = true;
    }
    else {
        g_any_key_down = false;
    }

    if (g_any_key_down && (get_elapsed_time() - g_time_to_speed) > 0.5f) {
        set_snake_speed(GAME_SNAKE_SPEED_FAST);
    }
    else {
        set_snake_speed(GAME_SNAKE_SPEED);
    }

    if (!g_is_paused) {
        GAME_EVENT event = game_run();
        switch (event) {
        case GAME_EVENT_NONE:
            break;
        case GAME_EVENT_SNAKE_MOVED:
            break;
        case GAME_EVENT_SNAKE_ATE_FOOD:
            play_food_audio();
            break;
        case GAME_EVENT_SNAKE_DIED:
            next_state = APP_NAV_STATE_GAME_OVER;
            break;
        default:
            log_msg("Invalid game event", LOG_TYPE_ERROR);
            break;
        }
    }

    if ((GAME_MAP_SIZE_X * GAME_MAP_SIZE_Y) == get_snake()->length) {
        next_state = APP_NAV_STATE_GAME_OVER;
        g_won_game = true;
    }

    return next_state;
}

APP_NAV_STATE handle_game_exec_event(GAME_EXEC_USER_ACTION action) {
    APP_NAV_STATE next_state = APP_NAV_STATE_GAME_EXEC;
   
    switch (action) {
    case GAME_EXEC_USER_ACTION_DOWN_KEYDOWN:
        g_time_to_speed = get_elapsed_time();
        if (actual_curr_snake_direction(get_snake()) != MOVEMENT_DIRECTION_UP) {
            g_down_key_down = true;
            set_snake_direction(MOVEMENT_DIRECTION_DOWN);
        }
        break;
    case GAME_EXEC_USER_ACTION_UP_KEYDOWN:
        g_time_to_speed = get_elapsed_time();
        if (actual_curr_snake_direction(get_snake()) != MOVEMENT_DIRECTION_DOWN) {
            g_up_key_down = true;
            set_snake_direction(MOVEMENT_DIRECTION_UP);
        }
        break;
    case GAME_EXEC_USER_ACTION_LEFT_KEYDOWN:
        g_time_to_speed = get_elapsed_time();
        if (actual_curr_snake_direction(get_snake()) != MOVEMENT_DIRECTION_RIGHT) {
            g_left_key_down = true;
            set_snake_direction(MOVEMENT_DIRECTION_LEFT);
        }
        break;
    case GAME_EXEC_USER_ACTION_RIGHT_KEYDOWN:
        g_time_to_speed = get_elapsed_time();
        if (actual_curr_snake_direction(get_snake()) != MOVEMENT_DIRECTION_LEFT) {
            g_right_key_down = true;
            set_snake_direction(MOVEMENT_DIRECTION_RIGHT);
        }
        break;
    case GAME_EXEC_USER_ACTION_DOWN_KEYUP:
            g_down_key_down = false;
        break;
    case GAME_EXEC_USER_ACTION_UP_KEYUP:
            g_up_key_down = false;
        break;
    case GAME_EXEC_USER_ACTION_LEFT_KEYUP:
            g_left_key_down = false;
        break;
    case GAME_EXEC_USER_ACTION_RIGHT_KEYUP:
            g_right_key_down = false;
        break;
    case GAME_EXEC_USER_ACTION_PAUSE:
        if (!g_is_paused) {
            g_is_paused = true;
            play_pause_audio();
        }
        else {
            g_is_paused = false;
        }
        break;
    default:
        break;
    }

    return next_state;
}
