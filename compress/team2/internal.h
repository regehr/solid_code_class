#ifndef HUFF_INTERNAL_H
#define HUFF_INTERNAL_H

/* Size typedefs because typing 'unsigned' all the time is a pain */
typedef unsigned long long uint64_t;
typedef unsigned char uint8_t;

/* Return-value constants for success and failure */
#define HUFF_FAILURE 255
#define HUFF_SUCCESS 0

/* return a pointer to 'size' bytes of memory. Fails the program with
 * HUFF_ERROR if the system is out of memory. */
void * xmalloc(size_t size); 

#endif
