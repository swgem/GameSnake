#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "allegro5/allegro5.h"

//// EXTERNAL FUNCTION DECLARATION

void init_graphical_resources();

void set_display(ALLEGRO_DISPLAY* display);
void destroy_display();

void draw_menu();

#endif
