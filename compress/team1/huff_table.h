/*
 * Header file for huff_table.c
 */

#ifndef HUFF_TABLE_H
#define HUFF_TABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#define ERR_CODE 255

/* Node for huffman tree coding. */
typedef struct node node;

/* A list of all nodes created. */
node *all_nodes[511];
int all_node_curr;

/* Type of depth first search. */
typedef enum { SORT, TABLE, DOT, CHECK}dfs_t;
dfs_t dfs_type;

/* Unique serial number for each node. */
unsigned serial;

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
 * Creates a count af each possible character.*/
void byte_freq(node **, uint64_t[256]);

/* Sets all nodes to unvisited. */
void clear_visited();

/* Sorts nodes in tree by frequency.
 * If frequencies are the same, then sorts
 * by lowest char value of left and right subtree. */
void sort_nodes(node **);

/* Builds huffman coding tree. The node ** will point
 * to the reference of the root node of the new tree. */
void build_tree(node **);

/* Stores the sorted codes for each character in the
 * char ** parameter. */
void create_compression_table(node **, char **);

/* Depth first search tree traversal from given root node.*/
void dfs(node *, void *);

/* Driver for sorting dfs. Searches each subtree for
 * lowest value character. Assumes root node of subtree 
 * has the lowest byte valued character. */
char find_lowest(node *);

/* Comparison routine for qsort. Ugly because of so many ifs
 * but it wouldn't work with fewer comparisons. */
int compare_nodes(const void*, const void*);

/* Checks built huffman tree. */
void check_tree(node **);

/* Generates a dot file from huffman tree. */
void tree_dot(node *);

/* Checks if leaf node. */
bool is_leaf(node *);

/* Malloc wrapper for node initialization. */
node * malloc_n(node *);

#endif