#include "Graphics.h"
#include "DefaultConfig.h"
#include "Logger.h"
#include "AppText.h"
#include "GameExec.h"
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

	g_font_b72 = al_load_ttf_font("res/Inconsolata-Bold.ttf", 72, 0);
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
	ALLEGRO_COLOR bg_color = al_color_html(APP_BG_COLOR);
	ALLEGRO_COLOR text_color = al_color_html(APP_TEXT_COLOR);
	ALLEGRO_COLOR text_highlight_color = al_color_html(APP_TEXT_HIGHLIGHT_COLOR);

	// Draw background

	al_clear_to_color(bg_color);

	// Draw title
	al_draw_text(g_font_b72, text_color, (DISPLAY_RESOLUTION_X / 2), (DISPLAY_RESOLUTION_Y / 2) - 108,
		ALLEGRO_ALIGN_CENTRE, get_app_text(APP_TEXT_ID_MENU_TITLE));

	// Draw option highlight (if there is any)
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

void draw_game_exec() {
	ALLEGRO_COLOR bg_color = al_color_html(APP_BG_COLOR);
	ALLEGRO_COLOR edge_color = al_color_html(APP_EDGE_COLOR);

	int header_h = 70;
	int map_padding = 15;
	int map_edge_thickness = 3;

	float map_h = 0;
	float map_w = 0;
	float map_x1 = 0;
	float map_y1 = 0;
	float map_y2 = 0;
	float map_x2 = 0;
	float map_block_h = 0;

	// Calculate map edges

	if (DISPLAY_RESOLUTION_X > DISPLAY_RESOLUTION_Y) {
		map_h = (float)DISPLAY_RESOLUTION_Y - header_h - 2 * map_padding;
		map_block_h = map_h / (float)GAME_MAP_SIZE_Y;
		map_w = map_block_h * (float)GAME_MAP_SIZE_X;

		map_x1 = ((float)DISPLAY_RESOLUTION_X - map_w) / 2;
		map_y1 = header_h + (float)map_padding;
		map_x2 = map_x1 + map_w;
		map_y2 = map_y1 + map_h;
	}
	else {

	}

	// Draw background
	al_clear_to_color(bg_color);

	// Draw header

	al_draw_line(0, header_h, DISPLAY_RESOLUTION_X, header_h, edge_color, map_edge_thickness);

	// Draw map
	
	al_draw_rectangle(map_x1, map_y1, map_x2, map_y2, edge_color, map_edge_thickness);

	for (int i = 0; i < (GAME_MAP_SIZE_X - 1); i++) {
		al_draw_line((map_x1 + map_block_h * (i + 1)), map_y1,
			(map_x1 + map_block_h * (i + 1)), map_y2, edge_color, map_edge_thickness);
	}
	for (int i = 0; i < (GAME_MAP_SIZE_Y - 1); i++) {
		al_draw_line(map_x1, (map_y1 + map_block_h * (i + 1)),
			map_x2, (map_y1 + map_block_h * (i + 1)), edge_color, map_edge_thickness);
	}

	// Draw snake head
	const SNAKE* snake = get_snake();
	al_draw_filled_rectangle((map_x1 + map_block_h * (snake->head.pos_x + 1)), (map_y1 + map_block_h * (snake->head.pos_y + 1)),
		(map_x1 + map_block_h * (snake->head.pos_x + 2)), (map_y1 + map_block_h * (snake->head.pos_y + 2)), edge_color);
}

MENU_OPTION get_option_in_click_point(int x, int y) {

}
