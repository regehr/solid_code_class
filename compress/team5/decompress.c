/* Jake Guckert */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "huff_table.h"
#include "decompress.h"

#define MAGIC_NUM "HURL"

void is_huff_file (FILE *input) 
{
    char magic_num[5] = {0};
    int i;

	// Check bytes 0-3 are equal to HUFF.
	for (i = 0; i < sizeof(magic_num); i++) {
		magic_num[i] = fgetc(input);
	}
    magic_num[4] = '\0';

    if (strcmp(magic_num, MAGIC_NUM) != 0) {
        printf("not a hurl file\n");
        exit(255);
    }
}

/* Remove the extension from the file that we are decompressing. */
char *get_decompressed_file_name (char *filename) 
{
    int length = strlen(filename);
    int end = 0;
    
    // Start from the back and stop at the first '.'.
    int i = length - 1;
    for (; i > 0; i--) {
        if (filename[i] == '.') {
            filename[i] = '\0';
            end = i;
            break;
        }
    }

    int size = end + 7;
    char *name = malloc(size*sizeof(char));
    int limit = size - 6;
    
    for (i = 0; i < limit; i++) {
        name[i] = filename[i];  
    }
    return name;
}

huff_tree *build_huff_tree_from_table (FILE *input) 
{
    huff_tree *root = (huff_tree *)malloc(sizeof(huff_tree));
    *root = (huff_tree){ 0 };
    huff_tree *current = root;
    
    char **encodings = (char **)malloc(CHAR_RANGE * sizeof(char *));
    *encodings = (char *){ 0 };
    int i, j;

    // Fill the encodings array with entries from the table.
    fseek(input, 12, SEEK_SET);

    for (i = 0; i < CHAR_RANGE; i++) {
        encodings[i] = (char *)malloc(sizeof(char) * CHAR_RANGE);
        *encodings[i] = (char){0};
        if (fgets(encodings[i], CHAR_RANGE, input) == NULL) {
            encodings[i] = "\n";
        }

        // Manually set null character.
        for (j = 0; j < CHAR_RANGE; j++) {
            if (encodings[i][j] == '\n') {
                encodings[i][j] = '\0';
                break;
            }
        }
    }

    // Build tree from encoding array.
    for (i = 0; i < CHAR_RANGE; i++) {
        if (strcmp(encodings[i], "null") == 0) {
            continue;
        }

        for (j = 0; j < strlen(encodings[i]); j++) {
            build_children_if_null(&current);
            current->character = -1;

            if (encodings[i][j] == '0') {
                current = current->zero_tree;
            }

            if (encodings[i][j] == '1') {
                current = current->one_tree;
            }
        }

        // Set currents character, and go back to root.
        if (current != root) {
            current->character = i; 
            current = root;
        }
    }

    return root;
}

/* Builds an empty huff tree, returning the root node pointer. */
void build_children_if_null (huff_tree ** parent)
{
    if ((*parent)->zero_tree == NULL) {
        (*parent)->zero_tree = (huff_tree *)malloc(sizeof(huff_tree));
        (*(*parent)->zero_tree) = (huff_tree){ 0 };
    }

    if ((*parent)->one_tree == NULL) {
        (*parent)->one_tree = (huff_tree *)malloc(sizeof(huff_tree));
        (*(*parent)->one_tree) = (huff_tree){ 0 };
    }
}

/* Decompress the input file bit by bit and writes out to the output file, 
   expects input to point at first byte after encoding table. */
void write_out_decompress (FILE *input, FILE *output, huff_tree *root, 
    uint64_t length)
{
    huff_tree *current = root;
    int out_c;
    int i = 0, bit, bytes_written = 0;
    char *buffer = (char *)malloc(1);
    *buffer = (char){ 0 };
    while((fread(buffer, 1, 1, input)) == 1) {
        for (i = 0; i < 8; i++) {
            bit = (*buffer) >> i & 0x1;

            if (bit == 1) {
                current = current->one_tree;
            } else {
                current = current->zero_tree;
            }

            if (current->character != -1) {
                out_c = current->character;

                fputc(out_c, output);

                current = root;
                bytes_written++;
            }

            if (bytes_written == length) break;
        }
        if (bytes_written == length) break;
    }

    if (bytes_written < length) {
        printf("Bytes decompressed vs. length encoded do not match.\n");
        exit(255);
    }
}

uint64_t get_huff_size (FILE *input) 
{
    unsigned long long size = 0;

    fseek(input, 4, SEEK_SET);
    fread(&size, 8, 1, input);

    return size;
}

void decompress (FILE *input, FILE *output) 
{
    huff_tree *tree;
    uint64_t size;
    // Exits if this file is not considered valid
    is_huff_file(input);

    // Fetch the size
    size = get_huff_size(input);

    // Build a tree from the encodings
    tree = build_huff_tree_from_table(input);

    if(output == NULL)
        fprintf(stderr , "panic!");

    // Write out the decompressed bits!
    write_out_decompress(input, output, tree, size);

    fclose(output);
    free_huff_tree(tree);
}