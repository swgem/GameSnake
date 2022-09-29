#include "GameController.h"
#include "GameConfig.h"
#include "LoggerInterface.h"
#include "Snake.h"
#include "Food.h"

//// INTERNAL VARIABLE 

static SNAKE g_snake = { .head = {.next_seg = (void*)0}, .length = 1 };
static FOOD g_food;
static int g_elapsed_time = 0; // seconds
static int g_score = 0;
static int g_gametick = 0; // count +1 every game running period and starts with game
static int g_last_score_gametick = 0;

//// INTERNAL FUNCTION DECLARATION

static void refresh_score(int snake_length, int period);

//// FUNCTION IMPLEMENTATION

static void refresh_score(int snake_length, int period) {
    int add_score = (int)(((float)cfg_max_score() - (2.0f * (float)period)) *
        (1.0f + (0.1f * ((float)snake_length - ((float)cfg_snake_initial_length() - 1.0f)))));
    if (add_score < 10) {
        add_score = 10;
    }
    g_score += add_score;
}

const SNAKE* get_snake() {
    return &g_snake;
}

const FOOD* get_food() {
    return &g_food;
}

int get_score() {
    return g_score;
}

float get_elapsed_time() {
    return (g_gametick * cfg_game_running_period() / 1000.0f);
}

void set_snake_direction(MOVEMENT_DIRECTION direction) {
    g_snake.direction = direction;
}

void set_snake_speed(int speed) {
    g_snake.speed = speed;
}

void game_restart() {
    reset_snake(&g_snake, cfg_snake_initial_length(),
        cfg_snake_initial_pos_x(), cfg_snake_initial_pos_y(),
        cfg_snake_initial_speed(), cfg_snake_initial_direction());

    refresh_food_position(&g_food, &g_snake, (cfg_game_map_size_x() - 1), (cfg_game_map_size_y() - 1));

    g_score = 0;
    g_last_score_gametick = 0;
}

GAME_EVENT game_run() {
    GAME_EVENT ret = GAME_EVENT_NONE;

    g_gametick++;
    int count_refresh = ((int)((1.0f / ((float)cfg_game_running_period() / 1000.0f)) / (float)g_snake.speed) - 1);
    if (count_refresh <= 0) {
        count_refresh = 1;
#ifdef USE_LOGGER
        log_msg("Snake speed too high to process", LOG_TYPE_ERROR);
#endif
    }
    if ((g_gametick % count_refresh) == 0) {
        move_snake(&g_snake, (cfg_game_map_size_x() - 1), (cfg_game_map_size_y() - 1));
        ret = GAME_EVENT_SNAKE_MOVED;

        //Check colision of the head with food
        if (check_collision_snake_food(&g_snake, &g_food)) {
            add_snake_seg(&g_snake);
            refresh_food_position(&g_food, &g_snake, (cfg_game_map_size_x() - 1), (cfg_game_map_size_y() - 1));

            int diff_sec = (int)((g_gametick - g_last_score_gametick) * cfg_game_running_period() / 1000.0f);
            refresh_score(g_snake.length, diff_sec);

            g_last_score_gametick = g_gametick;

            ret = GAME_EVENT_SNAKE_ATE_FOOD;
#ifdef USE_LOGGER
            log_msg("Snake ate food.", LOG_TYPE_INFO);
#endif
        }

        //Check collision with itself
        if (check_snake_collision(&g_snake)) {
            ret = GAME_EVENT_SNAKE_DIED;
#ifdef USE_LOGGER
            log_msg("Snake collided itself and died.", LOG_TYPE_INFO);
#endif
        }
    }

    return ret;
}
