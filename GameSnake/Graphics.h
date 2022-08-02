#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "allegro5/allegro5.h"

//// EXTERNAL FUNCTION DECLARATION

void init_graphical_resources();

const ALLEGRO_DISPLAY* get_display();
void destroy_display();

void draw_menu();

#endif
