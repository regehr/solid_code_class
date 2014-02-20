/* Daniel Setser
 * Date: February 2014
 *
 * Additions made by Keith Richards
 * February 2014
 * Entry point for huffman encoding implementation
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "tree.h"
#include "io.h"
#include "rle_encode.h"
#include "rle_decode.h"

/* name of a temporary file used in encoding, decoding, and other fun things */
const char *TMP_FILE = "/tmp/HisMajestyBarackHObama";

/* Compresses the file and writes out the new huff file */
void compress(unsigned char* file_pointer, unsigned long long file_length, char* filename)
{
    unsigned long long frequencies[256] = {0};
    find_frequencies(frequencies, file_pointer, file_length);

    char* mapping = get_huffman_table(frequencies);
    write_compressed_file(file_pointer, file_length, filename, mapping);
    free(mapping);
}

/* Decompresses the huff file and writes out the original file */
/* Not so much any more. it writes out a tmp file, namely /tmp/HisMajestyBarackHObama */
void decompress(unsigned char* file_pointer, unsigned long long file_length, char* filename)
{
    if(!check_format(file_pointer, file_length, filename))
    {
        printf("Can't decompress a non-hurl file.\n");
        exit(-1);
    }

    
    unsigned long long start_of_compressed;
    char* mapping = get_mapping_from_file(file_pointer, file_length, &start_of_compressed);
    write_decompressed_file(file_pointer, file_length, filename, mapping, start_of_compressed);
    free(mapping);
}

/* Prints out the table mapping bytes to huffman codes */
void print_table(unsigned char* file_pointer, unsigned long long file_length, char* filename)
{
    /* If this is a huff file, get it from the table in the file. Otherwise calculate it from the file */
    if(check_format(file_pointer, file_length, filename))
    {
        unsigned long long start_of_compressed;
        char* mapping = get_mapping_from_file(file_pointer, file_length, &start_of_compressed);
        printf("%s\n", mapping);
        free(mapping);
    }
    else
    {
        unsigned long long frequencies[256] = {0};
        find_frequencies(frequencies, file_pointer, file_length);

        char* mapping = get_huffman_table(frequencies);
        printf("%s", mapping);
        free(mapping);
    }
}


/* Entry point for the program. Opens the file, and executes the mode specified by command line args */
int main(int argc, char* argv[])
{
    if(argc != 3 || (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-d") != 0 && strcmp(argv[1], "-t") != 0))
    {
        printf("usage: rhuff [-c | -d | -t] file\n");
        return -1;
    }

    /* Open the file in a buffer */
    unsigned long long file_length;
    struct stat sb;
    if(stat(argv[2], &sb) < 0)
    {
        printf("File not found\n");
        exit(-1);
    }

    FILE* file = fopen(argv[2], "r");
    if(file == NULL)
    {
        printf("Error opening file\n");
        exit(-1);
    }
    file_length = sb.st_size;

    unsigned char* file_pointer = malloc(file_length * sizeof(unsigned char));
    if(file_pointer == NULL)
    {
        printf("Malloc failed, exiting.\n");
        exit(-1);
    }

    if(file_length != 0)
    {
        if(!fread(file_pointer, file_length, 1, file))
        {
            printf("Error reading file\n");
            exit(-1);
        }
        fclose(file);
    }

    /*
     * Admiral Ackbar says: 'It's a trap!'
     * 
     * Compressiong write a temporary file after rle encoding, then opens that file and
     * runs the huffman encoding on it.
     *
     * Decompression writes a temporary file after huffman decompression, then 
     * opens that file and runs rle decompression on it.
     */

    if(strcmp(argv[1], "-c") == 0)
    {
	/* This struct is super cool!
	   It contains a file_pointer and the length just like the compress function wants! */
	struct encode_state *state = rle_compress(file_pointer, file_length);
	/* be the change you want to see in the world */
        compress(state->file_pointer, state->file_length, argv[2]);
	/* that state is in bondage! Let's free it */
	free(state);
    }
    else if(strcmp(argv[1], "-d") == 0)
    {
        decompress(file_pointer, file_length, argv[2]);
	/* this struct is very cool!
	   It contains a file_pointer and the length just like the decompress wants! */
	struct decode_state *state = prepare_file_for_decode(argv[2]);
	/* here is some change you can believe in ! */
	rle_decompress(state);
	/* this state is in SERIOUS jeapordy! Free it!!! */
	free(state);
    }
    else if(strcmp(argv[1], "-t") == 0)
    {
        print_table(file_pointer, file_length, argv[2]);
    }
    
    free(file_pointer);

    return 0;
}
