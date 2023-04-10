#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define STACK_SIZE 20

typedef struct stack_cell stack_cell;

struct stack_cell
{
    double num;
    int pos;
    stack_cell *prev;
};

typedef struct
{
    void **arr;
    int n;
} free_address;

bool is_empty(stack_cell *a);
bool is_full_list(stack_cell *a);
stack_cell *push(stack_cell *a, double num);
stack_cell *pop(stack_cell *a, free_address *add);
void clear(stack_cell **a, free_address *add);
void print_stack_list(stack_cell *a);
void print_addresses(stack_cell *a);
void print_free_addresses(free_address *a);

#endif // STACK_H