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





//these are just some internal methods
int compareNodes (const void * a, const void * b);
huffResult* calcResult(huffNode *rootNode);
huffNode* calculateTree(huffNode *nodes, int count);
huffNode* minNode(huffNode *nodes, int count);
void fillResultArray(huffResult* resultArray, huffNode *node, char *currentString);
char* concat(char *s1, char *s2);
/** Check rep **/
void checkTree(huffNode *rootNode);
int countLeaves(huffNode *rootNode);
void checkTable(huffResult *resultArray);
void checkValidCode (char *s);


//turns an array of frequencies into a an array of huffresults, used for encoding
huffResult* createHuffResultArray(unsigned *frequencies)
{
    
    //we'll make a sum for checking later;
    unsigned long long sum = 0;
    for(int i = 0; i< 256; i++)
    {
        sum += frequencies[i];
       // printf("%d, %d\n",i,frequencies[i]);
    }
    
    //make an array of nodes big enough to hold everything.
    //in theory we would never be able to have 2048 of these, but lets make room just to be safe.
    huffNode * nodes = calloc(2048, sizeof(huffNode));
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
    
    //assemble the tree of nodes
    huffNode *rootNode = calculateTree(nodes, nodeCount);
    
    //we aren't interested in the nodes for encoding, just the results encoding.
    huffResult *result = calcResult(rootNode);
    
#ifdef CHECK_REP
    checkTree(rootNode);
    checkTable(result);
    exit(0);
#endif 
    
    //release the nodes
    free(nodes);
    
    return result;
    
}

//turns an array of nodes into a proper tree, the number of nodes in the array shoud be at most halfway filled up or less.
huffNode* calculateTree(huffNode *nodes,int count)
{
    //make some pointers to the lowest and second lowest nodes
    huffNode* lowestNode = NULL;
    huffNode* secondLowestNode = NULL;
    //get the minium values
    while (1) {
        //find the lowest node and mark it used
        lowestNode = minNode(nodes, count);
        assert(lowestNode);
        lowestNode->used = 1;
        
        //get the second lowest node
        secondLowestNode = minNode(nodes, count);
        
        
        //if we don't have a second lowest node, we are finished so we can exit this loop
        if(!secondLowestNode)break;
        
        //mark it used
        secondLowestNode->used = 1;
        
        //grab the nex available unnused node to be the parent for the two lowest nodes
        huffNode *newNode = &nodes[count++];
        assert(newNode);
        
        //set the partent
        lowestNode->parent = newNode;
        secondLowestNode->parent = newNode;
        
        //set the childrem
        newNode->leftLeaf = lowestNode;
        newNode->rightLeaf = secondLowestNode;
        
        //set the sum
        newNode->sum = lowestNode->sum + secondLowestNode->sum;
        
       
        //resett the the lowest node pointers and repeat.
        lowestNode = NULL;
        secondLowestNode = NULL;
    }
    
    // at this point, the lowest node is the root.
    return lowestNode;
}

//this turns a tree of huff nodes into a an array of huffresults, which contain encodings
huffResult* calcResult(huffNode *rootNode)
{
    //get some memroy
    huffResult* resultArray = calloc(256, sizeof(huffResult));
    
    //fill the result array with the encodings
    fillResultArray(resultArray, rootNode, "");
    
    //fill in any null strings with empty stings.
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

//this walks the tree and fills up the result array with encodings from the node.
void fillResultArray(huffResult* resultArray, huffNode *node, char *currentString)
{
    if(!node)return;
    
    if(!currentString) currentString = "";
    
    
    
    if(!(node->leftLeaf) && !(node->rightLeaf))
    {
        huffResult * resultElement = &resultArray[node->representedByte];
        char * tempString = calloc(40, sizeof(char));
        strcpy(tempString, currentString);
        resultElement->string = tempString;
        assert(resultElement->string);
        resultElement->value = node->representedByte;
        
    }
    
    char *leftString = concat(currentString, "0");
    char *rightString = concat(currentString, "1");
    
    fillResultArray(resultArray, node->leftLeaf,leftString);
    fillResultArray(resultArray, node->rightLeaf,rightString);
    
    
    
    free(leftString);
    free(rightString);
}

//prints out a node, used for debugging
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


//finds the mininum mode in the tree
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

//concats two chars.
char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

//prints out the huff result array
void printHuffResult(huffResult *result)
{
    for(int i = 0; i < 256; i++)
    {
        huffResult * currentResult = &result[i];
        printf("%d - %s\n",currentResult->value,currentResult->string);
        assert(currentResult->string);
    }
}

//frees the huff results array and its elements
void freeResultArray(huffResult *resultArray)
{
    for(int i = 0; i < 256; i++)
    {
        huffResult * currentResult = &resultArray[i];
        free(currentResult->string);
        
    }
    free(resultArray);
}

// Check rep on tree
void checkTree(huffNode *rootNode){

  // Tree must exist
  assert(rootNode);
  int leafCount = countLeaves(rootNode);
  assert (leafCount <= 256);

}


// Check rep on table
void checkTable(huffResult *resultArray){

  int i;
  for (i = 0; i < 256; i++) {
    char *s = resultArray->string;
    checkValidCode(s);
    resultArray++;
  }

}


// Count leaves (for checkTree)
int countLeaves(huffNode *rootNode){

  if (rootNode) {
    
      int count = countLeaves(rootNode->leftLeaf)+
	          countLeaves(rootNode->rightLeaf);
      return (count == 0) ? 1: count;
      
   }
   return 0;  
}


// Checks valid code (for checkTable)
void checkValidCode (char *s){

  int i = 0;
  while (s[i] != '\0') {
    
    char c = s[i];
    assert (c == '1' || c == '0');
    i++;
    
  }
}

