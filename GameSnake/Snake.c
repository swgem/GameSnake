#include "Snake.h"
#include <stdlib.h>
#include "Logger.h"

//// INTERNAL FUNCTION DECLARATION

void destroy_segments(SNAKE_SEG* seg);

//// FUNCTION IMPLEMENTATION

void add_snake_seg(SNAKE* snake) {
	SNAKE_SEG* iter_tail = &snake->head;
	SNAKE_SEG* iter_pre_tail = NULL;

	while (iter_tail->next_seg != NULL) {
		iter_pre_tail = iter_tail;
		iter_tail = iter_tail->next_seg;
	}

	SNAKE_SEG* new_seg = (SNAKE_SEG*)malloc(sizeof(SNAKE_SEG));
	new_seg->next_seg = NULL;

	if (iter_pre_tail == NULL) {
		switch (snake->direction) {
		case MOVEMENT_DIRECTION_DOWN:
			new_seg->pos_x = iter_tail->pos_x;
			new_seg->pos_y = iter_tail->pos_y - 1;
			break;
		case MOVEMENT_DIRECTION_UP:
			new_seg->pos_x = iter_tail->pos_x;
			new_seg->pos_y = iter_tail->pos_y + 1;
			break;
		case MOVEMENT_DIRECTION_LEFT:
			new_seg->pos_x = iter_tail->pos_x + 1;
			new_seg->pos_y = iter_tail->pos_y;
			break;
		case MOVEMENT_DIRECTION_RIGHT:
			new_seg->pos_x = iter_tail->pos_x - 1;
			new_seg->pos_y = iter_tail->pos_y;
			break;
		default:
			log_msg("In function add_snake_seg, direction error.", LOG_TYPE_ERROR);
			break;
		}
	}
	else {
		if (iter_tail->pos_x < iter_pre_tail->pos_x) {
			new_seg->pos_x = iter_tail->pos_x - 1;
		}
		else if (iter_tail->pos_x > iter_pre_tail->pos_x) {
			new_seg->pos_x = iter_tail->pos_x + 1;
		}
		else {
			new_seg->pos_x = iter_tail->pos_x;
		}
		if (iter_tail->pos_y < iter_pre_tail->pos_y) {
			new_seg->pos_y = iter_tail->pos_y - 1;
		}
		else if (iter_tail->pos_y > iter_pre_tail->pos_y) {
			new_seg->pos_y = iter_tail->pos_y + 1;
		}
		else {
			new_seg->pos_y = iter_tail->pos_y;
		}
	}
	
	iter_tail->next_seg = new_seg;

	snake->length++;
}

void destroy_segments(SNAKE_SEG* seg) {
	if (seg->next_seg != NULL) {
		destroy_segments(seg->next_seg);
	}
	free(seg);
}

void reset_snake(SNAKE* snake, int length, int pos_x, int pos_y, int speed, MOVEMENT_DIRECTION direction) {
	// Destroy all segments leaving only the head
	if (snake->head.next_seg != NULL) destroy_segments(snake->head.next_seg);
	snake->length = 1;
	snake->head.next_seg = NULL;
	snake->head.pos_x = pos_x;
	snake->head.pos_y = pos_y;
	snake->speed = speed;
	snake->direction = direction;



	// Because the head is already present, we just need to add LEN-1 segments to fill LEN
	for (int i = 0; i < (length - 1); i++) {
		add_snake_seg(snake);
	}
	
}

void move_snake(SNAKE* snake){
	int x_new = snake->head.pos_x;
	int y_new = snake->head.pos_y;
	switch (snake->direction) {
	case MOVEMENT_DIRECTION_DOWN:
		snake->head.pos_y++;
		break;
	case MOVEMENT_DIRECTION_UP:
		snake->head.pos_y--;
		break;
	case MOVEMENT_DIRECTION_LEFT:
		snake->head.pos_x--;
		break;
	case MOVEMENT_DIRECTION_RIGHT:
		snake->head.pos_x++;
		break;
	default:
		log_msg("In function move_snake, direction error.", LOG_TYPE_ERROR);
		break;
	}
	SNAKE_SEG* iter = &snake->head;
	while (iter->next_seg != NULL) {
		int x_old = iter->next_seg->pos_x;
		int y_old = iter->next_seg->pos_y;
		
		iter->next_seg->pos_x = x_new;
		iter->next_seg->pos_y = y_new;
		x_new = x_old;
		y_new = y_old;
		iter = iter->next_seg;
	}
}

