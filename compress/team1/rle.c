#include "rle.h"

static void read_char_error() {
  fprintf(stderr, "ERROR: Error while reading a character from original file.\n");
  exit(ERR_CODE);
}

static void malloc_error() {
  fprintf(stderr, "ERROR: Error while allocating space for array.\n");
  exit(ERR_CODE);
}

void encode_rle(FILE* file, char* to_return, unsigned long long num_bytes)
{
  int c, i, freq;
  char* bytes;

  // Malloc space for array and check that there wasn't an error
  if((bytes =  malloc(sizeof(char) * SIZE)) == NULL) {
    malloc_error();
  }

  do {
    c = fgetc(file);
    if(ferror(file)) { read_char_error(); }
    if(c != EOF) {
      
    }
  } while (c != EOF);
}
