#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "Snake.h"
#include "Food.h"

//// ENUM

typedef enum {
    GAME_EVENT_NONE = 0,
    GAME_EVENT_SNAKE_MOVED,
    GAME_EVENT_SNAKE_ATE_FOOD,
    GAME_EVENT_SNAKE_DIED
} GAME_EVENT;

//// EXTERNAL FUNCTION DECLARATION

const SNAKE* get_snake();
const FOOD* get_food();
int get_score();
int get_elapsed_time();

void set_snake_direction(MOVEMENT_DIRECTION direction);
void set_snake_speed(int speed);

void game_restart();

GAME_EVENT game_run();

#endif
