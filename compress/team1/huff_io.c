#include <stdio.h>
#include "huff_io.h"
#include "huff_table.h"

bool is_huff_file(const char* filename){
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return false;
    return strcmp(HUFF_EXT, dot) == 0;
}

bool is_huff_header(FILE* file){
    return true;
}

int get_frequencies(FILE* file, uint64_t* frequencies){
    int code = 0;
    int c;
    do {
        c = fgetc(file);
        if (c != EOF){
            frequencies[c]++;
        } else if (ferror(file)){
            fprintf(stderr, "ERROR: Error while reading characters from file\n");
            return code;
        }
    } while(c != EOF);
    return code;
}

int get_huff_tree(FILE* file, char** huff_table){
    uint64_t frequencies[256];
    int i;
    for (i = 0; i < 256; i++){
        frequencies[i] = 0;
    }
    int code = 0;
    code = get_frequencies(file, frequencies);
    if (!code) gen_huff_table(frequencies, huff_table);
    return code;
}