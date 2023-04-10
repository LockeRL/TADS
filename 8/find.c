#include "find.h"

void find(matrix *a, int *points, int p, int cur_len, int max_len)
{
    if (points[p] == 1)
        return;

    points[p] = 1;
    for (int i = 0; i < a->n; i++)
        if (a->mat[p][i] != 0 && (cur_len + a->mat[p][i]) <= max_len)
            find(a, points, i, cur_len + a->mat[p][i], max_len);
}

void find_points(matrix *a, int point, int max_len)
{
    int *arr = calloc(a->n, sizeof(int));

    find(a, arr, point, 0, max_len);

    print_arr(arr, a->n);

    free(arr);
}