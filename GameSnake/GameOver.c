#include "GameOver.h"
#include <stdlib.h>
#include "Audio.h"
#include "RecordsController.h"
#include "Logger.h"
#include "DefaultConfig.h"

//// INTERNAL VARIABLE

static int g_apptick; // count +1 every app running period
static int g_final_score;
static int g_elapsed_time;
static GAME_OVER_MODE g_game_over_mode;
static bool g_save_record_state;
static char g_name_buf[RECORDS_NAME_MAX_SIZE + 1];
static char g_name_size_curr;

//// INTERNAL FUNCTION DECLARATION

APP_NAV_STATE handle_game_over_event_display_only(GAME_OVER_USER_ACTION action);
APP_NAV_STATE handle_game_over_event_save_record_question(GAME_OVER_USER_ACTION action);
APP_NAV_STATE handle_game_over_event_save_record_input(GAME_OVER_USER_ACTION action);

//// FUNCTION IMPLEMENTATION

void reset_game_over() {
    play_death_audio();

    g_save_record_state = true;

    g_name_size_curr = 0;
    for (int i = 0; i < (RECORDS_NAME_MAX_SIZE + 1); i++) {
        g_name_buf[i] = (char)0;
    }

    int last_record = 0;
    get_last_record(NULL, &last_record);
    if (g_final_score > last_record) {
        g_game_over_mode = GAME_OVER_MODE_SAVE_RECORD_QUESTION;
    }
    else {
        g_game_over_mode = GAME_OVER_MODE_DISPLAY_ONLY;
    }
    if (is_game_won()) {
        g_game_over_mode = GAME_OVER_MODE_WON;
    }
}

APP_NAV_STATE handle_game_over_event_display_only(GAME_OVER_USER_ACTION action) {
    APP_NAV_STATE next_state = APP_NAV_STATE_GAME_OVER;

    switch (action) {
    case GAME_OVER_USER_ACTION_SELECT:
        next_state = APP_NAV_STATE_MENU;
        break;
    default:
        break;
    }

    return next_state;
}

APP_NAV_STATE handle_game_over_event_save_record_question(GAME_OVER_USER_ACTION action) {
    APP_NAV_STATE next_state = APP_NAV_STATE_GAME_OVER;

    switch (action) {
    case GAME_OVER_USER_ACTION_SELECT:
        if (g_save_record_state) {
            g_game_over_mode = GAME_OVER_MODE_SAVE_RECORD_INPUT;
        }
        else {
            next_state = APP_NAV_STATE_MENU;
        }
        break;
    case GAME_OVER_USER_ACTION_SAVE_RECORD_YES:
        g_save_record_state = true;
        break;
    case GAME_OVER_USER_ACTION_SAVE_RECORD_NO:
        g_save_record_state = false;
        break;
    default:
        break;
    }

    return next_state;
}

APP_NAV_STATE handle_game_over_event_save_record_input(GAME_OVER_USER_ACTION action) {
    APP_NAV_STATE next_state = APP_NAV_STATE_GAME_OVER;

    switch (action) {
    case GAME_OVER_USER_ACTION_SELECT:
        if (g_name_size_curr > 0) {
            g_name_buf[g_name_size_curr] = (char)0;
            insert_new_record(g_name_buf, g_final_score);
            next_state = APP_NAV_STATE_MENU;
        }
        break;
    default:
        break;
    }

    return next_state;
}

APP_NAV_STATE handle_game_over_timer() {
    APP_NAV_STATE next_state = APP_NAV_STATE_GAME_OVER;

    g_apptick++;
    int count_refresh = ((int)((1.0f / APP_MAIN_TIMER_PERIOD) * RECORDS_NAME_INPUT_CURSOR_PERIOD) - 1);
    if (count_refresh <= 0) {
        count_refresh = 1;
        log_msg("Cursor frequency too high to process", LOG_TYPE_ERROR);
    }
    if ((g_apptick % count_refresh) == 0) {
        if (g_name_size_curr < RECORDS_NAME_MAX_SIZE) {
            if (g_name_buf[g_name_size_curr] == (char)0 || g_name_buf[g_name_size_curr] == ' ') {
                g_name_buf[g_name_size_curr] = '_';
            }
            else {
                g_name_buf[g_name_size_curr] = ' ';
            }
        }
    }

    return next_state;
}

APP_NAV_STATE handle_game_over_event(GAME_OVER_USER_ACTION action) {
    APP_NAV_STATE next_state = APP_NAV_STATE_GAME_OVER;
    
    switch (g_game_over_mode) {
    case GAME_OVER_MODE_DISPLAY_ONLY:
        next_state = handle_game_over_event_display_only(action);
        break;
    case GAME_OVER_MODE_SAVE_RECORD_QUESTION:
        next_state = handle_game_over_event_save_record_question(action);
        break;
    case GAME_OVER_MODE_SAVE_RECORD_INPUT:
        next_state = handle_game_over_event_save_record_input(action);
        break;
    case GAME_OVER_MODE_WON:
        if (action == GAME_OVER_USER_ACTION_SELECT) {
            g_game_over_mode = GAME_OVER_MODE_SAVE_RECORD_QUESTION;
        }
        break;
    default:
        log_msg("Invalid game over mode", LOG_TYPE_ERROR);
        break;
    }

    return next_state;
}

APP_NAV_STATE handle_game_over_event_keychar(char unichar) {
    APP_NAV_STATE next_state = APP_NAV_STATE_GAME_OVER;
    switch (g_game_over_mode){
    case  GAME_OVER_MODE_SAVE_RECORD_INPUT:
        if ((unichar >= 'A') && (unichar <= 'Z') && (g_name_size_curr < RECORDS_NAME_MAX_SIZE)) {
            g_name_buf[g_name_size_curr] = (char)unichar;
            g_name_size_curr++;
            if (g_name_size_curr < RECORDS_NAME_MAX_SIZE) g_name_buf[g_name_size_curr] = ' ';
        }
        else if ((unichar >= 'a') && (unichar <= 'z') && (g_name_size_curr < RECORDS_NAME_MAX_SIZE)) {
            g_name_buf[g_name_size_curr] = (char)(unichar - 32);
            g_name_size_curr++;
            if (g_name_size_curr < RECORDS_NAME_MAX_SIZE) g_name_buf[g_name_size_curr] = ' ';
        }
        else if ((unichar == '\b') && (g_name_size_curr > 0)) {
            g_name_buf[g_name_size_curr] = (char)0; // Clear current last character (might be ' ' or '_')
            g_name_size_curr--;
            g_name_buf[g_name_size_curr] = ' ';
        }
        break;
    default:
        break;
    }
    

    return next_state;
}

void set_game_over_params(int final_score, int elapsed_time) {
    g_final_score = final_score;
    g_elapsed_time = elapsed_time;
}

int get_final_score() {
    return g_final_score;
}

int get_total_elapsed_time() {
    return g_elapsed_time;
}

GAME_OVER_MODE get_game_over_mode() {
    return g_game_over_mode;
}

bool get_save_record_state() {
    return g_save_record_state;
}

char* get_new_record_name() {
    return g_name_buf;
}

void finish_game_over() {
    reset_audio();
}
