#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "common.h"

static const char * const ERROR_STRINGS[] = {
    [-EBADEXT]      = "Extension was not a .huff extension.",
    [-ENOMAGIC]     = "No magic number in the input file.",
    [-EBADENTRY]    = "Bad entry in file translation table.",
    [-ETRUNC]       = "Input file ended before we finished reading.",
    [-EENTRY]       = "Impropery formatted translation table entry.",
    [-ENOWRITE]     = "An error occured while writing to the output file.",
    [-EFILETOOLONG] = "Input file's size could not be represented. Kudos on making"
                      "a file larger than 16,384 Petabytes.",
};

const char * huff_error(int code) {
    return ERROR_STRINGS[-code];
}

void * xmalloc(size_t size) {
    void * out = malloc(size);
    if (out == NULL) {
        fputs("Out of memory.\n", stderr);
        exit(HUFF_FAILURE);
    }
    return out;
}

void * xrealloc(void * ptr, size_t size) {
    void * out = realloc(ptr, size);
    if (out == NULL && size != 0) {
        fputs("Out of memory.\n", stderr);
        exit(HUFF_FAILURE);
    }
    return out;
}

/* fopen the given file, print an error message and terminate with
 * HUFF_FAILURE if we're unable to open the file. */
FILE* xfopen(const char * path, const char * mode) {
    FILE *file = fopen(path, mode);
    if (file == NULL) {
        if (errno == ENOENT) {
            fprintf(stderr, "Couldn't open '%s'.\n", path);
        } else {
            perror("Error opening file");
        }
        exit(HUFF_FAILURE);
    }
    return file;
}

int pfclose(FILE * file) {
    if (fclose(file) != 0) {
        perror("Couldn't close output file");
        return -1;
    }
    return 0;
}
