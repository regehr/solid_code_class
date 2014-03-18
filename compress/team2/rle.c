#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "rle.h"

#define BUFFER_SIZE 1

//decompresses a file from RLE to normal
void decompress_rle(FILE * readFrom, FILE * writeTo)
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
	      writeByte = writeByte|(onesMask<<(7-trackBit++));
	    }
	  else
	    {
	      //to fill in a zero pad the left with ones with a zero at the end then AND the last bit
	      writeByte = writeByte&(zerosMask<<(7-trackBit++));
	    }
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

//compresses a file using RLE
void compress_rle(FILE * readFrom, FILE * writeTo)
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
