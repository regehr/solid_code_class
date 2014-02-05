#include "internal.h"

#ifndef HUFF_H
#define HUFF_H

/* A translation table specifies an encoding for all 256 bytes as a null terminated
   string: uint8_t * translation_table[256] */

/* Compression
----------------------------------------------------------------------------- */

/* Returns a new translation table generated from an array of 256
   unsigned long longs representing the number of times the byte index has
   appeared in a file. Allocates (strlen(i) + 1) * 8 memory for each string. */
int huff_make_table(uint64_t freq[256], char *out_table[256]);

/* Decompression
----------------------------------------------------------------------------- */

/* A decompression context */
struct huff_decoder;

/* Build a new decoder struct from a
   translation table, which is an array of 256 char *s which are the ASCII
   representations of that byte index's translation. Returns 0 on success, 
   non-zero on failure. Should not fail. */
int huff_make_decoder(struct huff_decoder *, char *table[256]);

/* Takes the next bit to decode. Returns an unsigned char converted to an int if
   a character is decoded, returns -1 otherwise. If an error occurs, -2 or lower
   is returned */
int huff_decode(int bit, struct huff_decoder *);

#endif
