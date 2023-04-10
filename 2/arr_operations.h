#ifndef ARR_OPERATIONS_H
#define ARR_OPERATIONS_H

#include "struct.h"
#include <string.h>

void create_key_array(key a[], int n, theatre src[]);
void delete_by_name(key a[], theatre b[], int *n, const char *s);

#endif // ARR_OPERATIONS_H
