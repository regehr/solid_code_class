/* Jake Guckert */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "huff_table.h"

// returns the frequencies
int check_tree_df (huff_tree *node)
{
    int left_freq = 0, right_freq = 0;
    if (!node->zero_tree && ! node->one_tree) {
    	assert(node->character < 257);
    	assert(node->character >= 0);
    	return node->frequency;
    }

    if (node->zero_tree) left_freq  = check_tree_df(node->zero_tree);

    if (node->one_tree) right_freq = check_tree_df(node->one_tree);
    
    assert(left_freq + right_freq == node->frequency);
    return node->frequency;
}


// returns the number of leaf nodes in a tree
int count_leaf_nodes (huff_tree *node)
{
    int l_count = 0, r_count = 0;
    if (!node->zero_tree && !node->one_tree) return 1;

    if (node->zero_tree) l_count  = count_leaf_nodes(node->zero_tree);

    if (node->one_tree) r_count = count_leaf_nodes(node->one_tree);

    return l_count + r_count;
}


// Check rep for the tree, not the table
void check_rep_tree (huff_tree *tree)
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
void free_huff_tree (huff_tree *tree)
{
	if(tree) {
		free_huff_tree(tree->zero_tree);
		free_huff_tree(tree->one_tree);
		free(tree);
	}
}

/* free the memory of a huff table. */
void free_huff_table (char *huff_table[])
{
	int i;	
	for(i=0; i < CHAR_RANGE; i++) {
		if(huff_table[i]) {
			free(huff_table[i]);
		}
	}
}

/* Used to add a new character to the existing characters in a huff_tree_node. */
char *concat_characters (char *prefix, char new_char)
{
    assert(prefix != NULL);

    char *new_prefix = (char *)malloc(strlen(prefix) + 2);
    if (sprintf(new_prefix, "%s%c", prefix, new_char) < 0) {
        printf("Failed to sprintf the new prefix.\n");
        exit(255);
    }
    return new_prefix;
}

/* Compares 2 huff_nodes. */
int compare_huff_trees (const void *a, const void *b)
{	
	const huff_tree **t1 = (const huff_tree **) a;
	const huff_tree **t2 = (const huff_tree **) b;

    if (NULL == *t1) return 1;
    if (NULL == *t2) return -1;

	if((*t1)->frequency == (*t2)->frequency) {
        if ((*t1)->lowest == (*t2)->lowest) return 0;	

        return ((*t1)->lowest < (*t2)->lowest) ? 1 : -1;
	} else {
		return ((*t1)->frequency < (*t2)->frequency) ? 1 : -1;
	}
}

huff_tree *build_huff_tree (int frequencies[])
{
	int i, length = 0;
	huff_tree *q[CHAR_RANGE] = {0};

	// Create a huff_tree_node for each character in the frequency table
	for(i = 0; i < CHAR_RANGE; i++) {
        huff_tree *htree = (huff_tree *)calloc(1, sizeof(huff_tree));
        htree->character = i;
        htree->lowest = i;
		if(frequencies[i]) {
			htree->frequency = frequencies[i];
		} else {
            htree->frequency = 0;
        }
        q[length++] = htree;
	}

	// Compare and combine huff_trees
	while(length > 1) {
        char zt_l, ot_l; // Zero tree lowest, one tree lowest

        // Malloc
		huff_tree *htree = (huff_tree *)malloc(sizeof(huff_tree));

        // Sort the current table of nodes
		qsort(q, length, sizeof(huff_tree *), compare_huff_trees);

        // Set the character to -1
        htree->character = -1;

        // Set the zero tree and one tree
		htree->zero_tree = q[--length];
		htree->one_tree = q[--length];

        // Set the lowest
        zt_l = htree->zero_tree->lowest;
        ot_l = htree->one_tree->lowest;
        htree->lowest = (zt_l < ot_l) ? zt_l : ot_l;

        // Compute the frequency
		htree->frequency = htree->zero_tree->frequency + htree->one_tree->frequency;

        // Enqueue this htree
		q[length++] = htree;
	}

    if (q[0] == NULL) {
        q[0] = (huff_tree *)malloc(sizeof(huff_tree));
        *q[0] = (huff_tree){ 0 };
    }

	/* The queue now has only one huff_tree struct which is the complete huff tree. */
	return q[0];
}

/* Traverse the Huffman tree to build up a table of encodings. */
void traverse_huff_tree (huff_tree *tree, char **table, char *prefix)
{
    if(!tree->zero_tree && !tree->one_tree) {
    	table[tree->character] = prefix;	
    } else {
        if(tree->zero_tree) {
        	traverse_huff_tree(tree->zero_tree, table, concat_characters(prefix, '0'));	
        } 
        if(tree->one_tree) {
        	traverse_huff_tree(tree->one_tree, table, concat_characters(prefix, '1'));	
        } 
        free(prefix);
    }
}

/* Build a table of Huffman encodings given a set of frequencies. */
char **build_huff_table (int frequencies[]) 
{
    static char *huff_table[CHAR_RANGE];
    char *prefix = (char *)calloc(1, sizeof(char *));
    *prefix = '\0';
    huff_tree *tree = build_huff_tree(frequencies);
    traverse_huff_tree(tree, huff_table, prefix);

    // Check rep for a full fledged tree.
    if (CHECK_REP) check_rep_tree(tree);
    
    free_huff_tree(tree);
    return huff_table;
}

/* This will construct a huff_table and print out each line. */
void print_huff_table (FILE *input) 
{	
	int i, character, frequencies[CHAR_RANGE] = { 0 };
	char **huff_table;

	// Calculate character frequencies.
	while((character = fgetc(input)) != EOF) {
	    frequencies[character]++;
	}
	
	// Builds huff_table based on frequencies.
	huff_table = build_huff_table(frequencies);

	// Prints out each line of huff table.
	for(i = 0; i < CHAR_RANGE; i++) {
	    if(huff_table[i] == NULL)
            printf("\n");
	    else
            printf("%s\n", huff_table[i]);
	}
}