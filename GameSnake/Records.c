#include "Records.h"
#include <stdlib.h>
#include "RecordsController.h"

//// INTERNAL VARIABLE

static RECORD_UNIT* g_records;

static int g_record_cursor;
static int g_record_cursor_max;
static int g_number_of_records;

//// FUNCTION IMPLEMENTATION

void reset_records() {
    g_record_cursor = 0;

    get_records_buf(&g_records, &g_number_of_records);

    g_record_cursor_max = g_number_of_records - MAX_RECORDS_TO_PRINT;
}

APP_NAV_STATE handle_records_event(RECORDS_USER_ACTION action) {
    APP_NAV_STATE next_state = APP_NAV_STATE_RECORDS;

    switch (action) {
    case RECORDS_USER_ACTION_LEAVE:
        next_state = APP_NAV_STATE_MENU;
        break;
    case RECORDS_USER_ACTION_UP:
        if (g_record_cursor > 0) {
            g_record_cursor--;
        }
        break;
    case RECORDS_USER_ACTION_DOWN:
        if (g_record_cursor < g_record_cursor_max) {
            g_record_cursor++;
        }
        break;
    default:
        break;
    }

    return next_state;
}

void get_records_to_print(RECORD_UNIT** records_out, int* number_of_records_out) {
    *records_out = &g_records[g_record_cursor];

    if (g_number_of_records < MAX_RECORDS_TO_PRINT) {
        *number_of_records_out = g_number_of_records;
    }
    else {
        *number_of_records_out = MAX_RECORDS_TO_PRINT;
    }  
}

bool is_record_key_up_active() {
    return (g_record_cursor > 0);
}

bool is_record_key_down_active() {
    return (g_record_cursor < g_record_cursor_max);
}

void finish_records() {
    g_records = NULL;
    g_number_of_records = 0;
    clear_records_buf();
}
