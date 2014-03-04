//
//  decoder.c
//  rhuff
//
//  Created by Adam Bradford on 2/3/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//
//  Modified by Oscar Marshall.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <string.h>
#include "encoder.h"
#include "decoder.h"
#include "syscalls.h"

//turns a result array into a huff tree
void createDecodeTreeFromResultArray(huffResult *resultArray, huffNode out[511])
{
    memset(out, 0, sizeof(huffNode) * 511);
    //create a root node
    huffNode *rootNode = out;

    int nextFreeNode = 1;

    //iterate across the result array and place nodes where needed
    for(int i = 0; i < 256; i++)
    {
        huffResult *currentResult = &resultArray[i];
        char * valueString = currentResult->string;

        //simply walk down the tree adding nodes as needed until we reach the final character of the current encode string.
        huffNode *currentNode = rootNode;
        for(int j = 0;  (unsigned)j < strlen(valueString); j++)
        {
            if (valueString[j] == '0')
            {
                if(currentNode->leftLeaf == NULL)
                {
                    currentNode->leftLeaf = &out[nextFreeNode];
                    nextFreeNode++;
                }
                huffNode *parentNode = currentNode;
                currentNode = currentNode->leftLeaf;
                currentNode->parent = parentNode;
            }
            else
            {
                if(currentNode->rightLeaf == NULL)
                {
                    currentNode->rightLeaf = &out[nextFreeNode];
                    nextFreeNode++;
                }
                huffNode *parentNode = currentNode;
                currentNode = currentNode->rightLeaf;
                currentNode->parent = parentNode;

            }
        }
        currentNode->byte = i;
        assert(currentNode->leftLeaf == NULL && currentNode->rightLeaf == NULL);
    }
}

//returns the encodings from a givin file, returns null otherwise
unsigned long long huffmanEncodingsFromFile(FILE *file, char encodings[32768])
{
    rewind(file);
    //get the first 4 header characters
    char magic[4];
    size_t read = xfread(magic, 4, sizeof(char), file);
    /* We should have already done size checks. */
    assert(read == 1);

    //make sure it says HUFF
    if(!(magic[0] == 'H' &&
       magic[1] == 'U' &&
       magic[2] == 'R' &&
       magic[3] == 'L'))
    {
        fprintf(stderr, "Invalid File Header - missing \"HURL\"\n");
        exit(-1);
    }

    // Put the decoded length in the output variable
    unsigned long long decodedLength;
    xfread(&decodedLength, 1, sizeof(unsigned long long), file);

    //get the next 256 strings representing the encodings
    //create an index to keep track of where we are in copying the string
    int currentIndex = 0;
    for(int i = 0; i < 256; i ++)
    {
        // Loop until we hit a /n. If we hit any other character besides '0',
        // '1' or '/n' then it should fail.
        char currentByte;
        do
        {
            xfread(&currentByte, 1, 1, file);
            if (currentByte != '0' && currentByte != '1' && currentByte != '\n')
            {
                fprintf(stderr,
                    "Invalid character '%c' found in translation table.\n",
                    currentByte);
                exit(-1);
            }
            // Place the byte in the result.
            encodings[currentIndex] = currentByte;
            currentIndex++;
        }
        while (currentByte != '\n');
    }

    return decodedLength;
}

// Fills resultArray with the given encodings.
void createHuffResultArrayFromFileEncodings(
    char encodings[32768], huffResult resultArray[256])
{
    // Holds current index from the encodings
    int stringIndex = 0;

    for(int i = 0; i < 256; i++)
    {

        //get the current result and set defaults
        huffResult * currentResult = &resultArray[i];
        currentResult->value = i;
        currentResult->string = "";

        int currentStartIndex = stringIndex;

        //find the next newline
        while (encodings[stringIndex] != '\n')
        {
            char testChar = encodings[stringIndex++];
            if(!(testChar == '0' || testChar == '1'))
            {
                fprintf(stderr, "Invalid character found in encoding: %c\n",
                    testChar);
                return;
            }
        }

        //copy the encoding into the the currentresult
        if(currentStartIndex< stringIndex)
        {
            int length = stringIndex - currentStartIndex;

            char * value = calloc(length+1,sizeof(char) * length);
            assert(value);
            memcpy(value, &encodings[currentStartIndex], length);
            currentResult->string = value;

        }
        //increment
        stringIndex++;
    }

    //just a test to make sure every value has a string.
    for(int i = 0; i < 256; i++)
    {
        huffResult * currentResult = &resultArray[i];
        assert(currentResult->string);
    }
}
