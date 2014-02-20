#ifndef RLE_encode_decode
#define RLE_encode_decode

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <sys/stat.h>
#define ERR_CODE 255
#define SIZE 100000

/**
 *    Performs Run Length Ecoding (RLE) on an input FILE.
 *
 *    Takes a File pointer, char array, and unsigned long long. The char array
 *    will hold the RLE bytes that are generated, and the unsigned long long
 *    will be the number of bytes in the array.
 */
void encode_rle(FILE*, char*, unsigned long long);

/**
 *    Decodes a RLE into a supplied FILE.
 *
 *    Takes a char array, an unsigned long long, and a FILE pointer. The char
 *    array holds the encoded bytes to be decoded, the unsigned long long is
 *    the number of bytes in the array, and the FILE pointer is the file to
 *    write the decoded bytes to.
 */
void decode_rle(char*, unsigned long long, FILE*);

#endif
