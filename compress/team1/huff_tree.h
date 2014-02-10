/*
 * Header file for huff_table.c
 *
 * This implementaion is a memory hog and is using at least
 * 155.3 kB for encoding and decoding.
 */

#ifndef HUFF_TREE_H
#define HUFF_TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "huff_io.h"

/* Public accessing functions for this module. */

/* Builds a huffman tree from huffman table. */
void build_tree_tbl(char *table[256]);

/* Builds a huffman tree from character frequencies. */
void gen_tree_frq(uint64_t freq[256]);

/* Takes a huffman code * and returns the matching character. */
bool get_char(char *, char *);

/* Takes a character and returns the matching huffman code *. */
char * get_code(char);

/* Frees heap memory allocated for huffman tree nodes. */
void free_huff_tree();

/* Internal declarations. */

/* Node for huffman tree coding. */
typedef struct node
{
    char code[257]; /* This node's huffman code. Null terminated string. */
    struct node *left; /* The left child of this node. Null if leaf node. */
    struct node *right; /* The right child of this node. Null if leaf node. */
    uint64_t freq; /* The frequency of this node. Combined value if non-leaf node. */    
    unsigned id; /* Unique id for this node. */
    bool visited; /* Used for searching algorithms. */
    uint8_t c; /* The character this node represents. Null if non-leaf node. */
    uint8_t lowest; /* The lowest value character of this subtree. */
}node;

/* Character nodes. */
node *nodes[256];

/* Huffman table. */
char *table[256];

/* A list of all nodes created. */
node *all_nodes[511];
int all_node_curr;

/* Type of depth first search. */
typedef enum { SORT, TABLE, DOT, CHECK }dfs_t;
dfs_t dfs_type;

/* Unique serial number for each node. */
unsigned serial;

/* Initialize node. */
void init_node(node **, char);

/* Initialize all nodes. */
void init_nodes();

/* Copys file stream data to int array.
 * Creates a count af each possible character.*/
void byte_freq(uint64_t[256]);

/* Sets all nodes to unvisited. */
void clear_visited();

/* Sorts nodes in tree by frequency.
 * If frequencies are the same, then sorts
 * by lowest char value of left and right subtree. */
void sort_nodes();

/* Builds huffman coding tree. The node ** will point
 * to the reference of the root node of the new tree. */
void build_tree();

/* Stores the sorted codes for each character in the
 * char ** parameter. */
void create_table();

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
void check_tree();

/* */
void check_build(node *, node *);

/* Generates a dot file from huffman tree. */
void tree_dot();

/* Checks if leaf node. */
bool is_leaf(node *);

/* Malloc wrapper for node initialization. */
node * malloc_n(node *);

void build_tree_frq();

#endif
