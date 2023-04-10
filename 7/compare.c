#include "compare.h"

void compare_trees(FILE *f)
{
    static_arr a = read_words(f);

    tree_t *tree = create_tree(&a);
    tree_t *avl_tree = create_avl_tree(&a);
    free_static(&a);
    struct timeval stop1, start, stop2;

    printf("Введите символ: ");
    char symb = getchar();
    gettimeofday(&start, NULL);

    delete_tree(tree, symb);

    gettimeofday(&stop1, NULL);

    avl_tree = delete_avl(avl_tree, symb);

    gettimeofday(&stop2, NULL);
    getchar();

    free_tree(tree);
    free_tree(avl_tree);

    printf("Время удаления в ДДП: %lu микросекунд\n", (stop1.tv_sec - start.tv_sec) * 1000000 + stop1.tv_usec - start.tv_usec);
    printf("Время удаления в сбалансированном дереве: %lu микросекунд\n", (stop2.tv_sec - stop1.tv_sec) * 1000000 + stop2.tv_usec - stop1.tv_usec);

    printf("Объем памяти одинаковый и равен: %zu\n", (sizeof(tree_t) + sizeof(tree_t*)) * a.len);
}

void compare_hash(FILE *f)
{
    static_arr a = read_words(f);

    tree_t *avl_tree = create_avl_tree(&a);
    opened_hash ha = create_hash(&a);
    closed_hash hc = create_closed_hash(&a);
    free_static(&a);

    struct timeval stop1, start, stop2, stop3;

    printf("Введите слово: ");
    char word[WORD_LEN];
    scanf("%s", word);
    getchar();

    int avl_count = 0;
    int hash_count = 0;
    gettimeofday(&start, NULL);

    avl_tree = delete_avl_tree_word(avl_tree, word, &avl_count);

    gettimeofday(&stop1, NULL);

    hash_count = delete_hash_word(&ha, word);

    gettimeofday(&stop2, NULL);
    
    delete_closed_hash(&hc, word);
    
    gettimeofday(&stop3, NULL);

    free_tree(avl_tree);
    free_hash(&ha);
    free_closed_hash(&hc);

    printf("Время удаления в сбалансированном дереве: %lu микросекунд\n", (stop1.tv_sec - start.tv_sec) * 1000000 + stop1.tv_usec - start.tv_usec);
    printf("Время удаления в открытой хэш-таблице: %lu микросекунд\n", (stop2.tv_sec - stop1.tv_sec) * 1000000 + stop2.tv_usec - stop1.tv_usec);
    printf("Время удаления в закрытой хэш-таблице: %lu микросекунд\n", (stop3.tv_sec - stop2.tv_sec) * 1000000 + stop3.tv_usec - stop2.tv_usec);

    printf("Количество сравнений в сбалансированном: %d\n", avl_count);
    printf("Количество сравнений в хэш-таблице: %d\n", hash_count);

    printf("Объем памяти сбалансированного дерева: %zu\n", (sizeof(tree_t) + sizeof(tree_t*)) * a.len);
    printf("Объем памяти открытой хэш-таблицы: %zu\n", (sizeof(list_t) + sizeof(list_t *)) * a.len);
    printf("Объем памяти закрытой хэш-таблицы: %zu\n", sizeof(char*) * a.len);
}
