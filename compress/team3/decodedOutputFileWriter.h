//
//  compressedOutputFileWriter.h
//  rhuff
//
//  Created by Adam Bradford on 2/2/14.
//  Copyright (c) 2014 Adam Bradford. All rights reserved.
//
//  Modified by Oscar Marshall.
//

#ifndef huff_decodedOutputFileWriter_h
#define huff_decodedOutputFileWriter_h
#include "encoder.h"

// Begins writing decoding the the compressed file to a new file with the given
// file name. The current read from the compressed file must be at the begining
// of the encoded data.
void writeCompressedFileToNonCompressedOutput(
	FILE* compressedFile, FILE*uncompressedFile,
	unsigned long long decodedLength, huffNode* rootNode);

#endif
