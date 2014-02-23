#include <stdio.h>
#include <stdlib.h>
#include "rhuff_utils.h"
#include <string.h>
#define BITVAL(x,y) (((x)>>(y)) & 1)

void writeByte(FILE * , char *);

FILE * getFile(char *fileName , char *fileMode)
{
	FILE *filePointer;
	
	filePointer = fopen(fileName , fileMode);

	if(filePointer == NULL)
	{
		fprintf(stderr , "cannot open file in compress -> getFile");
		exit(1);
	}
	
	return filePointer;
}

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

void writeByte(FILE *writeFilePointer , char *toWrite)
{
	fwrite(toWrite , 1 , sizeof(char) , writeFilePointer);
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
	placeHolder.runLength = 0;
	while(fread(readBuffer , sizeof(readBuffer) , 1 , readFilePointer) == 1)
	{
		int byteIndex = 7;
		for(; byteIndex >= 0; --byteIndex)
		{
			unsigned char current = 0;
			current = BITVAL(readBuffer[0] , byteIndex + 1);
			placeHolder.runValue = current;
			//printf("Run Value = %x;" , current);
			
			unsigned char next = BITVAL(readBuffer[0] , byteIndex);

			if(current != next)
			{
				//construct byte
				//write to file
				unsigned char toWrite;
				printf("runValue(hex) = %02x; runLength(hex) = %02x\n" , placeHolder.runValue , placeHolder.runLength);
				struct2Byte(&placeHolder , &toWrite);
				placeHolder.runLength = 1;
				printf("the byte to be written(hex): %02x\n\n" , toWrite);
			}
			else
			{
				//increase struct values
				placeHolder.runLength += 1;
			}

		}
	}
}

void encode(char * fileName, char * writeFileName)
{
	//debug output
	printf("fileName is: %s\n" , fileName);
	
	// call to get a pointer to an opened file to read from
	FILE *readFilePointer = getFile(fileName , "rb");

	// call to get an open pointer to a file to write to
	FILE *writeFilePointer = getFile(writeFileName , "w");

	encodeFile(readFilePointer , writeFilePointer);

	//prettyPrintFile(readFilePointer);

	fclose(readFilePointer);
	fclose(writeFilePointer);
}
