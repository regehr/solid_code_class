#include <stdio.h>
#include <stdlib.h>

void writeByte(FILE *writeFilePointer , unsigned char *toWrite)
{
        fwrite(toWrite , 1 , sizeof(unsigned char) , writeFilePointer);
	if(ferror(writeFilePointer))
	{
		fprintf(stderr , "there was an error writing to file in writeByte");
		exit(1);
	}
}

FILE * getFile(char *fileName , char *fileMode)
{
        FILE *filePointer = NULL;

        filePointer = fopen(fileName , fileMode);

        if(filePointer == NULL)
        {
                fprintf(stderr , "cannot open file in compress -> getFile");
                exit(1);
        }

        return filePointer;
}

