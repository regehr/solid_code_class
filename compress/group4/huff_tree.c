/*
 * Huff tree model.
 *
 * Jonathon McDonald, Lynn Gao, Taylor Stapleton
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huff_io.h"
#include "huff_tree.h"


/*
 * Traverses the Huffman tree and assigns 0 or 1 to children 
 */
void traverse_tree(struct tree_node tree)
{
    // struct frequency huffTable[256, sizeof(table)];  
}


/*
 * Compares two Huffman nodes using weight
 */
int compare_to(struct tree_node* left, struct tree_node* right)
{
    if (left->weight < right->weight) {
        return -1; // if right greater than left
    }
    else if (left->weight > right->weight) {
        return 1; // if left greater than right
    } else {
        // use a tie breaker if nodes have equal weights
        if (left->current < right->current) {
            return -1; // left node goes before
        } else if (left->current > right->current) {
            return 1; // right node goes before
        } else {
            return 0; // nodes are assumed equal, this should never happen
        }      
    }
}


/*
 * Returns the leftmost leaf for inorder sort 
 */
int get_leftmost (struct tree_node *tn)
{
    struct tree_node * current;
    while (current->left != NULL) {
        current = current->left;
    }
    return current->current;
}


/* 
 * Add a node to the priority queue
 */
void enqueue (struct pq_node *head, struct pq_node *p)
{
    struct pq_node* prev = NULL; // represents this pq we are adding to  
    struct pq_node* current = head;

    while (p->priority < current->priority) {
        printf("p->priority %d : head->priority %d\n", p->priority, current->priority);
        prev = current;
        current = current->next;
    }
    printf("%s\n", "in enq");
    if (p->priority == current->priority) {
        //Tiebreaker code goes here
    }
    if (get_leftmost(&p->content) < get_leftmost(&current->content)) {
        p->next = current;
        prev->next = p;
    } else {
        current->next = p;
        prev->next = current;
    }
}


/*
 * Remove a node from the priority queue 
 */
struct tree_node dequeue (struct pq_node *head)
{
    struct tree_node ret = head->content;
    head = head->next;
    return ret;
}


/*
 * Prints the characters of nodes in a huffman tree
 */
void print_tree (struct tree_node head)
{
    print_tree(*head.left);
    printf("%d\n", head.current);
    print_tree(*head.right);
}


/* 
 * Creates a priority queue (pq_node) of nodes in the Huff tree (tree_node)
 */
struct pq_node make_pq (struct frequency table[])
{
    struct pq_node full;
    int i;
    int nodeCount = 0; // keep track of the number of nodes in the tree for length of huffman tree
    struct pq_node *head = NULL; // start of pq
    struct pq_node *prev = NULL; // prev initially NULL  
    struct pq_node *current = NULL;
  
    //get all character frequencies in file 
    // and add to priority queue
    for (i = 0; i < 256; i++) {    
        //  printf("%s\n", "got here");
        if (table[i].count > 0) {
            nodeCount = nodeCount + table[i].count;
            struct tree_node  newTNode = {NULL, NULL, NULL, table[i].count, (int)table[i].character};    
            struct pq_node  newQNode = {newTNode.weight, NULL, {&newTNode}}; 
            current = &newQNode;
            // print out to check weights
            printf("newQNode->priority %d\n", newQNode.priority);

            if (head == NULL) {
                head = current;
            } else {
                prev->next = current;         
            }     
            prev = current;    
        } 
    }

    full = *prev; 
    printf("full tree->priority %d\n", full.priority);
    printf("full tree->next->priority %d\n", full.next->priority);
    return full;
}


/*
 * Builds a Huffman tree for each character in terms of bit codes
 */
struct tree_node build_tree (struct pq_node pq)
{    
    struct pq_node *head = &pq;
    // start building tree
    while (head->next != NULL) {
        // grab 2 smallest nodes 
        struct tree_node lt = dequeue(head);
        struct tree_node rt = dequeue(head);
        // create a new node with smallest nodes as children
        struct tree_node pt = {NULL, &lt, &rt,lt.weight+rt.weight, -1};
        // associate children with parent
        lt.parent = &pt;
        rt.parent = &pt;      
        // enqueue new node to priority queue
        struct pq_node newNode = {pt.weight, NULL, {&pt}};
        enqueue(head, &newNode); // SEG FAULTS HERE
        //exit when there is only one node left in the pq (next is value in pq is null)
    }
    
    // when the loop ends, set remaining node as tree at root
    struct tree_node root = dequeue(head);  
    printf("print start:\n");
    print_tree(root);
    printf("print end:\n");
    return root;
}