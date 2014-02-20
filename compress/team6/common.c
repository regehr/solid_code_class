/*
 * common.h
 *
 * Written by Keith Richards
 * February 2014
 *
 * functions for general use
 */

#include <stdio.h>
#include <stdlib.h>
#include "common.h"

void * xmalloc(size_t size)
{
    void * ptr = malloc(size);
    if (!ptr)
    {
	printf("Malloc failed, exiting\n");
	exit(-1);
    }
    return ptr;
}

FILE * Fopen(const char *name, const char *mode)
{
    FILE *file = fopen(name, mode);
    if (!file)
    {
	printf("fopen failed, exiting\n");
	exit(-1);
    }
    return file;
}

