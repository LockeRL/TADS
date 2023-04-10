#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "print.h"
#include "struct.h"
#include "input.h"
#include "free.h"
#include "calc.h"
#include "compare.h"

int main(void)
{
    matrix mat;
    static_matrix stat_mat;
    arr vec;

    bool mat_f = false, vec_f = false, stat_mat_f = false;

    int code = 0;
    while (code != 10) {
        print_menu();

        printf("Введите команду: ");
        char buf[3];
        if (fgets(buf, 3, stdin) == NULL || (code = atoi(buf)) < 1 || code > 10) {
            printf("Некорректный ввод\n");
            continue;
        }
        if (code == 1)
        {
            if (mat_f)
                free_mat(&mat);
            if (vec_f)
                free_vec(&vec);
            if (stat_mat_f)
                free_stat_mat(&stat_mat);
            generate_mat_and_vec(&stat_mat, &mat, &vec);
            stat_mat_f = true;
            mat_f = true;
            vec_f = true;
        }
        else if (code == 2)
        {
            if (mat_f)
                free_mat(&mat);
            if (vec_f)
                free_vec(&vec);
            if (stat_mat_f)
                free_stat_mat(&stat_mat);
            create_matrix_and_vec(&stat_mat, &vec);
            create_mat_by_stat(&mat, &stat_mat);
            stat_mat_f = true;
            mat_f = true;
            vec_f = true;
        }
        else if (code == 3)
        {
            if (mat_f)
                print_mat(&mat);
            else
                printf("Матрица не введена\n");
        }
        else if (code == 4)
        {
            if (vec_f)
                print_vec_obj(&vec);
            else
                printf("Вектор не введен\n");
        }
        else if (code == 5)
        {
            if (vec_f)
                print_vec(&vec);
            else
                printf("Вектор не введён\n");
        }
        else if (code == 6)
        {
            print_stat_mat(&stat_mat);
        }
        else if (code == 7)
        {
            if (mat_f && vec_f)
                mult_pars(&mat, &vec);
            else
                printf("Матрица или вектор не введены\n");
        }
        else if (code == 8)
        {
            if (mat_f && vec_f)
                mult_ord(&stat_mat, &vec);
            else
                printf("Матрица или вектор не введены\n");
        }
        else if (code == 9)
        {
            if (mat_f && vec_f)
                compare(&mat, &vec, &stat_mat);
            else
                printf("Матрица или вектор не введены\n");
        }
    }
    if (mat_f)
        free_mat(&mat);
    if (vec_f)
        free_vec(&vec);
    if (stat_mat_f)
        free_stat_mat(&stat_mat);

    return EXIT_SUCCESS;
}