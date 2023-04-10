#include "tree.h"


void read_word(char *a, FILE *f)
{
    if (fscanf(f, "%s", a) != 1)
        a[0] = '\0';
}

int tree_height(FILE *f)
{
    char word[20];
    int a = 0;
    while (fscanf(f, "%s", word) == 1)
        a++;
    rewind(f);
    for (int i = 0; i < sqrt(a); i++)
        if (pow(2, i) <= a && pow(2, i + 1) > a)
            return i + 1;
}

tree *push_tree(tree *a, FILE *f, int cur_height, int max_height, tree *parent)
{
    if (cur_height > max_height)
        return NULL;
    char word[20];
    read_word(word, f);
    if (word[0] == '\0')
        return NULL;

    a = malloc(sizeof(tree));
    a->left = NULL;
    a->right = NULL;
    a->parent = parent;
    a->height = cur_height;
    a->word = strdup(word);

    a->left = push_tree(a->left, f, cur_height + 1, max_height, a);
    a->right = push_tree(a->right, f, cur_height + 1, max_height, a);
    return a;
}

void to_dot(tree *a, FILE *f)
{
    if (a->left)
        fprintf(f, "\"%s\" -> \"%s\";\n", a->word, a->left->word);
    if (a->right)
        fprintf(f, "\"%s\" -> \"%s\";\n", a->word, a->right->word);
}

void apply_pre(tree *a, void (*f)(tree*, FILE*), FILE *arg)
{
    if (a == NULL)
        return;
    f(a, arg);
    apply_pre(a->left, f, arg);
    apply_pre(a->right, f, arg);
}

void export_to_dot(tree *a, char *file_name)
{
    char name[10];
    sprintf(name, "%s.gv", file_name);
    FILE *f = fopen(name, "w");
    fprintf(f, "digraph out {\n");
    if (a)
    {
        if (a->left == NULL && a->right == NULL)
            fprintf(f, "\"%s\";\n", a->word);
        else
            apply_pre(a, to_dot, f);
    }
    fprintf(f, "}\n");
    fclose(f);
    char com[30];
    sprintf(com, "dot -Tpng %s -o%s.png\n", name, file_name);
    system(com);
    char com2[20];
    sprintf(com2, "xdg-open %s.png\n", file_name);
    system(com2);
}

void search_word(tree **find, tree *a, bool *flag, char s)
{
    if (*flag || a == NULL)
        return;
    if (a->word && a->word[0] != s)
    {
        *flag = true;
        *find = a;
        return;
    }
    else
    {
        search_word(find, a->left, flag, s);
        search_word(find, a->right, flag, s);
    }
}

tree *delete_words(tree *a, char s)
{
    if (a == NULL)
        return NULL;
    bool flag = false;
    if (!a->word || a->word[0] == s)
    {
        tree *word = NULL;
        search_word(&word, a, &flag, s);
        if (!flag)
        {
            free_tree(a);
            if (a->parent)
            {
                if (a == a->parent->left)
                    a->parent->left = NULL;
                else
                    a->parent->right = NULL;
            }
            else
                return NULL;
            a->left = NULL;
            a->right = NULL;
        }
        else
        {
            free(a->word);
            a->word = strdup(word->word);
            free(word->word);
            word->word = NULL;
        }
    }
    delete_words(a->left, s);
    delete_words(a->right, s);
    return a;
}

void free_tree(tree *a)
{
    if (a != NULL)
    {
        free_tree(a->left);
        free_tree(a->right);
        if (a->word)
            free(a->word);
        free(a);
    }
}