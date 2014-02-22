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
    char *encoding_string = malloc(CHAR_RANGE); // Not quite sure what the max size could be...we'll cheat for now.
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

    for (i = 0; i < CHAR_RANGE; i++) {
        printf("%i: %s\n", i, encodings[i]);
    }

    printf("encodings in array.\n");

    /* build tree from encoding array. loop through each row of encoding array. */
    for (i = 0; i < CHAR_RANGE; i++) {
        if (encodings[i] == NULL) {
            continue;
        }

        for (j = 0; j < strlen(encodings[i]); j++) {
            build_children_if_null(current);

            if (encodings[i][j] == '0' && root->zero_tree != NULL) {
                current = root->zero_tree;
            }

            if (encodings[i][j] == '1' && root->one_tree != NULL) {
                current = root->one_tree;
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

void decompress (FILE *input, char* filename) 
{
    huff_tree *tree;
    int i;
    
    /* check to make sure the input file is a .huff file. */
	is_huff_file(input);
    printf("This is a huff file, continuing...\n");
    
    /* build a huff tree from the huff table encodings.*/
    tree = build_huff_tree_from_table(input);
    printf("huff tree built successfully, continuing...\n");

    
    /* get rid of the old file extension */
    char* newName = get_decompressed_file_name(filename);
    printf("decompressed file named, continuing...\n");
    
    /* create a new file to write to */
    FILE *output = fopen(newName, "w");

    /* write each character to a file. */
    // input should be at correct line
    for (i = 0; i < sizeof(tree); i++) {
        fputc(tree[i].character, output);
    }
    printf("file decompressed successfully!\n");

    free_huff_tree(tree);
}