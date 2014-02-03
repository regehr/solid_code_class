#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include "huff.h"

const int ERROR_EXIT = 255;
const int SUCCESS_EXIT = 0;

const char HUFF_MAGIC[] = "HUFF";
const char HUFF_EXT[] = ".huff";

const int HUFF_MAGICLEN = sizeof(HUFF_MAGIC) - 1;
const int HUFF_EXTLEN = sizeof(HUFF_EXT) - 1;

void usage(FILE * to) {
    fputs("usage: huff [-t | -c | -d] FILE\n"
          "Arguments:\n"
          " -c      Compress the given file.\n"
          " -d      Decompress the given file.\n"
          " -t      Print FILE's compression table. If FILE is uncompressed\n"
          "         then a compression table is generated and printed.\n", to);
}

/* Returns 'true' when the given file has all the markings of a huff file,
 * returns 'false' when the given file lacks a marker. */
bool is_huff(FILE * file, char * filename) {
    /* make sure the name is at least as long as HUFF_EXT */
    size_t name_length = strlen(filename);
    if (name_length < HUFF_EXTLEN) { return false; }

    /* make sure the filename ends with HUFF_EXT */
    char * ext_start = &filename[name_length - HUFF_EXTLEN];
    if (! (strcmp(ext_start, HUFF_EXT) == 0)) { return false; }

    /* prepare a buffer for reading. */
    char magic[HUFF_MAGICLEN];
    memset(magic, 0, HUFF_MAGICLEN);

    /* check if the given file has the HUFF magic number */
    int items = fread(magic, HUFF_MAGICLEN, 1, file);
    if (items < 1 || ! (strncmp(magic, HUFF_MAGIC, HUFF_MAGICLEN) == 0)) {
        return false;
    }

    return true;
}

int compress(FILE * file, char * filename) { 
    return ERROR_EXIT; 
}

int decompress(FILE * file, char * filename) { 
    return ERROR_EXIT; 
}

int table(FILE * file, char * filename) { 
    return ERROR_EXIT; 
}

int main(int argc, char *argv[]) {
    int exit_code = ERROR_EXIT;
    FILE * input = NULL;

    if (argc < 3) { usage(stderr); exit(ERROR_EXIT); }

    /* attempt to open the input file for reading */
    input = fopen(argv[2], "r");
    if (input == NULL) {
        if (errno == ENOENT) {
            fprintf(stderr, "Couldn't open '%s' for reading.\n", argv[2]);
        } else {
            perror("Error opening file");
        }
        exit(ERROR_EXIT);
    }

    /* run the appropriate subroutine for the given option */
    if (strcmp(argv[1], "-c") == 0) {
        exit_code = compress(input, argv[2]);
    } else if (strcmp(argv[1], "-d") == 0) {
        exit_code = decompress(input, argv[2]);
    } else if (strcmp(argv[1], "-t") == 0) {
        exit_code = table(input, argv[2]);
    } else {
        usage(stderr); 
    }

    return exit_code;
}
