#include "Snake.h"
#include "LoggerInterface.h"
#include "Tools.h"
#include "GameConfig.h"

//// INTERNAL FUNCTION DECLARATION

static void destroy_segments(SNAKE_SEG* seg);

//// FUNCTION IMPLEMENTATION

void add_snake_seg(SNAKE* snake) {
	SNAKE_SEG* iter_tail = &snake->head;
	SNAKE_SEG* iter_pre_tail = (void*)0;

	while (iter_tail->next_seg != (void*)0) {
		iter_pre_tail = iter_tail;
		iter_tail = iter_tail->next_seg;
	}

	SNAKE_SEG* new_seg = (SNAKE_SEG*)mem_alloc(sizeof(SNAKE_SEG));
	if (new_seg == (void*)0) {
#ifdef USE_LOGGER
		log_msg("Could not allocate memory for snake seg", LOG_TYPE_FATAL);
#endif
		system_fatal();
	}
	
	new_seg->next_seg = (void*)0;

	if (iter_pre_tail == (void*)0) {
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
#ifdef USE_LOGGER
			log_msg("In function add_snake_seg, direction error.", LOG_TYPE_ERROR);
#endif
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

static void destroy_segments(SNAKE_SEG* seg) {
	if (seg->next_seg != (void*)0) {
		destroy_segments(seg->next_seg);
	}
	mem_free(seg);
}

void reset_snake(SNAKE* snake, int length, int pos_x, int pos_y, int speed, MOVEMENT_DIRECTION direction) {
	// Destroy all segments leaving only the head
	if (snake->head.next_seg != (void*)0) destroy_segments(snake->head.next_seg);
	snake->length = 1;
	snake->head.next_seg = (void*)0;
	snake->head.pos_x = pos_x;
	snake->head.pos_y = pos_y;
	snake->speed = speed;
	snake->direction = direction;



	// Because the head is already present, we just need to add LEN-1 segments to fill LEN
	for (int i = 0; i < (length - 1); i++) {
		add_snake_seg(snake);
	}
	
}

void move_snake(SNAKE* snake, int x_lim, int y_lim){
	int x_new = snake->head.pos_x;
	int y_new = snake->head.pos_y;
	switch (snake->direction) {
	case MOVEMENT_DIRECTION_DOWN:
		if (++snake->head.pos_y > y_lim) {
			snake->head.pos_y = 0;
		}
		break;
	case MOVEMENT_DIRECTION_UP:
		if (--snake->head.pos_y < 0) {
			snake->head.pos_y = y_lim;
		}
		break;
	case MOVEMENT_DIRECTION_LEFT:
		if (--snake->head.pos_x < 0) {
			snake->head.pos_x = x_lim;
		}
		break;
	case MOVEMENT_DIRECTION_RIGHT:
		if (++snake->head.pos_x > x_lim) {
			snake->head.pos_x = 0;
		}
		break;
	default:
#ifdef USE_LOGGER
		log_msg("In function move_snake, direction error.", LOG_TYPE_ERROR);
#endif
		break;
	}
	SNAKE_SEG* iter = &snake->head;
	while (iter->next_seg != (void*)0) {
		int x_old = iter->next_seg->pos_x;
		int y_old = iter->next_seg->pos_y;
		
		iter->next_seg->pos_x = x_new;
		iter->next_seg->pos_y = y_new;
		x_new = x_old;
		y_new = y_old;
		iter = iter->next_seg;
	}
}

int check_snake_collision(SNAKE* snake) {
	int collided = 0;
	SNAKE_SEG* iter = snake->head.next_seg;
	while (iter != (void*)0) {
		if (iter->pos_x == snake->head.pos_x && iter->pos_y == snake->head.pos_y) {
			collided = 1;
			break;
		}
		iter = iter->next_seg;
	}
	return collided;
}
