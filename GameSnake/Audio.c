#include "Audio.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"

static ALLEGRO_SAMPLE* menu_sample = NULL;
static ALLEGRO_SAMPLE_ID* menu_sample_id = NULL;

static ALLEGRO_SAMPLE* game_sample = NULL;
static ALLEGRO_SAMPLE_ID* game_sample_id = NULL;

static ALLEGRO_SAMPLE* food_sample = NULL;
static ALLEGRO_SAMPLE_ID* food_sample_id = NULL;

static ALLEGRO_SAMPLE* death_sample = NULL;
static ALLEGRO_SAMPLE_ID* death_sample_id = NULL;

void init_audio() {
	al_install_audio();
	al_init_acodec_addon();

	al_reserve_samples(4);
	menu_sample = al_load_sample("res/OST_MENU.ogg");
	game_sample = al_load_sample("res/OST_GAME.ogg");
	food_sample = al_load_sample("res/OST_FOOD.ogg");
	death_sample = al_load_sample("res/OST_DEATH.ogg");
}

void play_menu_audio() {
	al_play_sample(menu_sample, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, menu_sample_id);
}

void play_game_exec_audio() {
	al_play_sample(game_sample, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, game_sample_id);
}

void play_food_audio() {
	al_play_sample(food_sample, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, food_sample_id);
}

void play_death_audio() {
	al_play_sample(death_sample, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, death_sample_id);

}

void stop_menu_audio() {
	al_stop_sample(menu_sample_id);
}

void stop_game_audio() {
	al_stop_sample(game_sample_id);
}

void stop_food_audio() {
	al_stop_sample(food_sample_id);
}

void stop_death_audio() {
	al_stop_sample(death_sample_id);
}

void finish_audio() {
	al_destroy_sample(game_sample);
	al_destroy_sample(menu_sample);
	al_destroy_sample(food_sample);
	al_destroy_sample(death_sample);
}

