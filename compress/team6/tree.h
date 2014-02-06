#ifndef TREE_H
#define TREE_H

#include <stdbool.h>

typedef struct node {
  unsigned long long freq;
  struct node *parent;
  struct node *zero;
  struct node *one;
  char ascii;
} node;
typedef node *tree;

/* hi */
char *get_huffman_table(unsigned long long ascii_counts[256]);
tree get_huffman_tree(char *table[256]);
void free_tree(tree t);

#endif
