#include "Graphics.h"
#include "DefaultConfig.h"
#include "Logger.h"
#include "AppText.h"
#include "allegro5/allegro_color.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_primitives.h"

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
	if (!al_init_primitives_addon()) SYSTEM_FATAL("Could not initiate primitives addon!");


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
	ALLEGRO_COLOR text_color = al_color_html(APP_TEXT_COLOR);
	ALLEGRO_COLOR text_highlight_color = al_color_html(APP_TEXT_HIGHLIGHT_COLOR);

	al_clear_to_color(bg_color);

	// Draw title
	al_draw_text(g_font_b72, text_color, (DISPLAY_RESOLUTION_X / 2), (DISPLAY_RESOLUTION_Y / 2) - 108,
		ALLEGRO_ALIGN_CENTRE, get_app_text(APP_TEXT_ID_MENU_TITLE));

	int w = 0, h = 0;
	h = al_get_font_line_height(g_font_r36);
	switch (get_option_highlight()) {
	case MENU_OPTION_NONE:
		break;
	case MENU_OPTION_PLAY:
		w = al_get_text_width(g_font_r36, get_app_text(APP_TEXT_ID_MENU_OP1));
		al_draw_filled_rectangle((DISPLAY_RESOLUTION_X / 2) - (w / 2), (DISPLAY_RESOLUTION_Y / 2) + 36,
			(DISPLAY_RESOLUTION_X / 2) + (w / 2), (DISPLAY_RESOLUTION_Y / 2) + 36 + h, text_highlight_color);
		break;
	case MENU_OPTION_RECORDS:
		w = al_get_text_width(g_font_r36, get_app_text(APP_TEXT_ID_MENU_OP2));
		al_draw_filled_rectangle((DISPLAY_RESOLUTION_X / 2) - (w / 2), (DISPLAY_RESOLUTION_Y / 2) + 36 * 2,
			(DISPLAY_RESOLUTION_X / 2) + (w / 2), (DISPLAY_RESOLUTION_Y / 2) + 36 * 2 + h, text_highlight_color);
		break;
	case MENU_OPTION_SETTINGS:
		w = al_get_text_width(g_font_r36, get_app_text(APP_TEXT_ID_MENU_OP3));
		al_draw_filled_rectangle((DISPLAY_RESOLUTION_X / 2) - (w / 2), (DISPLAY_RESOLUTION_Y / 2) + 36 * 3,
			(DISPLAY_RESOLUTION_X / 2) + (w / 2), (DISPLAY_RESOLUTION_Y / 2) + 36 * 3 + h, text_highlight_color);
		break;
	case MENU_OPTION_EXIT:
		w = al_get_text_width(g_font_r36, get_app_text(APP_TEXT_ID_MENU_OP4));
		al_draw_filled_rectangle((DISPLAY_RESOLUTION_X / 2) - (w / 2), (DISPLAY_RESOLUTION_Y / 2) + 36 * 4,
			(DISPLAY_RESOLUTION_X / 2) + (w / 2), (DISPLAY_RESOLUTION_Y / 2) + 36 * 4 + h, text_highlight_color);
		break;
	default:
		log_msg("Invalid menu option!", LOG_TYPE_ERROR);
		break;
	}

	// Draw options
	al_draw_text(g_font_r36, text_color, (DISPLAY_RESOLUTION_X / 2), (DISPLAY_RESOLUTION_Y / 2) + 36,
		ALLEGRO_ALIGN_CENTRE, get_app_text(APP_TEXT_ID_MENU_OP1));
	al_draw_text(g_font_r36, text_color, (DISPLAY_RESOLUTION_X / 2), (DISPLAY_RESOLUTION_Y / 2) + 36 * 2,
		ALLEGRO_ALIGN_CENTRE, get_app_text(APP_TEXT_ID_MENU_OP2));
	al_draw_text(g_font_r36, text_color, (DISPLAY_RESOLUTION_X / 2), (DISPLAY_RESOLUTION_Y / 2) + 36 * 3,
		ALLEGRO_ALIGN_CENTRE, get_app_text(APP_TEXT_ID_MENU_OP3));
	al_draw_text(g_font_r36, text_color, (DISPLAY_RESOLUTION_X / 2), (DISPLAY_RESOLUTION_Y / 2) + 36 * 4,
		ALLEGRO_ALIGN_CENTRE, get_app_text(APP_TEXT_ID_MENU_OP4));
}

MENU_OPTION get_option_in_click_point(int x, int y) {

}
