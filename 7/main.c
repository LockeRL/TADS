#include <stdio.h>

#include "structs.h"
#include "file_work.h"
#include "print.h"
#include "compare.h"

int main(int argc, char **argv) {

    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Некорректный файл\n");
        return -1;
    }
    static_arr a = read_words(f);
    fclose(f);

    tree_t *tree = create_tree(&a);
    export_to_dot(tree, "common");
    printf("ДДП было создано\n");

    tree_t *avl_tree = create_avl_tree(&a);
    export_to_dot(avl_tree, "avl");
    printf("Сбалансированное дерево было создано\n");

    opened_hash ha = create_hash(&a);
    print_hash(&ha, "hash");
    printf("Хэш-таблица была создана\n");

    closed_hash ch = create_closed_hash(&a);
    print_closed_hash(&ch, "closed_hash");

    free_static(&a);


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
        {
            printf("Введите символ: ");
            char symb = getchar();
            delete_tree(tree, symb);
            avl_tree = delete_avl(avl_tree, symb);
            getchar();
            export_to_dot(tree, "ddp_deleted");
            export_to_dot(avl_tree, "avl_deleted");
        }
        else if (code == 2)
        {
            f = fopen(argv[1], "r");
            compare_trees(f);
            fclose(f);
        }
        else if (code == 3)
        {
            printf("Введите слово: ");
            char word[WORD_LEN];
            scanf("%s", word);
            getchar();

            delete_hash_word(&ha, word);
            print_hash(&ha, "hash_deleted");
            delete_closed_hash(&ch, word);
            print_closed_hash(&ch, "closed_del");
            
        }
        else if (code == 4)
        {
            f = fopen(argv[1], "r");
            compare_hash(f);
            fclose(f);
        }
    }

    free_tree(tree);
    free_tree(avl_tree);
    free_hash(&ha);

    return 0;
}
