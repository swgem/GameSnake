#include "Graphics.h"
#include "DefaultConfig.h"
#include "Logger.h"
#include "allegro5/allegro_color.h"
#include "allegro5/allegro_font.h"

//// INTERNAL VARIABLE

static ALLEGRO_DISPLAY* g_display = NULL;

ALLEGRO_FONT* g_font = NULL;

//// FUNCTION IMPLEMENTATION

void init_graphical_resources() {
	if (!al_init_font_addon()) SYSTEM_FATAL("Could not initiate font addon!");

	g_font = al_create_builtin_font();
	if (g_font == NULL) SYSTEM_FATAL("Could not initialize text font");
}

void set_display(ALLEGRO_DISPLAY* display) {
	g_display = display;
}

void destroy_display() {
	al_destroy_display(g_display);
}

void draw_menu() {
	// Draw background
	ALLEGRO_COLOR bg_color = al_color_html(APP_BG_COLOR);
	al_clear_to_color(bg_color);

	// Draw options
	ALLEGRO_COLOR text_color = al_color_html(APP_TEXT_COLOR);
	al_draw_text(g_font, text_color, 0, 0, 0, "Hello world!");
}
