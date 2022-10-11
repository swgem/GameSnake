#ifndef RECORDS_H
#define RECORDS_H

#include "AppNav.h"
#include "RecordsController.h"

//// ENUM

typedef enum {
    RECORDS_USER_ACTION_NONE = 0,
    RECORDS_USER_ACTION_LEAVE
} RECORDS_USER_ACTION;

//// EXTERNAL FUNCTION DECLARATION

void reset_records();
APP_NAV_STATE handle_records_event(RECORDS_USER_ACTION action);
void get_records(RECORD_UNIT** records_out, int* number_of_records_out);
void finish_records();

#endif
