#ifndef LOGGER_H
#define LOGGER_H

#include "LoggerInterface.h"

//// EXTERNAL FUNCTION DECLARATION

void SYSTEM_FATAL(const char* msg);

void log_msg(const char* msg, LOG_TYPE log_type);

#endif
