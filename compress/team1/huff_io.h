#ifndef Compress_huff_io_h
#define Compress_huff_io_h

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#define MAGIC_NUM "HUFF"
#define HUFF_EXT ".huff"
#define ERR_CODE 255

/**
 *	Returns true if the file has the huff extension.
 */
bool is_huff_file(const char*);

/**
 *	Returns true if the file contains a valid huff header
 */
bool is_huff_header(FILE*);

/**
 *	Writes the huff header to the file. Returns 0 if the write succeded.
 */
int write_huff_header(FILE*);

/**
 *	Gets the character frequencies from the file given and outputs them to the integer array. 
 * 	The array must be a length of 256. Returns 0 if the operation succeded.
 */
int get_frequencies(FILE*, uint64_t*);

/**
 *	Outputs the huffman tree from the file given to the character array given. The
 *	The array length must be 256. Returns 0 if the operation succeded.
 */
int get_huff_tree(FILE*, char**);

#endif
