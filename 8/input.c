#include "input.h"

int read_table(matrix *a, const char *file_name)
{
    FILE *f = fopen(file_name, "r");
    if (f == NULL)
        return 0;

    int n;
    if (fscanf(f, "%d", &n) != 2 && n <= 0)
    {
        fclose(f);
        return 0;
    }

    a->n = n;

    a->mat = alloc_matrix(n, n);
    if (a->mat == NULL)
    {
        fclose(f);
        return 0;
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (fscanf(f, "%d", &a->mat[i][j]) != 1 && a->mat[i][j] < 0)
            {
                fclose(f);
                free_matrix(a);
                return 0;
            }

    fclose(f);
    return 1;
}