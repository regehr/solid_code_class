/* John Clukey
 * Date: January 30 - ...
 * 
 * A tree data structure for Huffman Encoding.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "tree.h"


/* Error checking call to malloc. */
static void *Malloc(size_t size, char *func) {
  void *result = malloc(size);
  if (result == NULL) {
    fprintf(stderr, "%s: malloc error\n", func);
    exit(-1);
  }
  return result;
}

/* Nodes must be freed by calling function.
 */
static tree make_node_from_ascii_freq(char c, long long frequency) {
  tree t;
  t = (tree)Malloc(sizeof(node), "make_node_from_ascii");
  t->freq = frequency;
  t->parent = t->zero = t->one = NULL;
  t->ascii = c;
  return t;
}

static tree make_node_from_trees(tree zero, tree one) {
  tree t;
  t = (tree)Malloc(sizeof(node), "make_node_from_trees");
  t->freq = zero->freq + one->freq;
  zero->parent = one->parent = t;
  t->ascii = (unsigned char)zero->ascii < (unsigned char)one->ascii ?  zero->ascii : one->ascii;
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
 * second node's ascii value. This actually sorts the nodes in reverse
 * order
 */
static int compare_trees(const void *a, const void *b) {
  tree t1, t2;
  int r;
  t1 = *(tree *)a;
  t2 = *(tree *)b;
  if (t1->freq == t2->freq) {
    r = (unsigned char)t1->ascii >= (unsigned char)t2->ascii ? -1 : 1;
  }
  else {
    r = t1->freq > t2->freq ? -1 : 1;
  }
  return r;
}

static void check_rep_encode(tree t) {
  assert((t->zero == NULL && t->one == NULL)
	 || (t->zero != NULL && t->one != NULL));
  if (t->zero != NULL) {
    assert(t->freq == t->zero->freq + t->one->freq);
    assert(t->zero->freq <= t->one->freq);
    if (t->zero->freq == t->one->freq)
      assert((unsigned char)t->zero->ascii < (unsigned char)t->one->ascii);
  }
  if (t->zero != NULL) {
    check_rep_encode(t->zero);
    check_rep_encode(t->one);
  }
}


/* A helper for tree2table.
 */
static void find_char_encoding(tree t, char code[257], int *length, char c) {
  tree current;
  tree stack[511] = {NULL};
  int top;
  *length = top = 0;
  current = t;
  /* Post-order traversal of tree searching for given char */
  do {
    while (current) {
      if (current->one) {
	stack[top++] = current->one;
      }
      stack[top++] = current;
      if (current->ascii == c && current->zero == NULL) {
	code[(*length)++] = '\n';
	return;
      }
      current = current->zero;
      code[(*length)++] = '0';
    }
    (*length)--;
    current = stack[--top];
    if (current->one && stack[top - 1] == current->one) {
      stack[top - 1] = current;
      current = current->one;
      code[(*length)++] = '1';
    }
    else if (current->ascii == c && current->one == NULL) {
      code[(*length)++] = '\n';
      return;
    }
    else {
      current = NULL;
    }
  } while (top != 0);
}

/* Table must be freed by function calling get_huffman_table.
 */
static char *tree2table(tree t) {
  char temp[257] = {'\0'};
  int i, n, c;
  char *table;
  if ((table = (char *)calloc(33153, sizeof(char))) == NULL) {
    fprintf(stderr, "tree2table: calloc error\n");
    exit(-1);
  }
  i = n = 0;
  for (c = 0; c < 256; c++) {
    find_char_encoding(t, temp, &i, c);
    strncpy(&table[n], temp, i);
    n = n + i;
  }
  table[n] = '\0';
  return table;
}

/* Table must be free by function calling get_huffman_table.
 */
char *get_huffman_table(unsigned long long ascii_counts[256]) {
  int i, count, hdt, tlt;
  char *table;
  tree zero, one, t;
  tree tree_array[256];

  hdt = 0;
  tlt = 255;
  
  for (i = 0; i < 256; i++) {
    tree_array[i] = make_node_from_ascii_freq((char)i, ascii_counts[i]);
  }
  
  for (count = 256; count > 1; count--){
    qsort(tree_array, count, sizeof(tree), compare_trees);
    zero = tree_array[tlt--];
    one = tree_array[tlt];
    
    t = make_node_from_trees(zero, one);
    tree_array[tlt] = t;

    check_rep_encode(t);
  }
  t = tree_array[0];
  table = tree2table(t);
  free_tree(t);
  return table;
}

/* The extra assertions about frequency and ordering made in the
 * other check rep don't hold since we don't know frequencies.
 */
static void check_rep_decode(tree t) {
  assert((t->zero == NULL && t->one == NULL) ||
	 (t->zero != NULL && t->zero != NULL));
  if (t->zero != NULL) {
    check_rep_decode(t->zero);
    check_rep_decode(t->one);
  }
}

tree get_huffman_tree(char *encodings[256]) {
  tree root, current, next;
  int i, j;
  root = (tree)Malloc(sizeof(node), "get_huffman_tree");
  root->freq = 0;
  root->parent = root->zero = root->one = NULL;
  root->ascii = '\0';

  for (i = 0; i < 256; i++) {
    current = root;
    for (j = 0; encodings[i][j] != '\0'; j++) {
      if (encodings[i][j] == '0') {
	if (current->zero != NULL) {
	  current = current->zero;
	}
	else {
	  next = (tree)Malloc(sizeof(node), "get_huffman_tree");
	  current->zero = next;
	  next->freq = 0;
	  next->parent = current;
	  next->zero = next->one = NULL;
	  next->ascii = '\0';
	  current = next;
	}
      }
      else {
	if (current->one != NULL) {
	  current = current->one;
	}
	else {
	  next = (tree)Malloc(sizeof(node), "get_huffman_tree");
	  current->one = next;
	  next->freq = 0;
	  next->parent = current;
	  next->zero = next->one = NULL;
	  next->ascii = '\0';
	  current = next;
	}
      }
    }
    current->ascii = (unsigned char)i;
  }
  
  check_rep_decode(root);
  return root;
}
