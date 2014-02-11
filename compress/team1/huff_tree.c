/*
 * Common functions for compression and decompression.
 */

#include "huff_tree.h"

void init_node(node **n, char c)
{
    (*n) = malloc_n(*n);
    for (int i = 0; i < 257; i++)
        (*n)->code[i] = 0;
    (*n)->left = NULL;
    (*n)->right = NULL;
    (*n)->freq = 0;
    (*n)->visited = false;
    (*n)->c = c;
    (*n)->lowest = c;
}

void free_huff_tree()
{
    for (int i = 0; i < 511; i++)
        free(all_nodes[i]);
}

bool is_leaf(node *n)
{
    if (n->left != NULL || n->right != NULL)
        return false;
    return true;
}

node * malloc_n(node *n)
{
    n = (node*)malloc(sizeof(node));
    if (n == NULL)
    {
        fprintf(stderr, "Failed to allocate memory.");
        exit(255);
    }
    return n;
}
