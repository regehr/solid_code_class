//
//  encoder.h
//  huff
//
//  Created by Adam Bradford on 2/2/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//

#ifndef huff_encoder_h
#define huff_encoder_h

//this struct is used to hold encodings and values
typedef struct huffResult{
    char * string;
    int value;
}huffResult;

//this struct is what creates the tree.  a right leaf denotes a 1, left leaf denotes 0.
typedef struct huffNode huffNode;
struct huffNode{
    
    long long sum;
    unsigned representedByte;
    int used;
    
    huffNode* parent;
    huffNode* leftLeaf;
    huffNode* rightLeaf;
    
};

//creates an array of huffresults, or encodings for give frequencies
huffResult* createHuffResultArray(unsigned *frequencies);

//prints out a huffresult array
void printHuffResult(huffResult *result);

//frees elements of a huff result array.
void freeReusltArray(huffResult *);

#endif
