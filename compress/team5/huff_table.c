/* Jake Guckert */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "huff_table.h"

// returns the frequencies
int check_tree_df(huff_tree *node)
{
    if (!node->zero_tree && ! node->one_tree)
    {
	assert(node->character < 257);
	assert(node->character >= 0);
	return node->frequency;
    }

    int left_freq = 0;
    int right_freq = 0;

    if (node->zero_tree)
    {
	left_freq  = check_tree_df(node->zero_tree);
    }
    if (node->one_tree)
    {
	right_freq = check_tree_df(node->one_tree);
    }
    
    assert(left_freq + right_freq == node->frequency);
    return node->frequency;
}


// returns the number of leaf nodes in a tree
int count_leaf_nodes(huff_tree *node)
{
    if (!node->zero_tree && !node->one_tree)
    {
	return 1;
    }

    int l_count = 0;
    int r_count = 0;

    if (node->zero_tree)
    {
	l_count  = count_leaf_nodes(node->zero_tree);
    }
    if (node->one_tree)
    {
	r_count = count_leaf_nodes(node->one_tree);
    }
    
    return l_count + r_count;
}


// Check rep for the tree, not the table
void check_rep_tree(huff_tree *tree)
{
    // if the table has been built, it should not be null
    assert(tree);

    // recursivly assert frequencies are consistent
    check_tree_df(tree);

    // check that the count of leaf nodes is bounded
    int num_leaf_nodes = count_leaf_nodes(tree);
    assert(num_leaf_nodes <= 265);

    // must be okay
    fprintf(stderr, "OK\n");
}



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
	sprintf(new_prefix, "%s%c", prefix, new_char);
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
	huff_tree *q[CHAR_RANGE];

	/* create a huff_tree_node for each character in the frequency table. */
	for(i = 0; i < CHAR_RANGE; i++) {
		if(frequencies[i]) {
			huff_tree *htree = (huff_tree *)calloc(1, sizeof(huff_tree));
			htree->character = i;
			htree->frequency = frequencies[i];
			q[length++] = htree;
			}
		}

	/* compare and combine huff_trees */
	while(length > 1) {
		huff_tree *htree = (huff_tree *)malloc(sizeof(huff_tree));
		qsort(q, length, sizeof(huff_tree *), compare_huff_trees);
		htree->zero_tree = q[--length];
		htree->one_tree = q[--length];
		htree->frequency = htree->zero_tree->frequency + htree->one_tree->frequency;
		q[length++] = htree;
	}
	/* The queue now has only one huff_tree struct which is the complete huff tree. */
	return q[0];
}

/* traverse the Huffman tree to build up a table of encodings */
void traverse_huff_tree(huff_tree *tree, char **table, char *prefix)
{
    if(!tree->zero_tree && !tree->one_tree) {
    	table[tree->character] = prefix;	
    } else {
        if(tree->zero_tree){
        	traverse_huff_tree(tree->zero_tree, table, concat_characters(prefix, '0'));	
        } 
        if(tree->one_tree){
        	traverse_huff_tree(tree->one_tree, table, concat_characters(prefix, '1'));	
        } 
        free(prefix);
    }
}

/* build a table of Huffman encodings given a set of frequencies */
char **build_huff_table(int frequencies[]) {
    static char *huff_table[CHAR_RANGE];
    char *prefix = (char *)calloc(1, sizeof(char));
    huff_tree *tree = build_huff_tree(frequencies);
    traverse_huff_tree(tree, huff_table, prefix);

    /* check rep for a full fledged tree */
    if (CHECK_REP)
    {
	check_rep_tree(tree);
    }
    
    free_huff_tree(tree);
    
    return huff_table;
}

/* This will construct a huff_table and print out each line. */
void print_huff_table(FILE *input) {	
	int i, character, frequencies[CHAR_RANGE] = { 0 };
	char **huff_table;

	/* calculate character frequencies. */
	while((character = fgetc(input)) != EOF) {
	    frequencies[character]++;
	}
	
	/* builds huff_table based on frequencies. */
	huff_table = build_huff_table(frequencies);
	 
	/*prints out each line of huff table.*/
	for(i = 0; i < CHAR_RANGE; i++) {
	    printf("%d - ", i);
	    if(huff_table[i] == NULL) {
                printf("\n");
	    } else {
		printf("%s\n", huff_table[i]);
	    }
	}
}
