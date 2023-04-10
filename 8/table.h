#ifndef TABLE_H
#define TABLE_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int **mat;
    int n;
} matrix;

int **alloc_matrix(int n, int m);
void free_matrix(matrix *a);
int check(matrix *a);

#endif // TABLE_H
