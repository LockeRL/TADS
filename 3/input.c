#include "input.h"

void create_mat_by_stat(matrix *a, static_matrix *src)
{
    int k = 0;

    a->a.arr = NULL;
    a->ia.arr = NULL;
    a->ja.arr = malloc((src->m + 1) * sizeof(int));

    a->ja.len = src->m + 1;
    a->ja.arr[0] = 0;
    a->a.len = 0;
    a->ia.len = 0;
    a->n = src->n;
    a->m = src->m;

    for (int i = 0; i < src->m; i++)
    {
        for (int j = 0; j < src->n; j++)
        {
            if (src->mat[j * src->m + i] != 0)
            {
                a->a.arr = realloc(a->a.arr, (a->a.len + 1) * sizeof(int));
                a->a.arr[a->a.len++] = src->mat[j * src->m + i];
                a->ia.arr = realloc(a->ia.arr, (a->ia.len + 1) * sizeof(int));
                a->ia.arr[a->ia.len++] = j;
                k++;
            }
        }
        a->ja.arr[i + 1] = k;
    }
}

void generate_mat_and_vec(static_matrix *a, matrix *dst, arr *vec)
{
    srand(time(NULL));

    int n;
    int m;

    while (1)
    {
        printf("Введите целое количество строк матрицы: ");
        if (scanf("%d", &n) != 1 || n <= 0 || n > 1000)
        {
            printf("Неверное количество строк матрицы!\n");
            char cache[100];
            scanf("%s", cache);
        }
        else
            break;
    }

    while (1)
    {
        printf("Введите целое количество столбцов матрицы: ");
        if (scanf("%d", &m) != 1 || m <= 0 || m > 1000)
        {
            printf("Неверное количество столбцов матрицы!\n");
            char cache[100];
            scanf("%s", cache);
        }
        else
            break;
    }
    char cache = getchar();

    a->n = n;
    a->m = m;
    vec->len = a->n;

    a->mat = malloc(a->n * a->m * sizeof(int));
    vec->arr = malloc(a->n * sizeof(int));

    for (int i = 0; i < a->n; i++)
    {
        for (int j = 0; j < a->m; j++)
            a->mat[i * a->m + j] = rand() % 100;
        vec->arr[i] = rand() % 100;
    }

    create_mat_by_stat(dst, a);
}

void create_matrix_and_vec(static_matrix *mat, arr *vec)
{
    int tmp;
    int n;
    int m;

    while (1)
    {
        printf("Введите целое количество строк матрицы не большее 1000: ");
        if (scanf("%d", &n) != 1)
        {
            printf("Неверное количество строк матрицы!\n");
            char cache[100];
            scanf("%s", cache);
        }
        else if (n <= 0 || n > 1000)
            printf("Неверное количество строк матрицы!\n");
        else
            break;
    }

    while (1)
    {
        printf("Введите целое количество столбцов матрицы не большее 1000: ");
        if (scanf("%d", &m) != 1)
        {
            printf("Неверное количество столбцов матрицы!\n");
            char cache[100];
            scanf("%s", cache);
        }
        else if (m <= 0 || m > 1000)
            printf("Неверное количество столбцов матрицы!\n");
        else
            break;
    }

    mat->mat = calloc(n * m, sizeof(int));
    mat->n = n;
    mat->m = m;
    vec->arr = calloc(n, sizeof(int));
    vec->len = n;

    int num;
    while (1)
    {
        printf("Введите количество элементов не большее %d, которое хотите заполнить или -1, если хотите заполнить все вручную: ", n * m);
        if (scanf("%d", &num) != 1)
        {
            printf("Неверное количество элементов!\n");
            char cache[100];
            scanf("%s", cache);
        }
        else if (num < -1 || num > n * m)
            printf("Неверное количество элементов!\n");
        else
            break;
    }

    if (num == -1)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                while (1)
                {
                    printf("Введите %d-й элемент %d-й строки: ", j + 1, i + 1);
                    if (scanf("%d", &tmp) != 1)
                    {
                        printf("Некорректный элемент!\n");
                        char cache[100];
                        scanf("%s", cache);
                    } else
                        break;
                }
                *(mat->mat + i * m + j) = tmp;
            }
        for (int i = 0; i < n; i++) {
            while (1)
            {
                printf("Введите %d-й элемент вектора: ", i + 1);
                if (scanf("%d", &tmp) != 1)
                {
                    printf("Некорректный элемент!\n");
                    char cache[100];
                    scanf("%s", cache);
                } else
                    break;
            }
            *(vec->arr + i) = tmp;
        }
    }
    else
    {
        int i_i, j_j;
        for (int i = 0; i < num; i++)
        {
            while (1)
            {
                printf("Введите номер строки, не больший %d: ", n - 1);
                if (scanf("%d", &i_i) != 1)
                {
                    printf("Некорректный номер!\n");
                    char cache[100];
                    scanf("%s", cache);
                }
                else if (i_i < 0 || i_i >= n)
                    printf("Некорректный номер!\n");
                else
                    break;
            }
            while (1)
            {
                printf("Введите номер столбца, не больший %d: ", m - 1);
                if (scanf("%d", &j_j) != 1)
                {
                    printf("Некорректный номер!\n");
                    char cache[100];
                    scanf("%s", cache);
                }
                else if (j_j < 0 || j_j >= m)
                    printf("Некорректный номер!\n");
                else
                    break;
            }
            while (1)
            {
                printf("Введите элемент: ");
                if (scanf("%d", &tmp) != 1)
                {
                    printf("Некорректный элемент!\n");
                    char cache[100];
                    scanf("%s", cache);
                }
                else
                    break;
            }
            *(mat->mat + i_i * m + j_j) = tmp;
        }

        while (1)
        {
            printf("Введите количество элементов вектора не большее %d, которое хотите заполнить: ", n);
            if (scanf("%d", &num) != 1)
            {
                printf("Неверное количество элементов!\n");
                char cache[100];
                scanf("%s", cache);
            }
            else if (num < -1 || num > n)
                printf("Неверное количество элементов!\n");
            else
                break;
        }
        for (int i = 0; i < num; i++) {
            while (1)
            {
                printf("Введите номер элемента, не больший %d: ", n - 1);
                if (scanf("%d", &i_i) != 1)
                {
                    printf("Некорректный номер!\n");
                    char cache[100];
                    scanf("%s", cache);
                }
                else if (i_i < 0 || i_i >= n)
                    printf("Некорректный номер!\n");
                else
                    break;
            }
            while (1) {
                printf("Введите элемент: ");
                if (scanf("%d", &tmp) != 1) {
                    printf("Некорректный элемент!\n");
                    char cache[100];
                    scanf("%s", cache);
                } else
                    break;
            }
            *(vec->arr + i_i) = tmp;
        }
    }


    char cache = getchar();
}