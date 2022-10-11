#include "Records.h"
#include <stdlib.h>
#include "RecordsController.h"

//// INTERNAL VARIABLE

static RECORD_UNIT* g_records;
static int g_number_of_records = 0;

//// INTERNAL FUNCTION DECLARATION

void load_records() {
    get_records_buf(&g_records, &g_number_of_records);
}

//// FUNCTION IMPLEMENTATION

void reset_records() {
    load_records();
}

APP_NAV_STATE handle_records_event(RECORDS_USER_ACTION action) {
    APP_NAV_STATE next_state = APP_NAV_STATE_RECORDS;

    switch (action) {
    case RECORDS_USER_ACTION_LEAVE:
        next_state = APP_NAV_STATE_MENU;
        break;
    default:
        break;
    }

    return next_state;
}

void get_records(RECORD_UNIT** records_out, int* number_of_records_out) {
    *records_out = g_records;
    *number_of_records_out = g_number_of_records;
}

void finish_records() {
    g_records = NULL;
    g_number_of_records = 0;
    clear_records_buf();
}
