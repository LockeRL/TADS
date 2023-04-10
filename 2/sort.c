#include "sort.h"

int comp_theatre(const void *a, const void *b)
{
    return (*(theatre*)a).min_ticket_price - (*(theatre*)b).min_ticket_price;
}

int comp_key(const void *a, const void *b)
{
    return (*(key*)a).price - (*(key*)b).price;
}

void swap(theatre *a, theatre *b)
{
    theatre buf = *a;
    *a = *b;
    *b = buf;
}

void my_sort(theatre arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[i].min_ticket_price > arr[i + 1].min_ticket_price)
                swap(&arr[j], &arr[j + 1]);
}

void sort(unsigned long *time_key, unsigned long *time_theatre_qsort, unsigned long *time_theatre_bubble, theatre arr[], key a[], int n)
{
    struct timeval stop, start, stop2, stop3;
    theatre copy[ARR_MAX_LEN];
    for (int i = 0; i < n; i++)
        copy[i] = arr[i];

    gettimeofday(&start, NULL);
    qsort(arr, n, sizeof(theatre), comp_theatre);
    gettimeofday(&stop, NULL);

    qsort(a, n, sizeof(key), comp_key);

    gettimeofday(&stop2, NULL);
    my_sort(copy, n);
    printf(" ");
    gettimeofday(&stop3, NULL);

    *time_key = (stop2.tv_sec - stop.tv_sec) * 1000000 + stop2.tv_usec - stop.tv_usec;
    *time_theatre_qsort = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;
    *time_theatre_bubble = (stop3.tv_sec - stop2.tv_sec) * 1000000 + stop3.tv_usec - stop2.tv_usec;
}