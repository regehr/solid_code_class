#include "huff_table.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void* Malloc(int size){
	void* temp = malloc(size);
	if(temp == 0){
		printf("%s", "Malloc failed");
		exit(-1);
	}
	return temp;
}



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
	return head->next_node->object;
}
//returns the reference of the object in addition to removing the reference from the queue. 
huff_node* dequeue(queue_head* head)
{
	if(head->next_node == NULL){
		return NULL;
	}
	queue_node* q_node = head->next_node;
	huff_node* h_node = q_node->object;
	head->next_node = q_node->next_node;
	free (q_node);

	return h_node;


}
//Adds a huff_node* to the end of the queue.
void enqueue(queue_head* head, huff_node* h_node)
{
	assert(head !=0);
	assert(h_node != 0);
	//new q_node
	queue_node* q_node = Malloc(sizeof(queue_node));
	q_node->next_node = NULL;
	q_node->object = h_node;

	//add q_node to the end
	if(head->tail != NULL){
		head->tail->next_node = q_node;
	} 
	head->tail = q_node;
}

//Sets up the queue
void init_queue(queue_head* head){
	head->next_node = NULL;
	head->tail = NULL;
}


void delete_queue(queue_head* head){
	queue_node* current = head->next_node;
	queue_node* previous = current;
	while(current != NULL){
		previous = current;
		current = current->next_node;
		free(previous);
	}
	head->next_node = NULL;
	head->tail = NULL;
}


//************************  End Queue  ****************************//


//************************  Tree Code  ****************************//

huff_node* create_parent_node(huff_node* left_child, huff_node* right_child);

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
huff_root* create_huff_tree_from_frequency(int frequencyArray[])
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
		enqueue(&queue1, nodes[i]);
	}


	huff_root* root = 0;
	return root;
}

/*  
 *  Description in header file
 */
huff_root* create_huff_tree_from_encoding(char** encoding)
{
	huff_root* root = NULL;

	return root;
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
	char** encodings = 0;

	return encodings;
}


//**************************** End Tree Code  *****************************//



