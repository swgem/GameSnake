#include "Tools.h"
#include "LoggerInterface.h"
#include "GameConfig.h"

//// INTERNAL VARIABLE

static void (*g_system_fatal)() = (void*)0;
static void* (*g_mem_alloc)(int size) = (void*)0;
static int (*g_generate_random)() = (void*)0;

//// FUNCTION IMPLEMENTATION

void set_system_fatal_func(void (*system_fatal)()) {
	g_system_fatal = system_fatal;
}

void set_mem_alloc_func(void* (*mem_alloc)(int)) {
	g_mem_alloc = mem_alloc;
}

void set_generate_random_func(int (*generate_random)()) {
	g_generate_random = generate_random;
}

void system_fatal() {
	g_system_fatal();
}

void* mem_alloc(int size) {
	if (g_mem_alloc == (void*)0) {
#ifdef USE_LOGGER
		log_msg("Memory allocation function not defined", LOG_TYPE_FATAL);
#endif
		system_fatal();
	}

	return g_mem_alloc(size);
}

int generate_random() {
	if (g_generate_random == (void*)0) {
#ifdef USE_LOGGER
		log_msg("Random number function not defined", LOG_TYPE_FATAL);
#endif
		system_fatal();
	}

	return g_generate_random();
}
