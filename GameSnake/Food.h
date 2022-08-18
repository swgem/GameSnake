#ifndef FOOD_H
#define FOOD_H
#include "Snake.h"
#include <stdbool.h>

//// STRUCT

typedef struct {
	int pos_x;
	int pos_y;
}FOOD;

//// EXTERNAL FUNCTION DECLARATION

bool check_collision_snake_food(SNAKE* snake, FOOD* food);

void refresh_food_position(FOOD* food, SNAKE* snake, int x_lim, int y_lim);

#endif
