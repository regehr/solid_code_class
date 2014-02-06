/*
 * Utilities for handling I/O.  This parses user input from stdin, reads files,
 * and writes to files safely.  
 *
 * Jonathon McDonald, Lynn Gao, Taylor Stapleton
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huff_io.h"

/*
 * Parses the arguments passed by the user, returning the operation to be used.
 */
flags parse_args (char *argv[], char **out) {
    char *operation;

    operation = argv[1];
    *out = argv[2];

    if (strcmp(operation, "-c") == 0)
        return COMPRESS;
    else if (strcmp(operation, "-d") == 0)
        return DECOMPRESS;
    else if (strcmp(operation, "-t") == 0)
        return TABLE;
    else
        return UNHANDLED;
}


/*
 * Compares two frequency table rows' respective character counts.
 */
int compare (const void *p1, const void *p2) {
    const struct frequency *row1 = p1;
    const struct frequency *row2 = p2;

    if (row1->count != row2->count) 
        return ((int)row2->count - (int)row1->count);
    else
        return ((int)row2->character - (int)row1->character);
}


/*
 * Fills the provided frequency table using the file name, sorted highest 
 * frequency to lowest.
 */
void build_table (char *file_name, struct frequency table[]) {
    FILE *file;
    char character;

    file = fopen(file_name, "rb");
    if (NULL == file) {
        printf("Unable to open file.\n");
        exit(-1);
    }

    while ((character = fgetc(file)) != EOF) {
        table[(int)character].count++;
    }
    qsort(table, 256, sizeof(struct frequency), compare);  
}

/*
 * Prints out the compression table from the Huffman tree
 */
void dump_table(char* filename, struct frequency table[])
{
  //initialize node
  struct pqNode queue = makePQ(table);
  printf("%s\n", "made queue");
  // seg faults here
  struct treeNode node = build_tree(queue);
  //printTree(node);
}

/*
 * Traverses the Huffman tree and assigns 0 or 1 to children 
 */
void traverse_tree(struct treeNode tree)
{
  // struct frequency huffTable[256, sizeof(table)];  
}


/*
 * Compares two Huffman nodes using weight
 */
int compareTo(struct treeNode* left, struct treeNode* right)
{
  if(left->weight < right->weight)
    {
      return -1; // if right greater than left
    }
  else if(left->weight > right->weight)
    {
      return 1; // if left greater than right
    }
  else
    {
      // use a tie breaker if nodes have equal weights
      if(left->current < right->current)
	{
	  return -1; // left node goes before
	}
      else if(left->current > right->current)
	{
	  return 1; // right node goes before
	}
      else
	{
	  return 0; // nodes are assumed equal, this should never happen
	}      
    }
}

/*
 * Returns the leftmost leaf for inorder sort 
 */
int getLeftmost (struct treeNode *  tN)
{
  struct treeNode * current;
  while(current->left != NULL)
    {
      current = current->left;
    }
  return current->current;
}

/* 
 * Add a node to the priority queue
 */
void enqueue (struct pqNode* head, struct pqNode* p)
{
  struct pqNode* prev = NULL; // represents this pq we are adding to  
  struct pqNode* current = head;

  while(p->priority < current->priority)
    {
      //printf("%d vs %d\n", p->priority, current->priority);
      prev = current;
      current = current->next;
    }
  
  if(p->priority == current->priority)
    {
      //Tiebreaker code goes here
      if(getLeftmost(&p->content) < getLeftmost(&current->content))
	{
	  p->next = current;
	  prev->next = p;
	}
      else
	{
	  current->next = p;
	  prev->next = current;
	}
    }
  else
    {
      p->next = current;
      prev->next = p;
    }
}

/*
 * Remove a node from the priority queue 
 */
struct treeNode dequeue(struct pqNode* head)
{
  struct treeNode ret = head->content;
  head = head->next;
  return ret;
}

/*
 * Prints the characters of nodes in a huffman tree
 */
void printTree(struct treeNode head)
{
  printTree(*head.left);
  printf("%d\n", head.current);
  printTree(*head.right);
}

/* 
 * Creates a priority queue (pqNode) of nodes in the Huff tree (treeNode)
 */
struct pqNode makePQ(struct frequency table[])
{
  struct pqNode full;
  int i;
  int nodeCount = 0; // keep track of the number of nodes in the tree for length of huffman tree
  struct pqNode * head = NULL; // start of pq
  struct pqNode * prev = NULL; // prev initially NULL  
  struct pqNode * current = NULL;
  
//get all character frequencies in file 
  // and add to priority queue
  for(i = 0; i < 256; i++) 
    {    
      //  printf("%s\n", "got here");
      if(table[i].count > 0)
	{
	  nodeCount = nodeCount + table[i].count;
	  struct treeNode  newTNode = {NULL, NULL, NULL, table[i].count, (int)table[i].character};	 
	  struct pqNode  newQNode = {newTNode.weight, NULL, {&newTNode}}; 
	  current = &newQNode;
	  //printf("%s\n", "got here");

	  if(head == NULL)
	    {
	      head = current;
	    }
	  else
	    {
	      prev->next = current;	      
	    }	  
	  prev = current;	   
	} 
    }
printf("%s\n", "got here");
  full = *prev;
  return full;
}

/*
 * Builds a Huffman tree for each character in terms of bit codes
 */
struct treeNode build_tree(struct pqNode pq)
{  
  struct pqNode * head = &pq;
   // start building tree
  while(head->next != NULL)
    {
      // grab 2 smallest nodes 
      struct treeNode lt = dequeue(head);
      struct treeNode rt = dequeue(head);
      // create a new node with smallest nodes as children
      struct treeNode pt = {NULL, &lt, &rt,lt.weight+rt.weight, -1};
      // associate children with parent
      lt.parent = &pt;
      rt.parent = &pt;
      // enqueue new node to priority queue
      struct pqNode newNode = {pt.weight, NULL, {&pt}};
      enqueue(head, &newNode);
      //exit when there is only one node left in the pq (next is value in pq is null)
    }
  // when the loop ends, set remaining node as tree at root
   struct treeNode root = dequeue(head);  
   printf("print start:\n");
printTree(root);
 printf("print end:\n");
   return root;
}

