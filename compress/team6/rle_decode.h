/*
 * rle_decode.h 
 *
 * Written by Keith Richards
 * February 2014
 *
 * These functions are intended for use with huffman encoding and decoding
 */

#ifndef RLE_D_H
#define RLE_D_H

/*
 * internal struct that acts as the stats holder for a file that is encoded
 * and is being decoded
 */
struct decode_state
{
    unsigned long long file_length; /* length of file in bytes */
    unsigned char *bytes; /* pointer to first byte in file */
    FILE *new_file; /* tempoarary file where we write a rle compressed file */
    unsigned char bit_count; /* the number of bits that have been decoded */
    unsigned char byte; /* the byte we are currently writing */
    
};

/*
 * Prepare a file for decoding. This is done after huffman decompression, and before rle decompresson
 * Be warned! file_name here is not the name of the file we are preparing.  It is the name of
 * the original file that was already decompressed
 * Here file_name is guarenteed to be a .hurl file
 *
 * return the struct above, containing all the info required to decode with rle
 */
struct decode_state * prepare_file_for_decode(char *file_name);


/*
 * Decompress a file that was compressed using run length encoding.
 *
 * Writes a file called file_name without the .hurl extension
 */
void rle_decompress(struct decode_state *state);

#endif
