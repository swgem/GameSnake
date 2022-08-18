#include "Food.h"
#include <time.h>
#include <stdlib.h>


void change_food_position(FOOD* food, int x_lim, int y_lim){
	srand(time(NULL));
	int r_x = rand();
	int r_y = rand();

	int x_old = food->x;
	int y_old = food->y;

	food->x = (r_x % (x_lim + 1));
	food->y = (r_y % (y_lim + 1));

	if ((food->x == x_old) && (food->y == y_old)) {
		change_food_position(food, x_lim, y_lim);
	}
}

bool check_collision_snake_food(SNAKE* snake, FOOD* food, SNAKE_SEG* ret_collided_seg) {
	bool collided = false;
	ret_collided_seg = NULL;
	SNAKE_SEG* iter = &snake->head;
	while (iter->next_seg != NULL) {
		iter = iter->next_seg;
		if ((food->x == iter->pos_x) && (food->y == iter->pos_y)) {
			collided = true;
			ret_collided_seg = iter;
			break;
		}
	}
	return collided;
}

void refresh_food_position(SNAKE* snake, FOOD* food, int x_lim, int y_lim) {
	SNAKE_SEG* ret_collided_seg = NULL;
	change_food_position(food, x_lim, y_lim);
	while (check_collision_snake_food(snake, food, ret_collided_seg)) {
		change_food_position(food, x_lim, y_lim);
	}
}
