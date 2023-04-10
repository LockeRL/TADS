#include <stdio.h>

#include "tree.h"
#include "compare.h"

int main(int argc, char **argv) {

    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Некорректный файл\n");
        return -1;
    }
    tree *a = NULL;
    a = push_tree(a, f, 1, tree_height(f), NULL);
    fclose(f);

    printf("Дерево было считано\n\n");

    int code = 0;
    while (code != 5)
    {
        print_menu();

        printf("Введите команду: ");
        char buf[3];
        if (fgets(buf, 3, stdin) == NULL || (code = atoi(buf)) < 1 || code > 5) {
            printf("Некорректный ввод\n");
            continue;
        }
        if (code == 1)
            export_to_dot(a, "out");
        else if (code == 2)
        {
            printf("Введите символ: ");
            char symb = getchar();

            a = delete_words(a, symb);
            symb = getchar();

            export_to_dot(a, "deleted");
        }
        else if (code == 3)
            compare_delete(argv[1]);
        else if (code == 4)
            compare_search(argv[1]);
    }

    free_tree(a);

    return 0;
}
