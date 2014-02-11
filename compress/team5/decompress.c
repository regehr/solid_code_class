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
        exit(0);
    }
}

void build_huff_tree_from_table(){

}

void decompress(FILE *input) {
	FILE *output;
    
    /* check to make sure the input file is a .huff file. */
	is_huff_file(input);
    
    /* build a huff tree from the huff table (bytes 12-) in the file.*/

        /*frequencies = read_header(in);
        tree = build_huff_tree(frequencies);

        while((c = decode_char(input, tree)) != EOF) {
            fputc(c, output);
        }

        free_huff_tree(tree);*/
	
}