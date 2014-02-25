/*
 * Shared run length encoding methods that can be used by both the compressor
 * and the decompressor.
 */

void writeByte(FILE *writeFilePointer , unsigned char *toWrite);

FILE * getFile(char *fileName , char *fileMode);

// I added one more struct that works with my methods a little better
struct bitValue
{
	// bit value of the run
	unsigned char runValue;
	// length of the run < 127
	unsigned char runLength;
};

