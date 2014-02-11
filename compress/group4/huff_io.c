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
    struct pq_node * queue;
	struct tree_node node;
	char code[255];
    code[0] = '\0';
	// if the file is a huff file
	if(is_huff == 0) {
		// recover table from file
		build_from_huff(filename, table);
		queue = make_pq(table);
    	node = build_tree(queue);
		print_huff(&node, code);
	}
	else {
		// compute compression table
		queue = make_pq(table);
    	node = build_tree(queue);
    	print_huff(&node, code);
	}    
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


/*
 * Instantiates a new string.
 */
char * new_string (int size)
{
    char *str;
    size++;
    str = (char *)malloc(sizeof(char) * size);

    return str;
}


/*
 * Decompress a file
 */
void decompress (char *filename, struct frequency table[])
{
    FILE *file;
    char character;

    assert(filename != NULL && table != NULL);

    file = fopen(filename, "rb");
    if (NULL == file) {
        printf("Unable to open file.\n");
        exit(-1);
    }

    char string[256];
    int i = 0;
    int str_c = 0;
    while ((character = fgetc(file)) != EOF) {
        for (; i < 8; i++) {
            int bit = get_bit(character, i);
            string[str_c] = bit;
            str_c++;

            if (bit == 1) {
                string[str_c] = '\0';

                // Reset the string counter
                str_c = 0;
                printf("%s\n", string);
            }
        }
        i = 0;
    }
}


/*
 * Returns a bit at the given position in the byte.
 */
char get_bit (unsigned char c, int num)
{
    assert(num >= 0 && num <= 7);

    unsigned char mask_table[] = { 
        0x01, 
        0x02, 
        0x04, 
        0x08, 
        0x10, 
        0x20, 
        0x40, 
        0x80 
    };

    return ((c) & mask_table[num]);
}