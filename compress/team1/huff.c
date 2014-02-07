/*
 *
 */

#include "huff_tree.h"
#include "huff_io.h"

void print_tree(FILE* file, const char* filename){
    
    // Get table from file or generate
    if (is_huff_file(filename)){
        unsigned long long size = get_file_size(filename);
        if(!get_huff_header(file, &size)){
            fprintf(stderr, "File is in incorrect format\n.");
            exit(ERR_CODE);
        }
    } else {
        gen_huff_tree(file);
    }
    
    // Print table
    int i;
    for(i = 0; i < 256; i++)
        printf("%s\n", get_code(i));
    free_huff_tree();
}

void compress(FILE *original_file, const char* filename){
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
    gen_huff_tree(original_file);
    write_huff_header(newfile, size);
    
    // Write body
    write_huff_body(original_file, newfile, size);
    
    free_huff_tree();
    if (EOF == fclose(newfile)){
        fprintf(stderr, "ERROR: Could save file %s\n", filename);
        exit(ERR_CODE);
    }
}

void decompress(FILE *compressed, const char* filename){
    unsigned long long size;
    
    if(!is_huff_file(filename)){
        fprintf(stderr, "File is not a huff file.\n");
        exit(ERR_CODE);
    }
    
    // Get the header
    size = get_file_size(filename);
    if(!get_huff_header(compressed, &size)){
        fprintf(stderr, "File is in incorrect format\n.");
        exit(ERR_CODE);
    }
    
    // Create file from huff
    strcat((char*)filename, HUFF_EXT);
    FILE* decompressed = fopen((filename), "w");
    if (decompressed == NULL){
        fprintf(stderr, "ERROR: Could not create file %s\n", filename);
        exit(ERR_CODE);
    }
    
    // Write out decompressed file
    read_huff_body(compressed, decompressed, size);
    
    free_huff_tree();
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
