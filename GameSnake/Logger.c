#include "stdio.h"
#include "stdlib.h"
#include "Logger.h"

//// FUNCTION IMPLEMENTATION

void SYSTEM_FATAL(char* msg) {
	log_msg(msg, LOG_TYPE_FATAL);
	exit(1);
}

void log_msg(char* msg, LOG_TYPE log_type) {
#ifdef _DEBUG
	printf(msg);
#endif
	// escrever no arquivo
}
