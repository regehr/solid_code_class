/*
 * Huff tree model.
 *
 * Jonathon McDonald, Lynn Gao, Taylor Stapleton
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    if (get_leftmost(p->content) < get_leftmost(current->content)) {
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
tree_node * dequeue (struct pq_node *head)
{
    tree_node * ret = head->content;
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
struct pq_node * make_pq (struct frequency table[])
{
    int i;
    int node_count = 0; // keep track of the number of nodes in the tree for length of huffman tree
    struct pq_node *head = NULL; // start of pq
    struct pq_node *prev = NULL; // prev initially NULL  
  
    //get all character frequencies in file 
    // and add to priority queue
    for (i = 0; i < 256; i++) {    
        //  printf("%s\n", "got here");
        if (table[i].count > 0) {
            node_count = node_count + table[i].count;
            tree_node * new_tnode = new_tree_node(NULL, NULL, NULL, 
                table[i].count, (int)table[i].character);
   
            struct pq_node * current = new_pq_node(new_tnode->weight, NULL, 
                new_tnode);

            if (head == NULL)
                head = current;
            else 
                prev->next = current;   
            

            prev = current;    
        } 
    }
    
    return head;
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
        struct tree_node *lt = dequeue(head);
        struct tree_node *rt = dequeue(head);

        // create a new node with smallest nodes as children
        struct tree_node *pt = new_tree_node (NULL, lt, rt, lt->weight+rt->weight, -1);

        // associate children with parent
        lt->parent = pt;
        rt->parent = pt;

        // enqueue new node to priority queue
        struct pq_node * new_node = new_pq_node(pt->weight, NULL, pt);
        enqueue(head, new_node); // SEG FAULTS HERE
        //exit when there is only one node left in the pq (next is value in pq is null)
    }
    
    // when the loop ends, set remaining node as tree at root
    struct tree_node * root = dequeue(head);  
    printf("print start:\n");
    print_tree((*root));
    printf("print end:\n");
    return (*root);
}


/*
 * Initializes a new priority queue node in the heap.
 */
struct pq_node * new_pq_node (int priority, struct pq_node * next, 
    tree_node * content)
{
    char *space = malloc(sizeof(struct pq_node));
    struct pq_node * node = (struct pq_node *)space;

    node->priority = priority;
    node->next = next;
    node->content = content;

    return node;
}


/*
 * Initializes a new tree node in the heap.
 */
tree_node * new_tree_node (tree_node *parent, tree_node *left, tree_node *right,
    int weight, int current)
{
    char *space = malloc(sizeof(tree_node));
    tree_node * node = (tree_node *)space;

    node->parent = parent;
    node->left = left;
    node->right = right;
    node->weight = weight;
    node->current = current;

    return node;
}