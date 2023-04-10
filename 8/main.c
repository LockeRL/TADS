#include <stdio.h>
#include "table.h"
#include "input.h"
#include "print.h"
#include "find.h"

int main(int argc, char **argv)
{
    matrix a;

    if (read_table(&a, argv[1]) == 0)
        return -1;

    print_matrix(&a, "out");
    if (check(&a) == 1)
        printf("Граф связный\n");
    else
        printf("Граф несвязный\n");

    int code = 0;
    while (code != 2)
    {
        print_menu();

        printf("Введите команду: ");
        char buf[3];
        if (fgets(buf, 3, stdin) == NULL || (code = atoi(buf)) < 1 || code > 2) {
            printf("Некорректный ввод\n");
            continue;
        }
        if (code == 1)
        {
            int point;
            int max_len;

            while (1)
            {
                printf("Введите вершину от 0 до %d: ", a.n - 1);
                if (scanf("%d", &point) != 1 || point <= 0 || point >= a.n)
                {
                    printf("Неверная вершина!\n");
                    char cache[100];
                    scanf("%s", cache);
                }
                else
                    break;
            }

            while (1)
            {
                printf("Введите максимальную длину пути: ");
                if (scanf("%d", &max_len) != 1 || max_len < 0)
                {
                    printf("Неверная длина!\n");
                    char cache[100];
                    scanf("%s", cache);
                }
                else
                    break;
            }
            char cache = getchar();

            find_points(&a, point, max_len);
        }
    }
    free_matrix(&a);

    return 0;
}
