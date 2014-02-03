#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include "huff.h"

void DEBUG_print_freqtable(uint64_t table[256]) {
    for (int i = 0; i < 256; i++) {
        printf("0x%2X: %lld\n", i, table[i]);
    }
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

/* build a frequency table from the given file. If for some strange reason
 * the file is larger than uint64_t (which I'm pretty sure is impossible),
 * it will return EFILETOOLONG. Otherwise, byte frequencies are filled into the 
 * supplied 'table', and the size of the file is written into 'length'. */
int build_freqtable(FILE * input, uint64_t table[256], uint64_t *length) {
    uint8_t current = 0;
    uint64_t bytes_read = 0;
    memset(table, 0, 256 * sizeof(uint64_t));

    for (; fread(&current, 1, 1, input); table[current] += 1) {
        bytes_read += 1;
        /* if the byte counter overflows, then the file is too long */
        if (bytes_read == 0) { return EFILETOOLONG; }
    }

    *length = bytes_read;
    return 0;
}

int compress(FILE * file, char * filename) { 
    return ERROR_EXIT; 
}

int decompress(FILE * file, char * filename) { 
    return ERROR_EXIT; 
}

int table(FILE * file, char * filename) { 
    if (! is_huff(file, filename)) {
        uint64_t size;
        uint64_t table[256];
        build_freqtable(file, table, &size);
        printf("Filesize: %lld\n", size);
        DEBUG_print_freqtable(table);
    }
    return ERROR_EXIT; 
}

void usage(FILE * to) {
    fputs("usage: huff [-t | -c | -d] FILE\n"
          "Arguments:\n"
          " -c      Compress the given file.\n"
          " -d      Decompress the given file.\n"
          " -t      Print FILE's compression table. If FILE is uncompressed\n"
          "         then a compression table is generated and printed.\n", to);
}

int main(int argc, char *argv[]) {
    int exit_code = ERROR_EXIT;
    FILE * input = NULL;

    if (argc != 3) { usage(stderr); exit(ERROR_EXIT); }

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
        fprintf(stderr, "Invalid mode of operation: '%s'.\n", argv[1]);
        usage(stderr); 
    }

    fclose(input);
    return exit_code;
}
