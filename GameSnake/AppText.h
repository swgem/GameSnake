#ifndef APP_TEXT_H
#define APP_TEXT_H

//// ENUM

typedef enum {
    APP_TEXT_ID_MENU_TITLE = 0,
    APP_TEXT_ID_MENU_OP1,
    APP_TEXT_ID_MENU_OP2,
    APP_TEXT_ID_MENU_OP3,
    APP_TEXT_ID_MENU_OP4,
    APP_TEXT_ID_FINAL_SCORE,
    APP_TEXT_ID_CONGRATS_NEW_RECORD,
    APP_TEXT_ID_SAVE_RECORD_QUESTION,
    APP_TEXT_ID_YES,
    APP_TEXT_ID_NO,
    APP_TEXT_ID_TYPE_NAME,
    APP_TEXT_ID_GAME_OVER_WON,
    APP_TEXT_ID_RECORDS,
    APP_TEXT_ID_LOADING
} APP_TEXT_ID;

//// EXTERNAL FUNCTION DECLARATION

const char* get_app_text(APP_TEXT_ID id);

#endif
