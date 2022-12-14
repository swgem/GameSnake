#include "Graphics.h"
#include "DefaultConfig.h"
#include "Logger.h"
#include "AppText.h"
#include "GameExec.h"
#include "GameOver.h"
#include "Records.h"
#include "allegro5/allegro_color.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_primitives.h"
#include <stdio.h>

//// INTERNAL VARIABLE

static ALLEGRO_DISPLAY* g_display = NULL;

ALLEGRO_FONT* g_font_r24 = NULL;
ALLEGRO_FONT* g_font_r36 = NULL;
ALLEGRO_FONT* g_font_b36 = NULL;
ALLEGRO_FONT* g_font_b42 = NULL;
ALLEGRO_FONT* g_font_r64 = NULL;
ALLEGRO_FONT* g_font_b64 = NULL;
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

	g_font_b36 = al_load_ttf_font("res/Inconsolata-Bold.ttf", 36, 0);
	if (g_font_b36 == NULL) SYSTEM_FATAL("Could not initialize text font");

	g_font_b42 = al_load_ttf_font("res/Inconsolata-Bold.ttf", 42, 0);
	if (g_font_b42 == NULL) SYSTEM_FATAL("Could not initialize text font");

	g_font_r64 = al_load_ttf_font("res/Inconsolata-Regular.ttf", 64, 0);
	if (g_font_r64 == NULL) SYSTEM_FATAL("Could not initialize text font");

	g_font_b64 = al_load_ttf_font("res/Inconsolata-Bold.ttf", 64, 0);
	if (g_font_b64 == NULL) SYSTEM_FATAL("Could not initialize text font");

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

void draw_splash_screen() {
	ALLEGRO_COLOR bg_color = al_color_html(APP_BG_COLOR);
	ALLEGRO_COLOR text_color = al_color_html(APP_TEXT_COLOR);

	// Draw background
	al_clear_to_color(bg_color);
	// Draw loading
	al_draw_text(g_font_b64, text_color, 20, 400,
		ALLEGRO_ALIGN_LEFT, get_app_text(APP_TEXT_ID_LOADING));

	al_flip_display();
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
	float snake_color_h = APP_SNAKE_COLOR_H;
	float snake_color_s = APP_SNAKE_COLOR_S;
	float snake_color_v = APP_SNAKE_COLOR_V;

	ALLEGRO_COLOR bg_color = al_color_html(APP_BG_COLOR);
	ALLEGRO_COLOR header_text_color = al_color_html(APP_HEADER_TEXT_COLOR);
	ALLEGRO_COLOR paused_text_color = al_color_html(APP_PAUSED_TEXT_COLOR);
	ALLEGRO_COLOR map_line_color = al_color_html(APP_MAP_LINE_COLOR);
	ALLEGRO_COLOR snake_color = al_color_hsv(snake_color_h,
		snake_color_s, snake_color_v);
	ALLEGRO_COLOR snake_head_color = al_color_html(APP_SNAKE_HEAD_COLOR);
	ALLEGRO_COLOR food_color = al_color_html(APP_FOOD_COLOR);

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

	al_draw_line(0, header_h, DISPLAY_RESOLUTION_X, header_h, map_line_color, map_edge_thickness);

	if (!is_game_paused()) {
		char str_score[10];
		sprintf_s(str_score, sizeof(str_score), "%d", get_score());
		al_draw_text(g_font_r64, header_text_color, (DISPLAY_RESOLUTION_X / 2), 0, ALLEGRO_ALIGN_CENTRE, str_score);

		char str_time[10];
		sprintf_s(str_time, sizeof(str_time), "%d", (int)get_elapsed_time());
		al_draw_text(g_font_r64, header_text_color, DISPLAY_RESOLUTION_X - 15, 0, ALLEGRO_ALIGN_RIGHT, str_time);

		char str_length[10];
		sprintf_s(str_length, sizeof(str_length), "%d", get_snake()->length);
		al_draw_text(g_font_r64, header_text_color, 15, 0, ALLEGRO_ALIGN_LEFT, str_length);
	}
	else {
		char str_paused[10];
		sprintf_s(str_paused, sizeof(str_paused), "PAUSED");
		al_draw_text(g_font_b64, paused_text_color, (DISPLAY_RESOLUTION_X / 2), 0, ALLEGRO_ALIGN_CENTRE, str_paused);
	}
	// Draw snake

	const SNAKE* snake = get_snake();

	al_draw_filled_rectangle((map_x1 + map_block_h * snake->head.pos_x),
		(map_y1 + map_block_h * (snake->head.pos_y)),
		(map_x1 + map_block_h * (snake->head.pos_x + 1)),
		(map_y1 + map_block_h * (snake->head.pos_y + 1)), snake_head_color);
		
	SNAKE_SEG* iter = snake->head.next_seg;
	while (iter != NULL) {
		if (iter->pos_x >= 0 && iter->pos_x < GAME_MAP_SIZE_X 
			&& iter->pos_y >= 0 && iter->pos_y < GAME_MAP_SIZE_Y) {
			al_draw_filled_rectangle((map_x1 + map_block_h * iter->pos_x),
				(map_y1 + map_block_h * (iter->pos_y)),
				(map_x1 + map_block_h * (iter->pos_x + 1)),
				(map_y1 + map_block_h * (iter->pos_y + 1)), snake_color);
		}
		else {
			log_msg("Snake segment out of map.", LOG_TYPE_ERROR);
		}
		iter = iter->next_seg;
		snake_color_v += APP_SNAKE_COLOR_V_CHANGE_PACE;
		snake_color = al_color_hsv(snake_color_h, snake_color_s, snake_color_v);
	}

	// Draw food

	const FOOD* food = get_food();
	float raio = (map_block_h / 2) - (map_edge_thickness * 0.7);
	al_draw_filled_circle ((map_x1 + (map_block_h * food->pos_x) + (map_block_h * 0.5)), (map_y1 + map_block_h * (food->pos_y) + (map_block_h * 0.5)), raio, food_color);
	
	// Draw map
	
	al_draw_rectangle(map_x1, map_y1, map_x2, map_y2, map_line_color, map_edge_thickness);

	for (int i = 0; i < (GAME_MAP_SIZE_X - 1); i++) {
		al_draw_line((map_x1 + map_block_h * (i + 1)), map_y1,
			(map_x1 + map_block_h * (i + 1)), map_y2, map_line_color, map_edge_thickness);
	}
	for (int i = 0; i < (GAME_MAP_SIZE_Y - 1); i++) {
		al_draw_line(map_x1, (map_y1 + map_block_h * (i + 1)),
			map_x2, (map_y1 + map_block_h * (i + 1)), map_line_color, map_edge_thickness);
	}
}

void draw_game_over() {
	ALLEGRO_COLOR text_color = al_color_html(APP_TEXT_COLOR);
	ALLEGRO_COLOR bg_color = al_color_html(APP_BG_COLOR);
	ALLEGRO_COLOR text_highlight_color = al_color_html(APP_TEXT_HIGHLIGHT_COLOR);

	// Draw background
	al_clear_to_color(bg_color);
	
	// Print final result
	char str_score[10];
	int str_score_txt_size = strlen(get_app_text(APP_TEXT_ID_FINAL_SCORE)) + sizeof(str_score);
	char* str_score_txt = (char*)malloc(str_score_txt_size);
	sprintf_s(str_score, sizeof(str_score), "%d", get_final_score());
	if (str_score_txt) {
		sprintf_s(str_score_txt, str_score_txt_size, "%s%s",
			get_app_text(APP_TEXT_ID_FINAL_SCORE), str_score);
	}
	else {
		log_msg("Could not convert final score number to string", LOG_TYPE_ERROR);
	}

	switch (get_game_over_mode()) {
	case GAME_OVER_MODE_DISPLAY_ONLY:
		break;
	case GAME_OVER_MODE_SAVE_RECORD_QUESTION:
		al_draw_text(g_font_b42, text_color, (DISPLAY_RESOLUTION_X / 2), (DISPLAY_RESOLUTION_Y / 2),
			ALLEGRO_ALIGN_CENTRE, get_app_text(APP_TEXT_ID_CONGRATS_NEW_RECORD));
		al_draw_text(g_font_r36, text_color, (DISPLAY_RESOLUTION_X / 2), (DISPLAY_RESOLUTION_Y / 2 + 80),
			ALLEGRO_ALIGN_CENTRE, get_app_text(APP_TEXT_ID_SAVE_RECORD_QUESTION));

		// Draw selection rectangle behind yes or no
		if (get_save_record_state()) {
			int w = al_get_text_width(g_font_r36, get_app_text(APP_TEXT_ID_YES));
			al_draw_filled_rectangle((DISPLAY_RESOLUTION_X / 2 - 75) - (w / 2), (DISPLAY_RESOLUTION_Y / 2 + 120),
				(DISPLAY_RESOLUTION_X / 2 - 75) + (w / 2), (DISPLAY_RESOLUTION_Y / 2 + 120) + 36, text_highlight_color);
		}
		else {
			int w = al_get_text_width(g_font_r36, get_app_text(APP_TEXT_ID_NO));
			al_draw_filled_rectangle((DISPLAY_RESOLUTION_X / 2 + 75) - (w / 2), (DISPLAY_RESOLUTION_Y / 2 + 120),
				(DISPLAY_RESOLUTION_X / 2 + 75) + (w / 2), (DISPLAY_RESOLUTION_Y / 2 + 120) + 36, text_highlight_color);
		}
		

		al_draw_text(g_font_r36, text_color, (DISPLAY_RESOLUTION_X / 2 - 75), (DISPLAY_RESOLUTION_Y / 2 + 120),
			ALLEGRO_ALIGN_CENTRE, get_app_text(APP_TEXT_ID_YES));
		al_draw_text(g_font_r36, text_color, (DISPLAY_RESOLUTION_X / 2 + 75), (DISPLAY_RESOLUTION_Y / 2 + 120),
			ALLEGRO_ALIGN_CENTRE, get_app_text(APP_TEXT_ID_NO));
		break;
	case GAME_OVER_MODE_SAVE_RECORD_INPUT:
		al_draw_text(g_font_b42, text_color, (DISPLAY_RESOLUTION_X / 2), (DISPLAY_RESOLUTION_Y / 2),
			ALLEGRO_ALIGN_CENTRE, get_app_text(APP_TEXT_ID_CONGRATS_NEW_RECORD));
		al_draw_text(g_font_r36, text_color, (DISPLAY_RESOLUTION_X / 2), (DISPLAY_RESOLUTION_Y / 2 + 80),
			ALLEGRO_ALIGN_CENTRE, get_app_text(APP_TEXT_ID_TYPE_NAME));
		al_draw_text(g_font_b36, text_color, (DISPLAY_RESOLUTION_X / 2), (DISPLAY_RESOLUTION_Y / 2 + 120),
			ALLEGRO_ALIGN_CENTRE, get_new_record_name());
		break;
	case GAME_OVER_MODE_WON: 
		al_draw_text(g_font_r36, text_color, (DISPLAY_RESOLUTION_X / 2), (DISPLAY_RESOLUTION_Y / 2),
		ALLEGRO_ALIGN_CENTRE, get_app_text(APP_TEXT_ID_GAME_OVER_WON));
	default:
		log_msg("Invalid game over mode", LOG_TYPE_ERROR);
		break;
	}

	al_draw_text(g_font_r64, text_color, (DISPLAY_RESOLUTION_X / 2), (DISPLAY_RESOLUTION_Y / 3) - 50, ALLEGRO_ALIGN_CENTRE, str_score_txt);
}

void draw_settings() {
	ALLEGRO_COLOR text_color = al_color_html(APP_TEXT_COLOR);
	ALLEGRO_COLOR bg_color = al_color_html(APP_BG_COLOR);

	// Draw background
	al_clear_to_color(bg_color);
}

void draw_records() {
	ALLEGRO_COLOR bg_color = al_color_html(APP_BG_COLOR);
	ALLEGRO_COLOR list_bg_color = al_color_html(APP_LIST_BG_COLOR);
	ALLEGRO_COLOR record_text_color = al_color_html(APP_RECORD_LIST_TEXT_COLOR);
	ALLEGRO_COLOR arrow_color = al_color_html(APP_RECORD_ARROW_COLOR);

	// Draw background
	al_clear_to_color(bg_color);

	// Draw header
	int header_h = 150;
	al_draw_text(g_font_b64, record_text_color, DISPLAY_RESOLUTION_X / 2, 40, 
		ALLEGRO_ALIGN_CENTRE, get_app_text(APP_TEXT_ID_RECORDS));

	// Print records
	RECORD_UNIT* records = NULL;
	int number_of_records;
	get_records_to_print(&records, &number_of_records);

	int table_col_w = (DISPLAY_RESOLUTION_X / 2) - 110;
	int table_x0 = (DISPLAY_RESOLUTION_X / 2) - table_col_w;
	int table_row_h = 46;
	int table_y0 = header_h + 10;
	int table_h = table_row_h * number_of_records;
	int highlight_padding = 5;

	for (int i = 0; i < number_of_records; i++) {
		RECORD_UNIT* record = &records[i];
		char* str_score[10];
		sprintf_s(str_score, sizeof(str_score), "%d", record->score);
		al_draw_filled_rectangle(table_x0 + highlight_padding, (table_y0 + i * table_row_h),
			(table_x0 + 2*table_col_w) - highlight_padding, (table_y0 + (i+1) * table_row_h) - 2*highlight_padding, list_bg_color);
		al_draw_text(g_font_r36, record_text_color, table_x0 + table_col_w/2, (table_y0 + i * table_row_h),
			ALLEGRO_ALIGN_CENTRE, records[i].name);
		al_draw_text(g_font_r36, record_text_color, table_x0 + 3*table_col_w/2, (table_y0 + i * table_row_h),
			ALLEGRO_ALIGN_CENTRE, str_score);
	}

	// Draw arrows
	int thickness = 3;

	int key_up_x1 = table_x0 / 2;
	int key_up_y1 = (table_y0 + 8);
	int key_up_x2 = table_x0 / 2 - 20;
	int key_up_y2 = (table_y0 + 8) + 30;
	int key_up_x3 = table_x0 / 2 + 20;
	int key_up_y3 = (table_y0 + 8) + 30;
	if (is_record_key_up_active()) {
		al_draw_filled_triangle(key_up_x1, key_up_y1, key_up_x2, key_up_y2, key_up_x3, key_up_y3, arrow_color);
	}
	else {
		al_draw_triangle(key_up_x1, key_up_y1, key_up_x2, key_up_y2, key_up_x3, key_up_y3, arrow_color, thickness);
	}
	int key_down_x1 = table_x0 / 2;
	int key_down_y1 = (table_y0 + table_h - 8);
	int key_down_x2 = table_x0 / 2 - 20;
	int key_down_y2 = (table_y0 + table_h - 8) - 30;
	int key_down_x3 = table_x0 / 2 + 20;
	int key_down_y3 = (table_h + table_y0 - 8) - 30;
	if (is_record_key_down_active()) {
		al_draw_filled_triangle(key_down_x1, key_down_y1, key_down_x2, key_down_y2, key_down_x3, key_down_y3, arrow_color);
	}
	else {
		al_draw_triangle(key_down_x1, key_down_y1, key_down_x2, key_down_y2, key_down_x3, key_down_y3, arrow_color, thickness);
	}
}

MENU_OPTION get_option_in_click_point(int x, int y) {

}
