/*
 * rle_encode.c
 *
 * Written by Keith Richards
 * February 2014
 *
 * implementation of rle encoding
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <assert.h>
#include "rle_encode.h"
#include "common.h"

static void flush_encoded_state(struct encode_state *state)
{
    unsigned char byte = ((state->bit << 7) | state->bit_count);
    fwrite(&byte, 1, 1, state->tmp_file);
    /* reset the bit_count for the new bit type */
    state->bit_count = 1;
    /* increment the number of flushed bytes so far */
    state->file_length++;
}

static void encode_bit(unsigned char bit, struct encode_state *state)
{
    /* the first bit of the first byte of the file falls into here */
    if (!state->processing)
    {
	state->processing = 1;
	state->bit_count = 1;
	state->bit = bit;
	return;
    }

    assert(state->processing);
    assert(state->bit_count);
    
    /* compare the bit we are looking at, to the most recent bit */
    if (state->bit ^ bit)
    {
	flush_encoded_state(state); /* we have enbit_counted a different bit type */
    }
    else
    {
	state->bit_count++; /* we have enbit_counted the same bit type */
    }

    /* store the bit and move on */
    state->bit = bit;
}

static void encode_byte(unsigned char byte, struct encode_state *state)
{
    unsigned char bit_in_question;

    /* iterate from most significant bit to least */
    int i;
    for (i = 7; i >= 0; i--)
    {
	/* peel off the correct bit */
	bit_in_question = (0x01 & (byte >> i));
	encode_bit(bit_in_question, state);
    }
}

void finish(struct encode_state *state)
{
    flush_encoded_state(state); /* handle the end of file */
    state->processing = 0; /* we are done */
    rewind(state->tmp_file);
    state->file_pointer = xmalloc(state->file_length);
    if(!fread(state->file_pointer, state->file_length, 1, state->tmp_file))
    {
	printf("Error reading file\n");
	exit(-1);
    }
    fclose(state->tmp_file);
}

extern const char *TMP_FILE;
void prepare(struct encode_state *state)
{
    state->processing = 0;
    state->file_length = 0;
    state->tmp_file = Fopen(TMP_FILE, "w+b");
}

struct encode_state * rle_compress(unsigned char *file_pointer, unsigned long long file_length)
{
    struct encode_state *state = (struct encode_state *) xmalloc(sizeof(struct encode_state));
    prepare(state); /* just some internal stuff */

    unsigned long long i;
    for (i = 0; i < file_length; i++)
    {
	encode_byte(file_pointer[i], state);
    }

    finish(state); /* more internal stuff, prepare for huffman */
    return state;
}
