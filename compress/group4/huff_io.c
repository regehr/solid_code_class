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
 * Add a node to the priority queue
 */
void enqueue (struct pqNode* head, struct pqNode* p)
{
  struct pqNode* pq = head; // represents this pq we are adding to  
   
  while(p->priority > pq->priority)
    {
      pq = pq->next;
    }
  
  if(p->priority == pq->priority)
    {
      //Tiebreaker code goes here
      if(p->content->current < pq->content->current)
	{
	  p->next = pq->next;
	  pq->next = p;
	}
      else
	{
	  p->next = pq;
	}
    }
  else
    {
      p->next = pq->next;
      pq->next = p;
    }
}

/*
 * Remove a node from the priority queue 
 */
struct treeNode dequeue(struct pqNode* head)
{
  struct treeNode * ret = head->content;
  head = head->next;
  return *ret;
}

/*
 * Builds a Huffman tree for each character in terms of bit codes
 */
void build_tree(struct frequency table[])
{  
  int i; 
  struct pqNode * head = NULL; // start of pq
  struct pqNode * prev = NULL; // head initially NULL

  //get all character frequencies in file 
  // and add to priority queue
  for(i = 0; i < 256; i++)
    {      
       struct treeNode t = {NULL, NULL, NULL, table[i].count, (int)table[i].character};
       struct pqNode pq = {t.weight, NULL, &t};
       //If there is a previous, link it to current.      
      if(prev != NULL)
	prev->next = &pq;
       //If there is no previous, then current is head
      else
	head = &pq;

      prev = &pq; 
    }

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
      struct pqNode newNode = {pt.weight, NULL, &pt};
      enqueue(head, &newNode);
      //exit when there is only one node left in the pq (next is value in pq is null)
    }
  // when the loop ends, set remaining node as tree at root
   struct treeNode root = dequeue(head);  
}


