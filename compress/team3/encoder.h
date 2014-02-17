//
//  encoder.h
//  huff
//
//  Created by Adam Bradford on 2/2/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//

#ifndef huff_encoder_h
#define huff_encoder_h


typedef struct huffResult {
    char *string;
    int value;
} huffResult;

typedef struct huffNode {

    long long sum;
    int byte;
    int used;

    struct huffNode *parent;
    struct huffNode *leftLeaf;
    struct huffNode *rightLeaf;

} huffNode;

void createHuffmanTree(unsigned *frequencies, huffResult out[256]);

void printHuffResultArray(huffResult *resultArray);

void freeReusltArray(huffResult *);

#endif
