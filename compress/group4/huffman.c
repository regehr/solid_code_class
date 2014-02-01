/*
 * Huffman compressor/decompressor
 *
 * Jonathon McDonald, Lynn Gao, Taylor Stapleton
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    COMPRESS,
    DECOMPRESS,
    TABLE,
    UNHANDLED
} flags;


/*
 * Parses the arguments passed by the user, returning the operation to be used.
 */
flags parse_args (char *argv[], char **out) {
    char *operation;

    operation = argv[1];
    *out = argv[2];

    if (strcmp(operation, "-c") == 0)
        return COMPRESS;
    else if (strcmp(operation, "-d") == 0)
        return DECOMPRESS;
    else if (strcmp(operation, "-t") == 0)
        return TABLE;
    else
        return UNHANDLED;
}


/*
 * Fills the provided frequency table using the file name.
 */
void build_table (char *file_name, int table[]) {
    FILE * file;
    char character;

    file = fopen(file_name, "rb");
    if (NULL == file) {
        printf("Unable to open file.\n");
        exit(-1);
    }

    while ((character = fgetc(file)) != EOF) {
        // The character is used as an index into the table, and the value
        // represents the frequency of the character in the file
        table[(int)character]++;
    }
}


int main (int argc, char *argv[]) {
    char *file = "";
    int table[256], i;

    if (argc != 3) {
        printf("Incorrect amount of arguments supplied.\n");
        return -1;
    }

    for (i = 0; i < 256; i++) {
        table[i] = 0;
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

    return 0;
}