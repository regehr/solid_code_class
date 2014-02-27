/*
 * rle_encode.h 
 *
 * Written by Keith Richards
 * February 2014
 *
 * These functions are intended for use with huffman encoding and decoding
 */

#ifndef RLE_E_H
#define RLE_E_H

/*
 * internal struct that acts as my scrolling window view of the file
 * It holds the current bit in the file, a simple counter, bool for if
 * processing has started, total number of bytes flushed to file, and a temporary
 * FILE pointer where the bytes are being flushed
*/
struct encode_state
{
    unsigned char bit; /* the current bit we are looking at */
    unsigned char bit_count; /* the number of repeated occurrences of bit */
    unsigned char processing; /* 1 if we have begun to process the file, 0 before that */
    unsigned long long file_length; /* number of bytes written so far */
    FILE *tmp_file; /* tempoarary file where we write a rle compressed file */
    unsigned char* file_pointer; /* pointer to the open tempoarary file */
};


/* 
 * Compresses a file using run length encoding.  This is done before huffman compression
 *
 * writes a new file with the first byte at file_pointer.  This allows seamless transtion 
 * back to old code to run huffman encoding
 *
 * returns the struct above, containing all info required to continue with huffman
 */
struct encode_state * rle_compress(unsigned char *file_pointer, unsigned long long file_length);

#endif
