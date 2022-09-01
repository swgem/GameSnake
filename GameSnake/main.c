#include <stdio.h>
#include <stdlib.h>
#include "AppCore.h"

int main(int argc, char* argv[]) {
	// STARTUP
	app_init();

	// EXECUTION
	app_loop();

	// FINISH
	app_finish();

	return 0;
}
