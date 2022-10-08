#include "Audio.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include "Logger.h"
#include "GameExec.h"

//// INTERNAL VARIABLE

static bool audio_initialized = false;

static ALLEGRO_SAMPLE* g_menu_sample = NULL;
static ALLEGRO_SAMPLE_ID g_menu_id;

static ALLEGRO_SAMPLE* g_game_sample = NULL;
static ALLEGRO_SAMPLE_ID g_game_id;

static ALLEGRO_SAMPLE* g_food_sample = NULL;
static ALLEGRO_SAMPLE_ID g_food_id;

static ALLEGRO_SAMPLE* g_death_sample = NULL;
static ALLEGRO_SAMPLE_ID g_death_id;

static ALLEGRO_SAMPLE* g_paused_sample = NULL;
static ALLEGRO_SAMPLE_ID g_paused_id;

static ALLEGRO_SAMPLE* g_win_sample = NULL;
static ALLEGRO_SAMPLE_ID g_win_id;

//// FUNCTION IMPLEMENTATION


void init_audio() {
	audio_initialized = true;
	if (!al_install_audio()) {
		log_msg("Could not install audio!", LOG_TYPE_ERROR);
		audio_initialized = false;
	}
	if (!al_init_acodec_addon()) {
		log_msg("Could not install audio!", LOG_TYPE_ERROR);
		audio_initialized = false;
	}

	al_reserve_samples(5);
	g_menu_sample = al_load_sample("res/OST_MENU.ogg");
	if (g_menu_sample == NULL) log_msg("Could not load menu audio.", LOG_TYPE_ERROR);
	g_game_sample = al_load_sample("res/OST_GAME.ogg");
	if (g_game_sample == NULL) log_msg("Could not load game audio.", LOG_TYPE_ERROR);
	g_food_sample = al_load_sample("res/OST_FOOD.ogg");
	if (g_food_sample == NULL) log_msg("Could not load food audio.", LOG_TYPE_ERROR);
	g_death_sample = al_load_sample("res/OST_DEATH.ogg");
	if (g_death_sample == NULL) log_msg("Could not load death audio.", LOG_TYPE_ERROR);
	g_paused_sample = al_load_sample("res/OST_PAUSED.ogg");
	if (g_paused_sample == NULL) log_msg("Could not load pause audio.", LOG_TYPE_ERROR);
	g_win_sample = al_load_sample("res/OST_WIN.ogg");
	if (g_win_sample == NULL) log_msg("Could not load win audio.", LOG_TYPE_ERROR);
}

void play_menu_audio() {
	if (audio_initialized && g_menu_sample != NULL) {
		if (!al_play_sample(g_menu_sample, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, &g_menu_id)) {
			log_msg("Tried but could not play menu audio.", LOG_TYPE_ERROR);
		}
	}
	else {
		log_msg("Cannot play menu audio.", LOG_TYPE_ERROR);
	}
}

void play_game_exec_audio() {
		if (audio_initialized && g_game_sample != NULL) {
			if (!al_play_sample(g_game_sample, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, &g_game_id)) {
				log_msg("Tried but could not play game audio.", LOG_TYPE_ERROR);
			}
		}
		else {
			log_msg("Cannot play game audio.", LOG_TYPE_ERROR);
		}
}

void play_pause_audio() {
	if (audio_initialized && g_paused_sample != NULL) {
		if (!al_play_sample(g_paused_sample, 1, 0, 1 , ALLEGRO_PLAYMODE_ONCE, &g_paused_id)) {
			log_msg("Tried but could not play paused audio.", LOG_TYPE_ERROR);
		}
	}
	else {
		log_msg("Cannot play paused audio.", LOG_TYPE_ERROR);
	}
}

void play_food_audio() {
	if (audio_initialized && g_food_sample != NULL) {
		if (!al_play_sample(g_food_sample, 1, 0, 1.5, ALLEGRO_PLAYMODE_ONCE, &g_food_id)) {
			log_msg("Tried but could not play food audio.", LOG_TYPE_ERROR);
		}
	}
	else {
		log_msg("Cannot play food audio.", LOG_TYPE_ERROR);
	}
}

void play_death_audio() {
	if (audio_initialized && g_death_sample != NULL) {
		if (!al_play_sample(g_death_sample, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, &g_death_id)) {
			log_msg("Tried but could not play death audio.", LOG_TYPE_ERROR);
		}
	}
	else {
		log_msg("Cannot play death audio.", LOG_TYPE_ERROR);
	}
}

void play_win_audio() {
	if (audio_initialized && g_win_sample != NULL) {
		if (!al_play_sample(g_win_sample, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, &g_win_id)) {
			log_msg("Tried but could not play win audio.", LOG_TYPE_ERROR);
		}
	}
	else {
		log_msg("Cannot play win audio.", LOG_TYPE_ERROR);
	}
}

void reset_audio() {
	al_stop_samples();
}


void finish_audio() {
	al_destroy_sample(g_menu_sample);
	al_destroy_sample(g_game_sample);
	al_destroy_sample(g_food_sample);
	al_destroy_sample(g_death_sample);
}

