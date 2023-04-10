#include "compare.h"

void compare()
{
    data list, arr;

    struct timeval stop1, start, stop2;

    gettimeofday(&start, NULL);
    simulate_arr(&arr, 0, false);
    gettimeofday(&stop1, NULL);

    simulate_list(&list, 0, false);
    gettimeofday(&stop2, NULL);

    printf("Время работы списка: %lu микросекунд\n", (stop2.tv_sec - stop1.tv_sec) * 1000000 + stop2.tv_usec - stop1.tv_usec);
    printf("Время работы массива: %lu микросекунд\n", (stop1.tv_sec - start.tv_sec) * 1000000 + stop1.tv_usec - start.tv_usec);
    printf("\nПамять для списка: %zu байт\n", list.max * sizeof(queue_cell) + sizeof(queue_list));
    printf("Память для массива: %zu байт\n", sizeof(queue_arr));
}

void compare_operations()
{
    struct timeval stop1, start, stop2, stop3, stop4;

    queue_list a;
    a.len = 0;
    a.head = NULL;
    a.tail = NULL;
    a.out_num = 0;
    a.in_num = 0;
    a.max_len = 0;

    queue_arr b;
    b.len = 0;
    b.head = 0;
    b.tail = 0;
    b.out_num = 0;
    b.in_num = 0;

    gettimeofday(&start, NULL);
    push_list_new(&a);
    gettimeofday(&stop1, NULL);
    push_arr_new(&b);
    gettimeofday(&stop2, NULL);
    pop_list(&a);
    gettimeofday(&stop3, NULL);
    pop_arr(&b);
    gettimeofday(&stop4, NULL);

    printf("Время добавления в очередь-список: %lu микросекунд\n", (stop1.tv_sec - start.tv_sec) * 1000000 + stop1.tv_usec - start.tv_usec);
    printf("Время добавления в очередь-массив: %lu микросекунд\n", (stop2.tv_sec - stop1.tv_sec) * 1000000 + stop2.tv_usec - stop1.tv_usec);
    printf("Время удаления из очереди-списка: %lu микросекунд\n", (stop3.tv_sec - stop2.tv_sec) * 1000000 + stop3.tv_usec - stop2.tv_usec);
    printf("Время удаления из очереди-массива: %lu микросекунд\n", (stop4.tv_sec - stop3.tv_sec) * 1000000 + stop4.tv_usec - stop3.tv_usec);}