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
#include "decodedOutputFileWriter.h"
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
    {
        printf("Could not open file");
        return -1; /* Need error message. */
    }
    
    //find out how long the input file is
    long long length = lengthOfFile(file);
    
    //generate frequency table
    unsigned * frequencies;
    frequencies = calloc(256, sizeof(unsigned));
    assert(frequencies);
    generateFrequencyTable(file, length, frequencies);

    ////ENCODING Example////
    
    //this one call goes throught the motions and returns an array of "huffResults"
    //theses are the encodings.  They can be printed or used to write an encoded file.
    huffResult* resultArray = createHuffResultArray(frequencies);
    
    //this prints out the resultarray
    printHuffResult(resultArray);
    
    //here is an example of encoding a file.
    char *newFileName = strcat((char *)argv[2], ".huff");
    writeNonCompressedFileToCompressedOutput(file, newFileName, length, resultArray);
    
    
    //as an example to show the decodeing steps, we will reopen the newly created file.
    FILE *compressedFile = fopen(newFileName, "r");
    
    
    
    //////DECODING//////
    
    //this will return a string of the encoding and set the decoded length from the header, or return null if there was a problem.
    unsigned long long decodedLength = 0;
    char* encodings = huffmanEncodingsFromFile(compressedFile, &decodedLength);
    
    //this will turn the encodings into an array of huffResults. Use this to dump the table from an existing .huff file
    huffResult *decodedResultsArray = createHuffResultArrayFromFileEncodings(encodings);
    printHuffResult(decodedResultsArray);
    
    //this will turn the huff results into a huffNode tree for for the decoder to walk when parsing.
    huffNode *decodeTree = createDecodeTreeFromResultArray(decodedResultsArray);
    
   
    //this just making a string for testing to give a new name to save the decoded file to for comparison
    char *testUncompressedFile = calloc(256, sizeof(char));
    strcat(testUncompressedFile, newFileName);
    strcat(testUncompressedFile, ".decoded.txt");
    
    //this will decode the compressedfile and create a new file, cusing the length and tree we created earlier.
    writeCompressedFileToNonCompressedOutput(compressedFile, testUncompressedFile,decodedLength, decodeTree);
   
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