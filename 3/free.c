#include "free.h"

void free_vec(arr *a)
{
    free(a->arr);
    a->len = 0;
}

void free_mat(matrix *a)
{
    free_vec(&a->a);
    free_vec(&a->ia);
    free_vec(&a->ja);
}

void free_stat_mat(static_matrix *a)
{
    free(a->mat);
}