#include "structs.h"

void to_dot(tree_t *a, FILE *f)
{
    if (a->left)
        fprintf(f, "\"%s\" -> \"%s\";\n", a->word, a->left->word);
    if (a->right)
        fprintf(f, "\"%s\" -> \"%s\";\n", a->word, a->right->word);
}

void apply_pre(tree_t *a, void (*f)(tree_t *, FILE *), FILE *arg)
{
    if (a == NULL)
        return;
    f(a, arg);
    apply_pre(a->left, f, arg);
    apply_pre(a->right, f, arg);
}

void export_to_dot(tree_t *a, char *file_name)
{
    char name[50];
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

    char com[100];
    sprintf(com, "dot -Tpng %s -o %s.png\n", name, file_name);
    system(com);
    char com2[100];
    sprintf(com2, "xdg-open %s.png\n", file_name);
    system(com2);

}

void print_hash(opened_hash *a, char *file_name)
{
    char name[20];
    sprintf(name, "%s.gv", file_name);
    FILE *f = fopen(name, "w");
    fprintf(f, "digraph out {\n");
    for (int i = 0; i < a->len; i++)
    {
        list_t *buf = a->arr[i];
        if (buf == NULL)
            fprintf(f, "\"\";\n");
        for (; buf; buf = buf->next)
        {
            if (buf->next)
                fprintf(f, "\"%s\" -> \"%s\";\n", buf->word, buf->next->word);
            else if (buf == a->arr[i])
                fprintf(f, "\"%s\";\n", buf->word);
        }
    }
    fprintf(f, "}\n");
    fclose(f);
    char com[50];
    sprintf(com, "dot -Tpng %s -o%s.png\n", name, file_name);
    system(com);
    char com2[50];
    sprintf(com2, "xdg-open %s.png\n", file_name);
    system(com2);
}

void print_closed_hash(closed_hash *a, char *file_name)
{
    char name[20];
    sprintf(name, "%s.gv", file_name);
    FILE *f = fopen(name, "w");
    fprintf(f, "digraph out {\n");
    for (int i = 0; i < a->len; i++)
    {
         fprintf(f, "\"%s\";\n", a->arr[i]);
    }
    fprintf(f, "}\n");
    fclose(f);
    char com[50];
    sprintf(com, "dot -Tpng %s -o%s.png\n", name, file_name);
    system(com);
    char com2[50];
    sprintf(com2, "xdg-open %s.png\n", file_name);
    system(com2);
}


void print_menu()
{
    printf("Выберите команду:\n"
           "1) Удалить слова, начинающиеся с буквы и вывести на экран\n"
           "2) Сравнить удаление в исходном и сбалансированном дереве\n"
           "3) Удалить слово из хэш-таблицы и вывести на экран\n"
           "4) Сравнить удаление в сбалансированном дереве и в хэш-таблице\n"
           "5) Выйти\n");
}
