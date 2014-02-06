#include "huff_table.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
	int size;
	queue_node* tail;

} queue_head;

//************************   Queue  *************************/ 
//returns the reference of the object while keeping it in the front of the queue.
huff_node* peek(queue_head* head)
{
	if(head->next_node == NULL){
		return NULL;
	}

	return head->next_node->object;
}

int queue_size(queue_head* head){
	return head->size;
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
	if(head->tail == q_node){
		head->tail = NULL;
	}
	head->size = head->size-1;
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
	} else{
		head->next_node = q_node;
	}
	head->tail = q_node;
	head->size = head->size+1;
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
huff_node* build_tree(queue_head* queue1, queue_head* queue2);
char* encoding_for_char(int char_value, huff_node* root);

void init_huff_node(huff_node* node, int char_number, int frequency){
	node->left_child = 0;
	node->right_child = 0;
	node->char_number = char_number;
	node->lowest_value = char_number;
	node->frequency = frequency;
	node->parent = NULL;
	node->encoding = NULL;
}

int min(int a, int b){
	if( a > b){
		return b;
	} else{
		return a;
	}
}

//negative value means a comes before b
//zero of they are the same
//positive means b comes before a
int huff_node_frequency_comparer(const void * a, const void * b)
{

	huff_node* node_a = ((huff_node*)a);
	huff_node* node_b = ((huff_node*)b);
	int result = node_a->frequency - node_b->frequency;
	if(result == 0){
		if(node_a->lowest_value < node_b->lowest_value){
			return -1;
		} else{
			return 1;
		}
	}
	return result;
}

huff_node* create_parent_node(huff_node* left_child, huff_node* right_child)
{
	//create huff_node
	huff_node* parent = Malloc(sizeof(huff_node));
	init_huff_node(parent, -1, left_child->frequency + right_child->frequency);
	parent->left_child = left_child;
	parent->right_child = right_child;
	parent->lowest_value = left_child->lowest_value;
	left_child->parent = parent;
	right_child->parent = parent;

	return parent;

}

huff_node* find_lowest_node(queue_head* queue1, queue_head* queue2){
	
	if(peek(queue1) == NULL){
		return dequeue(queue2);
	} else if(peek(queue2) == NULL){
		return dequeue(queue1);
	}

	int peek_1 = peek(queue1)->frequency;
	int peek_2 = peek(queue2)->frequency;

	// queue 1 contains the lowest frequency
	if(peek_1 < peek_2){
		return dequeue(queue1);	
	}
	// queue 2 contains the lowest frequency
	else if( peek_2 < peek_1){
		return dequeue(queue2);
	}
	// queues tied for lowest frequency
	// tie breaker goes to the node whoes subtree contains
	// the nodes with the lowest ascii value.
	else{
		peek_1 = peek(queue1)->lowest_value;
		peek_2 = peek(queue2)->lowest_value;
		if(peek_1 < peek_2){
			return dequeue(queue1);
		} else{
			return dequeue(queue2);
		}
	}
}



/*	Queue 1 contains all the huff_node leaves
 *	Queue 2 starts empty and will contain parent nodes
 *
 *
 */
huff_node* build_tree(queue_head* queue1, queue_head* queue2)
{
	huff_node* child_1 = NULL;
	huff_node* child_2 = NULL;

	int size_1 = queue1->size;
	int size_2 = queue2->size;

	// While there are more than 1 nodes left
	// dequeue from the queue that contains the lowest frequency
	// make this a left child
	// dequeue from the queue that contains the new lowest frequency
	// make this a right child
	// create a parent node
	// enqueue the parent node into the 2nd queue
	while( (size_1 + size_2) > 1){

		// if queue 2 is empty, 2 lowest will be in queue 1
		// queue 1 is already sorted
		if(size_2 == 0){
			child_1 = dequeue(queue1);
			child_2 = dequeue(queue1);
		} 
		// queue 1 is empty so the 2 lowest will be in queue 2
		// first in queue is the lower frequency, however
		// the second node in the queue may have the same frequency
		// but the left child must be the one subtree that contains 
		// the node with the lowest ascii value.
		else if(size_1 == 0){
			child_1 = dequeue(queue2);
			child_2 = dequeue(queue1);
			if(child_2->lowest_value < child_1->lowest_value){
				huff_node* temp = child_2;
				child_2 = child_1;
				child_1 = temp;
			}
		} else{
			child_1 = find_lowest_node(queue1, queue2);
			child_2 = find_lowest_node(queue1, queue2);

			if(child_1->frequency == child_2->frequency){
				if(child_2->lowest_value < child_1->lowest_value){
				huff_node* temp = child_2;
				child_2 = child_1;
				child_1 = temp;
				}
			}
		}
		enqueue(queue2, create_parent_node(child_1, child_2));
		size_1 = queue1->size;
		size_2 = queue2->size;
	}

	huff_node* root = find_lowest_node(queue1, queue2);
	root->parent = NULL;
	root->encoding = "";

	return root;
}



void generate_encoding(huff_node* root, char* path)
{
	if(root == NULL){
		return;
	} 

	int length = strlen(root->parent->encoding);
    
	char* encoding = Malloc(length+1);
        int i = 0;
        for(; i < length+1; i++){
            encoding[i] = 0;
        }
        strcat( encoding, root->parent->encoding);
	strcat (encoding, path);
	root->encoding = encoding;
	generate_encoding(root->left_child, "0");
	generate_encoding(root->right_child, "1");

}

void generate_encoding_tree(huff_node* root){
    
	int length = 1;
    
	char* encoding = Malloc(length+1);
        int i = 0;
        for(; i < length+1; i++){
            encoding[i] = 0;
        }
	root->encoding = encoding;
	generate_encoding(root->left_child, "0");
	generate_encoding(root->right_child, "1");
}

/*  Description in header file
 * 
 */
huff_node* create_huff_tree_from_frequency(int frequencyArray[])
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

	huff_node* root = build_tree(&queue1, &queue2);
	generate_encoding_tree(root);
	return root;
}

/*  
 *  Description in header file
 */
huff_node* create_huff_tree_from_encoding(char** encoding)
{
	huff_node* root = 0;

	return root;
}

/*  Description in header file
 *
 */
void destroy_huff_tree(huff_node* root)
{

}

/*  Description in header file
 *
 */  
char** get_encoding(huff_node* root)
{
	char** encodings = Malloc(sizeof(char*[256]));
	int i = 0;
	for(;i < 256; i++){
            char* seqence = encoding_for_char(i, root);
		encodings[i] = seqence;
	}

	return encodings;
}

huff_node* find_leaf_node(int char_value, huff_node* root){

	if(root == NULL){
		return NULL;
	}
	if(root->char_number == char_value){
		return root;
	}
	huff_node* result =	find_leaf_node(char_value, root->left_child);
	if(result == NULL){
		result = find_leaf_node(char_value, root->right_child);
	}
	return result;
}

char* encoding_for_char(int char_value, huff_node* root)
{
	huff_node* node = find_leaf_node(char_value, root);
	return node->encoding;
}



//**************************** End Tree Code  *****************************//



