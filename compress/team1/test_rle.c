#include "rle.h"

int main(int argc, char* argv[])
{
  FILE *fp;
  fp = fopen(argv[1], "r");
  if(fp == NULL) {
    fprintf(stderr, "ERROR: Could not open file\n");
    exit(255);
  }

  unsigned char* bytes;
  unsigned long long len;
  encode_rle(fp, bytes, &len);

  int i;
  for(i = 0; i < len; i++) {
    printf("hex: %x for index: %d\n", bytes[i], i);
  }

  return 0;
}
