/* Jake Guckert */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "huff_table.h"
#include "decompress.h"

#define MAGIC_NUM "HUFF"

void is_huff_file (FILE *input) 
{
    char magic_num[5];
    int i;
	/* check bytes 0-3 are equal to HUFF */
	for (i = 0; i < sizeof(magic_num); i++) {
		magic_num[i] = fgetc(input);
	}
    magic_num[4] = '\0';

    if (strcmp(magic_num, MAGIC_NUM) != 0){
        printf("not a huff file\n");
        exit(255);
    }
}

/* remove the extension from the file that we are decompressing */
char *get_decompressed_file_name (char* filename) 
{
    int length = strlen(filename);
    int end = 0;
    
    /* start from the back and stop at the first '.' */
    int i = length - 1;
    for (; i > 0; i--) {
        if (filename[i] == '.') {
            end = i;
        }
    }
    
    int size = end + 6;
    char *name = malloc(size*sizeof(char));
    int limit = size - 6;
    
    for (i = 0; i < limit; i++) {
        name[i] = filename[i];  
    }
    
    strcat(name, ".txt");
    
    return name;
}

huff_tree *build_huff_tree_from_table (FILE *input) 
{
    huff_tree *root = malloc(sizeof(huff_tree));
    huff_tree *current = root;
    
    char **encodings = malloc(CHAR_RANGE);
    int i, j;

    /* fill the encodings array with entries from the table. */
    /* table starts at byte 12 */
    fseek(input, 12, SEEK_SET);
    printf("go to byte 12.\n");

    for (i = 0; i < CHAR_RANGE; i++) {
        encodings[i] = malloc(CHAR_RANGE);
        fgets(encodings[i], CHAR_RANGE, input);

        // Manually set null character
        for (j = 0; j < CHAR_RANGE; j++) {
            if (encodings[i][j] == '\n') {
                encodings[i][j] = '\0';
            }
        }
    }

    /* build tree from encoding array. loop through each row of encoding array. */
    for (i = 0; i < CHAR_RANGE; i++) {
        if (encodings[i] == NULL) {
            continue;
        }

        for (j = 0; j < strlen(encodings[i]); j++) {
            build_children_if_null(current);
            current->character = -1;

            if (encodings[i][j] == '0') {
                current = current->zero_tree;
            }

            if (encodings[i][j] == '1') {
                current = current->one_tree;
            }
        }

        // Set currents character, and go back to root
        current->character = i; 
        current = root;
    }

    return root;
}

/* Builds an empty huff tree, returning the root node pointer */
void build_children_if_null (huff_tree * parent)
{
    if (parent->zero_tree == NULL) {
        parent->zero_tree = malloc(sizeof(huff_tree));
    }

    if (parent->one_tree == NULL) {
        parent->one_tree = malloc(sizeof(huff_tree));
    }
}

/* Decompress the input file bit by bit and writes out to the output file, 
   expects input to point at first byte after encoding table */
void write_out_decompress (FILE *input, FILE *output, huff_tree *root, 
    unsigned long long length)
{
    /*
    root
    current
    while file has characters
        character = this;
        for each bit in character byte
            current is current zero tree if bit == 0
            current is one tree if bit == 0

            if current->char != null / 0
                write out character, increment file size, and reset current
    */
    unsigned char mask_table[] = { 
        0x01, 0x02, 0x03, 0x04, 
        0x05, 0x06, 0x07, 0x08 
    };
    huff_tree *current = root;
    char out_c;
    int i = 0, bit, bytes_written = 0, bytes_read = 0;
    char *buffer = malloc(1);

    while((fread(buffer, 1, 1, input)) == 1) {
        for (i = 0; i < 8; i++) {
            bit = (*buffer) >> i & 0x1;

            if (bit == 1) {
                current = current->one_tree;
            } else {
                current = current->zero_tree;
            }

            printf("%i", bit);

            if (current->character != -1) {

                out_c = (char)current->character;
                printf(" : %c\n", out_c);
                fwrite(&out_c, 1, 1, output);
                bytes_written++;

                current = root;
            }
        }

        bytes_read++;
    }

    printf("Bytes written: %i :: Bytes read: %i \n", bytes_written, bytes_read);
}

unsigned long long get_huff_size (FILE *input) {
    unsigned long long size = 0;

    fseek(input, 4, SEEK_SET);
    fread(&size, 8, 1, input);

    return size;
}

void decompress (FILE *input, char* filename) 
{
    huff_tree *tree;
    unsigned long long size;
    
    // Exits if this file is not considered valid
	is_huff_file(input);

    // Fetch the size
    size = get_huff_size(input);
    printf("%llu is the size.\n", size);

    // Build a tree from the encodings
    tree = build_huff_tree_from_table(input);

    // Name the file, and get a pointer
    char* new_name = get_decompressed_file_name(filename);
    FILE *output = fopen(new_name, "w");

    printf("Built new name \n");

    // Write out the decompressed bits!
    write_out_decompress(input, output, tree, size);

    free_huff_tree(tree);
}