#include "compare.h"

void delete_file(FILE *f, char s)
{
    FILE *out = fopen("delete_in_file.txt", "w");

    char buf[30];
    while (fscanf(f, "%s", buf) == 1)
        if (buf[0] == s)
            fprintf(out, "%s ", buf);

    fclose(out);
}

void compare_delete(char *file_name)
{
    FILE *f = fopen(file_name, "r");
    tree *a = NULL;
    a = push_tree(a, f, 1, tree_height(f), NULL);

    printf("Введите символ: ");
    char symb = getchar();

    struct timeval stop1, start, stop2;
    gettimeofday(&start, NULL);

    a = delete_words(a, symb);

    gettimeofday(&stop1, NULL);

    delete_file(f, symb);

    gettimeofday(&stop2, NULL);
    fclose(f);
    symb = getchar();

    printf("Время удаления из дерева: %lu микросекунд\n", (stop1.tv_sec - start.tv_sec) * 1000000 + stop1.tv_usec - start.tv_usec);
    printf("Время удаления из файла: %lu микросекунд\n", (stop2.tv_sec - stop1.tv_sec) * 1000000 + stop2.tv_usec - stop1.tv_usec);

    free_tree(a);
}

tree *push_one_side_tree(tree *a, FILE *f)
{
    char word[20];
    read_word(word, f);
    if (word[0] == '\0')
        return NULL;

    a = malloc(sizeof(tree));
    a->left = NULL;
    a->right = NULL;
    a->word = strdup(word);

    a->left = push_one_side_tree(a->left, f);
    return a;
}

void new_search_word(tree **find, tree *a, bool *flag, char *s)
{
    if (*flag || a == NULL)
        return;
    if (strcmp(a->word, s) == 0)
    {
        *flag = true;
        *find = a;
        return;
    }
    new_search_word(find, a->left, flag, s);
    new_search_word(find, a->right, flag, s);
}

char *find_right(tree *a)
{
    if (a->left == NULL)
        return a->word;
    return find_right(a->left);
}

void compare_search(char *file_name)
{
    FILE *f = fopen(file_name, "r");
    tree *a = NULL;
    a = push_tree(a, f, 1, tree_height(f), NULL);
    tree *b = NULL;
    rewind(f);
    b = push_one_side_tree(b, f);
    tree *find;
    bool flag = false;
    char *word = find_right(b);
    printf("Word to find: %s\n", word);
    export_to_dot(a, "bin");
    export_to_dot(b, "list");
    struct timeval stop1, start, stop2;

    gettimeofday(&start, NULL);

    new_search_word(&find, a, &flag, word);
    printf("Found word in bin: %s\n", find->word);

    gettimeofday(&stop1, NULL);

    flag = false;
    new_search_word(&find, a, &flag, word);
    printf("Found word in list: %s\n", find->word);

    gettimeofday(&stop2, NULL);

    printf("Время поиска самого правого элемента в бинарном дереве: %lu микросекунд\n", (stop1.tv_sec - start.tv_sec) * 1000000 + stop1.tv_usec - start.tv_usec);
    printf("Время поиска самого правого элемента в дереве-списке: %lu микросекунд\n", (stop2.tv_sec - stop1.tv_sec) * 1000000 + stop2.tv_usec - stop1.tv_usec);

    free_tree(a);
    free_tree(b);
}

void print_menu()
{
    printf("Выберите команду:\n"
           "1) Вывести граф\n"
           "2) Удалить слова, начинающиеся с буквы и вывести на экран\n"
           "3) Сравнить удаление из файла и из дерева\n"
           "4) Сравнить поиск самого правого элемента в бинарном дереве и дереве-списке\n"
           "5) Выйти\n");
}