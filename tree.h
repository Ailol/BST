#ifndef TREE_H
#define TREE_H
#include "common.h"

struct tree;
typedef struct tree tree_t;
typedef struct node node_t;
typedef void (*strfunc_t)(char *buf, int buflen, void *key, void *item);

tree_t *tree_create(cmpfunc_t cmpfunc, strfunc_t strfunc_t);

node_t *_tree_insert(tree_t *tree, node_t *node, node_t *new);

int tree_insert(tree_t *tree, void *key, void *elem);

void *tree_search(tree_t *tree, void *key);

void tree_print(tree_t *tree);


#endif