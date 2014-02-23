#include <stdio.h>
#include <stdlib.h>
#include "rhuff_utils.h"

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
	char readBuffer[8];

        while(fread(readBuffer , sizeof(readBuffer) , 1 , filePointer) == 1)
        {
                int i = 0;
                unsigned char singleByte;
                for(; i < sizeof(readBuffer); i++)
                {
                        printf("\033[32mbyte:\033[37m %x   \033[36mbits:\033[37m " , readBuffer[i]);
                        int j = 7;
                        for(; j >= 0; j--)
                        {
                                singleByte = readBuffer[i] & (1<<j);
                                singleByte >>= j;
				if(j == 4)
				{
					printf("%u " , singleByte);
				}
				else
				{
                                	printf("%u" , singleByte);
				}
                        }
                        printf("\n");
                }
        }
}

void encode(char * fileName)
{
	//debug output
	printf("fileName is: %s\n" , fileName);
	
	// call to get a pointer to an opened file
	FILE *filePointer = getFile(fileName , "rb");

	prettyPrintFile(filePointer);	

	fclose(filePointer);
}
