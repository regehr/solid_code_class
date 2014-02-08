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
typedef struct treeNode treeNode;
struct treeNode {
  struct treeNode* parent;
   struct treeNode* left;  // 0
   struct treeNode* right; // 1
   int weight; // frequency of character in file
   int current; //ascii value of character (int)char
   }; 

// represents a priority queue for nodes in the tree
struct pqNode {
  int priority;
  struct pqNode* next; // a pointer to the next node in the queue
  struct treeNode content;
  };



flags parse_args (char *[], char **);
int compare (const void *, const void *);
void build_table (char *, struct frequency []);

void dump_table(char *, struct frequency[]);
void traverse_tree(struct treeNode);
struct pqNode makePQ(struct frequency[]);
struct treeNode build_tree(struct pqNode);
void enqueue(struct pqNode*, struct pqNode*);
struct treeNode dequeue(struct pqNode*);
int compareTo(struct treeNode*, struct treeNode*);
void printTree(struct treeNode);


