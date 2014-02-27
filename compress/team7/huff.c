#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "huff.h"
#include "huff_table.h"
#include "util.h"
#include "rle.h"

/*
 * "Do something reasonable." ~ A Certain Professor
 */
int main(int argc, char *argv[])
{
  //Initial check for correct arg count
  if(argc != 3) {
    fprintf(stderr, "Invalid number of parameters: rhuff requires a flag (-c, -d, -t), and a filename as parameters.\n");
    return ERR;
  }
  
  //Determine flag and filename
  enum Flags given_flag = determine_flag(argv[1]);
  char *filename = argv[2];
  
  FILE *file = open_file(filename, "r");

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

FILE *open_file(char *filename, char *permission) {
  //Attempt to open the file
  FILE *file = fopen(filename, permission);
  
  //Ensure we can open the file
  if (file == NULL) {
    fprintf(stderr, "Unable to open file: %s, with given permission: %s\n", filename, permission);
    exit(ERR);
  }
  
  return file;
}

void compress(FILE *file, char *filename) {
  size_t fname_len = strlen(filename);
  size_t ext_len = strlen(EXT);
  // Make room for a new filename
  char *new_filename = (char *)xmalloc(fname_len + ext_len + 1);
  strncpy(new_filename, filename, fname_len + 1);
  //Cat filename with extension
  strncat(new_filename, EXT, ext_len + 1);
  
  //Open the file
  FILE *comp_file = open_file(new_filename, "w");
  free(new_filename);
  
  unsigned long long freq_table[256];
  for(int i = 0; i < 256; i++)
    freq_table[i] = 0;
  
  //Determine frequency/encoding tables
  size_t size = det_file_size(file);

  // Convert to rle encoding.
  uint8_t *original = (uint8_t *)xmalloc(sizeof(uint8_t) * size);
  size_t read = fread(original, 1, size, file);
  if (read < size) {
    fprintf(stderr, "Could not read full file.\n");
    exit(ERR);
  }
  size_t rle_size;
  uint8_t *rle_encoded = rle_encode(original, size, &rle_size);
  free(original);
  create_freq_table(freq_table, rle_encoded, rle_size);	
  huff_node *huff_tree = create_huff_tree_from_frequency(freq_table);
  char **encoded_table = get_encoding(huff_tree);
  
  
  assert(encoded_table != NULL);
  
  //Write data
  write_compressed_file(comp_file, rle_encoded, encoded_table, rle_size);
  free(rle_encoded);
  //Close the file
  fclose(comp_file);
  
  //free memory
  destroy_huff_tree(huff_tree);
  free(encoded_table);
}

void decompress(FILE *file, char *filename) {
  //Check if file isnt a .hurl
  if(!is_huff_type(filename)) {
    fprintf(stderr, "Given file is not a .hurl\n");
    exit(ERR);
  }
  
  char *encoding[256];
  
  for(int i = 0; i < 256; i++) {
    encoding[i] = (char *)xmalloc(257);
  }
  
  //Get huff table from file
  size_t file_size;
  get_huff_table(encoding, file, &file_size);
  
  assert(encoding != NULL);
    
  //Create tree based on huff table
  huff_node *huff_tree = create_huff_tree_from_encoding(encoding);
  
  //Determine filename without the .hurl extension
  size_t len = strlen(filename);
  size_t ext_len = strlen(".hurl");
  filename[len-ext_len] = '\0';
  
  //Open new file
  FILE *decomp_file = open_file(filename, "w");
  
  size_t byte_count = 0;
  uint8_t curr_byte;
  int decoded;
  uint8_t *rle_encoded = xmalloc(sizeof(uint8_t) * file_size);
  //Loop through encoded data, decode it and add to new file
  while(fread(&curr_byte, 1, 1, file) &&  byte_count < file_size) {
    for(int i = 7; (i >= 0) && (byte_count < file_size); i--) {
      decoded = get_next_character(huff_tree, (curr_byte >> i)&0x1);
      
      if(decoded > -1) {
        unsigned char decoded_char = (unsigned char)decoded;
	byte_count++;
    	
	//Write decompressed data to file
	//xfwrite(&decoded_char, 1, 1, decomp_file);    			
	rle_encoded[byte_count-1] = decoded_char;
      }
    }
  }
  assert(byte_count == file_size);
  size_t decoded_size;
  uint8_t *rle_decoded = rle_decode(rle_encoded, file_size, &decoded_size);
  free(rle_encoded);

  if (rle_decoded == NULL) {
    fprintf(stderr, "Invalid RLE data: exiting\n");
    exit(ERR);
  }

  size_t written = fwrite(rle_decoded, sizeof(uint8_t), decoded_size, decomp_file);
  if (written < decoded_size) {
    fprintf(stderr, "File write error");
    exit(ERR);
  }
  free(rle_decoded);
  //Close the file
  fclose(decomp_file);
  
  destroy_huff_tree(huff_tree);

  for (int i = 0; i < 256; i++) {
    free(encoding[i]);
  }
}

void dump(FILE *file, char *filename)
{
  size_t file_size = det_file_size(file);
  
  //Check if file is .hurl
  if(is_huff_type(filename)) {
    char *encoded_table[256];
    
    for(int i = 0; i < 256; i++) {
      encoded_table[i] = (char *)xmalloc(257);
      assert(encoded_table[i] != NULL);
    }
    
    get_huff_table(encoded_table, file, &file_size);
    
    assert(encoded_table != NULL);
    
    for(int i = 0; i < 256; i++) {
      printf("%s\n", encoded_table[i]);
      free(encoded_table[i]);
    }
  }
  else {
    unsigned long long freq_table[256];
    for(int i = 0; i < 256; i++)
      freq_table[i] = 0;
    
    // Convert to rle encoding.
    uint8_t *original = (uint8_t *)xmalloc(sizeof(uint8_t) * file_size);
    size_t read = fread(original, sizeof(uint8_t), file_size, file);
    if (read < file_size) {
      fprintf(stderr, "Could not read complete file");
      exit(ERR);
    }
    size_t rle_size;
    uint8_t *rle_encoded = rle_encode(original, file_size, &rle_size);
    free(original);
    
    // Now create the table.
    create_freq_table(freq_table, rle_encoded, rle_size);	
    free(rle_encoded);
    
    huff_node *huff_tree = create_huff_tree_from_frequency(freq_table);
    char **encoded_table = get_encoding(huff_tree);
    assert(encoded_table != NULL);
    for(int i = 0; i < 256; i++) {
      printf("%s\n", encoded_table[i]);
    }
    destroy_huff_tree(huff_tree);
    free(encoded_table);
  }
}

void create_freq_table(unsigned long long table[], uint8_t *rle, unsigned long long size) {
  int c;
  
  for(unsigned long long i = 0; i < size; i++) {
    c = rle[i];
    table[c]++;
  }
}

bool is_huff_type(char *filename) {
  //Last occurance of "."
  char *file_type = strrchr(filename, '.');
  
  //Error check
  if(file_type == NULL)
    return false;
  
  //Compare with huff extension
  return (strcmp(file_type, EXT) == 0);
}

size_t det_file_size(FILE *file) {
  //Go to end
  int res = fseek(file, 0L, SEEK_END);
  if (res < 0) {
    fprintf(stderr, "Error determining file size: exiting\n");
    exit(ERR);
  }
  
  //Count bytes
  long file_length = ftell(file);
  if (file_length < 0) {
    fprintf(stderr, "Error determining file size: exiting\n");
    exit(ERR);
  }
  
  //Rewind file
  rewind(file);
  
  return (size_t)file_length;
}

void get_huff_table(char **huff_table, FILE *file, size_t *size) {
  //Need to read in 4 bytes rather than string
  //Since magic number doesnt end in \n
  char magic_num[4];
  
  //Read magic number
  for(int i = 0; i < 4; i++) {
    int c = fgetc(file);
    if (c == EOF) {
      fprintf(stderr, "Error reading huff file: exiting\n");
      exit(ERR);
    }
    magic_num[i] = (char)c;
    if (magic_num[i] == 0) {
      fprintf(stderr, "Bad magic number: exiting");
      exit(ERR);
    }

  }
  
  //If not the proper number
  if(strncmp(magic_num, NUM, 4) != 0) {
    fprintf(stderr, "Improper huff magic number.\n");
    exit(ERR);
  }
  
  //Get huff length
  unsigned char size_le[sizeof(unsigned long long)];
  size_t res = fread(size_le, sizeof(unsigned long long), 1, file);
  //Check that we read a file length
  if(res != 1) {
    fprintf(stderr, "Improper huff uncompressed file length.\n");
    exit(ERR);
  }

  //copy into the size
  unsigned long long size_local = 0;
  for (int i = 0; i < sizeof(unsigned long long); i++) {
    unsigned long long value = size_le[i];
    value = value << (i*8);
    size_local |= value;
  }
  *size = size_local;
  
  //Generate the encoded table
  char longest_string[257];
  int curr_char;
  
  //For each huffman table entry
  for(int i = 0; i < 256; i++) {
    bool found_newline = false;
    //For each char in the string
    for(int j = 0; j < 257; j++) {
      curr_char = fgetc(file);
      if (curr_char == EOF) {
        fprintf(stderr, "Error reading huffman table: exiting\n");
        exit(ERR);
      }
      
      //Regular char
      if (curr_char == 0x00 || curr_char == 0x01) {
        longest_string[j] = (char)curr_char;
      } else if (curr_char == '\n') {
        found_newline = true;
        longest_string[j] = 0x00;
        break;
      } else {
        fprintf(stderr, "Bad char in hurl headers: exiting\n");
        exit(ERR);
      }
    }
    
    if (!found_newline) {
      fprintf(stderr, "Invalid .hurl file: exiting\n");
      exit(ERR);
    }

    strcpy(huff_table[i], longest_string);
  }
}

enum Flags determine_flag(char *user_flag) {
  if(strcmp(user_flag, "-c") == 0)
    return COMPRESS;
  else if(strcmp(user_flag, "-d") == 0)
    return DECOMPRESS;
  else if(strcmp(user_flag, "-t") == 0)
    return DUMP;
  else
    return INVALID;
}

static void compressed_write_bit(int bit, FILE *comp_file);
static void compressed_finish_file(FILE *comp_file);
void write_compressed_file(FILE *comp_file, uint8_t * rle, char **encoded_table, size_t file_size) {
  // Write magic number
  // Apparently fprintf is used for strings?
  int res = fprintf(comp_file, "%s", NUM);
  if (res < 0) {
    fprintf(stderr, "File write error: exiting.\n");
    exit(ERR);
  }
  // Write file size
  // Convert to LE-format for file_size (platform-indep)
  uint64_t file_size_64 = file_size;
  char file_size_le[sizeof(file_size_64)];
  for (int i = 0; i < sizeof(file_size_64); i++) {
    file_size_le[i] = (file_size_64 >> (i*8)) & 0xFF;
  }
  // And fwrite is for binary data >.>
  xfwrite(file_size_le, 8, 1, comp_file);
  
  // Write encoded table
  for(int i = 0; i < 256; i++) {
    res = fprintf(comp_file, "%s\n", encoded_table[i]);
    if (res < 0) {
      fprintf(stderr, "File write error: exiting.\n");
      exit(ERR);
    }
  }
  
  // Write compressed data
  
  int curr_char;
  char *encoded_char;
  for (size_t j = 0; j < file_size; j++) {
    curr_char = rle[j];
    encoded_char = encoded_table[curr_char];
    
    size_t bit_count = strlen(encoded_char);
    for (int i = 0; i < bit_count; i++) {
      int bit = encoded_char[i] == '0' ? 0 : 1;
      compressed_write_bit(bit, comp_file);
    }
  }

  compressed_finish_file(comp_file);
}

static unsigned char bit_buf = 0;
static int bit_idx = 0;

static void compressed_write_bit(int bit, FILE *comp_file) {
  // Insert the bit into the single-char buffer
  bit_buf |= (bit<< (7 - bit_idx));
  bit_idx++;

  if (bit_idx == 8) {
    int res = fputc(bit_buf, comp_file);
    if (res == EOF) {
      fprintf(stderr, "Error writing compressed file: exiting.\n");
      exit(ERR);
    }
    bit_buf = 0;
    bit_idx = 0;
  }
}

static void compressed_finish_file(FILE *comp_file) {
  // If we have any remaining bits
  if (bit_idx > 0) {
    // We can write the char as is, because any untouched bits will be zero
    int res = fputc(bit_buf, comp_file);
    if (res == EOF) {
      fprintf(stderr, "Error writing compressed file: exiting.\n");
      exit(ERR);
    }
  }
  bit_buf = 0;
  bit_idx = 0;
}
