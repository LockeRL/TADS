#include "utility.h"

void print_menu()
{
    printf("Меню:\n"
           "1) Моделирование на основе массива\n"
           "2) Моделирование на основе списка\n"
           "3) Сравнение списка и массива\n"
           "4) Сравнение операций\n"
           "5) Выход\n");
}

double gen_time(int start, int end)
{
    return (double)rand()/(double)(RAND_MAX) * (end - start) + start;
}