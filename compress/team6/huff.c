#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "tree.h"
#include "io.h"

void compress(unsigned char* file_pointer, size_t file_length, char* filename)
{
  /* Find the frequency of each char */
  unsigned long long frequencies[256] = {0}; 
  for(unsigned long long i = 0; i < file_length; i++)
  {
    frequencies[file_pointer[i]]++;
  }

  char* mapping = get_huffman_table(frequencies);
  write_compressed_file(file_pointer, file_length, filename, mapping);
  free(mapping);
}

void decompress(unsigned char* file_pointer, size_t file_length, char* filename)
{
  if(!check_format(file_pointer, file_length, filename))
  {
    printf("Can't decompress a non-huff file.\n");
    exit(-1);
  }  

  unsigned long long start_of_compressed;
  char* mapping = get_mapping_from_file(file_pointer, file_length, &start_of_compressed);
  write_decompressed_file(file_pointer, file_length, filename, mapping, start_of_compressed);
  free(mapping);
}

void print_table(unsigned char* file_pointer, size_t file_length, char* filename)
{
  /* If this is a huff file, get it from the table in the file. Otherwise calculate it from the file */
  if(check_format(file_pointer, file_length, filename))
  {
    unsigned long long start_of_compressed;
    char* mapping = get_mapping_from_file(file_pointer, file_length, &start_of_compressed);
    printf("%s\n", mapping);
    free(mapping);
  }
  else
  {
    /* Find the frequency of each char */
    unsigned long long frequencies[256] = {0}; 
    for(unsigned long long i = 0; i < file_length; i++)
    {
      frequencies[file_pointer[i]]++;
    }
    char* mapping = get_huffman_table(frequencies);
    printf("%s", mapping);
    free(mapping);
  }
}

int main(int argc, char* argv[])
{
  if(argc != 3 || (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-d") != 0 && strcmp(argv[1], "-t") != 0))
  {
    printf("usage: huff [-c | -d | -t] file\n");
    return -1;
  }

  /* Open the file in a buffer */
  size_t file_length;
  struct stat sb;

  if(stat(argv[2], &sb) < 0)
  {
    printf("File not found\n");
    exit(-1);
  }
  FILE* file = fopen(argv[2], "r");
  file_length = sb.st_size;
  if(file == NULL)
  {
    printf("Error opening file\n");
    exit(-1);
  }
  unsigned char* file_pointer = (unsigned char*)malloc(file_length * sizeof(unsigned char));
  if(file_length != 0)
  {
    fread(file_pointer, file_length, 1, file);
    fclose(file);
  }

  /* Compress, decompress, or print the mapping table depending on the flag */
  if(strcmp(argv[1], "-c") == 0)
  {
    compress(file_pointer, file_length, argv[2]);
  }
  else if(strcmp(argv[1], "-d") == 0)
  {
    decompress(file_pointer, file_length, argv[2]);
  }
  else if(strcmp(argv[1], "-t") == 0)
  {
    print_table(file_pointer, file_length, argv[2]);
  }

  free(file_pointer);
  return 0;
}
