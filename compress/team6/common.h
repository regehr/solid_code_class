/*
 * common.h
 *
 * Written by Keith Richards
 * February 2014
 *
 * functions for general use
 */

#ifndef RLE_H
#define RLE_H

/* bomb program on malloc failure */
void * xmalloc(size_t size);

/* read or write a file */
FILE * Fopen(const char *name, const char *mode);


#endif


