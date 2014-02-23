#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void decompress_rle(FILE * readFrom, FILE * writeTo);//decompresses a file from RLE to normal
void compress_rle(FILE * readFrom, FILE * writeTo);//compresses a file using RLE
int packByte(int current, int counter, FILE * writeTo);//packages the run information into a single byte
void unpackByte( int packed, int* symbol, int* number);//unpacks the symbol and number of symbols from a byte

