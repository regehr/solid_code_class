#ifndef HUFF_UTIL_H
#define HUFF_UTIL_H

#include <stdio.h>

void *xmalloc(size_t size);
void *xrealloc(void *ptr, size_t size);
size_t xfwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

#endif
