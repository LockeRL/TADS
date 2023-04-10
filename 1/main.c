#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

int main(void)
{
    char first_double[ARR_LEN + 15];
    char second_int[ARR_LEN + 5];
    my_double a;
    my_int b;
    my_double ans;
    int double_return_code, int_return_code;
    
    printf("Программа предназначена для вычисления произведения целого числа и действительное.\n\n");
    printf("Укажите действительное число в формате \"(+-)m.n E (+-)K\"; знаки '+' или '-' ставить обязательно, букву Е латинскую, которая разграничивает порядок, ставить обязательно, пробелы ставить в соответствии с образцом. Также m+n <= 30 и К - целое число из промежутка (-99999;99999).\n");
    printf("                               |         |         |        |\n");
    printf("Введите действительное число: ");
    if (!fgets(first_double, sizeof(first_double), stdin))
    {
        printf("Некорректные данные\n");
        return EXIT_FAILURE;
    }

    first_double[strlen(first_double) - 1] = '\0';
    double_return_code = get_double(&a, first_double);
    if (double_return_code == -1)
    {
        printf("Некорректные данные\n");
        return EXIT_FAILURE;
    }

    printf("Укажите целое число в формате \"(+-)m\"; знак '+' или '-' ставить обязательно. Также m <= 30.\n");
    printf("                      |         |         |        |\n");
    printf("Введите целое число: ");

    if (!fgets(second_int, sizeof(second_int), stdin))
    {
        printf("Некорректные данные\n");
        return EXIT_FAILURE;
    }

    second_int[strlen(second_int) - 1] = '\0';
    
    
    int_return_code = get_int(&b, second_int);
    if (int_return_code == -1)
    {
        printf("Некорректные данные\n");
        return EXIT_FAILURE;
    }
    
    if (double_return_code == 1 || int_return_code == 1)
    {
        printf("Произведение: +0.0 E +0\n");
        return EXIT_SUCCESS;
    }

    count(&a, &b, &ans);

    if (!print_new_double(&ans))
    {
        printf("Произошло переполнение\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

