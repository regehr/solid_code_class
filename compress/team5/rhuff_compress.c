#include <stdio.h>
#include <stdlib.h>


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
                        printf("byte: %x   bits (read backwards): " , readBuffer[i]);
                        int j = 0;
                        for(; j < 8; j++)
                        {
                                singleByte = readBuffer[i] & (1<<j);
                                singleByte >>= j;
                                printf("%u" , singleByte);
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
