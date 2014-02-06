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

 struct treeNode {
  struct treeNode* parent;
   struct treeNode* left; //0
   struct treeNode* right; //1
   int weight; // frequency of character in file
   int current; //ascii value of character (int)char
 };


struct pqNode {
  int priority;
  struct pqNode* next;
  struct treeNode* content;
};


flags parse_args (char *[], char **);
int compare (const void *, const void *);
void build_table (char *, struct frequency []);
void build_tree(struct frequency[]);
void enqueue(struct pqNode*, struct pqNode*);
struct treeNode dequeue(struct pqNode*);
int compareTo(struct treeNode*, struct treeNode*);
