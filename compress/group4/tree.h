#ifndef TREE_H
#define TREE_H


typedef struct node {
  unsigned long long freq;
  struct node *parent;
  struct node *zero;
  struct node *one;
  char ascii; /* If node is a leaf this is the associated ascii character.
	       * On encoding, if node is a branch this is the lowest valued 
	       * ascii character in the sub-tree. On decoding, this field
	       * carries no meaning in a branch node.
	       */
} node;

typedef node *tree;

/* Char * must be free by caller */
char *get_huffman_table(unsigned long long ascii_counts[256]);

/* Tree must be free by caller calling free_tree on it. */
tree get_huffman_tree(char *table[256]);
void free_tree(tree t);

#endif
