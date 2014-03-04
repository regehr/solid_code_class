//
//  decoder.h
//  rhuff
//
//  Created by Adam Bradford on 2/3/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//
//  Modified by Oscar Marshall.
//

#ifndef huff_decoder_h
#define huff_decoder_h

//returns the encodings from a given file, as a string including 256strings returns null if there is an error
//if successful the number of decoded bytes will be placed in the decoded length variable.
unsigned long long huffmanEncodingsFromFile(FILE *file, char out[32768]);

//creates an array of huffResults using the encodings
void createHuffResultArrayFromFileEncodings(
    char * encodings, huffResult resultArray[256]);
//creates a tree from huffResults
void createDecodeTreeFromResultArray(huffResult *resultArray, huffNode out[511]);

#endif
