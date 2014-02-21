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
static void enter_byte(unsigned char* bytes, uint8_t bit, uint8_t freq)
{
  assert(freq < 128);

  // Check if we need to increase the length of the byte array
  if((num_bytes + 1) > size) {
    bytes = grow_array(bytes);
  }

  // Make the new rle byte and put it in the array
  unsigned char temp = (unsigned char) ((bit << 7) | freq);
  printf("bit is: %x\n", bit);
  printf("freq is: %x\n", freq);
  printf("Adding hex: %x to byte array\n", temp);
  bytes[++num_bytes] = temp;
}

void encode_rle(FILE* file, unsigned char** to_return, unsigned long long* total_bytes)
{
  int c, i;
  uint8_t freq = 0;
  uint8_t curr_bit = 0; // Assume first bit is 0, will be changed to 1 if not
  uint8_t temp_bit;
  unsigned char* bytes;

  // Malloc space for array and check that there wasn't an error
  if((bytes =  malloc(sizeof(char) * SIZE)) == NULL) {
    malloc_error();
  }

  // Loop through all characters in the file building rle bytes along the way
  do {
    c = fgetc(file);
    if(ferror(file)) { read_char_error(); }
    if(c != EOF) {
      printf("full char is: %c\n", c);
      for (i = 0; i <= 7; i++){ // Iterate through bits of the character
	if(curr_bit == (temp_bit = bit_at(c, i))) { // See if the next bit matches our current bit
	  if((freq + 1) >= 128) { // Only 7 bits to represent frequency, so max frequency = 127
	    enter_byte(bytes, curr_bit, freq);
	    printf("most recent byte hex: %x\n", bytes[num_bytes]);
	    freq = 1;
	  } else {
	    freq++;
	  }
	} else { // Bits didn't match, enter current byte and set the new bit as current
	  if(freq != 0) {
	    enter_byte(bytes, curr_bit, freq);
	    printf("most recent byte hex: %x\n", bytes[num_bytes]);
	  }

	  // Set the new bit as current and show that we've seen it one time	  
	  curr_bit = temp_bit;
	  freq = 1;
	}
      }
    } else { // EOF found, push last rle byte to array
      enter_byte(bytes, curr_bit, freq);
      printf("most recent byte hex: %x\n", bytes[num_bytes]);
    }
    assert(num_bytes <= size);
  } while(c != EOF);

  *to_return = bytes;
  *total_bytes = num_bytes;
}
