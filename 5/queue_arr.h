#ifndef QUEUE_ARR_H
#define QUEUE_ARR_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "utility.h"
#include "constants.h"

typedef struct
{
    int arr[QUEUE_SIZE];
    int head;
    int tail;
    int len;
    int in_num;
    int out_num;
} queue_arr;

void simulate_arr_and_print();
void simulate_arr(data *data, int code, bool flag);
void pop_arr(queue_arr *a);
bool push_arr_new(queue_arr *a);

#endif // QUEUE_ARR_H