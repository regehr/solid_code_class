#ifndef HUFF_INTERNAL_H
#define HUFF_INTERNAL_H

#include <stdio.h>

#define UNUSED(x) __attribute__((unused)) x

/* Size typedefs because typing 'unsigned' all the time is a pain */
typedef unsigned long long uint64_t;
typedef unsigned char uint8_t;

/* Return-value constants for success and failure */
#define HUFF_FAILURE 255
#define HUFF_SUCCESS 0

/* return a pointer to 'size' bytes of memory. Fails the program with
 * HUFF_FAILURE if the system is out of memory. */
void * xmalloc(size_t size); 
void * xrealloc(void *ptr, size_t size);

/* fopen the given file, print an error message and terminate with
 * HUFF_FAILURE if we're unable to open the file. */
FILE* xfopen(const char * path, const char * mode);

/* fclose the given file and print an error message if file closing fails.
 * DOES NOT EXIT on failure. */
int pfclose(FILE * file);

#endif
