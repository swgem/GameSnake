#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

#include "Snake.h"

//// MACRO

#define USE_LOGGER // if defined, (!)implement external method

//// EXTERNAL FUNCTION DECLARATION

int cfg_game_running_period(); /// miliseconds
int cfg_game_map_size_x();
int cfg_game_map_size_y();
int cfg_max_score();
int cfg_snake_initial_length();
int cfg_snake_initial_pos_x();
int cfg_snake_initial_pos_y();
int cfg_snake_initial_speed();
MOVEMENT_DIRECTION cfg_snake_initial_direction();

void set_game_config(int game_running_period, int game_map_size_x, int game_map_size_y,
    int max_score, int snake_initial_length, int snake_initial_pos_x, int snake_initial_pos_y,
    int snake_initial_speed, MOVEMENT_DIRECTION snake_initial_direction);

#endif
