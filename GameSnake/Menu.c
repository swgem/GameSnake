#include "Menu.h"
#include "Logger.h"

//// INTERNAL VARIABLE

static MENU_OPTION g_option_highlight = MENU_OPTION_NONE;

//// INTERNAL FUNCTION DECLARATION

static void change_option_highlight(MENU_USER_ACTION action);

static APP_NAV_STATE get_next_nav_state();

//// FUNCTION IMPLEMENTATION

void reset_menu() {
    g_option_highlight = MENU_OPTION_NONE;
    play_menu_audio();
}

APP_NAV_STATE handle_menu_event(MENU_USER_ACTION action, MENU_OPTION next_option) {
    APP_NAV_STATE next_state = APP_NAV_STATE_MENU;

    switch (action) {
    case MENU_USER_ACTION_NONE:
        break;
    case MENU_USER_ACTION_DOWN:
        change_option_highlight(action);
        break;
    case MENU_USER_ACTION_UP:
        change_option_highlight(action);
        break;
    case MENU_USER_ACTION_SELECT:
        g_option_highlight = next_option;
        break;
    case MENU_USER_ACTION_DESELECT:
        g_option_highlight = MENU_OPTION_NONE;
        break;
    case MENU_USER_ACTION_ENTER: {
        APP_NAV_STATE _next_state = get_next_nav_state();
        if (_next_state != -1) next_state = _next_state;
        break;
    }
    default:
        log_msg("Invalid menu user action.\n", LOG_TYPE_ERROR);
        break;
    }

    return next_state;
}

APP_NAV_STATE get_option_highlight() {
    return g_option_highlight;
}

static void change_option_highlight(MENU_USER_ACTION action) {
    if (action == MENU_USER_ACTION_UP) {
        if ((g_option_highlight == MENU_OPTION_NONE) || (g_option_highlight == MENU_OPTION_PLAY)) {
            g_option_highlight = MENU_OPTION_EXIT;
        }
        else {
            g_option_highlight--;
        }
    }
    else if (action == MENU_USER_ACTION_DOWN) {
        if (g_option_highlight == MENU_OPTION_EXIT) {
            g_option_highlight = MENU_OPTION_PLAY;
        }
        else {
            g_option_highlight++;
        }
    }
    else {
        log_msg("Wrong action for changing option highlight function.\n", LOG_TYPE_ERROR);
    }
}

static APP_NAV_STATE get_next_nav_state() {
    APP_NAV_STATE next_state = -1;

    switch (g_option_highlight) {
    case MENU_OPTION_NONE:
        log_msg("Cannot set next nav state as none", LOG_TYPE_ERROR);
        break;
    case MENU_OPTION_PLAY:
        next_state = APP_NAV_STATE_GAME_EXEC;
        break;
    case MENU_OPTION_RECORDS:
        next_state = APP_NAV_STATE_RECORDS;
        break;
    case MENU_OPTION_SETTINGS:
        next_state = APP_NAV_STATE_SETTINGS;
        break;
    case MENU_OPTION_EXIT:
        next_state = APP_NAV_STATE_FINISH;
        break;
    default:
        log_msg("Invalid option highlight at getting next nav state", LOG_TYPE_ERROR);
        break;
    }

    return next_state;
}
