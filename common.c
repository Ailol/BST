/* Author: Steffen Viken Valvaag <steffenv@cs.uit.no> */
#include "common.h"
//#include "list.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void fatal_error(char *msg)
{
    fprintf(stderr, "fatal error: %s\n", msg);
    exit(1);
}


int compare_strings(void *a, void *b)
{
    return strcmp(a, b);
}
