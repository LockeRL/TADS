#include <stdio.h>
#include "utility.h"
#include "queue_list.h"
#include "queue_arr.h"
#include "compare.h"

int main(void)
{
    srand((time(NULL)));
    int code = 0;
    while (code != 5)
    {
        print_menu();

        printf("Введите команду: ");
        char buf[3];
        if (fgets(buf, 3, stdin) == NULL || (code = atoi(buf)) < 1 || code > 5) {
            printf("Некорректный ввод\n");
            continue;
        }
        if (code == 1)
            simulate_arr_and_print();
        else if (code == 2)
            simulate_list_and_print();
        else if (code == 3)
            compare();
        else if (code == 4)
            compare_operations();
    }


    return 0;
}
