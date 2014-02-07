#ifndef Compress_huff_io_h
#define Compress_huff_io_h

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <sys/stat.h>
#define MAGIC_NUM "HUFF"
#define HUFF_EXT ".huff"
#define ERR_CODE 255

/**
 *	Returns true if the file has the huff extension.
 */
bool is_huff_file(const char*);

/**
 *	Returns true if the file contains a valid huff header. The string array must be of length 256.
 */
bool get_huff_header(FILE* file, unsigned long long* size, char** huff_table);

/**
 *	Writes the huff header to the file. The character array must be of length 256.
 */
void write_huff_header(FILE*, unsigned long long, char**);

/**
 *	Outputs the huffman tree from the file given to the character array given. The
 *	The array length must be 256.
 */
void get_huff_tree(FILE*, char**);

/**
 *	Returns the size of the file in bytes.
 */
unsigned long long get_file_size(const char*);

/**
 *	Writes out the body of compressed.
 */
void write_huff_body(FILE*, FILE*, unsigned long long, char**);

#endif
