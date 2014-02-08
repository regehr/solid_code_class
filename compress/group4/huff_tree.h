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

void enqueue (struct pq_node *, struct pq_node *);
tree_node dequeue (struct pq_node*);
int compare_to (tree_node *, tree_node *);
void print_tree (tree_node);
void traverse_tree (tree_node);
struct pq_node make_pq (struct frequency[]);
struct tree_node build_tree (struct pq_node);