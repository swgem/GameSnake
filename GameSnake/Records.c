#include "Records.h"

//// INTERNAL VARIABLE

//// INTERNAL FUNCTION DECLARATION

void load_records() {

}

//// FUNCTION IMPLEMENTATION

void reset_records() {

}

APP_NAV_STATE handle_records_event(RECORDS_USER_ACTION action) {
    APP_NAV_STATE next_state = APP_NAV_STATE_RECORDS;

    switch (action) {
    case RERCODS_USER_ACTION_LEAVE:
        next_state = APP_NAV_STATE_MENU;
        break;
    default:
        break;
    }

    return next_state;
}

void finish_records() {

}
