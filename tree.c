#include "tree.h"
#include "plot.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct node node_t;
struct node{
	void   *elem;
	void   *key;
	node_t *left, *right;
};

struct tree{
	node_t	 *root;
	cmpfunc_t cmpfunc;
	strfunc_t strfunc;
};


static node_t *new_node(void *key, void *elem){

	node_t *node = malloc(sizeof(node_t));
	if(node == NULL)
		exit(1);

	node->elem	= elem;
	node->key   = key;
	node->left  = NULL;
	node->right = NULL;

	return node;
}

tree_t *tree_create(cmpfunc_t cmpfunc, strfunc_t strfunc){

	tree_t *tree = malloc(sizeof(tree_t));
	if(tree == NULL)
		exit(1);

	tree->root = NULL;
	tree->cmpfunc = cmpfunc;
	tree->strfunc = strfunc;
	return tree;
}

/*
*@Search
*	traverses tree
**/

void *_tree_search(tree_t *tree, node_t *node, void *key){
	int cmp;

	if(node == NULL)
		return NULL;

	cmp = tree->cmpfunc(node->key, key);
	if(cmp == 0)
		return node->elem;
	if(cmp < 0)
		return _tree_search(tree, node->left, key);
	else
		return _tree_search(tree, node->right, key);
}

void *tree_search(tree_t *tree, void *key){
	return _tree_search(tree, tree->root, key);
}

/**
 * @ INSERT
 * Inserts in binary tree with recursive insertion 
 * 
 */

node_t *_tree_insert(tree_t *tree, node_t *node, node_t *new){

	if(node == NULL){
		return new;
	}
	
	if(tree->cmpfunc(node->key, new->key) < 0)
		node->left = _tree_insert(tree, node->left, new);
	else if(tree->cmpfunc(node->key, new->key) > 0)
		node->right = _tree_insert(tree, node->right, new);

	return node;
}

int tree_insert(tree_t *tree, void *key, void *elem){

	node_t *node;

	if(tree_search(tree, key) != NULL)
		return -1;

	node = new_node(key, elem);
	if(node == NULL)
		return -1;
	tree->root = _tree_insert(tree, tree->root, node);

	return 0;
}


/**
 * @brief PLOT
 *  Plots the layout of the tree
 * in a pdf file.
 */

static void _tree_plot(tree_t *tree, plot_t *plot, node_t *node){

	char from[128];
	char to[128];

	if(node == NULL)
		return;

	tree->strfunc(from, 128, node->key, node->elem);

	if(node->left != NULL){
		tree->strfunc(to, 128, node->left->key, node->left->elem);
		plot_addlink(plot, from, to);
	}
	if(node->right != NULL){
		tree->strfunc(to, 128, node->right->key, node->right->elem);
		plot_addlink(plot,from,to);
	}
	_tree_plot(tree, plot, node->left);
	_tree_plot(tree, plot, node->right);
}

void tree_plot(tree_t *tree, char *name){

	plot_t *plot;
	plot = plot_create(name);

	_tree_plot(tree, plot, tree->root);

	plot_doplot(plot);
}



/*
* 	UNUSED
**/
node_t *_tree_print(tree_t *tree, node_t *node){

	node->left = _tree_print(tree, node->left);
	printf("%d\n", *(int*)node->elem);
	node->right = _tree_print(tree, node->right);
	
}

void tree_print(tree_t *tree){

	_tree_print(tree, tree->root);
}