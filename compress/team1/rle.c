#include "rle.h"

static void read_char_error() {
  fprintf(stderr, "ERROR: Error while reading a character from original file.\n");
  exit(ERR_CODE);
}

static void malloc_error() {
  fprintf(stderr, "ERROR: Error while allocating space for array.\n");
  exit(ERR_CODE);
}

static void array_resize_error() {
  fprintf(stderr, "ERROR: Error while trying to grow byte array.\n");
  exit(ERR_CODE);
}

static void decode_to_file_error() {
  fprintf(stderr, "ERROR: Error while trying to write decoded bits to the output file.\n");
  exit(ERR_CODE);
}

static unsigned long long size = SIZE; // Max number of allowed chars in the array
static unsigned long long num_bytes = 0; // Number of rle bytes in byte array

/**
 * Returns the bit at a desired position. This is intended to only work for a character
 * so this will only allow you to get the lowest 8 bits of the given int. The index starts
 * at 0 for the MSB in the specified range for the supplied int.
 */
static uint8_t bit_at(int c, int i)
{
  assert(i >= 0 && i < 8);
  int shift = 7 - i;
  return (uint8_t) (c >> shift) & 0x01; 
}

/**
 * Grow byte array to larger size
 */
static unsigned char* grow_array(unsigned char* ar)
{
  size += INCREMENT;
  unsigned char* tmp = realloc(ar, size);
  if(tmp != NULL) {
    ar = tmp;
  }
  else {
    free(ar);
    array_resize_error();
  }

  return ar;
}

/**
 * Construct rle byte and add it to the byte array
 */
static void enter_byte(unsigned char** bytes, uint8_t bit, uint8_t freq)
{
  assert(freq < 128);

  // Check if we need to increase the length of the byte array
  if((num_bytes + 1) > size) {
    *bytes = grow_array(*bytes);
    //printf("Grew array");
  }

  // Make the new rle byte and put it in the array
  unsigned char temp = (unsigned char) ((bit << 7) | freq);
  //printf("bit is: %x\n", bit);
  //printf("freq is: %x\n", freq);
  //printf("Adding hex: %x to byte array\n", temp);
  (*bytes)[num_bytes++] = temp;
}

void encode_rle(FILE* file, unsigned char** to_return, unsigned long long* total_bytes)
{
  int c, i;
  uint8_t freq = 0;
  uint8_t curr_bit = 0; // Assume first bit is 0, will be changed to 1 if not
  uint8_t temp_bit;
  unsigned char* bytes;

  // Malloc space for array and check that there wasn't an error
  if((bytes =  malloc(sizeof(unsigned char) * SIZE)) == NULL) {
    malloc_error();
  }

  // Loop through all characters in the file building rle bytes along the way
  do {
    c = fgetc(file);
    if(ferror(file)) { read_char_error(); }
    if(c != EOF) {
      //printf("full char is: %c\n", c);
      for (i = 0; i <= 7; i++){ // Iterate through bits of the character
	if(curr_bit == (temp_bit = bit_at(c, i))) { // See if the next bit matches our current bit
	  if((freq + 1) >= 128) { // Only 7 bits to represent frequency, so max frequency = 127
	    enter_byte(&bytes, curr_bit, freq);
	    //printf("most recent byte hex: %x\n", bytes[num_bytes]);
	    freq = 1;
	  } else {
	    freq++;
	  }
	} else { // Bits didn't match, enter current byte and set the new bit as current
	  if(freq != 0) {
	    enter_byte(&bytes, curr_bit, freq);
	    //printf("most recent byte hex: %x\n", bytes[num_bytes]);
	  }

	  // Set the new bit as current and show that we've seen it one time	  
	  curr_bit = temp_bit;
	  freq = 1;
	}
      }
    } else { // EOF found, push last rle byte to array
      enter_byte(&bytes, curr_bit, freq);
      //printf("most recent byte hex: %x\n", bytes[num_bytes]);
    }
    assert(num_bytes <= size);
  } while(c != EOF);

  *to_return = bytes;
  *total_bytes = num_bytes;
}

/**
 * Masks off the least significant 7 bits of an int so that we can determine how many instances
 * of the current bit need to be written to the file
 */
static uint8_t mask_lsbs(unsigned char c)
{
  return (uint8_t) (c & 0x7F);
}

static int current_bit = 7;
static unsigned char bit_buffer = 0;
static unsigned long long count = 0;

/**
 *	Takes a single bit as input and writes out to the file once 
 * 	a byte has been filled. 
 *
 *      This originally came from huff_io.c and had different parameters 
 *      and error message call, but I wanted all applicable methods 
 *      contained in this file so I copied method to here.
 */
static void write_bit (uint8_t bit, FILE* file)
{
    assert(bit == 1 || bit == 0);
    if (bit)
        bit_buffer |= (1<<current_bit);

    //printf("Will write bit: 0x%x to file\n", bit);
    count++;
    
    current_bit--;
    if (current_bit == -1)
    {
        if (fwrite (&bit_buffer, 1, 1, file) != 1){
            decode_to_file_error();
        }
	//printf("wrote char: %c to file\n", bit_buffer);
        current_bit = 7;
        bit_buffer = 0;
    }
}

void decode_rle(unsigned char* encodings, unsigned long long* length, FILE* outputFile)
{
  unsigned long long i;
  uint8_t j;
  unsigned long long len = *length;
  unsigned char c;
  uint8_t curr_bit;
  uint8_t num_bits;

  // Iterate through the encoded bytes, and determine what bits need to be written to the output file
  for(i = 0; i < len; i++)
  {
    // Pull out single encoded byte
    c = encodings[i];
    //printf("character is: 0x%X\n", c);

    // Get MSB, this will be the run of 0 or 1. Mask off the lower 7 bits, this will be the number of 
    // bits to write to the file
    curr_bit = bit_at((int) c, 0);
    num_bits = mask_lsbs(c);

    // num_bits should never be over 127 since we only have 7 bits to represent the number
    assert(num_bits <= 127);
    //printf("num_bits is: %d\n", num_bits);

    // Write the appropriate number of bits to the file
    for(j = 0; j < num_bits; j++)
    {
      //printf("bit in hex is: 0x%x\n", curr_bit);
      write_bit(curr_bit, outputFile);
    }
  }

  // Assert that what we wrote out to the file ended on a byte boundary
  //printf("current_bit: 0x%X and bit_buffer: 0x%X\n", current_bit, bit_buffer);
  //printf("number of bits set to be written: %d\n", count);
  assert((current_bit == 7) && (bit_buffer == 0));
}
