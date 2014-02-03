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


long long currentFileByteIndex = 0;
long long currentFileLength = 0;

//private headers
void writeHeader(FILE *file,unsigned long long length);
void writeHuffmanTable(FILE *file, huffResult * resultArray);
void writeEncodedFile(FILE *nonCompressedFile, FILE *compressedFile, huffResult *resultArray);
char getNextByte(FILE *file);
void writeByte(FILE *file, char byte);
char byteFromString(char *string);

void writeFileToOutput(FILE* nonCompressedFile, char* newFileName, unsigned long long length, huffResult* resultArray)
{
    assert(resultArray);
    assert(newFileName);
    assert(nonCompressedFile);
    
    
    //reset the file.
    currentFileLength = length;
    currentFileByteIndex = 0;
    rewind(nonCompressedFile);
    
    //make a new file to save our output
    
    FILE *compressedFile = fopen(newFileName, "w");
    assert(compressedFile);
    
    writeHeader(compressedFile, length);
    writeHuffmanTable(compressedFile, resultArray);
    
    
    writeEncodedFile(nonCompressedFile, compressedFile, resultArray);

    fclose(compressedFile);
}

void writeHeader(FILE *file,unsigned long long length)
{
    char *header = "HUFF";
    fwrite(header, sizeof(char), strlen(header), file);
    fwrite(&length, sizeof(unsigned long long), 1, file);
    
}

void writeEncodedFile(FILE *nonCompressedFile, FILE *compressedFile, huffResult *resultArray)
{
    
    
    //lets get some space to work in
    char *currentRead = calloc(512, sizeof(char));
    int currentStringLength = 0;
    
    while (currentFileByteIndex < currentFileLength)
    {
        char nextByte = getNextByte(nonCompressedFile);
        currentFileByteIndex++;
        
        
        
        
        //get the string value for the representation
        huffResult *result = &resultArray[(int)nextByte];
        
        currentStringLength += strlen(result->string);
        
        strcat(currentRead, result->string);
        while(strlen(currentRead) > 7)
        {
            char output = byteFromString(currentRead);
            writeByte(compressedFile,output);
            memcpy(currentRead, currentRead+8, strlen(currentRead));
            currentStringLength -= 8;
        }

    }
    
    if(currentStringLength > 0)
    {
        while (currentStringLength < 8)
        {
            strcat(currentRead, "0");
            currentStringLength++;
            
        }
        char output = byteFromString(currentRead);
        writeByte(compressedFile,output);
        memcpy(currentRead, currentRead+8, strlen(currentRead));
        currentStringLength -= 8;
        
        assert(currentStringLength == 0);
    
    }
}

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