#ifndef PRINT_H
#define PRINT_H

#include "structs.h"

void export_to_dot(tree_t *a, char *file_name);
void print_hash(opened_hash *a, char *file_name);
void print_menu();
void print_closed_hash(closed_hash *a, char *file_name);

#endif // PRINT_H
