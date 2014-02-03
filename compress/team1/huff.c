/*
 *
 */

#include "huff_table.h"
#include "huff_io.h"
#define ERR_CODE 255

int compress(FILE *file, char* filename){
    return ERR_CODE;
}

int decompress(FILE *file, char* filename){
    return ERR_CODE;
}

int print_tree(FILE *file, char* filename){
    char *huff_table[256];
    uint64_t frequencies[256];
    
    if (is_huff_file(filename) && is_huff_header(file)){
        // get the table from the file
        return ERR_CODE;
    }
    
    // Else, calculate the table
    
    
    return 0;
}

int main(int argc, const char *argv[])
{
    int exit_code = ERR_CODE;
    
    // Proper use
    if (argc != 3){
        fprintf(stderr, "Proper use:\n huff [ -c | -d | -t ] file\n");
        exit(exit_code);
    }
    
    // Valid file
    FILE *fp;
    fp = fopen(argv[2], "r");
    if (fp == NULL){
        fprintf(stderr, "Could not open file %s\n", argv[2]);
        exit(exit_code);
    }
    
    if (strcmp(argv[1], "-c") == 0){
        exit_code = compress(fp, argv[2]);
    } else if (strcmp(argv[1], "-d") == 0){
        exit_code = decompress(fp, argv[2]);
    } else if (strcmp(argv[1], "-t") == 0){
        exit_code = print_tree(fp, argv[2]);
    } else {
        fprintf(stderr, "Invalid operation %s\n", argv[1]);
    }
    
    fclose(fp);
    return exit_code;
}
