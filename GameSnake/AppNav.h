#ifndef APP_NAV_H
#define APP_NAV_H

// ENUM

typedef enum {
    APP_NAV_STATE_MENU = 0,
    APP_NAV_STATE_GAME_EXEC,
    APP_NAV_STATE_RECORDS,
    APP_NAV_STATE_FINISH
} APP_NAV_STATE;

//// EXTERNAL FUNCTION DECLARATION

void init_app_nav();

APP_NAV_STATE app_get_curr_state();

void app_set_next_state(APP_NAV_STATE state);

#endif
