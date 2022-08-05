#include "AppCore.h"
#include "DefaultConfig.h"
#include "Logger.h"
#include "AppNav.h"
#include "Graphics.h"
#include "Menu.h"
#include "GameExec.h"

//// INTERNAL VARIABLE

ALLEGRO_TIMER* g_main_timer = NULL;
ALLEGRO_EVENT_QUEUE* g_ev_queue = NULL;

APP_NAV_STATE g_curr_nav_state = APP_NAV_STATE_MENU;

//// INTERNAL FUNCTION DECLARATION

void change_nav_state(APP_NAV_STATE next_state);

void handle_event_timer();
void handle_event_key_up(int keycode);

//// FUNCTION IMPLEMENTATION

void init_allegro() {
	if (!al_init()) SYSTEM_FATAL("Could not initiate allegro!");
	if (!al_install_keyboard()) SYSTEM_FATAL("Could not install keyboard!");

	g_main_timer = al_create_timer(1.0 / 10.0);
	if (g_main_timer == NULL) SYSTEM_FATAL("Could not initialize main timer");
	g_ev_queue = al_create_event_queue();
	if (g_ev_queue == NULL) SYSTEM_FATAL("Could not initialize event queue");

	init_graphical_resources();

	al_register_event_source(g_ev_queue, al_get_keyboard_event_source());
	al_register_event_source(g_ev_queue, al_get_display_event_source(get_display()));
	al_register_event_source(g_ev_queue, al_get_timer_event_source(g_main_timer));

	reset_menu();

	al_start_timer(g_main_timer);
}

void finish_allegro() {
	al_destroy_timer(g_main_timer);
	al_destroy_event_queue(g_ev_queue);
	destroy_display();
}

void game_loop() {
	bool redraw = false;
	bool finished = false;
	ALLEGRO_EVENT event;

	while (1) {
		al_wait_for_event(g_ev_queue, &event);

		switch (event.type) {
		case ALLEGRO_EVENT_TIMER:
			handle_event_timer();
			redraw = true;
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			break;
		case ALLEGRO_EVENT_KEY_CHAR:
			break;
		case ALLEGRO_EVENT_KEY_UP:
			handle_event_key_up(event.keyboard.keycode);
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			finished = true;
			break;
		default:
			break;
		}

		if (finished) break;

		if (redraw && al_is_event_queue_empty(g_ev_queue)) {
			al_flip_display();
			redraw = false;
		}
	}
}

void change_nav_state(APP_NAV_STATE next_state) {
	// If app is navigating to next state, redefine navigation state params
	switch (g_curr_nav_state) {
	case APP_NAV_STATE_MENU:
		reset_menu();
		break;
	case APP_NAV_STATE_GAME_EXEC:
		reset_game_exec();
		break;
	case APP_NAV_STATE_RECORDS:
		break;
	case APP_NAV_STATE_FINISH:
		break;
	default:
		log_msg("Invalid next navigation state!", LOG_TYPE_ERROR);
		next_state = g_curr_nav_state; // Not allowed to change state
		break;
	}

	g_curr_nav_state = next_state;
}

void handle_event_timer() {
	APP_NAV_STATE next_state = g_curr_nav_state;
	
	switch (g_curr_nav_state) {
	case APP_NAV_STATE_MENU:
		draw_menu();
		break;
	case APP_NAV_STATE_GAME_EXEC:
		next_state = handle_game_exec_timer();
		break;
	case APP_NAV_STATE_RECORDS:
		break;
	case APP_NAV_STATE_FINISH:
		break;
	default:
		SYSTEM_FATAL("Invalid current navigation state!");
		break;
	}

	if (next_state != g_curr_nav_state) change_nav_state(next_state);
}

void handle_event_key_up(int keycode) {
	APP_NAV_STATE next_state = g_curr_nav_state;
	
	switch (g_curr_nav_state) {
	case APP_NAV_STATE_MENU: {
		MENU_USER_ACTION action = MENU_USER_ACTION_NONE;
		switch (keycode) {
		case ALLEGRO_KEY_UP:
			action = MENU_USER_ACTION_UP;
			break;
		case ALLEGRO_KEY_DOWN:
			action = MENU_USER_ACTION_DOWN;
			break;
		case ALLEGRO_KEY_ESCAPE:
			action = MENU_USER_ACTION_DESELECT;
			break;
		case ALLEGRO_KEY_ENTER:
		case ALLEGRO_KEY_PAD_ENTER:
		case ALLEGRO_KEY_SPACE:
			action = MENU_USER_ACTION_ENTER;
			break;
		default:
			break;
		}
		next_state = handle_menu_event(action);
		break;
	}
	case APP_NAV_STATE_GAME_EXEC:
		break;
	case APP_NAV_STATE_RECORDS:
		break;
	case APP_NAV_STATE_FINISH:
		break;
	default:
		SYSTEM_FATAL("Invalid current navigation state!");
		break;
	}

	if (next_state != g_curr_nav_state) change_nav_state(next_state);
}
