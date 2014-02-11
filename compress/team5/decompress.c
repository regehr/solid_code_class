/* Jake Guckert */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "huff_table.h"

#define MAGIC_NUM "HUFF"

void is_huff_file(FILE *input) {
    char magic_num[5];
    int i;
	/* check bytes 0-3 are equal to HUFF */
	for(i = 0; i < sizeof(magic_num); i++) {
		magic_num[i] = fgetc(input);
	}
    magic_num[4] = '\0';

    if(strcmp(magic_num, MAGIC_NUM) != 0){
        printf("not a huff file\n");
        exit(255);
    }
}

/* remove the extension from the file that we are decompressing */
char *get_decompressed_file_name(char* filename) {

    int length = strlen(filename);
    int end = 0;
    
    /* start from the back and stop at the first '.' */
    int i = length - 1;
    for(; i > 0; i--) {
        if(filename[i] == '.') {
            end = i;
        }
    }
    
    int size = end + 6;
    char *name = malloc(size*sizeof(char));
    int limit = size - 6;
    
    for(i = 0; i < limit; i++) {
        name[i] = filename[i];  
    }
    
    strcat(name, ".txt");
    
    return name;
}

huff_tree* build_huff_tree_from_table(FILE *input){
    huff_tree *new_tree = NULL;
    char *encodings[CHAR_RANGE] = { 0 };
    int i;

    /* fill the encodings array with entrys from the table. */
    /* table starts at byte 12 */
    fseek(input, 12, SEEK_SET);

    for(i = 0; i < sizeof(encodings); i++) {
        fgets(encodings[i], CHAR_RANGE, input);    
    }
    return new_tree;
}

void decompress(FILE *input, char* filename) {
    huff_tree *tree;
    
    
    /* check to make sure the input file is a .huff file. */
	is_huff_file(input);
    
    /* build a huff tree from the huff table encodings.*/
    tree = build_huff_tree_from_table(input);
    
    /* get rid of the old file extension */
    char* newName = get_decompressed_file_name(filename);
    
    /* create a new file to write to */
    FILE *output = fopen(newName, "w");

    /*if(fwrite() {
        printf("Write failure \n");
        exit(255);
    }*/
    
    free_huff_tree(tree);
}