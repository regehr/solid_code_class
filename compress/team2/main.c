#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "internal.h"
#include "parser.h"
#include "huff.h"
#include "encode.h"

/* build a frequency table from the given file. If for some strange reason
 * the file is larger than uint64_t (which I'm pretty sure is impossible),
 * it will return EFILETOOLONG. Otherwise, byte frequencies are filled into the
 * supplied 'table', and the size of the file is written into 'length'. */
static int build_freqtable(FILE * input, uint64_t table[256], uint64_t *length) {
    uint8_t current = 0;
    uint64_t bytes_read = 0;
    memset(table, 0, 256 * sizeof(uint64_t));

    for (; fread(&current, 1, 1, input); table[current] += 1) {
        bytes_read += 1;
        /* if the byte counter overflows, then the file is too long */
        if (bytes_read == 0) { return EFILETOOLONG; }
    }

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

    int encoded = 0;
    uint8_t current, buffer[32]; 
    while (fread(&current, 1, 1, input)) {
        encoded = huff_encode(current, buffer, &encoder);
        /* If there is encoded output, write it to the output file. If the write
         * fails exit with ENOWRITE. */
        if (encoded && ! fwrite(buffer, encoded, 1, output)) {
            return ENOWRITE;
        }
    }
    if (! feof(input)) { return ETRUNC; }

    /* Theres an extra byte to be written, write it out and fail with ENOWRITE
     * if the write fails */
    if (encoder.buffer != 0 && 
        ! fwrite(&encoder.buffer, 1, 1, output)) { 
        return ENOWRITE; 
    }

    return 0;
}

static int compress(FILE * file, char * filename) {
    uint64_t ftable[256];
    struct huff_header header;
    char * huff_filename = NULL;
    FILE * output = NULL;

    huff_filename = xmalloc(strlen(filename) + HUFF_EXTLEN + 1);
    memcpy(huff_filename, filename, strlen(filename) + 1);
    strcat(huff_filename, HUFF_EXT);

    assert(strlen(huff_filename) == strlen(filename) + HUFF_EXTLEN &&
           "Likely memory corruption building compression output file name");

    output = xfopen(huff_filename, "w");
    free(huff_filename);

    /* build our translation table and header, then seek to the 
     * start of the file */
    build_freqtable(file, ftable, &header.size);
    huff_make_table(ftable, header.table);

    int code = compress_file(output, file, &header);

    huff_free_hdrtable(&header);

    /* close our files */
    if (pfclose(output)) {
        return HUFF_FAILURE;
    } else if (code) {
        printf("%s\n", huff_error(code));
        return HUFF_FAILURE;
    }
    return HUFF_SUCCESS;
}

static int decompress(UNUSED(FILE * file), UNUSED(char * filename)) {
    return HUFF_FAILURE;
}

static int table(FILE * file, char * filename) {
    struct huff_header header;
    int code = huff_read_header(file, filename, &header);
    if (code != 0) {
        uint64_t ftable[256];
        build_freqtable(file, ftable, &header.size);
        huff_make_table(ftable, header.table);
    }

    for (int i = 0; i < 256; i++) {
        printf("%s\n", header.table[i]);
    }

    huff_free_hdrtable(&header);
    return HUFF_SUCCESS;
}

static void usage(FILE * to) {
    fputs("usage: huff [-t | -c | -d] FILE\n"
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

    /* attempt to open the input file for reading */
    input = xfopen(argv[2], "r"); 

    /* run the appropriate subroutine for the given option */
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
