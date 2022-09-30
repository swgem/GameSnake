#include "RecordsController.h"
#include <stdio.h>
#include <stdbool.h>
#include "Logger.h"
#include "DefaultConfig.h"

//// FUNCTION IMPLEMENTATION

void insert_new_record(char* name, int score) {
    FILE* file;
    if (!fopen_s(&file, RECORDS_FILENAME, "a+") && file) {
        char str_score[10];
        sprintf_s(str_score, sizeof(str_score), "%d", score);
        fprintf_s(file, "%s\ %s\n", name, str_score);
        fclose(file);
    }
    else {
        log_msg("Could not open records file to insert record", LOG_TYPE_ERROR);
    }
}

void get_last_record(char* buf_name, int* score) {
    FILE* file;
    int pos;
    if (!fopen_s(&file, "records.txt", "r") && file) {
        while(!feof(file)) {
            pos = ftell(file);
            char name[RECORDS_NAME_MAX_SIZE];
            if (fscanf_s(file, "%s %d", name, RECORDS_NAME_MAX_SIZE, score)) {
                pos = ftell(file);
                if (buf_name) {
                    sprintf_s(buf_name, RECORDS_NAME_MAX_SIZE, "%s", name);
                }
            }
            else {
                log_msg("Not enough buffer to read line from records file", LOG_TYPE_ERROR);
            }
        }
        
        fclose(file);
    }
    else {
        log_msg("Could not open records file to read last record", LOG_TYPE_ERROR);
    }
}
