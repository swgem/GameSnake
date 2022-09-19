#include "Food.h"
#include "Tools.h"

//// INTERNAL FUNCTION DECLARATION

static void change_food_position(FOOD* food, int x_lim, int y_lim);

//// FUNCTION IMPLEMENTATION

static void change_food_position(FOOD* food, int x_lim, int y_lim){
	int r_x = generate_random();
	int r_y = generate_random();

	int x_old = food->pos_x;
	int y_old = food->pos_y;

	food->pos_x = (r_x % (x_lim + 1));
	food->pos_y = (r_y % (y_lim + 1));

	if ((food->pos_x == x_old) && (food->pos_y == y_old)) {
		change_food_position(food, x_lim, y_lim);
	}
}

int check_collision_snake_food(const SNAKE* snake, const FOOD* food) {
	int collided = 0;
	if (food->pos_x == snake->head.pos_x && food->pos_y == snake->head.pos_y) {
		collided = 1;
	}
	return collided;
}

void refresh_food_position(FOOD* food, SNAKE* snake, int x_lim, int y_lim) {
	change_food_position(food, x_lim, y_lim);
	while (check_collision_snake_food(snake, food)) {
		change_food_position(food, x_lim, y_lim);
	}
}
