/*
 * Easily interface with the huffman encoder and decoder
 */

char *huff_encode (char *filename, FILE *input, FILE *output);
char *huff_decode (char *filename, FILE *input, FILE *output);