#ifndef INPUT_H
#define INPUT_H

#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void create_mat_by_stat(matrix *a, static_matrix *src);
void generate_mat_and_vec(static_matrix *a, matrix *dst, arr *vec);
void create_matrix_and_vec(static_matrix *mat, arr *vec);

#endif // INPUT_H