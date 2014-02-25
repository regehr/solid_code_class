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
#include "rle.h"


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


unsigned char *openFile(char *file_name, unsigned long long *file_length)
{
    /* Open the file in a buffer */
    
    struct stat sb;
    if(stat(file_name, &sb) < 0)
    {
        printf("File not found\n");
        exit(-1);
    }
    
    FILE *file = fopen(file_name, "r");
    if(file == NULL)
    {
        printf("Error opening file\n");
        exit(-1);
    }
    *file_length = sb.st_size;
    
    unsigned char* file_pointer = malloc(*file_length * sizeof(unsigned char));
    if(file_pointer == NULL)
    {
        printf("Malloc failed, exiting.\n");
        exit(-1);
    }
    
    if(file_length != 0)
    {
        if(!fread(file_pointer, *file_length, 1, file))
        {
            printf("Error reading file\n");
            exit(-1);
        }
        fclose(file);
    }
    return file_pointer;
    
        
}

/* Entry point for the program. Opens the file, and executes the mode specified by command line args */
int main(int argc, char* argv[])
{
  if(argc != 3 || (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-d") != 0 && strcmp(argv[1], "-t") != 0))
  {
    printf("usage: huff [-c | -d | -t] file\n");
    return -1;
  }


  /* Execute the correct mode */
  if(strcmp(argv[1], "-c") == 0)
  {
   //append the extension to the name
    char *tempFile = malloc(sizeof(char) * strlen(argv[2])+5);
    strncpy(tempFile, argv[2], strlen(argv[2]));
    strcat(tempFile, ".temp");
      
    //RLE encode the file
    rle_encode(argv[2], tempFile);
      
    //create a vairiable to hold hold the file length
      unsigned long long fileLength = 0;
      
      //get a buffer of the contents of the file as a unsigned char*
      unsigned char *file_pointer = openFile(tempFile, &fileLength);
      
      //huff compress the output.
      compress(file_pointer, fileLength, argv[2]);
      free(file_pointer);
      free(tempFile);
      remove(tempFile);
      
  }
  else if(strcmp(argv[1], "-d") == 0)
  {
      unsigned long long fileLength = 0;
      unsigned char *file_pointer = openFile(argv[2], &fileLength);
      decompress(file_pointer, fileLength, argv[2]);
      
      //remove the .hurl extension from the fileName;
      char *tempFileName = calloc(strlen(argv[2]), sizeof(char));
      strncpy(tempFileName, argv[2], strlen(argv[2]) - strlen(".hurl"));
      strncat(tempFileName, ".temp", sizeof(".temp"));
      
      char *outputFileName = calloc(sizeof(char), strlen(argv[2]));
      strncpy(outputFileName, argv[2], strlen(argv[2]));
      outputFileName[strlen(outputFileName) -5] = '\0';
      
      rle_decode(tempFileName, outputFileName);
      free(file_pointer);
      remove(tempFileName);
  }
  else if(strcmp(argv[1], "-t") == 0)
  {
      unsigned long long fileLength = 0;
      unsigned char *file_pointer = openFile(argv[2], &fileLength);
      print_table(file_pointer, fileLength, argv[2]);
      free(file_pointer);
      
  }
    
    // free(file_pointer);
    return 0;
}


