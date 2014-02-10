#ifndef HUFF_TREE_H
#define HUFF_TREE_H

#include "common.h"

/* Represents a node which points to other nodes. */
struct node {
    /* The tree paths. If a path is non-negative, represents an index into
       nodes. Else, |zero + 1| represents the byte value at pointed to leaf. */
    short paths[2];
};

struct tree {
    /* The nodes of the tree. nodes[0] is the root. */
    struct node nodes[255];
};

/* A decompression context */
struct huff_decoder {
    struct tree tree;
    short current_node;
};

/* A translation table specifies an encoding for all 256 bytes as a null terminated
   string: uint8_t * translation_table[256] */

/* Compression
----------------------------------------------------------------------------- */

/* Returns a new translation table generated from an array of 256
   unsigned long longs representing the number of times the byte index has
   appeared in a file. Allocates (strlen(i) + 1) * 8 memory for each string. */
void huff_make_table(const uint64_t freq[256], char *out_table[256]);

/* Decompression
----------------------------------------------------------------------------- */

/* Build a decoder struct from a translation table, which is an array of 256
   char *s which are the ASCII representations of that byte index's translation.
   Should not fail. */
void huff_make_decoder(struct huff_decoder *, const char * const table[256]);

/* Takes the next bit to decode. Returns an unsigned char converted to an int if
   a character is decoded, returns -1 otherwise. If an error occurs, -2 or lower
   is returned */
int huff_decode(int bit, struct huff_decoder *);

#endif
