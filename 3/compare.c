#include "compare.h"

void compare(matrix *mat, arr *vec, static_matrix *stat_mat)
{
    struct timeval stop1, start, stop2;
    arr res;
    res.arr = NULL;

    res.arr = malloc(mat->m * sizeof(int));
    res.len = mat->m;

    gettimeofday(&start, NULL);

    calc_ord(stat_mat, vec, &res);

    gettimeofday(&stop1, NULL);

    calc_pars(mat, vec, &res);

    gettimeofday(&stop2, NULL);

    free_vec(&res);

    printf("Время алгоритма для разреженных матриц: %lu микросекунд\n", (stop2.tv_sec - stop1.tv_sec) * 1000000 + stop2.tv_usec - stop1.tv_usec);
    printf("Время стандартного алгоритма: %lu микросекунд\n", (stop1.tv_sec - start.tv_sec) * 1000000 + stop1.tv_usec - start.tv_usec);
    printf("\nПамять алгоритма для разреженных матриц: %zu байт\n", sizeof(int) * (mat->a.len + mat->ia.len + mat->ja.len));
    printf("Память стандартного алгоритма: %zu байт\n", mat->m * mat->n * sizeof(int));
}