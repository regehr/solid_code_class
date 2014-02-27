#include <stdlib.h>
#include <stdio.h>
#include "huff.h"

void *xmalloc(size_t size) {
  void *ptr = malloc(size);
  if (ptr == NULL) {
    fprintf(stderr, "malloc error: exiting.\n");
    exit(ERR);
  }
  return ptr;
}

void *xrealloc(void *ptr, size_t size) {
  void *new_ptr = realloc(ptr, size);
  if (new_ptr == NULL) {
    fprintf(stderr, "realloc error: exiting.\n");
    free(ptr);
    exit(ERR);
  }
  return new_ptr;
}

size_t xfwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
  size_t result = fwrite(ptr, size, nmemb, stream);
  if (result < nmemb) {
    fprintf(stderr, "File write error: exiting.\n");
    exit(ERR);
  }
  return result;
}
