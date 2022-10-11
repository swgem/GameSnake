#ifndef RECORDS_CONTROLLER_H
#define RECORDS_CONTROLLER_H

#include "DefaultConfig.h"

//// ENUM

typedef struct {
    int score;
    char name[RECORDS_NAME_MAX_SIZE];
} RECORD_UNIT;

//// EXTERNAL FUNCTION DECLARATION

void insert_new_record(RECORD_UNIT* new_record);
void get_last_record(RECORD_UNIT* last_record_out);
void get_records_buf(RECORD_UNIT** records_out, int* number_of_records_out);
void clear_records_buf();

#endif
