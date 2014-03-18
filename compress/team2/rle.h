#ifndef RLE_H
#define RLE_H

/**
 * Takes the huffman decoded version of the file and writes out the appropriate number of ones and zeros
 * as specified by each byte
 * The first bit of each byte signifies whether the run is of ones (1) or zeros (0).
 * The next seven bits encode how many ones or zeros are in the run.
 * To decompress, simply read in each byte and write the appropriate number or ones or zeros to a file.
 */
void decompress_rle(FILE * readFrom, FILE * writeTo);

/**
 * Takes the huffman decoded version of the file and writes out the appropriate number of ones and zeros
 * as specified by each byte
 * The first bit of each byte signifies whether the run is of ones (1) or zeros (0).
 * The next seven bits encode how many ones or zeros are in the run.
 * To decompress, simply read in each byte and write the appropriate number or ones or zeros to a file.
 */
void compress_rle(FILE * readFrom, FILE * writeTo);

//packages the run information into a single byte
int packByte(int current, int counter, FILE * writeTo);

//unpacks the symbol and number of symbols from a byte
void unpackByte( int packed, int* symbol, int* number);

#endif

