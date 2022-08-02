#include "Graphics.h"
#include "DefaultConfig.h"
#include "Logger.h"
#include "allegro5/allegro_color.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"

//// INTERNAL VARIABLE

static ALLEGRO_DISPLAY* g_display = NULL;

ALLEGRO_FONT* g_font_r24 = NULL;
ALLEGRO_FONT* g_font_r36 = NULL;
ALLEGRO_FONT* g_font_b72 = NULL;

//// FUNCTION IMPLEMENTATION

void init_graphical_resources() {
	// Loading system fonts
	if (!al_init_font_addon()) SYSTEM_FATAL("Could not initiate font addon!");
	if (!al_init_ttf_addon()) SYSTEM_FATAL("Could not initiate TTF addon!");

	g_font_r24 = al_load_ttf_font("res/Inconsolata-Regular.ttf", 24, 0);
	if (g_font_r24 == NULL) SYSTEM_FATAL("Could not initialize text font");

	g_font_r36 = al_load_ttf_font("res/Inconsolata-Regular.ttf", 36, 0);
	if (g_font_r36 == NULL) SYSTEM_FATAL("Could not initialize text font");

	g_font_b72 = al_load_ttf_font("res/Inconsolata-Regular.ttf", 72, 0);
	if (g_font_b72 == NULL) SYSTEM_FATAL("Could not initialize text font");

	// Creating display

	g_display = al_create_display(DISPLAY_RESOLUTION_X,
								  DISPLAY_RESOLUTION_Y);
	if (g_display == NULL) SYSTEM_FATAL("Could not create display");
}

const ALLEGRO_DISPLAY* get_display() {
	return g_display;
}

void destroy_display() {
	al_destroy_display(g_display);
}

void draw_menu() {
	// Draw background
	ALLEGRO_COLOR bg_color = al_color_html(APP_BG_COLOR);
	al_clear_to_color(bg_color);

	ALLEGRO_COLOR text_color = al_color_html(APP_TEXT_COLOR);

	// Draw title
	al_draw_text(g_font_b72, text_color, (DISPLAY_RESOLUTION_X / 2), (DISPLAY_RESOLUTION_Y / 2) - 108,
		ALLEGRO_ALIGN_CENTRE, "SNAKE");

	// Draw options
	al_draw_text(g_font_r36, text_color, (DISPLAY_RESOLUTION_X / 2), (DISPLAY_RESOLUTION_Y / 2) + 36,
		ALLEGRO_ALIGN_CENTRE, "PLAY");
	al_draw_text(g_font_r36, text_color, (DISPLAY_RESOLUTION_X / 2), (DISPLAY_RESOLUTION_Y / 2) + 36 * 2,
		ALLEGRO_ALIGN_CENTRE, "RECORDS");
	al_draw_text(g_font_r36, text_color, (DISPLAY_RESOLUTION_X / 2), (DISPLAY_RESOLUTION_Y / 2) + 36 * 3,
		ALLEGRO_ALIGN_CENTRE, "SETTINGS");
	al_draw_text(g_font_r36, text_color, (DISPLAY_RESOLUTION_X / 2), (DISPLAY_RESOLUTION_Y / 2) + 36 * 4,
		ALLEGRO_ALIGN_CENTRE, "EXIT");
}
