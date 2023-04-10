#include "print.h"

void print_matrix(matrix *a, char *file_name)
{
    char name[20];
    sprintf(name, "%s.gv", file_name);
    FILE *f = fopen(name, "w");
    fprintf(f, "digraph out {\n");

    for (int i = 0; i < a->n; i++)
        for (int j = 0; j < a->n; j++)
            if (a->mat[i][j] != 0)
                fprintf(f, "\"%d\" -> \"%d\" [ label = \"%d\" ];\n", i, j, a->mat[i][j]);

    fprintf(f, "}\n");
    fclose(f);
    char com[50];
    sprintf(com, "dot -Tpng %s -o%s.png\n", name, file_name);
    system(com);
    char com2[50];
    sprintf(com2, "xdg-open %s.png\n", file_name);
    system(com2);
}

void print_arr(const int *a, int n)
{
    printf("Вершины: ");
    for (int i = 0; i < n; i++)
        if (a[i] != 0)
            printf("%d ", i);
    printf("\n");
}

void print_menu()
{
    printf("Выберите команду:\n"
           "1) Найти вершины, в которые можно добраться из данной\n"
           "2) Выйти\n");
}