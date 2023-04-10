#include "arr_operations.h"

void create_key_array(key a[], int n, theatre src[])
{
    for (int i = 0; i < n; i++)
    {
        a[i].index = i;
        a[i].price = src[i].min_ticket_price;
    }
}

void delete_by_name(key a[], theatre b[], int *n, const char *s)
{
    int pos = 0;
    for (; pos < *n; pos++)
        if (strcmp(b[pos].show, s) == 0)
            break;
    if (pos >= *n)
    {
        printf("Нет такого театра\n");
        return;
    }
    for (int i = pos; i < *n; i++)
    {
        a[i] = a[i + 1];
        b[i] = b[i + 1];
    }
    (*n)--;
}
