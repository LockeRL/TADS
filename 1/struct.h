#ifndef STRUCT_H
#define STRUCT_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define ARR_LEN 30

typedef enum
{
    plus = 1,
    minus = -1
} sign;

typedef struct
{
    sign sign;
    unsigned short mantissa[30];
    unsigned short mantissa_len;
    int power;
} my_double;

typedef struct
{
    sign sign;
    unsigned short mantissa[30];
    unsigned short mantissa_len;
} my_int;

int get_double(my_double *a, const char *s);
int get_int(my_int *a, const char *s);
void count(const my_double *a, const my_int *b, my_double *answer);
bool print_new_double(const my_double *a);

#endif // STRUCT_H