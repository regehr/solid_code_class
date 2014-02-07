/*
 *
 */

#include "huff_treee.h"
#include "huff_io.h"

void print_tree(FILE* file, const char* filename){
    char* huff_table[256];

    // Get table from file or generate
    if (is_huff_file(filename)){
        unsigned long long size = get_file_size(filename);
        get_huff_header(file, &size, huff_table);
    } else {
        get_huff_tree(file, huff_table);
    }
    
    // Print table
    int i;
    for(i = 0; i < 256; i++)
        printf("%s\n", huff_table[i]);
}

void compress(FILE *original_file, const char* filename){
    char* huff_table[256];
    unsigned long long size = get_file_size(filename);

    // Ignore files with huff extension
    if (is_huff_file(filename)){
        return;
    }
    
    // Create huff file
    strcat((char*)filename, HUFF_EXT);
    FILE* newfile = fopen((filename), "w");
    if (newfile == NULL){
        fprintf(stderr, "ERROR: Could not create file %s\n", filename);
        exit(ERR_CODE);
    }
    
    // Write header
    get_huff_tree(original_file, huff_table);
    write_huff_header(newfile, size, huff_table);
    
    // Write body
    write_huff_body(original_file, newfile, size, huff_table);
    
    if (EOF == fclose(newfile)){
        fprintf(stderr, "ERROR: Could save file %s\n", filename);
        exit(ERR_CODE);
    }
}

void decompress(FILE *file, const char* filename){
    char* huff_table[256];
    unsigned long long size;
    
    if(!is_huff_file(filename)){
        fprintf(stderr, "File is not a huff file.\n");
        exit(ERR_CODE);
    }
    
    size = get_file_size(filename);
    get_huff_header(file, &size, huff_table);
    
}

int main(int argc, const char *argv[])
{
    // Proper use
    if (argc != 3){
        fprintf(stderr, "ERROR:\nProper use:\n huff [ -c | -d | -t ] file\n");
        exit(ERR_CODE);
    }

    // Valid file
    FILE *fp;
    fp = fopen(argv[2], "r");
    if (fp == NULL){
        fprintf(stderr, "ERROR:\nCould not open file %s\n", argv[2]);
        exit(ERR_CODE);
    }
    
    if (strcmp(argv[1], "-c") == 0){
        compress(fp, argv[2]);
    } else if (strcmp(argv[1], "-d") == 0){
        decompress(fp, argv[2]);
    } else if (strcmp(argv[1], "-t") == 0){
        print_tree(fp, argv[2]);
    } else {
        fprintf(stderr, "ERROR:\nInvalid operation %s\n", argv[1]);
    }
    
    fclose(fp);
    return 0;
}
