/* Author: John Clukey
 * Date: January 30 - ...
 * 
 * A tree data structure for Huffman Encoding.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "tree.h"

/* Nodes must be freed by calling function or later function.
 */
tree make_node_from_ascii_freq(char c, long long frequency) {
  tree t;
  t = malloc(sizeof(node));
  t->freq = frequency;
  t->parent = t->zero = t->one = NULL;
  t->ascii = c;
  t->is_leaf = true;
  return t;
}

tree make_node_from_trees(tree zero, tree one) {
  tree t;
  t = malloc(sizeof(node));
  t->freq = zero->freq + one->freq;
  zero->parent = one->parent = t;
  t->ascii = 0;
  t->is_leaf = false;
  t->zero = zero;
  t->one = one;
  return t;
}

/* Frees node and all its children.
 * Would blow the stack if we weren't limited to 256 original nodes.
 */
void free_tree(tree t) {
  if (t->zero != NULL)
    free_tree(t->zero);
  if (t->one != NULL)
    free_tree(t->one);
  free(t);
}

/* Comparison function for huffman tree nodes.
 * A node is less if its frequency is less. If frequencies are equal,
 * first node is less if its ascii value is less than or equal to
 * second node's ascii value.
 */
int compare_trees(const void *a, const void *b) {
  unsigned long long comp;
  tree t1, t2;
  int r;
  t1 = *(tree *)a;
  t2 = *(tree *)b;
  comp = t1->freq - t2->freq;
  if (t1->freq == t2->freq) {
    r = t1->ascii <= t2->ascii ? -1 : 1;
  }
  else {
    r = t1->freq < t2->freq ? -1 : 1;
  }
  return r;
}

static void check_rep(tree t) {
  assert((t->zero == NULL && t->one == NULL)
	 || (t->zero != NULL && t->one != NULL));
  /* TODO: Assert more. */
}

char *get_huffman_table(unsigned long long ascii_counts[256]) {
  int i, hdt, tlt, hds, tls;
  tree zero, one, t;
  tree tree_array[256];
  tree second_array[128] = {NULL};

  hdt = hds = tls = 0;
  tlt = 255;

  for (i = 0; i < 256; i++) {
    tree_array[i] = make_node_from_ascii_freq((char)i, ascii_counts[i]);
  }
  
  qsort(tree_array, 256, sizeof(tree), compare_trees);
  
  for (i = 0; i < 256; i++) {
    printf("%u freq: %llu; ", (unsigned int)tree_array[i]->ascii, tree_array[i]->freq);
  }
  
  /* TODO: Finish implementing the two queue huffman tree
   * creation algorithm.
  while (tree_array[hdt] != NULL || second_array[hds] != NULL) {
    t = make_node_from_trees(zero, one);
    check_rep(t);
  }
   * TODO: build return string;
  free_tree(t); */
  
  return "TODO";
}
