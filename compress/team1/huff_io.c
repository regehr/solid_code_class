#include "huff_io.h"

static void read_body_error(){
    fprintf(stderr, "ERROR: Error while reading body from file.\n");
    exit(ERR_CODE);
}

static void read_header_error(){
    fprintf(stderr, "ERROR: Error while reading header from file.\n");
    exit(ERR_CODE);
}

static void write_header_error(){
    fprintf(stderr, "ERROR: Error while writing header to file.\n");
    exit(ERR_CODE);
}

static void write_body_error(){
    fprintf(stderr, "ERROR: Error while writing body to file.\n");
    exit(ERR_CODE);
}

static void read_file_error(){
	fprintf(stderr, "ERROR: Error while attempting to read file.\n");
	exit(ERR_CODE);
}

bool is_huff_file(const char* filename){
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return false;
    return strcmp(HUFF_EXT, dot) == 0;
}

char* remove_ext(const char* filename) {
    char *retstr;
    char *lastdot;
    if (filename == NULL)
        return NULL;
    if ((retstr = malloc (strlen (filename) + 1)) == NULL){
		fprintf(stderr, "Malloc Error.\n");
        exit(ERR_CODE);
    }
    strcpy (retstr, filename);
    lastdot = strrchr (retstr, '.');
    if (lastdot != NULL)
        *lastdot = '\0';
    return retstr;
}

bool get_huff_header(FILE* file, unsigned long long* size, bool print){
    int num_string = 256;
    int str_length = 257;
    char magic[strlen(MAGIC_NUM)+1];
    char* huff_table[num_string];
    
    // Init array
    int i;
	for (i = 0; i < num_string; i++){
        huff_table[i] =  malloc(str_length);
        if (huff_table[i] == NULL){
            read_header_error();
        }
    }
    
    int curr_char;
    // Read magic number
    for(i = 0; i < strlen(MAGIC_NUM); i++)
    {
    	curr_char = fgetc(file);
    	if(curr_char == EOF || ferror(file))
    		read_header_error();
    		
    	magic[i] = (char)curr_char;
    }
   	magic[i] = '\0'; //Add null terminator

    if(strcmp(magic, MAGIC_NUM) != 0)
        return false;
    
    // Read content length
    if (fread(size, 8, 1, file) != 1){
        read_header_error();
    }
    
    // Read huff table
    int j;
    for (i = 0; i < num_string; i++){
        char line[str_length];
        for(j = 0; j < str_length; j++){
            int c = fgetc(file);
            if (ferror(file)){
                read_header_error();
            } else if (c != '\n'){
                line[j] = c;
            } else {
                line[j] = '\0';
                break;
            }
        }
        strcpy(huff_table[i], line);
    }
    build_tree_tbl(huff_table);
    
    if (print){
	    for (i = 0; i < 256; i++){
        	printf("%s\n", huff_table[i]);
    	}
    }
    
    // free mem
    for (i = 0; i < num_string; i++){
        free(huff_table[i]);
    }
    
    return true;
}

/**
 *	Gets the character frequencies from the file given and outputs them to the integer array.
 * 	The array must be a length of 256. Returns 0 if the operation succeded.
 */
static void get_frequencies(FILE* file, uint64_t* frequencies){
    int c = 0;
    do {
        c = fgetc(file);
        if(c != EOF)
        	frequencies[c]++;
        else if(ferror(file))
        {
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
    int res = stat(filename, &st);
    if(res != 0)
    {
    	printf("%d\n", res);
    	read_file_error();
    	}
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
            || fputc('\n', file) 		== EOF)
        {
            write_header_error();
        }
    }
}

static int current_bit = 7;
static unsigned char bit_buffer = 0;

/**
 *	Takes a single bit as input and writes out to the file once 
 * 	a byte has been filled.
 */
static void write_bit (int bit, FILE* file)
{
    assert(bit == 1 || bit == 0);
    if (bit)
        bit_buffer |= (1<<current_bit);
    
    current_bit--;
    if (current_bit == -1)
    {
        if (fwrite (&bit_buffer, 1, 1, file) != 1){
            write_body_error();
        }
        current_bit = 7;
        bit_buffer = 0;
    }
}

/**
 *	Filles the rest of the byte with 0's and writes to file.
 */
static void flush_bits (FILE* file)
{
    while (current_bit)
        write_bit (0, file);
    
    // Write final byte.
    if (fwrite (&bit_buffer, 1, 1, file) != 1){
        write_body_error();
    }
}

void write_huff_body(FILE* original, FILE* newfile, unsigned long long size){
    rewind(original);
    
    // Read character and output corresponding encoding
    int c, i;
    do {
        c = fgetc(original);
        if (c != EOF){
            char* code_string = get_code(c);
            for (i = 0; code_string[i] != '\0'; i++){
                int bit = (code_string[i] - '0');
                write_bit(bit, newfile);
            }
        } else if (ferror(original)){
            write_body_error();
        }
    } while (c != EOF);
    flush_bits(newfile);
}

void read_huff_body(FILE* compressed, FILE* decompressed, unsigned long long size){
    
    // Read characters and write to decompresed file
    int c = 0, i = 0;
    unsigned long long bytes_read = 0;
    char in, out;
	while (c != EOF){
        c = fgetc(compressed);
        if (c != EOF){
            // Loop throught the bits of a byte
            for (i = 7; i >= 0; i--){
                in = (c >> i) & 0x01;
                if (get_char(in, &out)){
                    if(fputc(out, decompressed) == EOF){
                        read_body_error();
                    }
                    if (++bytes_read == size)
                        break;
                }
            }
        } else if (ferror(compressed)){
            read_body_error();
        }
    }
}
