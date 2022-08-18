#ifndef FOOD_H
#define FOOD_H
#include "Snake.h"
#include <stdbool.h>

//// STRUCT

typedef struct {
	int x;
	int y;
}FOOD;

//// EXTERNAL FUNCTION DECLARATION

void change_food_position(FOOD* food, int x_lim, int y_lim);

bool check_collision_snake_food(SNAKE* snake, FOOD* food, SNAKE_SEG* ret_collided_seg);

void refresh_food_position(SNAKE* snake, FOOD* food, int x_lim, int y_lim);

#endif
