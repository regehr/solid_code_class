#include <stdlib.h>
#include "huff.h"

void *xmalloc(size_t size) {
  void *ptr = malloc(size);
  if (ptr == NULL) {
    fprintf(stderr, "Malloc error: exiting.\n");
    exit(ERR);
  }
  return ptr;
}

size_t xfwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
  size_t result = fwrite(ptr, size, nmemb, stream);
  if (result < nmemb) {
    fprintf(stderr, "File write error: exiting.\n");
    exit(ERR);
  }
  return result;
}
