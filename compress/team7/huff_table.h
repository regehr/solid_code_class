/* 
 * File:   huff_table.h
 * Author: codyfoltz
 *
 * Created on February 1, 2014, 12:04 PM
 */

#include <stdlib.h>
#include <stdio.h>

#ifndef HUFF_TABLE_H
#define	HUFF_TABLE_H





 typedef struct huff_node
{
	struct huff_node* left_child;
	struct huff_node* right_child;
	int char_number;
	int lowest_value;
	int frequency;
}huff_node;

typedef struct huff_root
{
	struct huff_node* left_child;
	struct huff_node* right_child;
	int frequency;
	//not really needed. Just there to help make sure mem is freed.
	int node_count;

}huff_root;



/*  This method will create a huff tree based on an array containing ascii
 *  character frequencies.  The array is assumed to be of length 256.
 *  Element 0 refers to ascii number 0. Element 255 refers to ascii 255.
 *  The array should contain the count of each ascii character to encode.  
 *
 */
huff_root* create_huff_tree_from_frequency(int frequencyArray[]);

/*  This method will create a huff tree based on an array containing
 *  encodings for each ascii character 0 to 255.  Element 0 referes to 
 *  ascii character 0, 1 to ascii 1, etc.
 *
 *  Encodings are currently setup as strings of '0's and '1's.
 */
huff_root* create_huff_tree_from_encoding(char** encoding);

/*  This method will free all the memory used by a huff_root "object"
 *
 */
void destroy_huff_tree(huff_root* root);

/*  get_encoding will return an array of size 256.  This array will contain
 *  the encoding for each ascii character.  Element 0 is ascii 0, element 1 
 *  is ascii 1, etc.
 *
 *	Return type may if it needs too.
 *  Encodings are currently setup as strings of '0's and '1's.
 *
 */  
char** get_encoding(huff_root* root);


//Not sure how to do the decoding yet.  
//Might just have to manually go through the tree since encodings are varible length.
//  >.<




#endif	/* HUFF_TABLE_H */