#include <stdio.h>
#include "stack_list.h"
#include "stack_arr.h"
#include "compare.h"

int main(void) {

    stack_cell *stack_list = NULL;
    stack_arr stack_arr = init_stack();

    free_address address;
    address.arr = NULL;
    address.n = 0;

    int code = 0;
    while (code != 15)
    {
        printf("1) Добавить элемент в стек-список\n"
               "2) Добавить элемент в первый стек стека-массива\n"
               "3) Добавить элемент во второй стек стека-массива\n"
               "4) Удалить элемент из стека-списка\n"
               "5) Удалить элемент из первого стека стека-массива\n"
               "6) Удалить элемент из второго стека стека-массива\n"
               "7) Вывести стек-список\n"
               "8) Вывести стек-массив\n"
               "9) Вывести освобожденные адреса списка\n"
               "10) Вывести текущие адреса списка\n"
               "11) Очистить стек-список\n"
               "12) Очистить первый стек стек-массива\n"
               "13) Очистить второй стек стек-массива\n"
               "14) Сравнить операции\n"
               "15) Выйти\n");

        printf("Введите команду: ");
        char buf[10];
        if (fgets(buf, 10, stdin) == NULL || (code = atoi(buf)) < 1 || code > 15)
        {
            printf("Некорректный ввод\n");
            continue;
        }
        if (code == 1)
        {
            if (is_full_list(stack_list))
            {
                printf("Стек-список переполнен\n");
                continue;
            }

            double num;

            while (1)
            {
                printf("Введите вещественное число: ");
                if (scanf("%lf", &num) != 1)
                {
                    printf("Некорректное число!\n");
                    char cache[100];
                    scanf("%s", cache);
                }
                else
                {
                    char a;
                    scanf("%c", &a);
                    break;
                }
            }

            stack_list = push(stack_list, num);
        }
        else if (code == 2)
        {
            if (is_full_arr(&stack_arr))
            {
                printf("Стек-массив переполнен\n");
                continue;
            }
            double num;

            while (1)
            {
                printf("Введите вещественное число: ");
                if (scanf("%lf", &num) != 1)
                {
                    printf("Некорректное число!\n");
                    char cache[100];
                    scanf("%s", cache);
                }
                else
                {
                    char a;
                    scanf("%c", &a);
                    break;
                }
            }

            push_first(&stack_arr, num);
        }
        else if (code == 3)
        {
            if (is_full_arr(&stack_arr))
            {
                printf("Стек-массив переполнен\n");
                continue;
            }
            double num;

            while (1)
            {
                printf("Введите вещественное число: ");
                if (scanf("%lf", &num) != 1)
                {
                    printf("Некорректное число!\n");
                    char cache[100];
                    scanf("%s", cache);
                }
                else
                {
                    char a;
                    scanf("%c", &a);
                    break;
                }
            }

            push_second(&stack_arr, num);
        }
        else if (code == 4)
        {
            if (is_empty(stack_list))
            {
                printf("Список пуст\n");
                continue;
            }
            stack_list = pop(stack_list, &address);
        }
        else if (code == 5)
        {
            if (first_is_empty(&stack_arr))
            {
                printf("Первый стек стек-массива пуст\n");
                continue;
            }
            pop_first(&stack_arr);
        }
        else if (code == 6)
        {
            if (second_is_empty(&stack_arr))
            {
                printf("Второй стек стек-массива пуст\n");
                continue;
            }
            pop_second(&stack_arr);
        }
        else if (code == 7)
            print_stack_list(stack_list);
        else if (code == 8)
            print_stack_arr(&stack_arr);
        else if (code == 9)
            print_free_addresses(&address);
        else if (code == 10)
            print_addresses(stack_list);
        else if (code == 11)
            clear(&stack_list, &address);
        else if (code == 12)
            clear_first(&stack_arr);
        else if (code == 13)
            clear_second(&stack_arr);
        else if (code == 14)
            compare(stack_list, &address, &stack_arr);
    }

    clear(&stack_list, &address);
    free(address.arr);
    return 0;
}
