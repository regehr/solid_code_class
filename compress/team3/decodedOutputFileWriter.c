//
//  compressedOutputFileWriter.c
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
//#include "encoder.h"
//#include "compressedOutputFileWriter.h"
#include "decodedOutputFileWriter.h"
#include "syscalls.h"

void writeByte(FILE *file, char byte);

void writeCompressedFileToNonCompressedOutput(FILE *compressedFile,
    FILE *uncompressedFile, unsigned long long decodedLength,
    huffNode *rootNode)
{
    assert(uncompressedFile != NULL);
    assert(compressedFile != NULL);

    unsigned long long currentDecodeFileByteIndex = 0;

    huffNode *currentNode = rootNode;
    while(currentDecodeFileByteIndex < decodedLength)
    {
        //get the next byte
        char encodedByte;
        size_t read = xfread(&encodedByte, 1, 1, compressedFile);

        if (read == 0)
        {
            fprintf(stderr, "Unexpected end of file.\n");
            exit(-1);
        }

        //get the value of the byte and start walking the tree;
        for(int j = 7; j >= 0; j--)
        {
            char currentBit = encodedByte >> j;
            currentBit = currentBit & 1;

            //the bit is a 1, to right
            if(currentBit)
            {
                assert(currentNode->rightLeaf);
                currentNode = currentNode->rightLeaf;
            }
            else
            {
                assert(currentNode->leftLeaf);
                currentNode = currentNode->leftLeaf;
            }


            //is this a leaf?
            if(!currentNode->leftLeaf && !currentNode->rightLeaf)
            {
                //write the byte and reset the node to the top of the tree
                xfwrite(&currentNode->byte, sizeof(char), 1, uncompressedFile);
                currentNode = rootNode;
                currentDecodeFileByteIndex++;
                if(currentDecodeFileByteIndex >= decodedLength) break;
            }

        }
    }
}

