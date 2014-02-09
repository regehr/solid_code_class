/*
 * Utilities for handling I/O.  This parses user input from stdin, reads files,
 * and writes to files safely.  
 *
 * Jonathon McDonald, Lynn Gao, Taylor Stapleton
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "huff_tree.h"
#include "huff_io.h"

/*
 * Parses the arguments passed by the user, returning the operation to be used.
 */
flags parse_args (char *argv[], char **out) 
{
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
int compare (const void *p1, const void *p2) 
{
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
void build_table (char *filename, struct frequency table[]) 
{
    FILE *file;
    int i;

    assert(filename != NULL && table != NULL);

    for (i = 0; i < 256; i++) {
        table[i].character = (char)i;
        table[i].count = 0;
        table[i].sequence = NULL;
    }

    file = fopen(filename, "rb");
    if (NULL == file) {
        printf("Unable to open file.\n");
        exit(-1);
    }

    if (is_huff(file, filename))
        build_from_huff(file, table);
    else 
        build_from_normal(file, table);
}


/*
 * Builds a frequency table from a normal file.
 */
void build_from_normal (void *file_ptr, struct frequency table[])
{
    char character;

    assert(file_ptr != NULL && table != NULL);
    FILE *file = (FILE *)file_ptr;

    while ((character = fgetc(file)) != EOF) {
        table[(int)character].count++;
    }
    qsort(table, 256, sizeof(struct frequency), compare);  
}


/*
 * Builds a frequency table from a huff file.
 */
void build_from_huff (void *file_ptr, struct frequency table[])
{
    char *sequence = new_string(256);
    int i = 0;

    assert(file_ptr != NULL && table != NULL);
    FILE *file = (FILE *)file_ptr;

    // Set the pointer on byte 12
    fseek(file, 12, SEEK_SET);
    while (fgets(sequence, 256, file) != NULL && i < 256) {
        strtok(sequence, "\n");
        table[i].character = (char)i;
        table[i].sequence = sequence;

        sequence = new_string(256);
        i++;
    }
}


/*
 * Prints out the compression table from the Huffman tree.
 */
void dump_table (char *filename, struct frequency table[])
{
    struct pq_node *queue = make_pq(table);
    struct tree_node node = build_tree(queue);
    print_tree(node);
}


/*
 * Determines if this file is a huff file with proper headers.
 */
int is_huff (void *file_ptr, char *filename)
{
    size_t result;
    char word[5];
    word[4] = '\0';

    assert(file_ptr != NULL);

    if (!huff_ext(filename))
        return 0;

    FILE *file = (FILE *)file_ptr;
    rewind(file);
    fseek(file, 0L, SEEK_END);

    // There must be at least 268 bytes in a proper huff file
    result = ftell(file);
    if (result < 268)
        return 0;

    rewind(file);
    result = fread(word, 1, 4, file);

    return (result == 4 && (strcmp(word, "HUFF") == 0));
}


/* 
 * Returns true if the file is a huff file, false otherwise 
 */
int huff_ext (char *filename) 
{
    char *ext = strrchr(filename, '.');
    char *c = ".huff";

    return ((ext != NULL) && (strcmp(ext, c) == 0));
}


char * new_string (int size)
{
    char *str;
    size++;
    str = (char *)malloc(sizeof(char) * size);

    return str;
}