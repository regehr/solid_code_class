#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1

void decompress(FILE * readFrom, FILE * writeTo);//decompresses a file from RLE to normal
void compress(FILE * readFrom, FILE * writeTo);//compresses a file using RLE
int packByte(int current, int counter, FILE * writeTo);//packages the run information into a single byte
void unpackByte( int packed, int* symbol, int* number);//unpacks the symbol and number of symbols from a byte

int main(int argc, char *argv[])
{
  //open the file in binary read mode
  FILE * fhr = fopen(argv[1], "rb");
  if (fhr==NULL)
    {
      fputs ("File error", stderr);
      exit(1);
    }

  FILE * fhw = fopen("test_write.rle", "wb");
  if (fhw==NULL)
    {
      fputs ("File error", stderr);
      exit(1);
    }

  compress(fhr, fhw);
  fclose(fhr);
  fclose(fhw);
  
  FILE * fhr2 = fopen("test_write.rle", "rb");
  if (fhr==NULL)
    {
      fputs ("File error", stderr);
      exit(1);
    }

  FILE * fhw2 = fopen(argv[2], "wb");
  if (fhw==NULL)
    {
      fputs ("File error", stderr);
      exit(1);
    }

  decompress(fhr2, fhw2);
  fclose(fhr2);
  fclose(fhw2);

  return 0;
}

/**
 * Takes the huffman decoded version of the file and writes out the appropriate number of ones and zeros
 * as specified by each byte
 * The first bit of each byte signifies whether the run is of ones (1) or zeros (0).
 * The next seven bits encode how many ones or zeros are in the run.
 * To decompress, simply read in each byte and write the appropriate number or ones or zeros to a file.
 */
void decompress(FILE * readFrom, FILE * writeTo)
{
  char * buff = (char *)calloc(1, sizeof(char));//holds the byte as we read them in
  unsigned char writeByte;//holds the binary digits to print out (unsigned to avoid arithmetic shift behavior)

  //while there are bytes in the file
  int trackBit = 0;//tracks where we are in the byte we're filling up
  while(fread(buff, sizeof(char), 1, readFrom) == 1)
    {
      //unpack the byte
      int current;
      int count;
      int leftover = -1;
      char onesMask = 0x01;
      char zerosMask = 0xFE;
      unpackByte(*buff, &current, &count);

      //for loop for each of the bits we need to print to file
      int bitsToPrint;
      for(bitsToPrint = 0; bitsToPrint < count; bitsToPrint++)
	{
	  //if the byte is full
	  if(trackBit == 8)
	    {
	      //write it out to the file
	      fwrite(&writeByte, 1, sizeof(char), writeTo);
     
	      //reset the tracker
	      trackBit = 0;
	    }
	  //fill in the byte starting at trackBitNum
	  if(current == 1)
	    {
	      //to fill in a one, pad a bunch of zeros on the left, end with a one and OR the last bit
	      writeByte = writeByte>>(7-trackBit)|onesMask;
	    }
	  else
	    {
	      //to fill in a zero pad the left with ones with a zero at the end then AND the last bit
	      writeByte = writeByte>>(7-trackBit)&zerosMask;
	    }
	  //move the last bit back into position
	  writeByte = writeByte<<(7-trackBit++);
	}
    }

  //print out the last byte
  fwrite(&writeByte, 1, sizeof(char), writeTo);

  //clean up
  free(buff);
}

void unpackByte( int packed, int* symbol, int* number)
{
  short symbolMask = 0x80;//used to mask the bit to write
  short countMask = 0x7f;//used to mask the bits for count
  
  //get the symbol we need
  *symbol = (packed&symbolMask)>>7;

  //get the number of symbols
  *number = packed&countMask;
}

/**
 * Takes in a file and writes the runs into a run length file.
 * Each run is encoded into a single byte with the first bit indicating if the run is of ones (1) or zeros (0)
 * and the other seven encoding the number of ones or zeros in the run.
 * Each run terminates when either:
 * 1. the character changes from one to zero or zer to one
 * 2. we hit the max number of ones or zeros we can encode in a single byte
 * When a run terminates we just get the next bit from the file and start a new run encoded in a byte
 */
void compress(FILE * readFrom, FILE * writeTo)
{
  short mask = 0x01;//used to mask off bits as we process them
  int current = -1;//tracks the symbol of the current run
  int counter = -1;//tracks the number of symbols we're seen so far
  char * buff = (char*)calloc(1, sizeof(char));//stores the byte as we get it from file

  //while there are bytes in the file
  while(fread(buff, sizeof(char), 1, readFrom) == 1)
    {
      //loop through the byte
      short shiftBy = 7;
      while(shiftBy >= 0)
	{
	  //if this is a new run
	  if(current == -1)
	    {
	      //figure out which symbol we're processing
	      current = (*buff>>shiftBy)&mask;
	      
	      //reset counter
	      counter = 0;
	    }
	  //if the symbol is the same and we haven't overflowed our counter
	  if(current == ((*buff>>shiftBy)&mask) && counter < 127)
	    {
	      //update our count and the bit we're looking at
	      counter++;
	      shiftBy--;
	    }
	  //if the symbol changes or the counter overflows
	  else
	    {
	      //pack everything we have into a byte
	      packByte(current, counter, writeTo);
	      
	      //reset current
	      current = -1;
	      
	      //reset counter
	      counter = -1;
	    }
	}
    }
  //pack the last of it into a byte
  packByte(current, counter, writeTo);
  free(buff);
}

int packByte(int current, int counter, FILE * writeTo)
{
  char packed = current<<7|counter;
  return fwrite(&packed, 1, sizeof(char), writeTo);
}
