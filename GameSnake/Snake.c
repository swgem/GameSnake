#include "Snake.h"
#include <stdlib.h>
#include "Logger.h"

//// INTERNAL FUNCTION DECLARATION

void destroy_segments(SNAKE_SEG* seg);

//// FUNCTION IMPLEMENTATION

void add_snake_seg(SNAKE* snake) {
	SNAKE_SEG* iter = &snake->head;
	while (iter->next_seg != NULL) {
		iter = iter->next_seg;
	}
	SNAKE_SEG* new_seg = (SNAKE_SEG*)malloc(sizeof(SNAKE_SEG));
	new_seg->next_seg = NULL;
	new_seg->direction = iter->direction;
	switch (iter->direction) {
		case MOVEMENT_DIRECTION_DOWN:
			new_seg->pos_x = iter->pos_x;
			new_seg->pos_y = iter->pos_y - 1;
			break;
		case MOVEMENT_DIRECTION_UP:
			new_seg->pos_x = iter->pos_x;
			new_seg->pos_y = iter->pos_y + 1;
			break;
		case MOVEMENT_DIRECTION_LEFT:
			new_seg->pos_x = iter->pos_x + 1;
			new_seg->pos_y = iter->pos_y;
			break;
		case MOVEMENT_DIRECTION_RIGHT:
			new_seg->pos_x = iter->pos_x - 1;
			new_seg->pos_y = iter->pos_y;
			break;
		default:
			log_msg("In function add_snake_seg, direction error.", LOG_TYPE_ERROR);
			break;
	}
	iter->next_seg = new_seg;

	snake->length++;
}

void destroy_segments(SNAKE_SEG* seg) {
	if (seg->next_seg != NULL) {
		destroy_segments(seg->next_seg);
	}
	free(seg);
}

void reset_snake(SNAKE* snake, int length, int pos_x, int pos_y, MOVEMENT_DIRECTION direction) {
	// Destroy all segments leaving only the head
	if (snake->head.next_seg != NULL) destroy_segments(snake->head.next_seg);
	snake->length = 1;
	snake->head.next_seg = NULL;
	snake->head.pos_x = pos_x;
	snake->head.pos_y = pos_y;
	snake->head.direction = direction;

	// Because the head is already present, we just need to add LEN-1 segments to fill LEN
	for (int i = 0; i < (length - 1); i++) {
		add_snake_seg(snake);
	}
}
