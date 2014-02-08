/*
 * Utilities for handling I/O.  This parses user input from stdin, reads files,
 * and writes to files safely.  
 *
 * Jonathon McDonald, Lynn Gao, Taylor Stapleton
 */

typedef enum {
    COMPRESS,
    DECOMPRESS,
    TABLE,
    UNHANDLED
} flags;


struct frequency {
    unsigned int count;
    char character;
};

// represents nodes in the Huffman tree
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
    struct tree_node content;
};


flags parse_args (char *[], char **);
int compare (const void *, const void *);
void build_table (char *, struct frequency []);
void dump_table (char *, struct frequency[]);
void traverse_tree (tree_node);
struct pq_node make_pq (struct frequency[]);
struct tree_node build_tree (struct pq_node);
void enqueue (struct pq_node *, struct pq_node *);
struct tree_node dequeue (struct pq_node*);
int compare_to (tree_node *, tree_node *);
void print_tree (tree_node);