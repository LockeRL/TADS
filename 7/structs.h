#ifndef STRUCTS_H
#define STRUCTS_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define WORD_LEN 20

typedef struct tree tree_t;

struct tree
{
    char word[WORD_LEN];
    int height;
    tree_t *left;
    tree_t *right;
    tree_t *parent;
};

typedef struct list list_t;

struct list
{
    char word[WORD_LEN];
    list_t *next;
};

typedef struct
{
    list_t **arr;
    int len;
} opened_hash;

typedef struct
{
    char **arr;
    int len;
} static_arr;

typedef struct
{
    char **arr;
    int len;
} closed_hash;

void free_static(static_arr *a);
void free_tree(tree_t *a);
void free_hash(opened_hash *a);
void free_closed_hash(closed_hash *a);

tree_t *create_tree(static_arr *a);
closed_hash create_closed_hash(static_arr *a);
tree_t *create_avl_tree(static_arr *a);
opened_hash create_hash(static_arr *a);

void delete_tree(tree_t *a, char s);
tree_t *delete_avl(tree_t *a, char s);
tree_t *delete_avl_tree_word(tree_t *a, char *s, int *count);
int delete_hash_word(opened_hash *a, char *s);
void delete_closed_hash(closed_hash *a, char *s);

#endif // STRUCTS_H
