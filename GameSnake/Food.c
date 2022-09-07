#include "Food.h"
#include <time.h>
#include <stdlib.h>

//// INTERNAL FUNCTION DECLARATION

static void change_food_position(FOOD* food, int x_lim, int y_lim);

//// FUNCTION IMPLEMENTATION

static void change_food_position(FOOD* food, int x_lim, int y_lim){
	int r_x = rand();
	int r_y = rand();

	int x_old = food->pos_x;
	int y_old = food->pos_y;

	food->pos_x = (r_x % (x_lim + 1));
	food->pos_y = (r_y % (y_lim + 1));

	if ((food->pos_x == x_old) && (food->pos_y == y_old)) {
		change_food_position(food, x_lim, y_lim);
	}
}

bool check_collision_snake_food(SNAKE* snake, FOOD* food) {
	bool collided = false;
	SNAKE_SEG* iter = &snake->head;
	while (iter->next_seg != NULL) {
		iter = iter->next_seg;
		if ((food->pos_x == iter->pos_x) && (food->pos_y == iter->pos_y)) {
			collided = true;
			break;
		}
	}
	return collided;
}

void refresh_food_position(FOOD* food, SNAKE* snake, int x_lim, int y_lim) {
	change_food_position(food, x_lim, y_lim);
	while (check_collision_snake_food(snake, food)) {
		change_food_position(food, x_lim, y_lim);
	}
}
