#include "rle.h"

int main(int argc, char* argv[])
{
  FILE *fp;
  fp = fopen(argv[1], "r");
  if(fp == NULL) {
    fprintf(stderr, "ERROR: Could not open file\n");
    exit(255);
  }

  unsigned char* bytes = NULL;
  unsigned long long len = 0;
  encode_rle(fp, &bytes, &len);

  /*int i;
  for(i = 0; i < len; i++) {
    printf("hex: %x for index: %d\n", bytes[i], i);
  }
  */

  FILE * out = fopen("output_file.txt", "w");
  if(out != NULL) {
    decode_rle(bytes, &len, out);
    if(fclose(out) == EOF) {
      printf("ERROR: Error while trying to close output file.\n");
    }
  }

  free(bytes);
  return 0;
}
