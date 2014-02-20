
#include <stdio.h>
#include <assert.h>
#include "rle.h"

/*
 * internal struct that acts as my scrolling window view of the file
 * It holds the current bit in the file, and a simple counter
*/
struct encoding_state
{
    unsigned char counter; /* the number of repeated occurrences of bit */
    unsigned char bit; /* the current bit we are looking at */
    unsigned char processing; /* 1 if we have begun to process the file, 0 before that */
};

static void flush(struct encoding_state *state, FILE *out_file)
{
    unsigned char byte = ((state->bit << 7) | state->counter);
    fwrite(&byte, 1, 1, out_file);
    /* reset the counter for the new bit type */
    state->counter = 1;

}

static void process_bit(unsigned char bit, struct encoding_state *state, FILE *out_file)
{
    /* the first bit of the first byte of the file falls into here */
    if (!state->processing)
    {
	state->processing = 1;
	state->counter = 1;
	state->bit = bit;
	return;
    }

    assert(state->processing);
    assert(state->counter);
    
    /* compare the bit we are looking at, to the most recent bit */
    if (state->bit ^ bit)
    {
	/* we have encountered a different bit type */
	flush(state, out_file);
    }
    else
    {
	/* we have encountered the same bit type */
	state->counter++;
    }

    /* move to the next bit */
    state->bit = bit;
}

static void process_byte(unsigned char byte, struct encoding_state *state, FILE *out_file)
{
    unsigned char bit_in_question;

    /* iterate from most significant bit to least */
    int i;
    for (i = 7; i >= 0; i--)
    {
	/* peel off the correct bit */
	bit_in_question = (0x01 & (byte >> i));
	process_bit(bit_in_question, state, out_file);
    }
}

long long rle_pre_compress(unsigned char *file_pointer, long long file_length, char *file_name)
{

    FILE *out_file = fopen(FANCY_FILE_NAME, "rw+");
    if (!out_file)
    {
	printf("failed to open file\n");
	exit(-1);
    }
    struct encoding_state state = { .processing = 0 };
    long long i;    
    for (i = 0; i < file_length; i++)
    {
	process_byte(file_pointer[i], &state, out_file);
    }

    flush(&state, out_file); /* handle the end of file */
    assert(state.counter == 1); /* cleanup check */

    /* give the huffman encoder the file just created */
    file_pointer = (unsigned char *)out_file;
    return 0;
}

void rle_pre_print(unsigned char *file_pointer, long long file_length, char *file_name)
{
    return;
}
