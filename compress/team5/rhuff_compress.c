#include <stdio.h>
#include <stdlib.h>
#include "rhuff_utils.h"
#include <string.h>

// helpful bit level macro
#define BITVAL(x,y) (((x)>>(y)) & 1)

// helpfull for viewing a files bit level contents
void prettyPrintFile(FILE *filePointer)
{
	char readBuffer[1];

        while(fread(readBuffer , sizeof(readBuffer) , 1 , filePointer) == 1)
        {
                int i = 0;
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

// convert a bitValue struct to a byte
void struct2Byte(struct bitValue* toConvert, unsigned char * convertTo)
{
	convertTo[0] = 0;
	convertTo[0] |= (toConvert->runValue << 7);
	convertTo[0] |= toConvert->runLength;
}

// does the bulk of the encoding work
void encodeFile(FILE * readFilePointer , FILE * writeFilePointer)
{
	// variable declarations
	char readBuffer[1];
 	struct bitValue placeHolder;
	unsigned char firstIter = 1;

	// init for our first loop iter
	unsigned char current = 0;

	// while fread returns bytes from reading the file
	while(fread(readBuffer , sizeof(readBuffer) , 1 , readFilePointer) == 1)
	{
		// init our index into the byte
		int byteIndex = 0;
		for(; byteIndex < 8; byteIndex++)
		{
			current = BITVAL(readBuffer[0], byteIndex);

			if (firstIter == 1)
			{
				placeHolder.runValue = current;
				placeHolder.runLength = 0;
				firstIter = 0;
			}

			if (placeHolder.runValue != current || placeHolder.runLength == 127)
			{
				unsigned char c;
				struct2Byte(&placeHolder, &c);
				fputc(c, writeFilePointer);
				placeHolder.runValue = current;
				placeHolder.runLength = 0;
			}

			placeHolder.runLength++;
		}
	}

	if (placeHolder.runLength > 0)
	{
		unsigned char c;
		struct2Byte(&placeHolder, &c);
		fputc(c, writeFilePointer);
		placeHolder.runValue = current;
		placeHolder.runLength = 0;
	}

	// if fread returned 0 bytes we got here.
	// lets make sure it wasnt an error
	if(ferror(readFilePointer))
	{
		fprintf(stderr , "read file error in encode -> encodeFile");
		exit(1);
	}
}

// main driver method
void encode(FILE * readFilePointer, FILE *out)
{
	// call to main encode
	encodeFile(readFilePointer , out);
}
