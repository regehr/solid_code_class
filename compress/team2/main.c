#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include "common.h"
#include "header.h"
#include "tree.h"
#include "encoder.h"
#include "rle.h"

/* Build a frequency table from the given file. Byte frequencies are filled
 * into the supplied 'table', and the size of the file is written into 'length'.
 * If for some strange reason  the file is larger than uint64_t (which I'm
 * pretty sure is impossible), it will return EFILETOOLONG. If a read error
 * occurs, ENOREAD is returned. */
static int build_freqtable(FILE * input, uint64_t table[256], uint64_t *length) {
    uint64_t bytes_read = 0;
    memset(table, 0, 256 * sizeof(uint64_t));

    for(uint8_t current = 0; fread(&current, 1, 1, input); table[current]++) {
        if (bytes_read == UINT64_MAX) { return EFILETOOLONG; }
        bytes_read += 1;
    }

    if (! feof(input)) { return ENOREAD; }

    *length = bytes_read;
    
    return 0;
}

static int compress_file(FILE * output, FILE * input, struct huff_header * header) {
    struct huff_encoder encoder;
    huff_make_encoder(&encoder, header->table);
    fseek(input, 0L, SEEK_SET);
    fseek(output, 0L, SEEK_SET);

    int code = huff_write_header(output, header);
    if (code != 0) { return code; }

    for (uint8_t current = 0; fread(&current, 1, 1, input); ) {
        uint8_t buffer[256 / 8];
        int encoded = huff_encode(current, buffer, &encoder);
        /* If there is encoded output, write it to the output file. If the write
         * fails, exit with ENOWRITE. */
        if (encoded && ! fwrite(buffer, encoded, 1, output)) {
            return ENOWRITE;
        }
    }

    if (! feof(input)) { return ETRUNC; }
    
    /* If there's an extra byte to be written, write it out. Fail with ENOWRITE
     * if the write fails */
    if (encoder.buffer_used &&
        ! fwrite(&encoder.buffer, 1, 1, output)) {
        return ENOWRITE;
    }

    return 0;
}

/* Use RLE encoding to create new rle-encoded file
 * from parameter 'file'. */
static int create_rle_file(FILE * file, FILE * rle_encoded) {
    // Compress input file into temporary file.
    compress_rle(file, rle_encoded);
    
    // Rewind file pointer.
    if (fseek(rle_encoded, 0L, SEEK_SET)) {
        return HUFF_FAILURE;
    }
    else {
        return HUFF_SUCCESS;
    }
}

static int compress(FILE * file, char * filename) {
    uint64_t ftable[256];
    struct huff_header header;
    char * huff_filename = NULL;
    FILE * output = NULL;
    
    /* Open a temp file to store rle encodings. */
    FILE * rle_encoded = tmpfile();
    if (!rle_encoded) { return HUFF_FAILURE; }
    /* Compress 'file' into an rle_encoded file. */
    int code = create_rle_file(file, rle_encoded);
    if (code != 0) { return code; }
    
    /* Build filename. */
    huff_filename = xmalloc(strlen(filename) + HUFF_EXTLEN + 1);
    memcpy(huff_filename, filename, strlen(filename) + 1);
    strcat(huff_filename, HUFF_EXT);
    if (strlen(huff_filename) != strlen(filename) + HUFF_EXTLEN) {
        fprintf(stderr, "Likely memory corruption building compression output file name.\n");
        return HUFF_FAILURE;
    }
    output = xfopen(huff_filename, "w");
    free(huff_filename);

    /* build our translation table and header, then seek to the
     * start of the file */
    build_freqtable(rle_encoded, ftable, &header.length);
    huff_make_table(ftable, header.table);
    code = compress_file(output, rle_encoded, &header);
    huff_free_hdrtable(&header);

    /* Close output file. */
    if (pfclose(output)) {
        return HUFF_FAILURE;
    }
    /* Close temp file. */
    if (pfclose(rle_encoded)) {
        return HUFF_FAILURE;
    }
    /* Check for compression failure. */
    if (code) {
        printf("%s\n", huff_error(code));
        return HUFF_FAILURE;
    }
    return HUFF_SUCCESS;
}

static int decompress_file(FILE * output, FILE * input, struct huff_header * header) {
    struct huff_decoder decoder;
    uint64_t decoded_bytes = 0;
    uint8_t current = 0;
    int decoded = 0;
    huff_make_decoder(&decoder, (const char **) header->table);

    while (fread(&current, 1, 1, input) && decoded_bytes < header->length) {
        for (int i = 7; i >= 0 && decoded_bytes < header->length; i--) {
            decoded = huff_decode((current >> i) & 0x1, &decoder);
            if (decoded > -1) {
                decoded_bytes += 1;
                /* Warning: I believe this is little-endian dependent */
                if (! fwrite(&decoded, 1, 1, output)) { return ENOWRITE; }
            }
        }
    }

    long here = ftell(input);
    fseek(input, 0L, SEEK_END);
    if ((ftell(input) - here) > 0 || decoded_bytes < header->length) {
        return ETRUNC;
    }

    return 0;
}

static int decompress(FILE * file, char * filename) {
    struct huff_header header;
    FILE * huff_output = NULL;
    char * ext_index = NULL;

    int code = huff_read_header(file, filename, &header);
    /* Our header table is implicitly free'd when huff_read_header fails */
    if (code != 0) {
        fprintf(stderr, "Cannot decompress file: %s\n",
                huff_error(code));
        return HUFF_FAILURE;
    }

    /* Find index of filename extension. */
    ext_index = filename + (strlen(filename) - HUFF_EXTLEN);
    if (ext_index > filename && strcmp(ext_index, HUFF_EXT) != 0) {
        fprintf(stderr, "Our file to decompress does not have a .hurl extension.\n");
        return HUFF_FAILURE;
    }
    /* Remove the .hurl extension */
    *ext_index = '\0';

    /* Open file for huffman decompression. */
    huff_output = tmpfile();
    if (!huff_output) { return HUFF_FAILURE; }
    code = decompress_file(huff_output, file, &header);
    huff_free_hdrtable(&header);
    
    /* Rewind rle file pointer. */
    if (fseek(huff_output, 0L, SEEK_SET)) {
        return HUFF_FAILURE;
    }

    /* Send huffman decompressed file through rle decompression. */
    FILE * rle_output = xfopen(filename, "wb");
    decompress_rle(huff_output, rle_output);
    
    /* Close temp file */
    if (pfclose(huff_output)) {
        return HUFF_FAILURE;
    }
    /* Close final decoded file. */
    if (pfclose(rle_output)) {
        return HUFF_FAILURE;
    }
    if (code != 0) {
        fprintf(stderr, "Couldn't decompress: %s\n", huff_error(code));
        return HUFF_FAILURE;
    }
    return HUFF_SUCCESS;
}

static int table(FILE * file, char * filename) {
    struct huff_header header;
    int code = huff_read_header(file, filename, &header);
    if (code != 0) {
        uint64_t ftable[256];
        build_freqtable(file, ftable, &header.length);
        huff_make_table(ftable, header.table);
    }

    for (int i = 0; i < 256; i++) {
        printf("%s\n", header.table[i]);
    }

    huff_free_hdrtable(&header);
    return HUFF_SUCCESS;
}

static void usage(FILE * to) {
    fputs("usage: rhuff [-t | -c | -d] FILE\n"
          "Arguments:\n"
          " -c      Compress the given file.\n"
          " -d      Decompress the given file.\n"
          " -t      Print FILE's compression table. If FILE is uncompressed\n"
          "         then a compression table is generated and printed.\n", to);
}

int main(int argc, char *argv[]) {
    int exit_code = HUFF_FAILURE;
    FILE * input = NULL;

    if (argc != 3) { usage(stderr); exit(HUFF_FAILURE); }

    /* Attempt to open the input file for reading. */
    input = xfopen(argv[2], "r");

    /* Run the appropriate subroutine for the given option. */
    if (strcmp(argv[1], "-c") == 0) {
        exit_code = compress(input, argv[2]);
    } else if (strcmp(argv[1], "-d") == 0) {
        exit_code = decompress(input, argv[2]);
    } else if (strcmp(argv[1], "-t") == 0) {
        exit_code = table(input, argv[2]);
    } else {
        fprintf(stderr, "Invalid mode of operation: '%s'.\n", argv[1]);
        usage(stderr);
    }

    if (pfclose(input)) {
        exit_code = HUFF_FAILURE;
    }

    return exit_code;
}
