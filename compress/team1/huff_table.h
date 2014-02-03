/*
 *
 */

#ifndef HUFF_TABLE_H
#define HUFF_TABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

typedef struct node node;

/* Driver function for this module. Takes an sorted array
 * of frequencies of type uint64_t and returns sorted huffman
 * coding. 
 * Functionality is not yet implemented. */
void gen_huff_table(uint64_t[256], char*[256]);

/* Initialize node. */
void init_node(node **, char);
/* Initialize all nodes. */
void init_nodes(node **);
/* Copys file stream data to int array.
 * Creates a count af each possible character.
 */
void byte_freq(node **, uint64_t[256]);
/* Sets all nodes to unvisited. */
void clear_visited();
void sort_nodes(node **);
void build_tree(node **);
void create_compression_table(node **);

node *all_nodes[511];
int all_node_curr;

/* Depth first search tree traversal from given root node.
 * Sets second parameter to the node with lowest valued
 * character in subtree. */
void dfs(node *, char *);

/* Helper function for recursive depth first search.
 * Assumes root node of subtree has the lowest byte
 * valued character.
 */
char find_lowest(node *);

/* Comparison routine for qsort. Ugly because of so many ifs
 * but it wouldn't work with fewer comparisons. */
int compare_nodes(const void*, const void*);

/* Sort length nodes in specified array.
 */
void sort_nodes(node **);

void build_tree(node **);

/* Depth first search tree traversal from given root node. */
void code_dfs(node *);

/* Builds a compression table from huffman tree. */
void create_compression_table(node **);

void tree_dot(node *);


#endif