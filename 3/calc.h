#ifndef CALC_H
#define CALC_H

#include "struct.h"
#include "free.h"
#include "print.h"
#include <stdlib.h>
#include <stdbool.h>

int mult_ord(static_matrix *mat, arr *vec);
int mult_pars(matrix *mat, arr *vec);
void calc_ord(static_matrix *mat, arr *vec, arr *res);
void calc_pars(matrix *mat, arr *vec, arr *res);

#endif // CALC_H