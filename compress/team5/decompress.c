/* Jake Guckert */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "huff_table.h"

/* read in the header of a Huffman encoded file */
int *ReadHeader(FILE *in)
{
    static int frequencies[CHAR_RANGE];
    int i, count, letter, freq;
    
    if(fscanf(in, "%d", &count) != 1) Error("invalid input file.");
    
    for(i = 0; i < count; i++)
    {
        if((fscanf(in, "%d %d", &letter, &freq) != 2)
           || letter < 0 || letter >= CHAR_RANGE) Error("invalid input file.");
        
        frequencies[letter] = freq;
    }
    fgetc(in); /* discard last newline */
    
    return frequencies;
}

/* read a single bit from the input file */
int ReadBit(FILE *in)
{
    /* buffer holding raw bits and size of MSB filled */
    static int bits = 0, bitcount = 0;
    int nextbit;
    
    if(bitcount == 0)
    {
        bits = fgetc(in);
        bitcount = (1 << (CHAR_BITS - 1));
    }
    
    nextbit = bits / bitcount;
    bits %= bitcount;
    bitcount /= 2;
    
    return nextbit;
}

int decode_char(FILE *in, huff_tree *tree) {
    while(tree->zero_tree || tree->one_tree) {
        if(ReadBit(in)){
        	tree = tree->one_tree;	
        } else {
			tree = tree->zero_tree;
        } 
   
        if(!tree){
        	//Error("invalid input file.");	
        } 
    }
    return tree->character;
}

int is_huff_file(FILE *input) {
	char* magic_num = "HUFF";
	int i = 0;
	/* check the file extension is equal to .huff */
	/* check bytes 0-3 are equal to HUFF */
	for(i; i < sizeof(magic_num); i++) {
		if(input[i] != magic_num[i]) {
			return 0;
		}
	}
}

void decode(FILE *input, FILE *output) {
	int *frequencies, c;
	huff_tree *tree;
	
	/* check to make sure the input file is a .huff file. */
	if(is_huff_file(input)){
		frequencies = read_header(in);
		tree = build_huff_tree(frequencies);

		while((c = decode_char(input, tree)) != EOF) {
			fputc(c, output);
		}

		free_huff_tree(tree);
	} else {
		/* file is not valid format */
	}
	
}