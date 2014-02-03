#ifndef HUFF_TABLE_H
#define HUFF_TABLE_H


/* struct used to represent a node in the huffman tree. */
typedef struct huff_tree() {
	int frequency;
	int character;
	struct huff_tree *zero_tree;
	struct huff_tree *one_tree;
} huff_tree;

void print_huff_table(FILE *input);

#endif