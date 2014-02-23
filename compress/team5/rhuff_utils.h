/*
 * Shared run length encoding methods that can be used by both the compressor
 * and the decompressor.
 */


struct rle_block {
    // Decoded info
    int byte_count;          // Count of total bytes for this run
    int remaining_bit_count; // Count of bits in last byte that are valid
    char * bytes;            // Pointer to bytes

    // Encoded info
    int hex;                 // Integer value of the two bytes
    char hex_str[2];         // Two characters representing the two bytes
};


/*
 * Encodes a run of bits and returns a rle_block with encoded info populated.
 * Expects an integer that points to the first bit to encode the run for.
 */
struct rle_block encode_run (unsigned char *, int);


/*
 * Decodes a number into a run of bits and builds a run length encoding block.
 */
struct rle_block decode_run (int);
