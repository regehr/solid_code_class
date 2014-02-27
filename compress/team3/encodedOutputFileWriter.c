//
//  encodedOutputFileWriter.c
//  rhuff
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
    char *header = "HURL";
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
    char outputBuffer[512];
    memset(outputBuffer, 0, 512);
    int outputBufferIndex = 0;

    unsigned long long nonCompressedFileSize = lengthOfFile(nonCompressedFile);

    for (unsigned long long nonCompressedFileIndex = 0;
        nonCompressedFileIndex < nonCompressedFileSize;
        nonCompressedFileIndex++)
    {
        char nextByte;
        size_t read = xfread(&nextByte, 1, 1, nonCompressedFile);
        /* Because we only issue one read for every byte in the file, we should
           never try to read past the EOF. Also, since xfread handles and exits
           on an error, we should always get back 1 from xfread. */
        assert(read == 1);

        //get the huffresult at the index of the nextbyte
        huffResult *result = &resultArray[(unsigned char)nextByte];

        // Concat the encoding to the outputBuffer.
        // We should've flushed the buffer if we had at least 256 bits to write.
        assert(strlen(outputBuffer) < 256);
        // The largest a huffman encoding can be is 255.
        assert(strlen(result->string) < 256);
        // Concatenation with a buffer of size 512 is safe because the largest
        // resulting string is 510 characters long. Plus the null terminator,
        // our string will only take 511 bytes.
        strcat(outputBuffer, result->string);

        //writes out byte by byte.
        while (strlen(outputBuffer + outputBufferIndex) > 7)
        {
            // Write the byte to the compressed file.
            char output = byteFromString(outputBuffer + outputBufferIndex);
            xfwrite(&output, 1, 1, compressedFile);

            // Chop off the first 8 characters by moving forward the index.
            outputBufferIndex += 8;
            // If we've used up the first half of the buffer, then copy the
            // second half into the first. The second half will include the null
            // terminator so the second half can be treated as garbage after the
            // memcpy
            if (outputBufferIndex == 256) {
                memcpy(outputBuffer, outputBuffer + 256, 256);
                // The null terminator should now be within the first half.
                assert(strlen(outputBuffer) < 256);
                outputBufferIndex = 0;
            }
        }
    }

    // Deal with any leftover bits
    if(strlen(outputBuffer + outputBufferIndex))
    {
        // Pad the bits with 0's
        memset(outputBuffer + strlen(outputBuffer), '0',
            8 - strlen(outputBuffer + outputBufferIndex));
        memset(outputBuffer + outputBufferIndex + 8, 0, 1);

        // Add the last byte to the output
        char output = byteFromString(outputBuffer + outputBufferIndex);
        xfwrite(&output, 1, 1, compressedFile);
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

    //writes the HURL and length
    writeHeader(compressedFile, currentEncodeFileLength);

    //writes out the encodings
    writeHuffmanTable(compressedFile, resultArray);

    //writes out the encoded data
    writeEncodedFile(nonCompressedFile, compressedFile, resultArray);
}
