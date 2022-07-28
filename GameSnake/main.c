#include <stdio.h>
#include <stdlib.h>
#include "AppCore.h"

int main(int argc, char* argv[]) {
	// STARTUP
	init_allegro();

	// EXECUTION
	game_loop();

	// FINISH
	finish_allegro();

	return 0;
}
