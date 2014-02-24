#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "huff_table.h"
#include "compress.h"
#include "decompress.h"

/* Easy interface to encode a huffman file. Output will be set to the created 
   file. */
char *huff_encode (char *filename, FILE *input, FILE *output)
{
    uint64_t size;

    fseek(input, 0L, SEEK_END);
    size = ftell(input);
    fseek(input, 0L, SEEK_SET);

    compress(input, filename, size);

    char *name = get_new_name(filename);
   // output = fopen(filename, "r");

    return name;
}

/* Easy interface to decode a huffman file. Output will be set to the created 
   file. */
char *huff_decode (char *filename, FILE *input, FILE *output)
{
    uint64_t size;

    fseek(input, 0L, SEEK_END);
    size = ftell(input);
    fseek(input, 0L, SEEK_SET);

    decompress(input, filename);

    char *name = get_decompressed_file_name(filename);
    output = fopen(filename, "r");

    return name;
}
