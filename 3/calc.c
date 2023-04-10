#include "calc.h"

void calc_ord(static_matrix *mat, arr *vec, arr *res)
{
    int sum;
    for (int i = 0; i < mat->m; i++)
    {
        sum = 0;

        for (int j = 0; j < mat->n; j++)
            sum += mat->mat[j * mat->m + i] * vec->arr[j];

        res->arr[i] = sum;
    }
}

int mult_ord(static_matrix *mat, arr *vec)
{
    if (vec->len != mat->n)
        return -1;

    arr res;
    res.arr = NULL;

    res.arr = malloc(mat->m * sizeof(int));
    res.len = mat->m;

    calc_ord(mat, vec, &res);

    print_vec_obj(&res);

    free_vec(&res);

    return 0;
}

void calc_pars(matrix *mat, arr *vec, arr *res)
{
    int sum;
    for (int i = 0; i < mat->ja.len - 1; i++)
    {
        sum = 0;

        for (int j = mat->ja.arr[i]; j < mat->ja.arr[i + 1]; j++)
            sum += vec->arr[mat->ia.arr[j]] * mat->a.arr[j];

        res->arr[i] = sum;
    }
}

int mult_pars(matrix *mat, arr *vec)
{
    if (vec->len != mat->n)
        return -1;
    arr res;
    res.arr = NULL;

    res.arr = malloc((mat->ja.len - 1) * sizeof(int));
    res.len = mat->ja.len - 1;

    calc_pars(mat, vec, &res);

    print_vec_obj(&res);

    free_vec(&res);

    return 0;
}

