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
	placeHolder.runValue = 0;
	placeHolder.runLength = 1;

	// while fread returns bytes from reading the file
	while(fread(readBuffer , sizeof(readBuffer) , 1 , readFilePointer) == 1)
	{
		// init our index into the byte
		int byteIndex = 7;
		for(; byteIndex >= 0; --byteIndex)
		{
			unsigned char current = 0;
			unsigned char next = 0;

			// a gross little bandaid for some edge cases when spanning fread segments
			if(!firstIter && byteIndex == 7)
			{
				// this case is for spanning fread segments
				current = placeHolder.runValue;
				next = BITVAL(readBuffer[0] , byteIndex);
			}
			else if(byteIndex == 7)
			{
				// this case is for the very first loop iteration to get us off the ground
				firstIter = 0;
				continue;
			}
			else
			{
				// general case
				current = BITVAL(readBuffer[0] , byteIndex + 1);
				next = BITVAL(readBuffer[0] , byteIndex);

				placeHolder.runValue = current;
			}
			
			// the run is over. time to write to file
			if(current != next)
			{
				unsigned char toWrite;
				// convert our info to a writable byte
				struct2Byte(&placeHolder , &toWrite);
				// reset our struct values
				placeHolder.runValue = next;
				placeHolder.runLength = 1;
				// write out the byte
				writeByte(writeFilePointer , &toWrite);
			}
			else
			{
				// the run continues
				placeHolder.runLength += 1;
			}
		}
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
void encode(FILE * readFilePointer, char * writeFileName)
{
	// get a FILE to write to
	FILE *writeFilePointer = getFile(writeFileName , "w");
	
	// call to main encode
	encodeFile(readFilePointer , writeFilePointer);

	// finally, close files
	fclose(readFilePointer);
	fclose(writeFilePointer);
}
