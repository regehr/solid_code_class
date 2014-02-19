#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "huff.h"
#include "huff_table.h"
#include "util.h"

/*
 * "Do something reasonable." ~ A Certain Professor
 */
int main(int argc, char* argv[])
{
  //Initial check for correct arg count
  if(argc != 3) {
    fprintf(stderr, "Invalid number of parameters. Huff requires a flag (-c, -d, -t), and a filename as parameters.\n");
    return ERR;
  }
  
  //Determine flag and filename
  enum Flags given_flag = determine_flag(argv[1]);
  char* filename = argv[2];
  
  FILE* file = open_file(filename, "r");
  
  switch(given_flag) {
  case COMPRESS:
    compress(file, filename);
    break;
  case DECOMPRESS:
    decompress(file, filename);
    break;
  case DUMP:
    dump(file, filename);
    break;
  case INVALID:
    fprintf(stderr, "Invalid flag given. Expected one of the following: -c, -d, -t.\n");
    return ERR;
  }
  
  fclose(file);
  
  return 0;
}

FILE* open_file(char* filename, char* permission) {
  //Attempt to open the file
  FILE* file = fopen(filename, permission);
  
  //Ensure we can open the file
  if (file == NULL) {
    fprintf(stderr, "Unable to open file: %s, with given permission: %s\n", filename, permission);
    exit(ERR);
  }
  
  return file;
}

void compress(FILE* file, char* filename) {
  int fname_len = strlen(filename);
  int ext_len = strlen(EXT);
  // Make room for a new filename
  char new_filename[fname_len + ext_len + 1];
  strncpy(new_filename, filename, fname_len + 1);
  //Cat filename with extension
  strncat(new_filename, EXT, ext_len);
  
  //Open the file
  FILE* comp_file = open_file(new_filename, "w");
  
  unsigned long long size = det_file_size(file);
  
  int i;
  unsigned long long freq_table[256];
  for(i = 0; i < 256; i++)
    freq_table[i] = 0;
  
  //Determine frequency/encoding tables
  create_freq_table(freq_table, file, size);	
  huff_node* huff_tree = create_huff_tree_from_frequency(freq_table);
  char **encoded_table = get_encoding(huff_tree);
  
  
  assert(encoded_table != NULL);
  
  //Write data
  write_compressed_file(comp_file, file, encoded_table, size);
  
  //Close the file
  fclose(comp_file);
  
  //free memory
  destroy_huff_tree(huff_tree);
  free(encoded_table);
}

void decompress(FILE* file, char* filename) {
  //Check if file isnt a .huff
  if(!is_huff_type(filename)) {
    fprintf(stderr, "Given file is not a .huff\n");
    exit(ERR);
  }
  
  char *encoding[256];
  int i;
  
  for(i = 0; i < 256; i++) {
    encoding[i] = (char *)xmalloc(sizeof(char) * 257);
    assert(encoding[i] != NULL);
    }
  
  //Get huff table from file
  unsigned long long file_size;
  get_huff_table(encoding, file, &file_size);
  
  assert(encoding != NULL);
    
  //Create tree based on huff table
  huff_node* huff_tree = create_huff_tree_from_encoding(encoding);
  
  //Determine filename without the .huff extension
  int len = strlen(filename);
  int ext_len = strlen(".huff");
  filename[len-ext_len] = '\0';
  
  //Open new file
  FILE* decomp_file = open_file(filename, "w");
  
  unsigned long long byte_count = 0;
  uint8_t curr_byte;
  int decoded_bit;
  
  //Loop through encoded data, decode it and add to new file
  while(fread(&curr_byte, 1, 1, file) &&  byte_count < file_size) {
    for(i = 7; (i >= 0) && (byte_count < file_size); i++) {
      decoded_bit = get_next_character(huff_tree, (curr_byte >> i)&0x1);
      
      if(decoded_bit > -1) {
	byte_count++;
    	
	//Write decompressed data to file
	int res = fwrite(&decoded_bit, 1, 1, decomp_file);    			
	assert(res == 1 && "Failed to write decoded information to file.");
      }
    }
  }
  
  rewind(decomp_file);
  unsigned long long final_size = det_file_size(decomp_file);
  
  assert(file_size == final_size && "Compressed size information and decompressed file size don't match.");
  
  //Close the file
  fclose(decomp_file);
  
  destroy_huff_tree(huff_tree);
  free(encoding);
}

void dump(FILE* file, char* filename)
{
  int i;		
  unsigned long long file_size = det_file_size(file);
  
  //Check if file is .huff
  if(is_huff_type(filename)) {
    char *encoded_table[256];
    
    for(i = 0; i < 256; i++) {
      encoded_table[i] = (char *)xmalloc(sizeof(xmalloc) * 257);
      assert(encoded_table[i] != NULL);
    }
    
    file_size = det_file_size(file);
    get_huff_table(encoded_table, file, &file_size);
    
    assert(encoded_table != NULL);
    
    for(i = 0; i < 256; i++)
      printf("%s\n", encoded_table[i]);
  }
  else {
    unsigned long long freq_table[256];
    for(i = 0; i < 256; i++)
      freq_table[i] = 0;
    
    create_freq_table(freq_table, file, file_size);	
    huff_node* huff_tree = create_huff_tree_from_frequency(freq_table);
    char** encoded_table = get_encoding(huff_tree);
    assert(encoded_table != NULL);
    for(i = 0; i < 256; i++) {
      printf("%s\n", encoded_table[i]);
    }
    destroy_huff_tree(huff_tree);
    free(encoded_table);
  }
}

void create_freq_table(unsigned long long table[], FILE* file, unsigned long long size) {
  unsigned long long i;
  int c;
  
  for(i = 0; i < size; i++) {
    c = fgetc(file);
    if (c < 0) {
      fprintf(stderr, "Fgetc error: exiting.\n");
      exit(ERR);
    }
    table[c]++;
  }
}

bool is_huff_type(char* filename) {
  //Last occurance of "."
  char* file_type = strrchr(filename, '.');
  
  //Error check
  if(file_type == NULL)
    return false;
  
  //Compare with huff extension
  return (strcmp(file_type, EXT) == 0);
}

unsigned long long det_file_size(FILE* file) {
  //Go to end
  fseek(file, 0L, SEEK_END);
  
  //Count bytes
  unsigned long long file_length = ftell(file);
  
  //Rewind file
  rewind(file);
  
  return file_length;
}

void get_huff_table(char** huff_table, FILE* file, unsigned long long* size) {
  //Need to read in 4 bytes rather than string
  //Since magic number doesnt end in \n
  char magic_num[5];
  int i, j;
  
  //Read magic number
  for(i = 0; i < 4; i++) {
    magic_num[i] = fgetc(file);
    assert(magic_num[i]);
  }
  magic_num[4] = '\0';
  
  //If not the proper number
  if(strcmp(magic_num, NUM) != 0) {
    fprintf(stderr, "Improper huff magic number.\n");
    exit(ERR);
  }
  
  //Get huff length
  unsigned long long res = fread(size, 8, 1, file);
  fprintf(stderr, "size = %llu\n", res);
  
  //Check that we read a file length
  if(res != 1) {
    fprintf(stderr, "Improper huff uncompressed file length.\n");
    exit(ERR);
  }
  
  //Generate the encoded table
  char longest_string[257];
  int curr_char;
  
  //For each huffman table entry
  for(i = 0; i < 256; i++) {
    //For each char in the string
    for(j = 0; j < 257; j++) {
      curr_char = fgetc(file);
      
      //Regular char
      if(curr_char != '\n')
	longest_string[j] = curr_char;
      //Convert newline to null terminated char
      else {
	longest_string[j] = '\0';
	break;
      }
    }
    
    strcpy(huff_table[i], longest_string);
  }
}

enum Flags determine_flag(char* user_flag) {
  if(strcmp(user_flag, "-c") == 0)
    return COMPRESS;
  else if(strcmp(user_flag, "-d") == 0)
    return DECOMPRESS;
  else if(strcmp(user_flag, "-t") == 0)
    return DUMP;
  else
    return INVALID;
}

void write_compressed_file(FILE* comp_file, FILE* orig_file, char** encoded_table, unsigned long long file_size) {
  int res;
  // Write magic number
  // Apparently fprintf is used for strings?
  res = fprintf(comp_file, "%s", NUM);
  if (res < 0) {
    fprintf(stderr, "File write error: exiting.\n");
    exit(ERR);
  }
  // Write file size
  // And fwrite is for binary data >.>
  res = xfwrite(&file_size, 8, 1, comp_file);
  
  // Write encoded table
  // Also, fputs apparently appends "\n" for you, what the hell C
  int i;
  for(i = 0; i < 256; i++) {
    res = fputs(encoded_table[i], comp_file);
    if (res < 0) {
      fprintf(stderr, "File write error: exiting.\n");
      exit(ERR);
    }
    res = fputc(10, comp_file);
    if (res < 0) {
      fprintf(stderr, "File write error: exiting.\n");
      exit(ERR);
    }
  }
  
  // Write compressed data
  rewind(orig_file);
  
  int curr_char;
  char* encoded_char;
  curr_char = fgetc(orig_file);
  
  while(curr_char != EOF) {
    encoded_char = encoded_table[(int)curr_char];
    
    unsigned char byte_version = (unsigned char)strtol(encoded_char, NULL, 2) & 0xFF;
		
    int write_res = fputc(byte_version, comp_file);
    // int write_res = fputs(encoded_char, comp_file);
    assert(write_res != EOF && "Error occured when writing huff body.");
    
    curr_char = fgetc(orig_file);
  }
}
