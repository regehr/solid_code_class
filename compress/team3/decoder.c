//
//  decoder.c
//  huff
//
//  Created by Adam Bradford on 2/3/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <string.h>
#include "encoder.h"
#include "decoder.h"

//private headers
huffNode* createTreeFromResultArray(huffResult *resultArray);

huffNode* createHuffmanTreeFromFileEncodings(char * encodings)
{
    
    huffResult * resultArray = calloc(512, sizeof(huffResult));
    int stringIndex = 0;
    for(int i = 0; i < 256; i++)
    {
        huffResult * node = &resultArray[i];
        node->value = i;
        node->string = "";
        
        
        int currentStartIndex = stringIndex;
        
        while (encodings[stringIndex] != '\n')
        {
            stringIndex++;
        }
        
        if(currentStartIndex< stringIndex)
        {
            int length = stringIndex - currentStartIndex;
            
            char * value = malloc(sizeof(char) * length);
            memcpy(value, &encodings[currentStartIndex], length);
            node->string = value;
            
        }
        stringIndex++;
    }
    
    huffNode *rootNode = createTreeFromResultArray(resultArray);
    
    return rootNode;
}

huffNode* createTreeFromResultArray(huffResult *resultArray)
{
    huffNode *rootNode = malloc(sizeof(huffNode));
    for(int i = 0; i < 256; i++)
    {
        huffResult *currentResult = &resultArray[i];
        char * valueString = currentResult->string;
        
        huffNode *nextNode = rootNode;
        int stringLength = (int)strlen(valueString);
        for(int j = 0;  j < stringLength ;j++)
        {
            
            char currentBit = valueString[j];
            if(currentBit == '0')
            {
                if(!nextNode->leftLeaf)
                {
                    nextNode->leftLeaf = calloc(1, sizeof(huffNode));
                }
                huffNode *parentNode = nextNode;
                nextNode = nextNode->leftLeaf;
                nextNode->parent = parentNode;
            }
            else if(currentBit == '1')
            {
                if(!nextNode->rightLeaf)
                {
                    nextNode->rightLeaf = calloc(1, sizeof(huffNode));
                }
                huffNode *parentNode = nextNode;
                nextNode = nextNode->rightLeaf;
                nextNode->parent = parentNode;
                
            }
            
            
            nextNode->representedByte = i;
        }
        
        
    }
    return rootNode;
}