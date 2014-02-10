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
//#include "encoder.h"
//#include "compressedOutputFileWriter.h"
#include "decodedOutputFileWriter.h"


long long currentDecodeFileByteIndex = 0;

char getNextByte(FILE *file);
void writeByte(FILE *file, char byte);
char byteFromString(char *string);

void writeCompressedFileToNonCompressedOutput(FILE* compressedFile, FILE*uncompressedFile, unsigned long long decodedLength, huffNode* rootNode)
{
    assert(uncompressedFile);
    assert(compressedFile);
    
    currentDecodeFileByteIndex = 0;
    
    huffNode *currentNode = rootNode;
    while(currentDecodeFileByteIndex < decodedLength)
    {
        //get the next byte
        char encodedByte = getNextByte(compressedFile);
        
        
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
                writeByte(uncompressedFile, currentNode->representedByte);
                currentNode = rootNode;
                currentDecodeFileByteIndex++;
                if(currentDecodeFileByteIndex >= decodedLength) break;
            }
            
        }
    }
}

