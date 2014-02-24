#include <stdio.h>
#include <stdlib.h>
#include "rhuff_utils.h"
#include <string.h>
#define BITVAL(x,y) (((x)>>(y)) & 1)

void prettyPrintFile(FILE *filePointer)
{
	char readBuffer[1];

        while(fread(readBuffer , sizeof(readBuffer) , 1 , filePointer) == 1)
        {
                int i = 0;
                unsigned char singleByte;
                for(; i < sizeof(readBuffer); i++)
                {
                        printf("\033[32mbyte:\033[37m %x   \033[36mbits:\033[37m " , readBuffer[i]);
			int j = 7;
			for(; j >=0 ; j--)
			{
				printf("%u" , BITVAL(readBuffer[i] , j));
				if(j == 4)
				{
					printf(" ");
				}
			}
                        printf("\n");
                }
        }
}

void struct2Byte(struct bitValue* toConvert, unsigned char * convertTo)
{
	convertTo[0] = 0;
	convertTo[0] |= (toConvert->runValue << 7);
	convertTo[0] |= toConvert->runLength;
}

void encodeFile(FILE * readFilePointer , FILE * writeFilePointer)
{
	char readBuffer[1];
 	struct bitValue placeHolder;
	placeHolder.runValue = 0;
	placeHolder.runLength = 1;
	unsigned char firstIter = 1;
	while(fread(readBuffer , sizeof(readBuffer) , 1 , readFilePointer) == 1)
	{
		int byteIndex = 7;
		for(; byteIndex >= 0; --byteIndex)
		{
			unsigned char current = 0;
			unsigned char next = 0;
			if(!firstIter && byteIndex == 7)
			{
				current = placeHolder.runValue;
				next = BITVAL(readBuffer[0] , byteIndex);
			}
			else if(byteIndex == 7)
			{
				firstIter = 0;
				continue;
			}
			else
			{
				current = BITVAL(readBuffer[0] , byteIndex + 1);
				placeHolder.runValue = current;
				//printf("Run Value = %x;" , current);
				next = BITVAL(readBuffer[0] , byteIndex);
			}

			if(current != next)
			{
				//construct byte
				//write to file
				unsigned char toWrite;
				//printf("runValue(hex) = %02x; runLength(hex) = %02x\n" , placeHolder.runValue , placeHolder.runLength);
				struct2Byte(&placeHolder , &toWrite);
				placeHolder.runValue = next;
				placeHolder.runLength = 1;
				//printf("cur = %02x;  next = %02x\n" , current , next);
				//printf("the byte to be written(hex): %02x\n\n" , toWrite);
				writeByte(writeFilePointer , &toWrite);
			}
			else
			{
				//increase struct values
				placeHolder.runLength += 1;
			}
		}
	}
}

void encode(FILE * readFilePointer, char * writeFileName)
{
	//debug output
	//printf("fileName is: %s\n" , fileName);
	
	// call to get a pointer to an opened file to read from
	//FILE *readFilePointer = getFile(fileName , "rb");

	// call to get an open pointer to a file to write to
	FILE *writeFilePointer = getFile(writeFileName , "w");

	encodeFile(readFilePointer , writeFilePointer);

	//prettyPrintFile(readFilePointer);
	char *endOfFile;

	fclose(readFilePointer);
	fclose(writeFilePointer);
}
