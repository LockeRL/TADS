#include "structs.h"

void free_static(static_arr *a)
{
    for (int i = 0; i < a->len; i++)
        free(a->arr[i]);
    free(a->arr);
}

void free_tree(tree_t *a)
{
    if (a != NULL)
    {
        free_tree(a->left);
        free_tree(a->right);
        free(a);
    }
}

void free_list(list_t *a)
{
    list_t *buf;
    for (; a; a = buf)
    {
        buf = a->next;
        free(a);
    }
}

void free_hash(opened_hash *a)
{
    for (int i = 0; i < a->len; i++)
        free_list(a->arr[i]);
    free(a->arr);
}

tree_t *init_tree(char *word)
{
    tree_t *a = malloc(sizeof(tree_t));
    strcpy(a->word, word);
    a->right = NULL;
    a->left = NULL;

    return a;
}

tree_t *add_block(tree_t *a, char *word, tree_t *parent)
{
    if (!a)
        a = init_tree(word);
    else if (strcmp(word, a->word) < 0)
        a->left = add_block(a->left, word, a);
    else
        a->right = add_block(a->right, word, a);
    a->parent = parent;
    return a;
}

void sort(static_arr *a)
{
    for (int i = 0; i < a->len - 1; i++)
        for (int j = 0; j < a->len - 1 ; j++)
            if (strcmp(a->arr[j + 1], a->arr[j]) < 0)
            {
                char *tmp= a->arr[j + 1];
                a->arr[j + 1] = a->arr[j];
                a->arr[j] = tmp;
            }
}

tree_t *create_tree(static_arr *a)
{
    sort(a);
    char *buf = a->arr[a->len / 2];
    a->arr[a->len / 2] = a->arr[0];
    a->arr[0] = buf;

    tree_t *head = NULL;
    for (int i = 0; i < a->len; i++)
        head = add_block(head, a->arr[i], NULL);

    return head;
}

int find_height(tree_t *a)
{
    return a ? a->height : 0;
}

int balance_count(tree_t *a)
{
    return find_height(a->right) - find_height(a->left);
}

void correct_height(tree_t *a)
{
    int left = find_height(a->left);
    int right = find_height(a->right);

    a->height = (left > right ? left : right) + 1;
}

tree_t *rotate_right(tree_t *a)
{
    tree_t *new_root = a->left;

    a->left = new_root->right;
    new_root->right = a;

    correct_height(a);
    correct_height(new_root);

    return new_root;
}

tree_t *rotate_left(tree_t *a)
{
    tree_t *new_root = a->right;

    a->right = new_root->left;
    new_root->left = a;

    correct_height(a);
    correct_height(new_root);

    return new_root;
}

tree_t *balance_root(tree_t *a)
{
    correct_height(a);

    if (balance_count(a) == 2)
    {
        if (balance_count(a->right) < 0)
            a->right = rotate_right(a->right);

        return rotate_left(a);
    }

    if (balance_count(a) == -2)
    {
        if (balance_count(a->left) > 0)
            a->left = rotate_left(a->left);

        return rotate_right(a);
    }

    return a;
}

tree_t *add_avl_block(tree_t *a, char *word)
{
    if (!a)
        a = init_tree(word);
    else if (strcmp(word, a->word) < 0)
        a->left = add_avl_block(a->left, word);
    else
        a->right = add_avl_block(a->right, word);

    return balance_root(a);
}

tree_t *create_avl_tree(static_arr *a)
{
    tree_t *head = NULL;
    for (int i = 0; i < a->len; i++)
        head = add_avl_block(head, a->arr[i]);

    return head;
}

int count_hash(char *s, int n)
{
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++)
        count += s[i];
    return count % n;
}

list_t *find_last(list_t *a)
{
    for (; a->next; a = a->next);
    return a;
}

opened_hash create_hash(static_arr *a)
{
    opened_hash hash;
    hash.arr = calloc(a->len, sizeof(list_t*));
    hash.len = a->len;

    for (int i = 0; i < a->len; i++)
    {
        int key = count_hash(a->arr[i], a->len);
        list_t *node = malloc(sizeof(list_t));
        strcpy(node->word, a->arr[i]);
        node->next = NULL;

        if (hash.arr[key] == NULL)
            hash.arr[key] = node;
        else
            find_last(hash.arr[key])->next = node;
    }
    return hash;
}

tree_t *most_left(tree_t *a) {
    if (a == NULL)
        return NULL;
    if (a->left != NULL) {
        return most_left(a->left);
    }
    return a;
}

tree_t *most_right(tree_t *a) {
    if (a == NULL)
        return NULL;
    if (a->right != NULL) {
        return most_right(a->right);
    }
    return a;
}


void delete_tree(tree_t *a, char s)
{
    if (a == NULL)
        return;

    if (s < a->word[0])
        return delete_tree(a->left, s);
    else if(s > a->word[0])
        return delete_tree(a->right, s);

    if (a->right == NULL && a->left == NULL)
    {
        tree_t *buf = a->parent;
        if (a == buf->left)
            buf->left = NULL;
        else
            buf->right = NULL;
        free(a);
        return;
    }
    else
    {
        tree_t *new = NULL;
        if (a->left != NULL)
            new = most_right(a->left);
        else
            new = most_left(a->right);

        if (new->parent->left == new)
            new->parent->left = new->left;
        else if (new->parent->right == new)
            new->parent->right = new->right;

        if (a->parent)
        {
            if (a->parent->left == a)
                a->parent->left = new;
            else
                a->parent->right = new;
        }

        new->parent = a->parent;
        new->left = a->left;
        new->right = a->right;
        strcpy(a->word, new->word);
        free(a);
        return delete_tree(new, s);
    }
}

tree_t *find_left(tree_t *a)
{
    return a->left ? find_left(a->left) : a;
}

tree_t *remove_left(tree_t *a)
{
    if(a->left == NULL)
        return a->right;
    a->left = remove_left(a->left);
    return balance_root(a);
}

tree_t *delete_avl_tree(tree_t *a, char s, bool *flag)
{
    if (!a)
        return NULL;
    if (s < a->word[0])
        a->left = delete_avl_tree(a->left, s, flag);
    else if (s > a->word[0])
        a->right = delete_avl_tree(a->right, s, flag);
    else
    {
        tree_t *q = a->left, *r = a->right;
        free(a);
        *flag = true;

        if (!r)
            return q;
        tree_t *min = find_left(r);
        min->right = remove_left(r);
        min->left = q;
        return balance_root(min);
    }
    return balance_root(a);
}

tree_t *delete_avl(tree_t *a, char s)
{
    bool flag = true;
    while (flag)
    {
        flag = false;
        a = delete_avl_tree(a, s, &flag);
    }
    return a;
}

tree_t *delete_avl_tree_word(tree_t *a, char *s, int *count)
{
    (*count)++;
    if (!a)
        return NULL;
    if (strcmp(s, a->word) < 0)
        a->left = delete_avl_tree_word(a->left, s, count);
    else if (strcmp(s, a->word) > 0)
        a->right = delete_avl_tree_word(a->right, s, count);
    else
    {
        tree_t *q = a->left, *r = a->right;
        free(a);

        if (!r)
            return q;
        tree_t *min = find_left(r);
        min->right = remove_left(r);
        min->left = q;
        return balance_root(min);
    }
    return balance_root(a);
}

int delete_hash_word(opened_hash *a, char *s)
{
    int key = count_hash(s, a->len);
    if (a->arr[key] == NULL)
        return -1;

    list_t *buf = a->arr[key];
    int count = 0;
    for (; buf; buf = buf->next, count++)
        if (strcmp(buf->word, s) == 0)
        {
            if (a->arr[key] == buf)
                a->arr[key] = buf->next;
            else
            {
                printf("enter\n");
                list_t *cur = a->arr[key];
                for (; cur->next != buf; cur = cur->next, count++);
                cur->next = NULL;
            }
            free(buf);
            return count;
        }
    return -1;
}

void free_closed_hash(closed_hash *a)
{
    for (int i = 0; i < a->len; i++)
        free(a->arr[i]);
    free(a->arr);
}

void delete_closed_hash(closed_hash *a, char *s)
{
    int key = count_hash(s, a->len);
    if (strcmp(a->arr[key], s) != 0)
        for (; strcmp(a->arr[key], s) != 0; key %= a->len)
        key++;
    free(a->arr[key]);
    a->arr[key] = NULL;
}

closed_hash create_closed_hash(static_arr *a)
{
    closed_hash hash;
    hash.arr = calloc(a->len, sizeof(char*));
    hash.len = a->len;

    for (int i = 0; i < a->len; i++)
    {
        int key = count_hash(a->arr[i], a->len);
        if (hash.arr[key] != NULL)
            for (; hash.arr[key] != NULL; key %= a->len)
                key++;
        //printf("%d\n", key);
        hash.arr[key] = strdup(a->arr[i]);
        //printf("%s\n", hash.arr[key]);
    }
    //hash.arr[7] = strdup("lwliw");
    return hash;
}
