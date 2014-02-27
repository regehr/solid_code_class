/*
 * rle_decode.c
 *
 * Written by Keith Richards
 * February 2014
 *
 * implementation of rle decoding
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <assert.h>
#include "rle_decode.h"
#include "common.h"


void flush_decoded_bit(unsigned char bit, struct decode_state *state)
{
    state->byte = (bit << (7 - state->bit_count)) | state->byte;
    if (++state->bit_count == 8)
    {
	state->bit_count = 0;
	fwrite(&state->byte, 1, 1, state->new_file);
	state->byte = 0x00;
    }
}


void decode_byte(unsigned char byte, struct decode_state *state)
{
    unsigned char bit = (0x80 & byte) >> 7;
    unsigned char bit_count = 0x7F & byte;

    assert(bit_count > 0);

    for (; bit_count > 0; bit_count--)
    {
	flush_decoded_bit(bit, state);
    }
}

extern const char * TMP_FILE;
struct decode_state * prepare_file_for_decode(char *file_name)
{
    /* remove the .hurl */
    file_name[strlen(file_name)-5] = '\0';

    struct decode_state *file_info = (struct decode_state *) xmalloc(sizeof(struct decode_state));

    /* get a file */
    FILE *file = Fopen(TMP_FILE, "r");

    /* get the length in bytes of the file and store it */
    struct stat sb;
    stat(TMP_FILE, &sb);
    file_info->file_length = sb.st_size;

    /* store the actual file in memory starting at file_info->bytes */
    file_info->bytes = (unsigned char *) xmalloc(file_info->file_length);
    if(!fread(file_info->bytes, file_info->file_length, 1, file))
    {
	printf("Error reading file\n");
	exit(-1);
    }
    fclose(file);

    /* store the new file we are going to write */
    file_info->new_file = Fopen(file_name,"w+b");

    return file_info;
}



void rle_decompress(struct decode_state *state)
{
    state->bit_count = 0;
    state->byte = 0x00;
    unsigned long long i;
    for (i = 0; i < state->file_length; i++)
    {
	decode_byte(state->bytes[i], state);
    }
}
