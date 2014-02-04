#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <assert.h>
#include "io.h"

int index_of(char* arr[256], char* string)
{
  for(int i = 0; i < 256; i++)
  {
    if(strcmp(arr[i], string) == 0)
    {
      return i;
    }
  }
  return -1;
}

int bit_at(unsigned char* pointer, size_t length, unsigned long long index)
{
  if(index/8 >= length)
    return -1;
  unsigned char byte = pointer[index/8];
  int remaining = index % 8;
  return (byte >> (7 - remaining)) & 0x1;
}

unsigned long long get_size_from_file(unsigned char* file_pointer, size_t file_length)
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

void write_compressed_file(unsigned char* file_pointer, size_t file_length, char* filename, char* mapping)
{
  /* Make a copy of the mapping */
  char orig_mapping[strlen(mapping)+1];
  strcpy(orig_mapping, mapping);

  /* Convert string to array */
  char* map[256];
  char* pch = strtok(mapping, "\n");
  map[0] = pch;
  int index = 1;
  while(pch != NULL)
  {
    pch = strtok(NULL, "\n");
    if(pch != NULL)
      map[index++] = pch;
  }

  /* Figure out how large our array needs to be */
  unsigned long long array_size = 0;
  for(unsigned long long i = 0; i < file_length; i++)
  {
    array_size += strlen(map[file_pointer[i]]);
  }

  /* Use the map to get the string we need to write */
  char to_write_strings[array_size]; 
  unsigned long long count = 0;
  for(unsigned long long i = 0; i < file_length; i++)
  {
    char* mapped = map[file_pointer[i]];
    int j = 0;
    while(mapped[j] != '\0')
    {
      to_write_strings[count++] = mapped[j++];
    }
  }
 
  /* Convert String array to Byte array. */
  unsigned char to_write[(array_size/8)+1];
  for(unsigned long long i = 0; i < array_size/8; i++)
  {
    char curr_string[9];
    for(int j = 0; j < 8; j++)
    {
      curr_string[j] = to_write_strings[(i*8)+j];
    }
    curr_string[8] = '\0';
    to_write[i] = (unsigned char)(strtol(curr_string, NULL, 2) & 0xFF);
  }
  char remaining[9] = {0};
  for(unsigned long long i = 0; i < array_size%8; i++)
  {
    remaining[i] = to_write_strings[(array_size-(array_size%8))+i];
  }
  to_write[array_size/8] = (unsigned char)(strtol(remaining, NULL, 2) & 0xFF) << (8-array_size%8);

  /* Append .huff to filename and write out file with header */
  char new_filename[strlen(filename) + 6];
  strcpy(new_filename, filename);
  strcat(new_filename, ".huff");

  FILE* f = fopen(new_filename, "w");
  char* magic_number = "HUFF";
  fwrite(magic_number, sizeof(char), strlen(magic_number), f);
  fwrite(&file_length, sizeof(size_t), 1, f);
  fwrite(orig_mapping, sizeof(char), strlen(orig_mapping), f);
  fwrite(to_write, sizeof(unsigned char), array_size/8+1, f);
  fclose(f);
}

void write_decompressed_file(unsigned char* file_pointer, size_t file_length, char* filename, char* mapping, unsigned long long start_of_compressed)
{
  /* Convert string to array */
  char* map[256];
  char* pch = strtok(mapping, "\n");
  map[0] = pch;
  int index = 1;
  while(pch != NULL)
  {
    pch = strtok(NULL, "\n");
    if(pch != NULL)
      map[index++] = pch;
  }
  unsigned long long size = get_size_from_file(file_pointer, file_length);
  unsigned long long bit_index = (start_of_compressed+1)*8;
  unsigned char to_write[size];
  unsigned long long to_write_index = 0;
   
  for(int i = 0; i < size; i++)
  {
   int string_index = 0;
   char curr_string[257] = {0};
   int complete = 0;
   while(!complete)
   {
     assert(string_index < 256);
     assert(bit_at(file_pointer, file_length, bit_index) != -1);

     if(bit_at(file_pointer, file_length, bit_index++))
       curr_string[string_index++] = '1';
     else
     {
       curr_string[string_index++] = '0';
     }
     int index = index_of(map, curr_string);
     if(index != -1)
     {
       assert(index < 256);
       assert(to_write_index <= size);
       to_write[to_write_index++] = (unsigned char)index;
       complete = 1;
      }
    }
  }

  /* Remove.huff and write out file */
  filename[strlen(filename)-5] = '\0';
  FILE* f = fopen(filename, "w");
  fwrite(to_write, sizeof(unsigned char), size, f);
  fclose(f);
  
  
}

int check_format(unsigned char* file_pointer, size_t file_length, char* filename)
{
  if(strlen(filename) <= 5 || strcmp(filename + strlen(filename) - 5, ".huff") != 0)
  {
    return 0;
  }

  char* magic_number = "HUFF";

  for(unsigned long long i = 0; i < strlen(magic_number); i++)
  {
    if((i >= file_length) || (file_pointer[i] != magic_number[i]))
    {
      return 0;
    }
  }
  
  return 1;
}

char* get_mapping_from_file(unsigned char* file_pointer, size_t file_length, unsigned long long* start_of_compressed)
{
  char* table = calloc(33153, sizeof(char));
  unsigned long long pos = 0;
  int newline_count = 0;
  while(newline_count < 256)
  {
    table[pos] = (char)(file_pointer[pos+12]);
    pos++;
    if(file_pointer[pos+12] == '\n')
    { 
      newline_count++;
    }
  }
  table[pos] = '\0';
  *start_of_compressed = pos+12;
  return table;
}

