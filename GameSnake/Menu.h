#ifndef MENU_H
#define MENU_H

#include "AppNav.h"

//// ENUM

typedef enum {
    MENU_OPTION_NONE = 0,
    MENU_OPTION_PLAY,
    MENU_OPTION_RECORDS,
    MENU_OPTION_SETTINGS,
    MENU_OPTION_EXIT
} MENU_OPTION;

typedef enum {
    MENU_USER_ACTION_NONE = 0,
    MENU_USER_ACTION_DOWN,
    MENU_USER_ACTION_UP,
    MENU_USER_ACTION_SELECT,
    MENU_USER_ACTION_DESELECT,
    MENU_USER_ACTION_ENTER
} MENU_USER_ACTION;

//// EXTERNAL FUNCTION DECLARATION

void reset_menu();

APP_NAV_STATE handle_menu_event(MENU_USER_ACTION action);

APP_NAV_STATE get_option_highlight();

void finish_menu();

#endif
