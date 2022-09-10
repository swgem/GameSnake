#include "Audio.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include "Logger.h"

//// INTERNAL VARIABLE

static bool audio_initialized = false;

static ALLEGRO_SAMPLE* g_menu_sample = NULL;
static ALLEGRO_SAMPLE* g_game_sample = NULL;
static ALLEGRO_SAMPLE* g_food_sample = NULL;
static ALLEGRO_SAMPLE* g_death_sample = NULL;

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

	al_reserve_samples(4);
	g_menu_sample = al_load_sample("res/OST_MENU.ogg");
	if (g_menu_sample == NULL) log_msg("Could not load menu audio.", LOG_TYPE_ERROR);
	g_game_sample = al_load_sample("res/OST_GAME.ogg");
	if (g_game_sample == NULL) log_msg("Could not load game audio.", LOG_TYPE_ERROR);
	g_food_sample = al_load_sample("res/OST_FOOD.ogg");
	if (g_food_sample == NULL) log_msg("Could not load food audio.", LOG_TYPE_ERROR);
	g_death_sample = al_load_sample("res/OST_DEATH.ogg");
	if (g_death_sample == NULL) log_msg("Could not load death audio.", LOG_TYPE_ERROR);
}

void play_menu_audio() {
	if (audio_initialized && g_menu_sample != NULL) {
		if (!al_play_sample(g_menu_sample, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL)) {
			log_msg("Tried but could not play menu audio.", LOG_TYPE_ERROR);
		}
	}
	else {
		log_msg("Cannot play menu audio.", LOG_TYPE_ERROR);
	}
}

void play_game_exec_audio() {
	if (audio_initialized && g_game_sample != NULL) {
		if (!al_play_sample(g_game_sample, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL)) {
			log_msg("Tried but could not play game audio.", LOG_TYPE_ERROR);
		}
	}
	else {
		log_msg("Cannot play game audio.", LOG_TYPE_ERROR);
	}
}

void play_food_audio() {
	if (audio_initialized && g_food_sample != NULL) {
		if (!al_play_sample(g_food_sample, 1, 0, 1.5, ALLEGRO_PLAYMODE_ONCE, NULL)) {
			log_msg("Tried but could not play food audio.", LOG_TYPE_ERROR);
		}
	}
	else {
		log_msg("Cannot play food audio.", LOG_TYPE_ERROR);
	}
}

void play_death_audio() {
	if (audio_initialized && g_death_sample != NULL) {
		if (!al_play_sample(g_death_sample, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL)) {
			log_msg("Tried but could not play death audio.", LOG_TYPE_ERROR);
		}
	}
	else {
		log_msg("Cannot play death audio.", LOG_TYPE_ERROR);
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

