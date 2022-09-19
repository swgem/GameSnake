#ifndef SNAKE_H
#define SNAKE_H

//// ENUM

typedef enum MOVEMENT_DIRECTION {
	MOVEMENT_DIRECTION_DOWN = 0,
	MOVEMENT_DIRECTION_UP,
	MOVEMENT_DIRECTION_LEFT,
	MOVEMENT_DIRECTION_RIGHT
} MOVEMENT_DIRECTION;

//// STRUCT

typedef struct SNAKE_SEG {
	int pos_x, pos_y;
	struct SNAKE_SEG* next_seg;
} SNAKE_SEG;

typedef struct SNAKE {
	SNAKE_SEG head;
	MOVEMENT_DIRECTION direction;
	int length;
	int speed; // blocks per frame
} SNAKE;

//// EXTERNAL FUNCTION DECLARATION

void add_snake_seg(SNAKE* snake);

void reset_snake(SNAKE* snake, int length, int pos_x, int pos_y, int speed, MOVEMENT_DIRECTION direction);

void move_snake(SNAKE* snake, int x_lim, int y_lim);

int check_snake_collision(SNAKE* snake);

#endif
