typedef enum MOVEMENT_DIRECTION {
	MOVEMENT_DIRECTION_DOWN = 0,
	MOVEMENT_DIRECTION_UP,
	MOVEMENT_DIRECTION_LEFT,
	MOVEMENT_DIRECTION_RIGHT
} MOVEMENT_DIRECTION;

typedef struct SNAKE_SEG {
	int pos_y, pos_x;
	struct SNAKE_SEG* next_seg;
	MOVEMENT_DIRECTION direction;
} SNAKE_SEG;

typedef struct SNAKE {
	SNAKE_SEG head;
	int length;
	
} SNAKE;

void add_snake_seg(SNAKE* snake);
