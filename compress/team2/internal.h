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

/* Common error codes */
#define EBADEXT      (-1)   // Non .huff file extension 
#define ENOMAGIC     (-2)   // No magic number in file
#define EBADENTRY    (-3)   // Bad entry in translation table
#define ETRUNC       (-4)   // A file we were reading  from ended before we
                            // finished reading from it. 
#define EENTRY       (-7)   // An entry in a file's translation table was too long
#define ENOWRITE     (-6)   // Could not write to the file.

#define EFILETOOLONG (-5)    // The file was too long to be stored in a uint64_t

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

/* Return the error string corresponding to the given code. */
const char * huff_error(int code);
#endif
