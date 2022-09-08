#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "allegro5/allegro5.h"
#include "Menu.h"

//// EXTERNAL FUNCTION DECLARATION

void init_graphical_resources();

const ALLEGRO_DISPLAY* get_display();
void destroy_display();

void draw_menu();
void draw_game_exec();
void draw_game_exec_finish();
MENU_OPTION get_option_in_click_point(int x, int y);

#endif
