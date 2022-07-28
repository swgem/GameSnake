#include "graphics.h"

//// INTERNAL VARIABLE

static ALLEGRO_DISPLAY* g_display = NULL;

//// FUNCTION IMPLEMENTATION

void set_display(ALLEGRO_DISPLAY* display) {
	g_display = display;
}

void destroy_display() {
	al_destroy_display(g_display);
}
