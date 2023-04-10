#ifndef FREE_H
#define FREE_H

#include <stdlib.h>
#include "struct.h"

void free_mat(matrix *a);
void free_vec(arr *a);
void free_stat_mat(static_matrix *a);

#endif // FREE_H