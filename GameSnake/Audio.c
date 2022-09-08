#include "Audio.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"

static ALLEGRO_SAMPLE* menu_sample = NULL;
static ALLEGRO_SAMPLE* game_sample = NULL;
static ALLEGRO_SAMPLE* food_sample = NULL;
static ALLEGRO_SAMPLE* death_sample = NULL;

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
	al_play_sample(menu_sample, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
}

void play_game_exec_audio() {
	al_play_sample(game_sample, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);
}

void play_food_audio() {
	al_play_sample(food_sample, 1, 0, 1.5, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void play_death_audio() {
	al_play_sample(death_sample, 1, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);

}

void reset_audio() {
	al_stop_samples();
}


void finish_audio() {
	al_destroy_sample(game_sample);
	al_destroy_sample(menu_sample);
	al_destroy_sample(food_sample);
	al_destroy_sample(death_sample);
}

