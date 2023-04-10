#include "stack_arr.h"

stack_arr init_stack()
{
    stack_arr a;
    a.first_len = 0;
    a.second_len = 0;
    return a;
}

bool first_is_empty(stack_arr *a)
{
    return a->first_len == 0;
}

bool second_is_empty(stack_arr *a)
{
    return a->second_len == 0;
}

bool is_full_arr(stack_arr *a)
{
    return a->first_len + a->second_len >= STACK_SIZE * 2;
}

void push_first(stack_arr *a, double num)
{
    if (is_full_arr(a))
        return;

    a->stack[a->first_len++] = num;
}

void push_second(stack_arr *a, double num)
{
    if (is_full_arr(a))
        return;

    a->second_len++;
    double tmp;
    double new = num;
    for (int i = 0; i < a->second_len; i++)
    {
        tmp = a->stack[STACK_SIZE * 2 - i - 1];
        a->stack[STACK_SIZE * 2 - i - 1] = new;
        new = tmp;
    }
}

void pop_first(stack_arr *a)
{
    if (first_is_empty(a))
        return;

    a->first_len--;
}

void pop_second(stack_arr *a)
{
    if (second_is_empty(a))
        return;

    a->second_len--;
    for (int i = 0; i < a->second_len; i++)
        a->stack[STACK_SIZE * 2 - i - 1] = a->stack[STACK_SIZE * 2 - i - 2];
}

void clear_first(stack_arr *a)
{
    a->first_len = 0;
}

void clear_second(stack_arr *a)
{
    a->second_len = 0;
}

void print_stack_arr(stack_arr *a)
{
    printf("Stack 1: ");
    for (int i = 0; i < a->first_len; i++)
            printf("%lf ", a->stack[i]);
    printf("\n");
    printf("Stack2: ");
    for (int i = 0; i < a->second_len; i++)
        printf("%lf ", a->stack[STACK_SIZE * 2 - i - 1]);
    printf("\n");
}