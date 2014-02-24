#include <stdio.h>
#include <stdlib.h>

void writeByte(FILE *writeFilePointer , char *toWrite)
{
        fwrite(toWrite , 1 , sizeof(char) , writeFilePointer);
}

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

