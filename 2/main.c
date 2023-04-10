#include <stdio.h>
#include "read.h"
#include "print.h"
#include "struct.h"
#include "sort.h"
#include "arr_operations.h"
#include "write.h"

int main(void)
{
    theatre arr[ARR_MAX_LEN];

    FILE *f = NULL;
    if ((f = fopen("data.csv", "r")) == NULL)
        return 1;

    int n = 0;
    int return_code;
    while ((return_code = read_theatre(&arr[n], f)) == 0)
        n++;

    if (return_code && !feof(f))
    {
        printf("База данных некорректна\n");
        fclose(f);
        return -1;
    }

    fclose(f);

    key key[ARR_MAX_LEN];

    create_key_array(key, n, arr);

    int code = 0;

    unsigned long time_key = 0, time_theatre_qsort = 0, time_theatre_bubble = 0;

    while (code != 11)
    {
        print_menu();

        printf("Введите команду: ");
        if (scanf("%d", &code) != 1)
        {
            printf("Некорректный ввод\n");
            char cache[100];
            if (scanf("%s", cache) == 1)
                continue;
            continue;
        }
        
        
        if (code < 1 || code > 11)
        {
            printf("Некорректный ввод\n");
            continue;
        }

        printf("\n");
        if (code == 1)
            print_data_table();
        else if (code == 2)
        {
            theatre buf;
            if (read_theatre_stdin(&buf) != 0)
                continue;
            arr[n] = buf;
            key[n].index = n;
            key[n++].price = buf.min_ticket_price;
        }
        else if (code == 3)
        {
            char tet[22];
            printf("Введите название спектакля: ");
            if (scanf("%s", tet) != 1 || strlen(tet) > 20)
            {
                printf("Некорректный ввод\n");
                continue;
            }

            delete_by_name(key, arr, &n, tet);
        }
        else if (code == 4)
            print_key_table(key, n);
        else if (code == 5)
            sort(&time_key, &time_theatre_qsort, &time_theatre_bubble, arr, key, n);
        else if (code == 6)
        {
            int age;
            printf("Введите возраст: ");
            if (scanf("%d", &age) != 1 || age < 0)
            {
                printf("Некорректный ввод\n");
                continue;
            }

            int duration;
            printf("Введите длительность: ");
            if (scanf("%d", &duration) != 1 || duration <= 0)
            {
                printf("Некорректный ввод\n");
                continue;
            }

            print_musical_by_age_duration(arr, n, age, duration);
        }
        else if (code == 7)
            print_table(arr, n);
        else if (code == 8)
        {
            printf("Time for table: %lu millisec\n", time_theatre_qsort);
            printf("Time for keys: %lu millisec\n", time_key);
        }
        else if (code == 9)
        {
            printf("Time for bubble: %lu millisec\n", time_theatre_bubble);
            printf("Time for qsort: %lu millisec\n", time_theatre_qsort);
        }
        else if (code == 10)
            print_by_key(key);
    }

    file_write(arr, n);

    return 0;
}
