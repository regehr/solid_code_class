#include "huff_io.h"

bool is_huff_file(const char* filename){
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return false;
    return strcmp(HUFF_EXT, dot) == 0;
}

static void read_header_error(){
    fprintf(stderr, "ERROR: Error while header from file\n");
    exit(ERR_CODE);
}

static void write_header_error(){
    fprintf(stderr, "ERROR: Error while writing header to file\n");
    exit(ERR_CODE);
}

static void write_body_error(){
    fprintf(stderr, "ERROR: Error while writing body to file.\n");
    exit(ERR_CODE);
}

bool get_huff_header(FILE* file, unsigned long long* size){
    char magic[5];
    char* huff_table[256];
    
    // Read magic number
    magic[0] = fgetc(file);
    magic[1] = fgetc(file);
    magic[2] = fgetc(file);
    magic[3] = fgetc(file);
    magic[4] = '\0';
    if (ferror(file)){
        read_header_error();
    }
    if(strcmp(magic, MAGIC_NUM) != 0){
        return false;
    }
    
    // Read content length
    if (fread(size, sizeof(size), 1, file) != 1){
        read_header_error();
    }
    
    // Read huff table
    int i;
    char line[258];
    for (i = 0; i < 256; i++){
        if (fgets(line, 258, file) == NULL){
            read_header_error();
        }
        huff_table[i] = line;
    }
	gen_tree_tbl(huff_table);
    return true;
}

/**
 *	Gets the character frequencies from the file given and outputs them to the integer array.
 * 	The array must be a length of 256. Returns 0 if the operation succeded.
 */
static void get_frequencies(FILE* file, uint64_t* frequencies){
    int c;
    do {
        c = fgetc(file);
        if (c != EOF){
            frequencies[c]++;
        } else if (ferror(file)){
            fprintf(stderr, "ERROR: Error while reading characters from file\n");
            exit(ERR_CODE);
        }
    } while(c != EOF);
}

void gen_huff_tree(FILE* file){
    uint64_t frequencies[256];
    
    // Initialize frequencies
    int i;
	for (i = 0; i < 256; i++){
        frequencies[i] = 0;
    }
    get_frequencies(file, frequencies);
    gen_tree_frq(frequencies);
}

unsigned long long get_file_size(const char* filename){
    struct stat st;
    stat(filename, &st);
    return (unsigned long long)st.st_size;
}

void write_huff_header(FILE* file, unsigned long long filesize){
    
    // Write magic number
    if (fprintf(file, MAGIC_NUM) < 0){
        write_header_error();
    }
    
    // Write the length out
    if (fwrite(&filesize, sizeof(filesize), 1, file) != 1){
        write_header_error();
    }
    
    // Write huff_table
    int i;
    for (i = 0; i < 256; i++){
       	if (fputs(get_code(i), file) 	== EOF
            || fputc('\0', file) 		== EOF
            || fputc('\n', file) 		== EOF)
        {
            write_header_error();
        }
    }
}

void write_huff_body(FILE* original, FILE* newfile, unsigned long long size){
    rewind(original);
    
    // Read character and output corresponding encoding
    int c;
    do {
        c = fgetc(original);
        if (c != EOF){
            char* code_string = get_code(c);
            if(fputs(code_string, newfile) == EOF){
                write_body_error();
            }
        } else if (ferror(original)){
            write_body_error();
        }
    } while (c != EOF);
}

void read_huff_body(FILE* compressed, FILE* decompressed, unsigned long long size){
    
    // Read characters 
}