#include "stack_list.h"

stack_cell *create(stack_cell *address, double num, int pos)
{
    stack_cell *a = calloc(1, sizeof(stack_cell));
    if (!a)
        return NULL;
    a->pos = pos;
    a->num = num;
    a->prev = address;
    return a;
}

bool is_empty(stack_cell *a)
{
    return a == NULL;
}

bool is_full_list(stack_cell *a)
{
    if (a == NULL)
        return false;
    return a->pos >= STACK_SIZE;
}

void free_cell(stack_cell *a)
{
    free(a);
}

stack_cell *push(stack_cell *a, double num)
{
    if (is_full_list(a))
        return a;

    stack_cell *tmp = NULL;
    if (is_empty(a))
        tmp = create(a, num, 0);
    else
        tmp = create(a, num, a->pos + 1);
    if (!tmp)
        return a;
    return tmp;
}

stack_cell *pop(stack_cell *a, free_address *add)
{
    if (is_empty(a))
        return NULL;

    add->n++;
    add->arr = realloc(add->arr, add->n * sizeof(void*));
    add->arr[add->n - 1] = (void*)a;

    stack_cell *tmp = a->prev;
    free_cell(a);
    return tmp;
}

void clear(stack_cell **a, free_address *add)
{
    for (; *a; *a = pop(*a, add));
}

void print_stack_list(stack_cell *a)
{
    stack_cell *tmp = a;
    printf("Stack: ");
    for (; tmp; tmp = tmp->prev)
        printf("%lf ", tmp->num);
    printf("\n");
}

void print_addresses(stack_cell *a)
{
    stack_cell *tmp = a;
    printf("Addresses: ");
    for (; tmp; tmp = tmp->prev)
        printf("%p ", (void*)tmp);
    printf("\n");
}

void print_free_addresses(free_address *a)
{
    printf("Free addresses: ");
    for (int i = 0; i < a->n; i++)
        printf("%p ", a->arr[i]);
    printf("\n");
}