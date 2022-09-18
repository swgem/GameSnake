#include "GameConfig.h"

//// INTERNAL VARIABLE

static int g_game_running_period = 0;
static int g_game_map_size_x = 0;
static int g_game_map_size_y = 0;
static int g_max_score = 0;
static int g_snake_initial_length = 0;
static int g_snake_initial_pos_x = 0;
static int g_snake_initial_pos_y = 0;
static int g_snake_initial_speed = 0;
static MOVEMENT_DIRECTION g_snake_initial_direction = (MOVEMENT_DIRECTION)0;

//// FUNCTION IMPLEMENTATION

int cfg_game_running_period() {
    return g_game_running_period;
}

int cfg_game_map_size_x() {
    return g_game_map_size_x;
}

int cfg_game_map_size_y() {
    return g_game_map_size_y;
}

int cfg_max_score() {
    return g_max_score;
}

int cfg_snake_initial_length() {
    return g_snake_initial_length;
}

int cfg_snake_initial_pos_x() {
    return g_snake_initial_pos_x;
}

int cfg_snake_initial_pos_y() {
    return g_snake_initial_pos_y;
}

int cfg_snake_initial_speed() {
    return g_snake_initial_speed;
}

MOVEMENT_DIRECTION cfg_snake_initial_direction() {
    return g_snake_initial_direction;
}

void set_game_config(int game_running_period, int game_map_size_x, int game_map_size_y,
    int max_score, int snake_initial_length, int snake_initial_pos_x, int snake_initial_pos_y,
    int snake_initial_speed, MOVEMENT_DIRECTION snake_initial_direction) {
    g_game_running_period = game_running_period;
    g_game_map_size_x = game_map_size_x;
    g_game_map_size_y = game_map_size_y;
    g_max_score = max_score;
    g_snake_initial_length = snake_initial_length;
    g_snake_initial_pos_x = snake_initial_pos_x;
    g_snake_initial_pos_y = snake_initial_pos_y;
    g_snake_initial_speed = snake_initial_speed;
    g_snake_initial_direction = snake_initial_direction;
}
