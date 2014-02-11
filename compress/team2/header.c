#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include "common.h"
#include "header.h"

/* Header reading helper */
static int _huff_read_header(FILE *, char * filename, struct huff_header *);

/* Return true if 'filename' ends with a '.huff' extension */
static bool has_huff_ext(const char * filename) {
    /* make sure the name is at least as long as HUFF_EXT */
    size_t name_length = strlen(filename);
    if (name_length < HUFF_EXTLEN) { return false; }

    /* make sure the filename ends with HUFF_EXT */
    const char * ext_start = &filename[name_length - HUFF_EXTLEN];
    return strcmp(ext_start, HUFF_EXT) == 0;
}

/* Return true if 'file' begins with HUFF_MAGIC */
static bool has_huff_magic(FILE * file) {
    /* prepare a buffer for reading. */
    char magic[HUFF_MAGICLEN];
    memset(magic, 0, HUFF_MAGICLEN);

    /* check if the given file has the HUFF magic number */
    int items = fread(magic, HUFF_MAGICLEN, 1, file);
    return items > 0 && strncmp(magic, HUFF_MAGIC, HUFF_MAGICLEN) == 0;
}

int huff_read_entry(FILE * file, char **out) {
    char current = 0;
    int status = 0;
    int byte_count = 0;
    char * buffer = xmalloc(256);

    for (; fread(&current, 1, 1, file); byte_count++) {
        /* When we hit a newline, the entry is finished. */
        if (current == '\n') {
            buffer[byte_count] = '\0';
            break;
        /* if an entry contains something that isn't a zero or a one, it
         * is malformed. */
        } else if (current != '0' && current != '1') {
            status = EBADENTRY;
            break;
        /* if an entry is larger than the buffer we've allocated, it's
         * an invalid entry. */
        } else if (byte_count == 256) {
            status = EENTRYTOOLONG;
            break;
        }
        buffer[byte_count] = current;
    }

    if (feof(file) || ferror(file)) {
        status = ETRUNC;
    }

    /* status == 0 implies that strlen(buffer) == byte_count */
    assert(status != 0 || (strlen(buffer) == ((size_t) byte_count) &&
           "Translation table entry length and number of bytes read don't match."));

    if (status == 0) {
        /* re-size the buffer to the actual size of the entry */
        *out = xrealloc(buffer, byte_count + 1);
    } else {
        free(buffer);
    }

    return status;
}

/* Helper that cleans up the file and header structure when a parsing error
 * occurs, _huff_read_header does the actual parsing. */
int huff_read_header(FILE * file, char * filename, struct huff_header * header) {
    /* zero the translation table, so that all pointers are null pointers */
    memset(&header->table, 0, 256 * sizeof(char *));
    int code = _huff_read_header(file, filename, header);
    /* If we failed to read a valid header, then clear the input struct and
     * seek back to the beginning of the file. */
    if (code != 0) {
        huff_free_hdrtable(header);
        fseek(file, 0L, SEEK_SET);
    }

    return code;
}

static int _huff_read_header(FILE * file, char * filename, struct huff_header * header) {
    if (! has_huff_ext(filename)) {
        return EBADEXT;
    }

    if (! has_huff_magic(file)) {
        return ENOMAGIC;
    }

    /* read out the number of bytes. If the file is too short, return ETRUNC. */
    if (! fread(&header->length, sizeof(uint64_t), 1, file)) {
        return ETRUNC;
    }

    /* Attempt to decode the translation table stored in the top of the file.
     * If decoding an entry fails, return that error code. */
    int code = 0;
    for (int i = 0; i < 256; i++) {
        code = huff_read_entry(file, &header->table[i]);
        if (code != 0) { return code; }
    }

    return 0;
}

int huff_write_header(FILE * file, struct huff_header * header) {
    if (! (fwrite(HUFF_MAGIC, HUFF_MAGICLEN, 1, file) &&
           fwrite(&header->length, sizeof(uint64_t), 1, file))) {
        return ENOWRITE;
    }

    /* buffer needs to be at least 255+1 bytes long since we need to store
     * the newline as well. */
    char buffer[257];
    for (int i = 0; i < 256; i++) {
        assert(header->table[i] != 0 && "Translation table had null pointer.");

        size_t entry_length = strlen(header->table[i]);
        assert(entry_length <= 255 && "Translation table string larger than buffer size.");

        memcpy(buffer, header->table[i], entry_length);
        buffer[entry_length] = '\n';
        if (! fwrite(buffer, entry_length + 1, 1, file)) {
            return ENOWRITE;
        }
    }

    return 0;
}

int huff_free_hdrtable(struct huff_header * header) {
    for (int i = 0; i < 256; i++) {
        free(header->table[i]);
    }
    memset(header->table, 0, 256 * sizeof(char *));
    return 0;
}
