//
//  compressedOutputFileWriter.c
//  huff
//
//  Created by Adam Bradford on 2/2/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "encoder.h"
#include "compressedOutputFileWriter.h"


long long currentEncodeFileByteIndex = 0;
long long currentEncodeFileLength = 0;

//private headers
void writeHeader(FILE *file,unsigned long long length);
void writeHuffmanTable(FILE *file, huffResult * resultArray);
void writeEncodedFile(FILE *nonCompressedFile, FILE *compressedFile, huffResult *resultArray);
char getNextByte(FILE *file);
void writeByte(FILE *file, char byte);
char byteFromString(char *string);

void writeNonCompressedFileToCompressedOutput(FILE* nonCompressedFile, char* newFileName, unsigned long long length, huffResult* resultArray)
{
    assert(resultArray);
    assert(newFileName);
    assert(nonCompressedFile);
    
    
    //reset the file.
    currentEncodeFileLength = length;
    currentEncodeFileByteIndex = 0;
    rewind(nonCompressedFile);
    
    //make a new file to save our output
    FILE *compressedFile = fopen(newFileName, "w");
    assert(compressedFile);
    
    //writes the HUFF and length
    writeHeader(compressedFile, length);
    
    //writes out the encodings
    writeHuffmanTable(compressedFile, resultArray);
    
    //writes out the encoded data
    writeEncodedFile(nonCompressedFile, compressedFile, resultArray);

    
    fclose(compressedFile);
    
    return;
}

void writeHeader(FILE *file,unsigned long long length)
{
    char *header = "HUFF";
    fwrite(header, sizeof(char), strlen(header), file);
    fwrite(&length, sizeof(unsigned long long), 1, file);
}

void writeEncodedFile(FILE *nonCompressedFile, FILE *compressedFile, huffResult *resultArray)
{
    //lets get some space to work in, in reality we only need 2 bytes, but we have memory to spare.
    char *currentRead = calloc(512, sizeof(char));
    int currentStringLength = 0;
    
    while (currentEncodeFileByteIndex < currentEncodeFileLength)
    {
        char nextByte = getNextByte(nonCompressedFile);
        currentEncodeFileByteIndex++;
        
        //get the huffresult at the index of the nextbyte
        huffResult *result = &resultArray[(u_int8_t)nextByte];
        
        //adjust the current string length
        currentStringLength += strlen(result->string);
        
        //concat the encoding to the currentRead
        strcat(currentRead, result->string);
        
        //writes out byte by byte.
        while(strlen(currentRead) > 7)
        {
            char output = byteFromString(currentRead);
            writeByte(compressedFile,output);
            memcpy(currentRead, currentRead+8, strlen(currentRead));
            currentStringLength -= 8;
        }
    }
    
    //we may have some leftover bits
    if(currentStringLength > 0)
    {
        //pad the bits with 0's
        while (currentStringLength < 8)
        {
            strcat(currentRead, "0");
            currentStringLength++;
        }
        
        //add the last byte to the output
        char output = byteFromString(currentRead);
        writeByte(compressedFile,output);
        memcpy(currentRead, currentRead+8, strlen(currentRead));
        currentStringLength -= 8;
        
        assert(currentStringLength == 0);
    }
}

//given a string of 8 chars containing 1's and 0's, this will return a byte with the same 1's and 0's set.
char byteFromString(char *string)
{
    uint8_t result;
    for(int i = 7; i >= 0; i--)
    {
        char currentBit = string[7-i];
        if(currentBit == '1')
        {
            uint8_t temp = 1<<i;
            result = result | temp;
        }
    }
    return (char)result;
}

//writes a huffresult array to the file.
void writeHuffmanTable(FILE *file, huffResult * resultArray)
{
    char * newLine = "\n";
    for(int i = 0; i < 256; i++)
    {
        huffResult *currentResult = &resultArray[i];
        fwrite(currentResult->string, sizeof(char), strlen(currentResult->string), file);
        fwrite(newLine, sizeof(char), strlen(newLine), file);
    }
}

void writeByte(FILE *file, char byte)
{
    fwrite(&byte, sizeof(char), 1, file);
}

char getNextByte(FILE *file)
{

    unsigned char currentByte;
    size_t err = fread( &currentByte , 1, 1 , file);
    assert(err == 1);
    return currentByte;

}