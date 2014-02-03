#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "huff.h"

static const int ERROR_EXIT = 255;
static const int SUCCESS_EXIT = 0;

void usage(FILE * to) {
    fputs("usage: huff [-t | -c | -d] FILE\n"
          "Arguments:\n"
          " -c      Compress the given file.\n"
          " -d      Decompress the given file.\n"
          " -t      Print FILE's compression table. If FILE is uncompressed\n"
          "         then a compression table is generated and printed.\n", to);
}

int compress(FILE * file, char * filename) { return ERROR_EXIT; }
int decompress(FILE * file, char * filename) { return ERROR_EXIT; }
int table(FILE * file) { return ERROR_EXIT; }

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
        exit_code = table(input);
    } else {
        usage(stderr); 
    }

    return exit_code;
}
