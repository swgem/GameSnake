#ifndef DEFAULT_CONFIG_H
#define DEFAULT_CONFIG_H

#include "AppNav.h"

//// DISPLAY DEFINITION

#define DISPLAY_RESOLUTION_X 640
#define DISPLAY_RESOLUTION_Y 480

#define DISPLAY_FRAME_RATE 30.0f // Hz

#define APP_BG_COLOR "#c9c72c"
#define APP_TEXT_COLOR "#737119"
#define APP_TEXT_HIGHLIGHT_COLOR "#ffffff"
#define APP_MAP_LINE_COLOR "#ffffff"
#define APP_SNAKE_COLOR "#008000"
#define APP_SNAKE_HEAD_COLOR "#8a2be2"
#define APP_FOOD_COLOR "#0000ff"

//// GAME DEFINITION

#define GAME_MAP_SIZE_X 15 // block
#define GAME_MAP_SIZE_Y 15 // block

#define GAME_SNAKE_SPEED 2 // blocks/seg
#define GAME_SNAKE_INITIAL_LENGTH 3
#define GAME_SNAKE_INITIAL_POS_X 6
#define GAME_SNAKE_INITIAL_POS_Y 8
#define GAME_SNAKE_INITIAL_DIRECTION MOVEMENT_DIRECTION_RIGHT

//// LOGGER DEFINITION

#define LOGGER_FILENAME "gamesnake.log"
#define LOGGER_MAX_FILE_SIZE 2*1024*1024 // 2MB in bytes

#endif
