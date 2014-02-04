/*
 * Utilities for handling I/O.  This parses user input from stdin, reads files,
 * and writes to files safely.  
 *
 * Jonathon McDonald, Lynn Gao, Taylor Stapleton
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huff_io.h"

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
 * Compares two frequency table rows' respective character counts.
 */
int compare (const void *p1, const void *p2) {
    const struct frequency *row1 = p1;
    const struct frequency *row2 = p2;

    if (row1->count != row2->count) 
        return ((int)row2->count - (int)row1->count);
    else
        return ((int)row2->character - (int)row1->character);
}


/*
 * Fills the provided frequency table using the file name, sorted highest 
 * frequency to lowest.
 */
void build_table (char *file_name, struct frequency table[]) {
    FILE *file;
    char character;

    file = fopen(file_name, "rb");
    if (NULL == file) {
        printf("Unable to open file.\n");
        exit(-1);
    }

    while ((character = fgetc(file)) != EOF) {
        table[(int)character].count++;
    }

    qsort(table, 256, sizeof(struct frequency), compare);
}