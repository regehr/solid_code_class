//
//  encodedOutputFileWriter.c
//  huff
//
//  Created by Adam Bradford on 2/2/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//
//  Modified by Oscar Marshall.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "encoder.h"
#include "encodedOutputFileWriter.h"
#include "syscalls.h"

static void writeHeader(FILE *file, unsigned long long length)
{
    char *header = "HUFF";
    xfwrite(header, sizeof(char), strlen(header), file);
    xfwrite(&length, sizeof(unsigned long long), 1, file);
}

//given a string of 8 chars containing 1's and 0's, this will return a byte with the same 1's and 0's set.
static char byteFromString(char *string)
{
    assert(string);

    unsigned char result = 0;
    for(int i = 7; i >= 0; i--)
    {
        char currentBit = string[7-i];
        if(currentBit == '1')
        {
            unsigned char temp = 1<<i;
            result = result | temp;
        }
    }
    return (char)result;
}

//writes a huffresult array to the file.
static void writeHuffmanTable(FILE *file, huffResult * resultArray)
{
    char * newLine = "\n";
    for(int i = 0; i < 256; i++)
    {
        huffResult *currentResult = &resultArray[i];
        xfwrite(currentResult->string, sizeof(char),
            strlen(currentResult->string), file);
        xfwrite(newLine, sizeof(char), strlen(newLine), file);
    }
}

static unsigned long long lengthOfFile(FILE *file)
{
    long int currentPosition = xftell(file);
    xfseek(file , 0L , SEEK_END);
    long int length = xftell(file);
    xfseek(file, currentPosition, SEEK_SET);

    return length;
}

static void writeEncodedFile(
    FILE *nonCompressedFile, FILE *compressedFile, huffResult *resultArray)
{
    //lets get some space to work in, in reality we only need 2 bytes, but we have memory to spare.
    char currentRead[512];
    assert(currentRead);

    int currentStringLength = 0;

    unsigned long long currentEncodeFileLength = lengthOfFile(nonCompressedFile);

    for (unsigned long long currentEncodeFileByteIndex = 0;
        currentEncodeFileByteIndex < currentEncodeFileLength;
        currentEncodeFileByteIndex++)
    {
        char nextByte;
        xfread(&nextByte, 1, 1, nonCompressedFile);

        //get the huffresult at the index of the nextbyte
        huffResult *result = &resultArray[(unsigned char)nextByte];

        //adjust the current string length
        currentStringLength += strlen(result->string);

        //concat the encoding to the currentRead
        strcat(currentRead, result->string);

        //writes out byte by byte.
        while(strlen(currentRead) > 7)
        {
            char output = byteFromString(currentRead);
            xfwrite(&output, sizeof(char), 1, compressedFile);
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
        xfwrite(&output, sizeof(char), 1, compressedFile);
        memcpy(currentRead, currentRead+8, strlen(currentRead));
        currentStringLength -= 8;

        assert(currentStringLength == 0);
    }
}

void writeNonCompressedFileToCompressedOutput(
    FILE* nonCompressedFile, FILE* compressedFile, huffResult resultArray[256])
{
    assert(compressedFile);
    assert(nonCompressedFile);


    //reset the file.
    unsigned long long currentEncodeFileLength = lengthOfFile(nonCompressedFile);
    rewind(nonCompressedFile);

    //writes the HUFF and length
    writeHeader(compressedFile, currentEncodeFileLength);

    //writes out the encodings
    writeHuffmanTable(compressedFile, resultArray);

    //writes out the encoded data
    writeEncodedFile(nonCompressedFile, compressedFile, resultArray);
}
