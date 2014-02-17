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
#include <stdbool.h>





int compareNodes (const void * a, const void * b);
char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void fillResultArray(
    huffResult* resultArray, huffNode *node, char *currentString)
{
    if(!node)return;

    if(!currentString) currentString = "";

    //make sure the string is not insanely long;
    assert(strlen(currentString) < 1024);

    //this is a leaf, set it's string representation and represented byte
    if(!node->leftLeaf && !node->rightLeaf)
    {
        huffResult * resultElement = &resultArray[node->byte];
        char * tempString = calloc(strlen(currentString), sizeof(char));
        assert(tempString);
        resultElement->string = strcpy(tempString, currentString);
        resultElement->value = node->byte;

    }

    //adjust our strings and keep working on the tree.
    char *leftString = concat(currentString, "0");
    char *rightString = concat(currentString, "1");

    fillResultArray(resultArray, node->leftLeaf,leftString);
    fillResultArray(resultArray, node->rightLeaf,rightString);

    free(leftString);
    free(rightString);
}

void calcResult(huffNode *rootNode, huffResult resultArray[256])
{
    //fill them up
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
}

huffNode* calculateTree(huffNode *nodes, int count);
huffNode* minNode(huffNode *nodes, int count);
void printNode(huffNode *node, char *currentString);
/** Check rep **/
void checkTree(huffNode *rootNode);
int countLeaves(huffNode *rootNode);
void checkTable(huffResult *resultArray);
void checkValidCode (char *s);

//this craetes a tree and returns the resulting strings as an array of huffresults
void createHuffmanTree(unsigned *frequencies, huffResult resultArray[256])
{
    //make an array of nodes big enough to hold everything.
    huffNode nodes[512];

    int nodeCount = 0;

    //lets fill em up with the frequencies
    for(int i = 0; i < 256; i++)
    {

        huffNode *node = &nodes[nodeCount];
        nodeCount++;
        node->sum = frequencies[i];
        node->byte = i;
    }

    //make a tree of nodes
    huffNode *rootNode = calculateTree(nodes, nodeCount);
    assert(rootNode);

    //turn those nodes into the array of results
    calcResult(rootNode, resultArray);

#ifdef CHECK_REP
    checkTree(rootNode);
    checkTable(resultArray);
#endif
}

void printHuffResultArray(huffResult *resultArray)
{
        for(int i = 0; i < 256; i++)
        {
            huffResult * currentResult = &resultArray[i];
            printf("%s\n", currentResult->string);
        }
}

huffNode* calculateTree(huffNode nodes[512], int count)
{
    assert(count >= 0 && count < 512);

    huffNode *lowestNode = minNode(nodes, count);
    assert(lowestNode);
    lowestNode->used = 1;

    huffNode *secondLowestNode = minNode(nodes, count);
    if (!secondLowestNode) return lowestNode;

    secondLowestNode->used = 1;

    assert(count < 511);
    struct huffNode *newNode = &nodes[count];

    lowestNode->parent = newNode;
    secondLowestNode->parent = newNode;

    *newNode = (struct huffNode) {
        .sum = lowestNode->sum + secondLowestNode->sum,
        .byte = lowestNode->byte < secondLowestNode->byte ?
            lowestNode->byte : secondLowestNode->byte,
        .used = false,
        .leftLeaf = lowestNode,
        .rightLeaf = secondLowestNode,
    };

    return calculateTree(nodes, count + 1);
}


//just prints out a node for test purposes
void printNode(huffNode *node, char *currentString)
{
    if(!node)return;

    if(!currentString) currentString = "";



    if(!node->leftLeaf && !node->rightLeaf)
    {
        printf("value: %d - sum: %lld - string:%s\n",node->byte,node->sum,currentString);
    }

    char *leftString = concat(currentString, "0");
    char *rightString = concat(currentString, "1");

    printNode(node->leftLeaf,leftString);
    printNode(node->rightLeaf,rightString);

    free(leftString);
    free(rightString);
}


//returns the current min node
huffNode* minNode(huffNode nodes[512], int count)
{
    assert(count >= 0 && count < 512);
    huffNode *lowestNode = NULL;


    for (int i = 0; i < count; i++)
    {
        huffNode *currentNode = &nodes[i];
        if (currentNode->used) continue;
        if (lowestNode == NULL ||
            currentNode->sum < lowestNode->sum ||
            (currentNode->sum == lowestNode->sum &&
                currentNode->byte < lowestNode->byte))
        {
            lowestNode = currentNode;
        }
    }
    return lowestNode;
}


//cleans up the result array
void freeResultArray(huffResult *resultArray)
{
    for(int i = 0; i < 256; i++)
    {
        huffResult * currentResult = &resultArray[i];
        free(currentResult->string);

    }
    free(resultArray);
}



void checkTree(huffNode *rootNode){

  // Tree must exist
  assert(rootNode);
  int leafCount = countLeaves(rootNode);
  assert (leafCount <= 256);

}



void checkTable(huffResult *resultArray){

  int i;
  for (i = 0; i < 256; i++) {
    char *s = resultArray->string;
    checkValidCode(s);
    resultArray++;
  }

}



int countLeaves(huffNode *rootNode){

  if (rootNode) {

      int count = countLeaves(rootNode->leftLeaf)+
	          countLeaves(rootNode->rightLeaf);
      return (count == 0) ? 1: count;

   }
   return 0;
}



void checkValidCode (char *s){

  int i = 0;
  while (s[i] != '\0') {

    char c = s[i];
    assert (c == '1' || c == '0');
    i++;

  }
}
