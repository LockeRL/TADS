#ifndef STACK_ARR_H
#define STACK_ARR_H

#define STACK_SIZE 20

#include <stdbool.h>
#include <stdio.h>

typedef struct
{
    double stack[STACK_SIZE * 2];
    int first_len;
    int second_len;
} stack_arr;

stack_arr init_stack();
bool first_is_empty(stack_arr *a);
bool second_is_empty(stack_arr *a);
bool is_full_arr(stack_arr *a);
void push_first(stack_arr *a, double num);
void push_second(stack_arr *a, double num);
void pop_first(stack_arr *a);
void pop_second(stack_arr *a);
void print_stack_arr(stack_arr *a);
void clear_first(stack_arr *a);
void clear_second(stack_arr *a);

#endif // STACK_ARR_H