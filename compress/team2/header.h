#ifndef HUFF_HEADER_H
#define HUFF_HEADER_H

#include <stdio.h>

/* magic identifiers and their sizes */
#define HUFF_MAGIC "HUFF"
#define HUFF_EXT   ".huff"

#define HUFF_MAGICLEN (sizeof(HUFF_MAGIC) - 1)
#define HUFF_EXTLEN   (sizeof(HUFF_EXT) - 1)

struct huff_header {
    uint64_t length;
    char * table[256];
};

/* read an entry in the huff translation table from the given file. 
 * may return EBADENTRY or ETRUNC on error, returns 0 on success. */
int huff_read_entry(FILE *, char **out_entry);

/* Read a huff_header from the given file. This function validates magic numbers
 * and extensions. */
int huff_read_header(FILE *, char * filename, struct huff_header *out);

/* Free all entries in the translation table */
int huff_free_hdrtable(struct huff_header *);

/* write the supplied huff header to the current position in the supplied file. */
int huff_write_header(FILE *, struct huff_header *);
#endif
