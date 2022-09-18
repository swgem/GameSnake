#ifndef LOGGER_INTERFACE_H
#define LOGGER_INTERFACE_H

//// ENUM

typedef enum {
    LOG_TYPE_ERROR = 0,
    LOG_TYPE_INFO,
    LOG_TYPE_FATAL
} LOG_TYPE;

//// EXTERNAL FUNCTION DECLARATION

void log_msg(const char* msg, LOG_TYPE log_type);

#endif
