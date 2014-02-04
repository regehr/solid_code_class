#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include "huff_table.h"

int main (int argc, char *argv[])
{
  srand (getpid() + time (NULL));
  
  if (argc != 3) {
  	printf("Must have 2 arguments, -t, -c, or -d filename\n");
    exit (255);
  }

  FILE *input = NULL;
  
  input = fopen(argv[2], "r");
  
  if(input == NULL) {
  	printf("Couldn't open file, error code: %i\n", errno);
  	exit(255);
  }
  
  if(strncmp(argv[1], "-t", 2) == 0) {
  	print_huff_table(input);
  } else if(strncmp(argv[1], "-c", 2) == 0) {
  	printf("Compress to come soon");  	
  } else if(strncmp(argv[1], "-d", 2) == 0) {
  	printf("Decompress to come soon");
  } else {
  	printf("First argument must be -t, -c or -d\n");
  	exit(255); 
  }
  
  fclose(input);
  exit(0);
}

