#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include "huff_table.h"
#include "compress.h"
#include "decompress.h"
#include "rhuff_compress.h"
#include "rhuff_decompress.h"
#include "huff_interface.h"

int CHECK_REP;

int main (int argc, char *argv[])
{
    srand(getpid() + time (NULL));

    if (argc < 3) {
        printf("Must have 2 arguments, -t, -c, or -d filename\n");
        exit(255);
    }

    CHECK_REP = 0;
    // if the last item is the string test, we are going to run the check rep
    if (argc == 4 && !strncmp(argv[argc - 1], "check", 4)) {
        fprintf(stderr, "RUNNING CHECK_REP with file: %s ... ", argv[2]);
        CHECK_REP = 1;
    }


    FILE *input = NULL;
    struct stat sb;
    unsigned long long length = 0;

    if (stat(argv[2], &sb) < 0) {
        printf("File not found\n");
        exit(255);
    }

    input = fopen(argv[2], "r");

    if (input == NULL) {
        printf("Couldn't open file, error code: %i\n", errno);
        exit(255);
    }

    length = sb.st_size;

    if (strncmp(argv[1], "-t", 2) == 0) {
        print_huff_table(input);
    } else if (strncmp(argv[1], "-c", 2) == 0) {
        char *interFileName = "interFile";
        encode(input, interFileName);
        input = fopen(interFileName, "r");
        FILE* output = NULL;
        huff_encode(argv[2] , input , &output);
    } else if (strncmp(argv[1], "-d", 2) == 0) {
        FILE *output = NULL;
        char *interFileName = "interFile";
        huff_decode(interFileName, input, &output);
        char *name = get_decompressed_file_name(argv[2]);
        decode(output, name);
    } else {
        printf("First argument must be -t, -c or -d\n");
        exit(255); 
    }

    fclose(input);
    exit(0);
}
