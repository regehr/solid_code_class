//
//  encoder.c
//  huff
//
//  Created by Adam Bradford on 2/2/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//

#include "encoder.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <string.h>






int compareNodes (const void * a, const void * b);
huffResult* calcResult(huffNode *rootNode);
huffNode* calculateTree(huffNode *nodes, int count);
huffNode* minNode(huffNode *nodes, int count);
void printNode(huffNode *node, char *currentString);
void fillResultArray(huffResult* resultArray, huffNode *node, char *currentString);




char* concat(char *s1, char *s2);

huffResult* createHuffmanTree(unsigned *frequencies)
{
    //ok so we have an array of frequencies, what now?
    
    //we'll make a sum for checking later;
    unsigned long long sum = 0;
    for(int i = 0; i< 256; i++)
    {
        sum += frequencies[i];
       // printf("%d, %d\n",i,frequencies[i]);
    }
    
    //make an array of nodes big enough to hold everything.
    huffNode * nodes = calloc(512, sizeof(huffNode));
    int nodeCount = 0;
    
    //lets fill em up!
    for(int i = 0; i < 256; i++)
    {
        if(frequencies[i] > 0)
        {
            huffNode *node = &nodes[nodeCount];
            nodeCount++;
            node->sum = frequencies[i];
            node->representedByte = i;
        }
        
    }
    
    huffNode *rootNode = calculateTree(nodes, nodeCount);
    
    
    
    huffResult *result = calcResult(rootNode);
    
    for(int i = 0; i < 256; i++)
    {
        huffResult * currentResult = &result[i];
        printf("%d - %s\n",currentResult->value,currentResult->string);
    }
    
    free(nodes);
    
    return result;
    
}

huffNode* calculateTree(huffNode *nodes,int count)
{
    huffNode* lowestNode = NULL;
    huffNode* secondLowestNode = NULL;
    //get the minium values
    while (1) {
        lowestNode = minNode(nodes, count);
        assert(lowestNode);
        lowestNode->used = 1;
        
        secondLowestNode = minNode(nodes, count);
        
        if(!secondLowestNode)break;
        
        secondLowestNode->used = 1;
        
        huffNode *newNode = &nodes[count++];
        assert(newNode);
        
        lowestNode->parent = newNode;
        secondLowestNode->parent = newNode;
        
        newNode->leftLeaf = lowestNode;
        newNode->rightLeaf = secondLowestNode;
        
        newNode->sum = lowestNode->sum + secondLowestNode->sum;
        
       
        
        lowestNode = NULL;
        secondLowestNode = NULL;
    }
    
    
    return lowestNode;
}


huffResult* calcResult(huffNode *rootNode)
{
    huffResult* resultArray = calloc(256, sizeof(huffResult));
    
    fillResultArray(resultArray, rootNode, "");
    
    //fill in any missing values
    for(int i = 0; i < 256; i++)
    {
        huffResult * currentResult = &resultArray[i];
        if(!currentResult->string)
        {
            currentResult->value = i;
            currentResult->string = "";
        }
    }
    
    return resultArray;
}

void fillResultArray(huffResult* resultArray, huffNode *node, char *currentString)
{
    if(!node)return;
    
    if(!currentString) currentString = "";
    
    
    
    if(!node->leftLeaf && !node->rightLeaf)
    {
        huffResult * resultElement = &resultArray[node->representedByte];
        char * tempString = calloc(20, sizeof(char));
        resultElement->string = strcpy(tempString, currentString);
        resultElement->value = node->representedByte;
        
    }
    
    char *leftString = concat(currentString, "0");
    char *rightString = concat(currentString, "1");
    
    fillResultArray(resultArray, node->leftLeaf,leftString);
    fillResultArray(resultArray, node->rightLeaf,rightString);
    
    free(leftString);
    free(rightString);
}

void printNode(huffNode *node, char *currentString)
{
    if(!node)return;
    
    if(!currentString) currentString = "";
    
    
    
    if(!node->leftLeaf && !node->rightLeaf)
    {
        printf("value: %d - sum: %lld - string:%s\n",node->representedByte,node->sum,currentString);
    }
    
    char *leftString = concat(currentString, "0");
    char *rightString = concat(currentString, "1");
    
    printNode(node->leftLeaf,leftString);
    printNode(node->rightLeaf,rightString);
    
    free(leftString);
    free(rightString);
}



huffNode* minNode(huffNode * nodes, int count)
{
    long long currentMin = LONG_LONG_MAX;
    huffNode *lowestNode = NULL;
    
    
    for( int i = 0; i < count; i++)
    {
        huffNode *currentNode = &nodes[i];
        if(!currentNode->used)
        {
            if(currentNode->sum < currentMin)
            {
                currentMin = currentNode->sum;
                lowestNode = currentNode;
            }
        }
    }
    return lowestNode;
}
char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}




void freeResultArray(huffResult *resultArray)
{
    for(int i = 0; i < 256; i++)
    {
        huffResult * currentResult = &resultArray[i];
        free(currentResult->string);
        
    }
    free(resultArray);
}




