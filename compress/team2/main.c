#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include "internal.h"
#include "parser.h"
#include "huff.h"

static void DEBUG_print_freqtable(uint64_t table[256]) {
    for (int i = 0; i < 256; i++) {
        printf("0x%2X: %lld\n", i, table[i]);
    }
}

/* build a frequency table from the given file. If for some strange reason
 * the file is larger than uint64_t (which I'm pretty sure is impossible),
 * it will return EFILETOOLONG. Otherwise, byte frequencies are filled into the 
 * supplied 'table', and the size of the file is written into 'length'. */
static int build_freqtable(FILE * input, uint64_t table[256], uint64_t *length) {
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

static int compress(FILE * file, char * filename) { 
    return HUFF_FAILURE; 
}

static int decompress(FILE * file, char * filename) { 
    return HUFF_FAILURE; 
}

static int table(FILE * file, char * filename) { 
    struct huff_header header;
    int code = huff_read_header(file, filename, &header);
    if (code != 0) {
        uint64_t size;
        uint64_t table[256];
        build_freqtable(file, table, &size);
        printf("Filesize: %lld\n", size);
        DEBUG_print_freqtable(table);
        return HUFF_FAILURE;
    }
    for (int i = 0; i < 256; i++) {
        printf("%s\n", header.table[i]);
    }
    huff_free_hdrtable(&header);
    return HUFF_SUCCESS; 
}

static void usage(FILE * to) {
    fputs("usage: huff [-t | -c | -d] FILE\n"
          "Arguments:\n"
          " -c      Compress the given file.\n"
          " -d      Decompress the given file.\n"
          " -t      Print FILE's compression table. If FILE is uncompressed\n"
          "         then a compression table is generated and printed.\n", to);
}

int main(int argc, char *argv[]) {
    int exit_code = HUFF_FAILURE;
    FILE * input = NULL;

    if (argc != 3) { usage(stderr); exit(HUFF_FAILURE); }

    /* attempt to open the input file for reading */
    input = fopen(argv[2], "r");
    if (input == NULL) {
        if (errno == ENOENT) {
            fprintf(stderr, "Couldn't open '%s' for reading.\n", argv[2]);
        } else {
            perror("Error opening file");
        }
        exit(HUFF_FAILURE);
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
