#ifndef STRUCT_H
#define STRUCT_H

typedef struct
{
    int *arr;
    int len;
} arr;

typedef struct
{
    int n;
    int m;
    arr a;
    arr ia;
    arr ja;
} matrix;

typedef struct
{
    int *mat;
    int n;
    int m;
} static_matrix;

#endif // STRUCT_H