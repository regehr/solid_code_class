/*
 *
 */

#include "huff_table.h"
#include "huff_io.h"

int print_tree(FILE* file, const char* filename){
    char* huff_table[256];
    int code = 0;

    if (is_huff_file(filename) && is_huff_header(file)){
        // get the table from the file
        fprintf(stderr, "ERROR: Get table from huff file not implemented\n");
		code = ERR_CODE;
    } else {
        code = get_huff_tree(file, huff_table);
    }
    
    // Print table
    if (!code){
    	int i;
    	for(i = 0; i < 256; i++)
	        printf("%s\n", huff_table[i]);
    }
    return code;
}

int compress(FILE *file, const char* filename){
    return ERR_CODE;
}

int decompress(FILE *file, const char* filename){
    return ERR_CODE;
}

int main(int argc, const char *argv[])
{
    int exit_code = ERR_CODE;
    
    // Proper use
    if (argc != 3){
        fprintf(stderr, "ERROR:\nProper use:\n huff [ -c | -d | -t ] file\n");
        exit(exit_code);
    }

    // Valid file
    FILE *fp;
    fp = fopen(argv[2], "r");
    if (fp == NULL){
        fprintf(stderr, "ERROR:\nCould not open file %s\n", argv[2]);
        exit(exit_code);
    }
    
    if (strcmp(argv[1], "-c") == 0){
        exit_code = compress(fp, argv[2]);
    } else if (strcmp(argv[1], "-d") == 0){
        exit_code = decompress(fp, argv[2]);
    } else if (strcmp(argv[1], "-t") == 0){
        exit_code = print_tree(fp, argv[2]);
    } else {
        fprintf(stderr, "ERROR:\nInvalid operation %s\n", argv[1]);
    }
    
    fclose(fp);
    return exit_code;
}
