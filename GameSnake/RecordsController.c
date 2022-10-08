#include "RecordsController.h"
#include <stdio.h>
#include <stdbool.h>
#include "Logger.h"
#include "DefaultConfig.h"

//// FUNCTION IMPLEMENTATION

void insert_new_record(RECORD_UNIT* new_record) {
    FILE* file;
    if (!fopen_s(&file, RECORDS_FILENAME, "a+") && file) {
        char str_score[10];
        sprintf_s(str_score, sizeof(str_score), "%d", new_record->score);
        fprintf_s(file, "%s\ %s\n", &new_record->name, str_score);
        fclose(file);
    }
    else {
        log_msg("Could not open records file to insert record", LOG_TYPE_ERROR);
    }
}

void get_last_record(RECORD_UNIT* last_record_out) {
    FILE* file;
    if (!fopen_s(&file, "records.txt", "r") && file) {
        char name[RECORDS_NAME_MAX_SIZE];
        int score;
        while (fscanf_s(file, "%s %d", name, RECORDS_NAME_MAX_SIZE, &score) != EOF) {
            sprintf_s(&last_record_out->name, RECORDS_NAME_MAX_SIZE, "%s", name);
            last_record_out->score = score;
        }
        
        fclose(file);
    }
    else {
        log_msg("Could not open records file to read last record", LOG_TYPE_ERROR);
    }
}
