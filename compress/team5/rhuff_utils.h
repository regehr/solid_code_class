/*
 * Shared run length encoding methods that can be used by both the compressor
 * and the decompressor.
 */


struct rle_block {
    // Decoded info
    int byte_count;
    int remaining_bit_count;
    char * bytes;

    // Encoded info
    int hex;
    char[2] hex_str;
};


/*
 * Encodes a run of bits and returns an run length encoding block with the
 * encoded info populated.
 */
struct rle_block encode_run (unsigned char *, int);


/*
 * Decodes a number into a run of bits and builds a run length encoding block.
 */
struct rle_block decode_run (int);