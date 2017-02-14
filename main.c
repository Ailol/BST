#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "plot.h"

int mycmpfunc(int a, int b)
{
	return b-a;
}

void mystrfunc(char *buf, int buflen, int key, int *elem)
{
	snprintf(buf, buflen, "%d", key);
}



int main(){

	int i;
	long test[1024];

	tree_t *tree = tree_create((cmpfunc_t)mycmpfunc, (strfunc_t)mystrfunc);
	if(tree == NULL){
		printf("MEM ERR INN TREE CREATION\n");
		exit(1);
	}

	srand(234525);

	for(i = 0; i < 1024; i++)
		test[i] = rand() % 512;

	for (i = 0; i < 64; i++){
		printf("%ld ", test[i]);
		tree_insert(tree, (void*)test[i], &test[i]);
	}

	tree_plot(tree, "TheTree");
	
	printf("Searching for key %ld: %s\n", 
			test[2], tree_search(tree, (void*) test[2]) != NULL ? "FOUND" : "NOT FOUND");
	printf("Searching for key %ld: %s\n", 
           test[20], tree_search(tree, (void*)test[20]) != NULL ? "FOUND" : "NOT FOUND");
    printf("Searching for key %d: %s\n", 
           23, tree_search(tree, (void*)23) != NULL ? "FOUND" : "NOT FOUND");

 	return 0;
}