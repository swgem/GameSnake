#include "AppText.h"
#include "allegro5/allegro.h"

//// INTERNAL VARIABLE

static const char* g_app_text_array[] = {
    "SNAKE",
    "PLAY",
    "RECORDS",
    "SETTINGS",
    "EXIT",
    "FINAL SCORE: ",
    "CONGRATULATIONS, NEW RECORD!",
    "WOULD YOU LIKE TO SAVE IT?",
    "YES",
    "NO",
    "TYPE YOUR NAME BELOW:",
    "CONGRATULATIONS, YOU WON!!!!",
    "RECORDS",
    "LOADING..."
};

//// FUNCTION IMPLEMENTATION

const char* get_app_text(APP_TEXT_ID id) {
    return g_app_text_array[id];
}
