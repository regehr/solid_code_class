/*
 * rle.h 
 *
 * Written by Keith Richards
 * February 2014
 *
 *
 * These functions are intended for use before huffman encoding, decoding and dumping, hence "pre_"
 */


#ifndef RLE_H
#define RLE_H

/* Tempoaray file that rle generates and feeds to huffman */
static char *FANCY_FILE_NAME = "/tmp/HisMajestyBarackHObama";

/* 
 * Compresses a file using run length encoding.  This is done before huffman compression
 * justifying the name pre_compress
 *
 * writes a new file with the first byte at file_pointer.  This allows seamless transtion 
 * back to old code to run huffman encoding
 *
 * returns the length of the temprary file that it generates generates in bytes
 */
long long rle_pre_compress(unsigned char *file_pointer, long long file_length, char *file_name);


/*
 * not implemented
 */
void rle_pre_print(unsigned char *file_pointer, long long file_length, char *file_name);




#endif
