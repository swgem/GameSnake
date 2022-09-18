#include "stdio.h"
#include "stdlib.h"
#include "Logger.h"

//// FUNCTION IMPLEMENTATION

void SYSTEM_FATAL(const char* msg) {
	log_msg(msg, LOG_TYPE_FATAL);
	(void)getchar();
	exit(1);
}

void log_msg(const char* msg, LOG_TYPE log_type) {
#ifdef _DEBUG
	printf("%s\n", msg);
#endif
	// escrever no arquivo
}
