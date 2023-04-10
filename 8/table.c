#include "table.h"

int **alloc_matrix(int n, int m)
{

    int **mat = malloc(n * sizeof(int*) + n * m * sizeof(int));

    if (!mat)
        return NULL;

    for (int i = 0; i < n; i++)
        mat[i] = (int*)((char*)mat + n * sizeof(int*) + i * m * sizeof(int));

    return mat;
}

void free_matrix(matrix *a)
{
    free(a->mat);
    a->mat = NULL;
    a->n = 0;
}

void check_connection(matrix *con, matrix *a, int from, int cur)
{
    bool flag = con->mat[from][cur] == 1;
    con->mat[from][cur] = 1;

    for (int i = 0; i < a->n; i++)
        if (!flag && a->mat[cur][i] != 0)
            check_connection(con, a, from, i);
}

int check(matrix *a)
{
    matrix p;
    p.n = a->n;
    p.mat = alloc_matrix(p.n, p.n);
    for (int i = 0; i < a->n; i++)
        for (int j = 0; j < a->n; j++)
            p.mat[i][j] = 0;

    for (int i = 0; i < a->n; i++)
        check_connection(&p, a, i, i);

    for (int i = 0; i < a->n; i++)
        for (int j = 0; j < a->n; j++)
            if (p.mat[i][j] != 1)
            {
                free_matrix(&p);
                return 0;
            }

    free_matrix(&p);
    return 1;
}