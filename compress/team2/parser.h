#ifndef HUFF_PARSER_H
#define HUFF_PARSER_H

#include <stdio.h>

/* magic indentfiers and their sizes */
#define HUFF_MAGIC "HUFF"
#define HUFF_EXT   ".huff"

#define HUFF_MAGICLEN (sizeof(HUFF_MAGIC) - 1)
#define HUFF_EXTLEN   (sizeof(HUFF_EXT) - 1)

#define EBADEXT    (-1)   // Non .huff file extension 
#define ENOMAGIC   (-2)   // No magic number in file
#define EBADENTRY  (-3)   // Bad entry in translation table
#define ETRUNC     (-4)   // Either file truncated, or a non-terminated entry
                          // the translation table.
                          //
#define EFILETOOLONG (-5);    // The file was too long to be stored in a uint64_t

struct huff_header {
    uint64_t size;
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

/* Returns 'true' if a file pointed to by FILE and named 'filename' is a valid
 * huff file. Returns false otherwise. Non side-effecting. */
bool is_huff(FILE *, char * filename);

#endif
