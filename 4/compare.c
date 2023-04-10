#include "compare.h"

void compare(stack_cell *a, free_address *address, stack_arr *arr)
{
    struct timeval stop1, start, stop2, stop3, stop4, stop5, stop6;

    gettimeofday(&start, NULL);
    a = push(a, 0);
    gettimeofday(&stop1, NULL);
    push_first(arr, 1);
    gettimeofday(&stop2, NULL);
    push_second(arr, 2);
    gettimeofday(&stop3, NULL);
    a = pop(a, address);
    gettimeofday(&stop4, NULL);
    pop_first(arr);
    gettimeofday(&stop5, NULL);
    pop_second(arr);
    gettimeofday(&stop6, NULL);

    printf("Время добавления в список: %lu микросекунд\n", (stop1.tv_sec - start.tv_sec) * 1000000 + stop1.tv_usec - start.tv_usec);
    printf("Время добавления в массив, расширяющийся к концу: %lu микросекунд\n", (stop2.tv_sec - stop1.tv_sec) * 1000000 + stop2.tv_usec - stop1.tv_usec);
    printf("Время добавления в массив, расширяющийся к началу: %lu микросекунд\n", (stop3.tv_sec - stop2.tv_sec) * 1000000 + stop3.tv_usec - stop2.tv_usec);
    printf("Время удаления из списка: %lu микросекунд\n", (stop4.tv_sec - stop3.tv_sec) * 1000000 + stop4.tv_usec - stop3.tv_usec);
    printf("Время удаления из массива, расширяющегося к концу: %lu микросекунд\n", (stop5.tv_sec - stop4.tv_sec) * 1000000 + stop5.tv_usec - stop4.tv_usec);
    printf("Время удаления из массива, расширяющегося к началу: %lu микросекунд\n", (stop6.tv_sec - stop5.tv_sec) * 1000000 + stop6.tv_usec - stop5.tv_usec);
}