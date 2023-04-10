#ifndef PRINT_H
#define PRINT_H

#include "struct.h"
#include "read.h"

void print_theatre(theatre *a);
void print_musical_by_age_duration(theatre arr[], int n, int age, int duration);
void print_menu(void);
void print_data_table(void);
void print_key_table(key a[], int n);
void print_table(theatre a[], int n);
void print_by_key(key b[]);

#endif // PRINT_H
