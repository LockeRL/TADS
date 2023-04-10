#include "print.h"

void print_menu(void)
{
    printf("Меню:\n"
           "1) Заполнить матрицу и вектор-строку рандомно\n"
           "2) Заполнить вектор-строку и матрицу вручную\n"
           "3) Вывести объекты матрицы\n"
           "4) Вывести объект вектора\n"
           "5) Вывести вектор-строку\n"
           "6) Вывести исходную матрицу\n"
           "7) Умножить специальным алгоритмом для разреженных матриц и вывести результат\n"
           "8) Умножить стандартным алгоритмом и вывести результат\n"
           "9) Сравнить алгоритмы\n"
           "10) Выход\n");
}

void print_stat_mat(static_matrix *a)
{
    for (int i = 0; i < a->n; i++)
    {
        for (int j = 0; j < a->m; j++)
            printf("%d\t", a->mat[i * a->m + j]);
        printf("\n");
    }
}

void print_vec(arr *a)
{
    for (int i = 0; i < a->len; i++)
        printf("%d ", a->arr[i]);
    printf("\n");
}

void print_mat(matrix *a)
{
    printf("A: ");
    print_vec(&a->a);
    printf("IA: ");
    print_vec(&a->ia);
    printf("JA: ");
    print_vec(&a->ja);
}

void print_vec_obj(arr *a)
{
    arr vec_a;
    arr vec_ia;

    vec_a.arr = calloc(a->len, sizeof(int));
    vec_ia.arr = calloc(a->len, sizeof(int));

    vec_a.len = 0;
    vec_ia.len = 1;
    vec_ia.arr[0] = 0;

    for (int i = 0; i < a->len; i++)
        if (a->arr[i] != 0)
        {
            vec_a.arr[vec_a.len++] = a->arr[i];
            vec_ia.arr[vec_ia.len++] = i;
        }

    printf("A: ");
    print_vec(&vec_a);
    printf("IA: ");
    print_vec(&vec_ia);
    free(vec_a.arr);
    free(vec_ia.arr);
}