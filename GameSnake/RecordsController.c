#include "RecordsController.h"
#include <stdio.h>
#include "Logger.h"

//// FUNCTION IMPLEMENTATION

void insert_new_record(char* name, int score) {
    FILE* file;
    if (!fopen_s(&file, "records.txt", "a+") && file) {
        char str_score[10];
        sprintf_s(str_score, sizeof(str_score), "%d", score);
        fprintf_s(file, "%s\t%s\n", name, str_score);
        fclose(file);
    }
    else {
        log_msg("Could not open records file", LOG_TYPE_ERROR);
    }
}
