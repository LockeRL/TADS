#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

void print_menu(void);
void print_vec(arr *a);
void print_mat(matrix *a);
void print_stat_mat(static_matrix *a);
void print_vec_obj(arr *a);

#endif // PRINT_H