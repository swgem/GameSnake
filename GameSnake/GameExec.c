#include "GameExec.h"
#include <stdbool.h>
#include "DefaultConfig.h"
#include "Logger.h"
#include "GameOver.h"
#include "Audio.h"

//// INTERNAL VARIABLE 

static bool g_is_paused = false;
static bool g_can_change_direction = true;

//// FUNCTION IMPLEMENTATION

void reset_game_exec() {
    play_game_exec_audio();
    game_restart();
}

void finish_game_exec() {
    set_game_over_params(get_score(), get_elapsed_time());
    reset_audio();
}

APP_NAV_STATE handle_game_exec_timer() {
    APP_NAV_STATE next_state = APP_NAV_STATE_GAME_EXEC;
    if (!g_is_paused) {
        GAME_EVENT event = game_run();
        switch (event) {
        case GAME_EVENT_NONE:
            break;
        case GAME_EVENT_SNAKE_MOVED:
            g_can_change_direction = true;
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
    return next_state;
}

APP_NAV_STATE handle_game_exec_event(GAME_EXEC_USER_ACTION action) {
    APP_NAV_STATE next_state = APP_NAV_STATE_GAME_EXEC;

    switch (action) {
    case GAME_EXEC_USER_ACTION_DOWN:
        if (g_can_change_direction && get_snake()->direction != MOVEMENT_DIRECTION_UP) {
            set_snake_direction(MOVEMENT_DIRECTION_DOWN);
            g_can_change_direction = false;
        }
        break;
    case GAME_EXEC_USER_ACTION_UP:
        if (g_can_change_direction && get_snake()->direction != MOVEMENT_DIRECTION_DOWN) {
            set_snake_direction(MOVEMENT_DIRECTION_UP);
            g_can_change_direction = false;
        }
        break;
    case GAME_EXEC_USER_ACTION_LEFT:
        if (g_can_change_direction && get_snake()->direction != MOVEMENT_DIRECTION_RIGHT) {
            set_snake_direction(MOVEMENT_DIRECTION_LEFT);
            g_can_change_direction = false;
        }
        break;
    case GAME_EXEC_USER_ACTION_RIGHT:
        if (g_can_change_direction && get_snake()->direction != MOVEMENT_DIRECTION_LEFT) {
            set_snake_direction(MOVEMENT_DIRECTION_RIGHT);
            g_can_change_direction = false;
        }
        break;
    case GAME_EXEC_USER_ACTION_PAUSE:
        if (!g_is_paused) {
            g_is_paused = true;
        }
        else {
            g_is_paused = false;
        }
        break;
    case GAME_EXEC_USER_ACTION_SPACEBAR_KEYUP:
        set_snake_speed(GAME_SNAKE_SPEED);
        break;
    case GAME_EXEC_USER_ACTION_SPACEBAR_KEYDOWN:
        set_snake_speed(GAME_SNAKE_SPEED_FAST);
        break;
    default:
        break;
    }

    return next_state;
}
