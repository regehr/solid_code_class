#include <stdio.h>
#include <stdlib.h>
#include "internal.h"

void * xmalloc(size_t size) {
    void * out = malloc(size);
    if (out == NULL) {
        fputs("Out of memory.\n", stderr);
        exit(HUFF_FAILURE);
    }
    return out;
}
