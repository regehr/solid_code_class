#include "huff_table.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>



//Queue objects
typedef struct queue_node
{
	struct huff_node* object;
	struct queue_node* next_node;

} queue_node;

typedef struct queue_head
{
	queue_node* next_node;
	queue_node* tail;

} queue_head;

//************************   Queue  *************************/ 
//returns the reference of the object while keeping it in the front of the queue.
huff_node* peek(queue_head* head)
{

}
//returns the reference of the object in addition to removing the reference from the queue. 
huff_node* dequeue(queue_head head)
{

}
//Adds a huff_node* to the end of the queue.
void enqueue(queue_head head, huff_node* node)
{
	
}

void init_queue(queue_head* root){

}


//************************  End Queue  ****************************//


//************************  Tree Code  ****************************//
void init_huff_node(huff_node* node, int char_number, int frequency){
	node->left_child = 0;
	node->right_child = 0;
	node->char_number = char_number;
	node->frequency = frequency;
}

int huff_node_frequency_comparer(const void * a, const void * b)
{
  return (  ((huff_node*)a)->frequency - ((huff_node*)b)->frequency );
}



/*  Description in header file
 * 
 */
huff_root create_huff_tree_from_frequency(int frequencyArray[])
{
	int i = 0;
	huff_node* nodes[256];
	for(; i < 256; i++){
		nodes[i] = (huff_node*)Malloc(sizeof(huff_node));
		init_huff_node(nodes[i], i, frequencyArray[i]);
	}
	qsort(nodes, 256, sizeof(huff_node*),huff_node_frequency_comparer);
	assert( nodes[0]->frequency <= nodes[255]->frequency);

	queue_head queue1;
	queue_head queue2;
	for(i = 0; i < 256; i++){
		enqueue(queue1, nodes[i]);
	}




}

/*  
 *  Description in header file
 */
huff_root create_huff_tree_from_encoding(char** encoding)
{

}

/*  Description in header file
 *
 */
void destroy_huff_tree(huff_root* root)
{

}

/*  Description in header file
 *
 */  
char** get_encoding(huff_root* root)
{

}



