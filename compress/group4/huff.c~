/*
 * Huffman compressor/decompressor
 *
 * Jonathon McDonald, Lynn Gao, Taylor Stapleton
 */
#include "huff_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {
    char *file = "";
    struct frequency table[256];
    int i;

    if (argc != 3) {
        printf("Incorrect amount of arguments supplied.\n");
        return -1;
    }

    for (i = 0; i < 256; i++) {
        table[i].character = (char)i;
        table[i].count = 0;
    }

    switch (parse_args(argv, &file)) {
        case COMPRESS:
        break;
        case DECOMPRESS:
        break;
        case TABLE:
            build_table(file, table); 
        break;
        case UNHANDLED:
        break;
    }

    for (i = 0; i < 256; i++) {
        printf("%c: %d\n", table[i].character, table[i].count);
    }

    return 0;
}