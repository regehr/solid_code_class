/* Daniel Setser
 * Date: February 2014
 * 
 * Entry point for huffman encoding implementation
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "tree.h"
#include "io.h"

/* Compresses the file and writes out the new huff file */
void compress(unsigned char* file_pointer, unsigned long long file_length, char* filename)
{
  unsigned long long frequencies[256] = {0}; 
  find_frequencies(frequencies, file_pointer, file_length);

  char* mapping = get_huffman_table(frequencies);
  write_compressed_file(file_pointer, file_length, filename, mapping);
  free(mapping);
}

/* Decompresses the huff file and writes out the original file */
void decompress(unsigned char* file_pointer, unsigned long long file_length, char* filename)
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

/* Prints out the table mapping bytes to huffman codes */
void print_table(unsigned char* file_pointer, unsigned long long file_length, char* filename)
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
    unsigned long long frequencies[256] = {0}; 
    find_frequencies(frequencies, file_pointer, file_length);

    char* mapping = get_huffman_table(frequencies);
    printf("%s", mapping);
    free(mapping);
  }
}

/* Entry point for the program. Opens the file, and executes the mode specified by command line args */
int main(int argc, char* argv[])
{
  if(argc != 3 || (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-d") != 0 && strcmp(argv[1], "-t") != 0))
  {
    printf("usage: huff [-c | -d | -t] file\n");
    return -1;
  }

  /* Open the file in a buffer */
  unsigned long long file_length;
  struct stat sb;
  if(stat(argv[2], &sb) < 0)
  {
    printf("File not found\n");
    exit(-1);
  }

  FILE* file = fopen(argv[2], "r");
  if(file == NULL)
  {
    printf("Error opening file\n");
    exit(-1);
  }
  file_length = sb.st_size;

  unsigned char* file_pointer = malloc(file_length * sizeof(unsigned char));
  if(file_pointer == NULL)
  {
    printf("Malloc failed, exiting.\n");
    exit(-1);
  }

  if(file_length != 0)
  {
    if(!fread(file_pointer, file_length, 1, file))
    {
      printf("Error reading file\n");
      exit(-1);
    }
    fclose(file);
  }

  /* Execute the correct mode */
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
