/* Jake Guckert */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huff_table.h"

#define CHAR_RANGE 256 // I dont know

/* free the memory of a single huff_tree struct. */
void free_huff_tree(huff_tree *tree) {
	if(tree) {
		free_huff_tree(tree->zero_tree);
		free_huff_tree(tree->one_tree);
		free(tree);
	}
}

/* free the memory of a huff table. */
void free_huff_table(char *huff_table[]) {
	int i;	
	for(i=0; i < CHAR_RANGE; i++) {
		if(huff_table[i]) {
			free(huff_table[i]);
		}
	}
}

/* Used to add a new character to the existing characters in a huff_tree_node. */
char *concat_characters(char *prefix, char new_char){
	char *new_prefix = (char *)malloc(strlen(prefix) + 2);
	return new_prefix;
}

/* Compares 2 huff_nodes. */
int compare_huff_trees(const void *a, const void *b) {	
	const huff_tree **t1 = (const huff_tree **) a;
	const huff_tree **t2 = (const huff_tree **) b;

	if((*t1)->frequency == (*t2)->frequency){
		return 0;	
	} else {
		return ((*t1)->frequency < (*t2)->frequency) ? 1 : -1;
	}
    	
}

huff_tree *build_huff_tree(int frequencies[]) {
	int i, length = 0;
	huff_tree *q[256];

	/* create a huff_tree_node for each character in the frequency table. */
	for(i = 0; i <= 256; i++) {
		if(frequencies[i]) {
			huff_tree *new_huff_tree = (huff_tree *)calloc(1, sizeof(huff_tree));
			new_huff_tree->character = i;
			new_huff_tree->frequency = frequencies[i];
			q[length++] = new_huff_tree;
		}
	}

	/* compare and combine huff_trees */
	while(length > 1) {
		huff_tree *new_huff_tree = (huff_tree *)malloc(sizeof(huff_tree));
		qsort(q, length, sizeof(huff_tree *), compare_huff_trees);
		new_huff_tree->zero_tree = q[--length];
		new_huff_tree->one_tree = q[--length];
		new_huff_tree->frequency = new_huff_tree->zero_tree->frequency + new_huff_tree->one_tree->frequency;

		q[length++] = new_huff_tree;
	}
	/* The queue now has only one huff_tree struct which is the complete huff tree. */
	return q[0];
}

/* traverse the Huffman tree to build up a table of encodings */
void traverse_huff_tree(huff_tree *tree, char **table, char *prefix)
{
    if(!tree->zero_tree && !tree->one_tree) {
    	table[tree->character] = prefix;	
    } 
    else
    {
        if(tree->zero_tree) traverse_huff_tree(tree->zero_tree, table, concat_characters(prefix, '0'));
        if(tree->one_tree) traverse_huff_tree(tree->one_tree, table, concat_characters(prefix, '1'));
        free(prefix);
    }
}

/* build a table of Huffman encodings given a set of frequencies */
char **build_huff_table(int frequencies[]) {
    static char *huff_table[CHAR_RANGE];
    char *prefix = (char *)calloc(1, sizeof(char));
    huff_tree *tree = build_huff_tree(frequencies);
    traverse_huff_tree(tree, huff_table, prefix);
    free_huff_tree(tree);
    
    return huff_table;
}

/* This will construct a huff_table and print out each line. */
void print_huff_table(FILE *input) {
	int character = 0;
	int i;
	int frequencies[256] = { 0 };
	char **huff_table;

	/* calculate character frequencies. */
	while((character = fgetc(input)) != EOF) {
		frequencies[character]++;
	}

	/* builds huff_table based on frequencies. */
	huff_table = build_huff_table(frequencies);

	/* prints out each line of huff table. */
	for(i = 0; i < CHAR_RANGE; i++) {
	        printf("%s\n", huff_table[i]);
	}
}

