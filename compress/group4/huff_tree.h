/*
 * Huff tree model.
 *
 * Jonathon McDonald, Lynn Gao, Taylor Stapleton
 */
// represents nodes in the Huffman tree
#include <stdio.h>

typedef struct tree_node tree_node;
struct tree_node {
    tree_node *parent;
    tree_node *left;  // 0
    tree_node *right; // 1
    int weight; // frequency of character in file
    int current; //ascii value of character (int)char
}; 

// represents a priority queue for nodes in the tree
struct pq_node {
    int priority;
    struct pq_node *next; // a pointer to the next node in the queue
    tree_node *content;
};

struct frequency {
    unsigned int count;
    char character;
    char *sequence;
};

char * huff_bit_code;

struct pq_node * enqueue (struct pq_node *, struct pq_node *);
tree_node * dequeue (struct pq_node *);
int compare_to (tree_node *, tree_node *);
void print_tree (tree_node);
char * get_bit_code(char);
char * traverse_tree (tree_node *, char *);
void print_huff(tree_node *, char *);
struct pq_node * make_pq (struct frequency[]);
struct tree_node build_tree (struct pq_node *);
struct pq_node * new_pq_node (int, struct pq_node *, tree_node *);
tree_node * new_tree_node (tree_node *, tree_node *, tree_node *, int, int);
void traverse_pq(struct pq_node *);
int check_rep(tree_node *);
int is_leaf(tree_node *);
void compress(char *, struct frequency[]);
void write_encoding(FILE *, char);

