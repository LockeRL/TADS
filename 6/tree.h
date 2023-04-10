#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct tree tree;

struct tree
{
    char *word;
    int height;
    tree *left;
    tree *right;
    tree *parent;
};


tree *push_tree(tree *a, FILE *f, int cur_height, int max_height, tree *parent);
void read_word(char *a, FILE *f);
int tree_height(FILE *f);
void export_to_dot(tree *a, char *name);
void free_tree(tree *a);
tree *delete_words(tree *a, char s);

#endif // TREE_H