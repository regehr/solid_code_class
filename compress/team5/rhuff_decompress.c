#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rhuff_decompress.h"
#include "rhuff_utils.h"

// helpful bit level macros
#define BIT(x) (1 << (x))
#define BITVAL(x,y) (((x)>>(y)) & 1)
#define SETBIT(x,y) (((x) |= BIT(y)))

// get value of an RLE byte
void getValueOfEncodedBlock(unsigned char *toParse , unsigned char *returnedValue)
{
	returnedValue[0] = 0;
	returnedValue[0] = ((toParse[0] & 0x80U) >> 7);
}
// get the length of an RLE byte
void getLengthOfEncodedBlock(unsigned char *toParse , unsigned char *returnedLength)
{
	returnedLength[0] = 0;
	returnedLength[0] = toParse[0] & 0x7FU;
}

// do the actual decoding work
void decodeFile(FILE *readFilePointer , FILE *writeFilePointer)
{
	//variable declarations
	unsigned char readBuffer[1];
	unsigned short spacesRemaining = 7;
	unsigned char current = 0;

	// while we continue to recieve bytes from our call to fread
	while(fread(readBuffer , sizeof(readBuffer) , 1 , readFilePointer) == 1)	
	{
		// variable declarations	
		unsigned char value;
		unsigned char length;

		// get the value and length for this run
		getValueOfEncodedBlock(&readBuffer[0] , &value);
		getLengthOfEncodedBlock(&readBuffer[0] , &length);

		// loop index
		int index = 0;

		// loop while we still have bits to write to the file
		for(; index < length; index++)
		{	
			// if we are placing a "1"
			if(value)
			{
				SETBIT(current , spacesRemaining);
			}

			// if there are no more bit spaces in this byte
			// then we should write it out
			if(spacesRemaining == 0)
			{
				writeByte(writeFilePointer , &current);
				spacesRemaining = 7;
				current = 0x00U;	
			}
			else
			{
				// we have written a bit
				// decrease our remaining spaces in this byte
				spacesRemaining--;
			}
		}	
	}

	// if we finished reading from our file but there are bits that havnt been written
	// then we should write those bits out
	if(spacesRemaining > 0 && spacesRemaining < 7)
	{
		writeByte(writeFilePointer , &current);
	}
}

// main decode method
void decode(FILE *readFilePointer , char *writeFileName)
{
	// get a FILE to write to
	FILE *writeFilePointer = getFile(writeFileName , "wb");

	// make the call to decode
	decodeFile(readFilePointer , writeFilePointer);
	
	// finally, close our two files
	fclose(readFilePointer);
	fclose(writeFilePointer);
}
