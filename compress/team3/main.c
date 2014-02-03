//
//  main.c
//  huff
//
//  Created by Adam Bradford on 2/2/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "frequencyCounter.h"
#include "compressedOutputFileWriter.h"
#include <assert.h>
#include <string.h>
#include "encoder.h"
#include "decoder.h"

long long lengthOfFile(FILE *file);

int main(int argc, const char * argv[])
{

    FILE *file;
    file = fopen(argv[2], "r");
    if (file == NULL || file == 0)
        return -1; /* Need error message. */
    
    long long length = lengthOfFile(file);
    
    unsigned * frequencies;
    frequencies = calloc(256, sizeof(unsigned));
    assert(frequencies);
    
    generateFrequencyTable(file, length, frequencies);

    //printFrequencyArray(frequencies);
    
    huffResult* resultArray = createHuffmanTree(frequencies);
    
    char * test = calloc(2048,sizeof(char));
    for(int i = 0; i < 256; i++)
    {
        huffResult *result = &resultArray[i];
        strcat(test, result->string);
        strcat(test, "\n");
        
    }
    
    createHuffmanTreeFromFileEncodings(test);
    
    char *newFileName = strcat((char *)argv[2], ".huff");
    //////for debugging, just send in a file called testinput.txt...////
    writeFileToOutput(file, newFileName, length, resultArray);
    printf("Hello, World!\n");
    return 0;
}

long long lengthOfFile(FILE *file)
{
    long long length;
    
    fseek(file , 0L , SEEK_END);
    length = ftell( file );
    rewind( file );
    
    return length;
}