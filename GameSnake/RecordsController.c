#include "RecordsController.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Logger.h"
#include "DefaultConfig.h"

//// INTERNAL MACRO

#define RECORDS_BUF_BLOCK_SIZE 3

//// INTERNAL GLOBAL VARIABLE

static RECORD_UNIT* g_records_buf;
static int g_records_buf_size = 0;
static int g_number_of_records = 0;

//// FUNCTION IMPLEMENTATION

void insert_new_record(RECORD_UNIT* new_record) {
    FILE* file;
    if (!fopen_s(&file, RECORDS_FILENAME, "a+") && file) {
        char str_score[10];
        sprintf_s(str_score, sizeof(str_score), "%d", new_record->score);
        fprintf_s(file, "%s %s\n", &new_record->name, str_score);
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

void get_records_buf(RECORD_UNIT** records_out, int* number_of_records_out) {
    FILE* file;

    clear_records_buf();
    g_records_buf_size = RECORDS_BUF_BLOCK_SIZE;
    g_records_buf = (RECORD_UNIT*)malloc(g_records_buf_size * sizeof(RECORD_UNIT));

    if (!fopen_s(&file, "records.txt", "r") && file) {
        char name[RECORDS_NAME_MAX_SIZE];
        int score;
        while (fscanf_s(file, "%s %d", name, RECORDS_NAME_MAX_SIZE, &score) != EOF) {
            g_number_of_records++;
            
            while (g_number_of_records >= g_records_buf_size) {
                g_records_buf_size += RECORDS_BUF_BLOCK_SIZE;
                g_records_buf = (RECORD_UNIT*)realloc(g_records_buf, (g_records_buf_size * sizeof(RECORD_UNIT)));
            }

            RECORD_UNIT* new_record = &g_records_buf[g_number_of_records - 1];
            sprintf_s(&new_record->name, RECORDS_NAME_MAX_SIZE, "%s", name);
            new_record->score = score;
        }

        fclose(file);
    }
    else {
        log_msg("Could not open records file to read last record", LOG_TYPE_ERROR);
    }

    *records_out = g_records_buf;
    *number_of_records_out = g_number_of_records;
}

void clear_records_buf() {
    free(g_records_buf);
    g_records_buf_size = 0;
    g_number_of_records = 0;
}
