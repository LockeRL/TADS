#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "utility.h"
#include "constants.h"

typedef struct queue_cell queue_cell;

struct queue_cell
{
    int a;
    queue_cell *prev;
};

typedef struct
{
    queue_cell *head;
    queue_cell *tail;
    int len;
    int in_num;
    int out_num;
    int max_len;
} queue_list;

void simulate_list_and_print();
void simulate_list(data *data, int code, bool flag);
void pop_list(queue_list *a);
bool push_list_new(queue_list *a);

#endif // QUEUE_H
