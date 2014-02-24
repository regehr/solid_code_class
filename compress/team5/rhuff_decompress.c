#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rhuff_decompress.h"

#define BIT(x) (1 << (x))
#define BITVAL(x,y) (((x)>>(y)) & 1)
#define SETBIT(x,y) (((x) |= BIT(y)))


void getValue(unsigned char *toParse , unsigned char *returnedValue)
{
	returnedValue[0] = 0;
	returnedValue[0] = ((toParse[0] & 0x80U) >> 7);
}

void getLength(unsigned char *toParse , unsigned char *returnedLength)
{
	returnedLength[0] = 0;
	returnedLength[0] = toParse[0] & 0x7FU;
}

void decodeFile(FILE *readFilePointer , FILE *writeFilePointer)
{
	char readBuffer[1];
	unsigned short left = 7;
	unsigned char current = 0;

	while(fread(readBuffer , sizeof(readBuffer) , 1 , readFilePointer) == 1)	
	{
		printf("buffer = %02x\n" , readBuffer[0]);
		unsigned char value;
		unsigned char length;

		getValue(&readBuffer[0] , &value);
		getLength(&readBuffer[0] , &length);

		printf("value = %02x  length = %02x\n" , value , length);

		int index = 0;
		for(; index < length; index++)
		{	
			if(value)
			{
				SETBIT(current , left);
			}
			if(left == 0)
			{
				writeByte(writeFilePointer , &current);
				left = 7;
				current = 0x00U;	
			}
			else
			{
				left--;
			}
		}	
	}
	if(left > 0 && left < 7)
	{
		writeByte(writeFilePointer , &current);
	}
}

void decode(FILE *readFilePointer , char *writeFileName)
{
	//FILE *readFilePointer = getFile(readFileName , "rb");
	FILE *writeFilePointer = getFile(writeFileName , "wb");

	
	decodeFile(readFilePointer , writeFilePointer);


	fclose(readFilePointer);
	fclose(writeFilePointer);
}
