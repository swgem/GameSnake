#include "AppCore.h"
#include "Logger.h"
#include "AppNav.h"
#include "Graphics.h"

//// INTERNAL VARIABLE

ALLEGRO_TIMER* g_main_timer = NULL;
ALLEGRO_EVENT_QUEUE* g_ev_queue = NULL;

//// FUNCTION IMPLEMENTATION

void init_allegro() {
	if (!al_init()) SYSTEM_FATAL("Could not initiate allegro!");
	if (!al_install_keyboard()) SYSTEM_FATAL("Could not install keyboard!");

	g_main_timer = al_create_timer(1.0 / 10.0);
	if (g_main_timer == NULL) SYSTEM_FATAL("Could not initialize main timer");
	g_ev_queue = al_create_event_queue();
	if (g_ev_queue == NULL) SYSTEM_FATAL("Could not initialize event queue");
	ALLEGRO_DISPLAY* display = al_create_display(640, 480);
	(display == NULL) ? SYSTEM_FATAL("Could not create display") : set_display(display);

	al_register_event_source(g_ev_queue, al_get_keyboard_event_source());
	al_register_event_source(g_ev_queue, al_get_display_event_source(display));
	al_register_event_source(g_ev_queue, al_get_timer_event_source(g_main_timer));

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
		log_msg("Some random event happened.", LOG_TYPE_INFO);

		switch (event.type) {
		case ALLEGRO_EVENT_TIMER:
			redraw = true;
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			//?
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
