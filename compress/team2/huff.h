#ifndef HUFF_H
#define HUFF_H

/* Compression
----------------------------------------------------------------------------- */

struct HuffmanTable;

/* Frees a HuffmanTable struct. Returns 1 on success, 0 otherwise. */
int huff_freetable(struct HuffmanTable *table);

/* Returns a pointer to a new translation table generated from an array of 256
   unsigned long longs representing the number of times the byte index has
   appeared in a file. */
HuffmanTable *huff_tablefromfreq(unsigned long long freq[256]);

/* Encodes byte using table and places the ASCII representation of the encoding
   in out. Returns 1 on success, 0 otherwise. The longest possible encoding is
   255 zeros. */
int huff_encode(char byte, char out[256], HuffmanTable *table);

/* Decompression
----------------------------------------------------------------------------- */

struct DecompressionContext;

/* Frees a DecompressionContext struct. Returns 1 on success, 0 otherwise. */
int huff_freecontext(struct DecompressionContext *context);

/* Returns a pointer to a new DecompressionContext struct generated from a
   translation table, which is an array of 256 char *s which are the ASCII
   representations of that byte index's translation. */
struct DecompressionContext *contextfromtable(char *table[]);

/* Takes the next bit to decode. Returns an unsigned char converted to an int if
   a character is decoded, returns -1 otherwise. If an error occurs, -2 or lower
   is returned */
int huff_decode(int bit, DecompressionContext *context);

#endif
