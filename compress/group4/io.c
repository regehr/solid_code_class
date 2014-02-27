/* Daniel Setser
 * Date: February 2014
 * 
 * File implementing I/O functions needed for huffman encoding
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <assert.h>
#include "tree.h"
#include "io.h"

/* Finds the number of times each character appears in a file */
void find_frequencies(unsigned long long frequencies[256], unsigned char* file_pointer, unsigned long long file_length)
{
  for(unsigned long long i = 0; i < file_length; i++)
  {
    frequencies[file_pointer[i]]++;
  }
}

/* Returns the bit at a given index in an array, or -1 if out of range */
static int get_bit(unsigned char* pointer, unsigned long long length, unsigned long long index)
{
  if(index/8 >= length)
    return -1;
  return (pointer[index/8] >> (7 - (index%8))) & 0x1;
}

/* Sets the specified bit in the given array */
static void put_bit(unsigned char* buffer, unsigned long long index, int bit)
{
  buffer[index/8] = buffer[index/8] | (bit << (7-(index%8)));
}

/* Converts mapping of characters to huffman encodings from string to string array */
static void get_map_from_table(char* map[256], char* mapping)
{
  char* curr_string = strtok(mapping, "\n");
  map[0] = curr_string;
  int index = 1;
  while(curr_string != NULL)
  {
    curr_string = strtok(NULL, "\n");
    if(curr_string != NULL)
    {
      assert(index < 256);
      map[index++] = curr_string;
    }
  }
}

/* Returns the number of huffman encodings this compressed file should have */
static unsigned long long get_size_from_file(unsigned char* file_pointer, unsigned long long file_length)
{
  unsigned char num[8];
  for(int i = 0; i < 8; i++)
  {
    num[i] = file_pointer[i+4];
  }
  unsigned long long value = 
  (unsigned long long)(num[0]) |
  (unsigned long long)(num[1]) << 8 |
  (unsigned long long)(num[2]) << 16 |
  (unsigned long long)(num[3]) << 24 |
  (unsigned long long)(num[4]) << 32 |
  (unsigned long long)(num[5]) << 40 |
  (unsigned long long)(num[6]) << 48 |
  (unsigned long long)(num[7]) << 56;
  
  return value;
}

/* Error checking call to fwrite */
static void Fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream)
{
  if(fwrite(ptr, size, nmemb, stream) != nmemb)
  {
    printf("Error writing file.\n");
    exit(-1);
  }
}

/* Uses the mapping to write the compressed file */
void write_compressed_file(unsigned char* file_pointer, unsigned long long file_length, char* filename, char* mapping)
{
  char orig_mapping[strlen(mapping)+1];
  strcpy(orig_mapping, mapping);

  char* map[256];
  get_map_from_table(map, mapping);

  unsigned long long array_size = 0;
  for(unsigned long long i = 0; i < file_length; i++)
  {
    array_size += strlen(map[file_pointer[i]]);
  }
  if(array_size%8 == 0)
    array_size = array_size/8;
  else
    array_size = (array_size/8)+1;

  /* Use the map to convert from bytes to huffman codes */
  unsigned char* to_write = calloc(array_size, sizeof(unsigned char));
  unsigned long long count = 0;
  for(unsigned long long i = 0; i < file_length; i++)
  {
    char* mapped = map[file_pointer[i]];
    int j = 0;
    while(mapped[j] != '\0')
    {
      assert(count < array_size*8);
      if(mapped[j++] == '0')
        put_bit(to_write, count++, 0);
      else
        put_bit(to_write, count++, 1);
    }
  }
 
  /* Append .huff to filename and write out file with header */
  char new_filename[strlen(filename) + 6];
  strcpy(new_filename, filename);
  strcat(new_filename, ".hurl");

  FILE* f = fopen(new_filename, "w");
  if(f == NULL)
  {
    printf("Error opening file to write\n");
    exit(-1);
  }

  char* magic_number = "HURL";
  Fwrite(magic_number, sizeof(char), strlen(magic_number), f);
  Fwrite(&file_length, sizeof(unsigned long long), 1, f);
  Fwrite(orig_mapping, sizeof(char), strlen(orig_mapping), f);
  if(array_size != 0)
    Fwrite(to_write, sizeof(unsigned char), array_size, f);

  fclose(f);
  free(to_write);
}

/* Uses the mapping to write the original file */
void write_decompressed_file(unsigned char* file_pointer, unsigned long long file_length, char* filename, char* mapping, unsigned long long start_of_compressed)
{
  char* map[256];
  get_map_from_table(map, mapping);
  
  tree root = get_huffman_tree(map);

  unsigned long long size = get_size_from_file(file_pointer, file_length);
  unsigned long long bit_index = (start_of_compressed+1)*8;
  unsigned char* to_write = malloc(size * sizeof(unsigned char));
  if(to_write == NULL)
  {
    printf("Malloc failed, exiting.\n");
    exit(-1);
  }  
 
  unsigned long long to_write_index = 0;
   
  /* Traverse the tree to convert huffman codes to original bytes */
  for(int i = 0; i < size; i++)
  {
   tree current_node = root;
   while(1)
   {
     if(current_node->one == NULL)
     {
       to_write[to_write_index++] = current_node->ascii;
       break;
     }

     int bit = get_bit(file_pointer, file_length, bit_index++);
     assert(bit != -1);

     if(bit)
     {
       assert(current_node->one != NULL);
       current_node = current_node->one;
     }
     else
     {
       assert(current_node->zero != NULL);
       current_node = current_node->zero;
     }
    }
  }
  free_tree(root);

  /* Remove.huff and write out file */
  filename[strlen(filename)-5] = '\0';
  strncat(&filename[strlen(filename)],".temp",strlen(".temp"));
  FILE* f = fopen(filename, "w");
  if(f == NULL)
  {
    printf("Error opening file to write\n");
    exit(-1);
  }
  Fwrite(to_write, sizeof(unsigned char), size, f);
  fclose(f);
  free(to_write);
}

/* Returns whether or not the file is in huff format */
int check_format(unsigned char* file_pointer, unsigned long long file_length, char* filename)
{
  if(strlen(filename) <= 5 || strcmp(filename + strlen(filename) - 5, ".hurl") != 0)
  {
    return 0;
  }

  char* magic_number = "HURL";

  for(unsigned long long i = 0; i < strlen(magic_number); i++)
  {
    if((i >= file_length) || (file_pointer[i] != magic_number[i]))
    {
      return 0;
    }
  }
  
  return 1;
}

/* Returns the table found in a file, and sets start_of_compressed to the start of the compressed output */
char* get_mapping_from_file(unsigned char* file_pointer, unsigned long long file_length, unsigned long long* start_of_compressed)
{
  char* table = calloc(33153, sizeof(char));
  if(table == NULL)
  {
    printf("Calloc failed, exiting.\n");
    exit(-1);
  }  
  unsigned long long pos = 0;
  int newline_count = 0;
  while(newline_count < 256)
  {
    assert(pos < 33153);
    table[pos] = (char)(file_pointer[pos+12]);
    pos++;
    assert(pos+12 < file_length);
    if(file_pointer[pos+12] == '\n')
    { 
      newline_count++;
    }
  }
  *start_of_compressed = pos+12;
  return table;
}

