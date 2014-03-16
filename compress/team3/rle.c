#include <stdbool.h>
#include <stdio.h>
#include "rle.h"

#define MAX_RUN_LENGTH 0x7f

static char rle_bit(char byte)
{
    return (byte >> 7) & 0x1;
}

static char rle_length(char byte)
{
    return byte & MAX_RUN_LENGTH;
}

static void rle_encode_write(char value, char length, FILE *output)
{
    assert(value == 0 || value == 1);
    assert(length > 0);
    assert(length <= MAX_RUN_LENGTH);
    assert(output);

    char byte = (value << 7) | length;
    xfwrite(&byte, 1, 1, output);
}

void rle_encode(FILE *input, FILE *output)
{
    assert(input);
    assert(output);

    char encoding_value = -1;
    int encoding_length = 0;

    /* Read out a byte. If the number of bytes read isn't 1, then we're at
       the EOF because xfread will kill the program if there was actually an
       error. */
    char byte = 0;
    while (xfread(&byte, 1, 1, input) == 1)
    {
        /* For each bit index... */
        for (int i = 0; i < 8; i++)
        {
            char bit = (byte >> (7 - i)) & 0x1;

            if (encoding_value == -1) {
                encoding_value = bit;
            }

            if (bit != encoding_value) {
                rle_encode_write(encoding_value, encoding_length, output);
                encoding_value = bit;
                encoding_length = 1;
                continue;
            }

            encoding_length++;

            /* If we've reached the max length possible, write out the byte. */
            if (encoding_length == MAX_RUN_LENGTH) {
                rle_encode_write(encoding_value, encoding_length, output);
                encoding_value = -1;
                encoding_length = 0;
            }
        }
    }

    /* flush the remaining encoding if one exists */
    if (encoding_length != 0) {
        rle_encode_write(encoding_value, encoding_length, output);
    }
}

void rle_decode(FILE *input, FILE *output)
{
    char decode_buffer = 0;
    char decode_index = 0;

    char byte = 0;
    while (xfread(&byte, 1, 1, input) == 1)
    {
        for (int i = 0; i < rle_length(byte); i++)
        {
            decode_buffer |= rle_bit(byte) << (7 - decode_index);
            decode_index++;

            /* When we've read a whole byte, flush the buffer. */
            if (decode_index == 8) {
                xfwrite(&decode_buffer, 1, 1, output);
                decode_buffer = 0;
                decode_index = 0;
            }
        }
    }

    /* If our bit count isn't divisible by 8, then we have a bad .hurl file */
    if (decode_index != 0) {
        fprintf(stderr, "Bad .hurl file.\n");
        exit(-1);
    }
}
