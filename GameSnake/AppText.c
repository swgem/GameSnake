#include "AppText.h"
#include "allegro5/allegro.h"

//// INTERNAL VARIABLE

const char* g_app_text_array[] = {
    "SNAKE",
    "PLAY",
    "RECORDS",
    "SETTINGS",
    "EXIT"
};

//// FUNCTION IMPLEMENTATION

const char* get_app_text(APP_TEXT_ID id) {
    return g_app_text_array[id];
}
