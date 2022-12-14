#ifndef RECORDS_H
#define RECORDS_H

#include "AppNav.h"
#include <stdbool.h>
#include "RecordsController.h"

//// ENUM

typedef enum {
    RECORDS_USER_ACTION_NONE = 0,
    RECORDS_USER_ACTION_LEAVE,
    RECORDS_USER_ACTION_UP,
    RECORDS_USER_ACTION_DOWN
} RECORDS_USER_ACTION;

//// EXTERNAL FUNCTION DECLARATION

void reset_records();
APP_NAV_STATE handle_records_event(RECORDS_USER_ACTION action);
void get_records_to_print(RECORD_UNIT** records_out, int* number_of_records_out);
bool is_record_key_up_active();
bool is_record_key_down_active();
void finish_records();

#endif
