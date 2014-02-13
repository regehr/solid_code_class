//
//  encoder.h
//  huff
//
//  Created by Adam Bradford on 2/2/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//

#ifndef huff_encoder_h
#define huff_encoder_h


typedef struct huffResult{
    char * string;
    int value;
}huffResult;

typedef struct huffNode huffNode;
struct huffNode{
    
    long long sum;
    int representedByte;
    int used;
    
    huffNode* parent;
    huffNode* leftLeaf;
    huffNode* rightLeaf;
    
};

huffResult* createHuffmanTree(unsigned *frequencies);

void printHuffResultArray(huffResult *resultArray);

void freeReusltArray(huffResult *);

#endif
