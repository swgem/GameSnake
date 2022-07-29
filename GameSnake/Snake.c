#include "Snake.h"
#include <stdlib.h>
#include "Logger.h"

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
