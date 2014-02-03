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

huffResult* createHuffmanTree(unsigned *frequencies);

void freeReusltArray(huffResult *);

#endif
