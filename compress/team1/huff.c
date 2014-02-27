/*
 *
 */

#include "huff_tree.h"
#include "huff_io.h"
#include "rle.h"
#include <stdio.h>

static char* TEMP_FILE = "temp_file";

void print_tree(FILE* file, const char* filename){
    
    // Get table from file or generate
    if (is_huff_file(filename)){
        unsigned long long size = get_file_size(filename);
        if(!get_huff_header(file, &size, true)){
            fprintf(stderr, "File is in incorrect format\n.");
            exit(ERR_CODE);
        }
    } else {
        
        //get rle encoding
        unsigned char* rle_encoding = NULL;
        unsigned long long encoding_length = 0;
        encode_rle(file, &rle_encoding, &encoding_length );
        //save to temp file
        FILE* temp_file = tmpfile();
        write_array_to_file(rle_encoding, encoding_length, temp_file);
        //rewind temp file to the beginning of the stream.
        rewind(temp_file);
        gen_huff_tree(temp_file);
        //close temp file
        fclose(temp_file);
        //temp file is auto deleted when fclose is called.
        //http://www.cplusplus.com/reference/cstdio/tmpfile/
        
        // Print table
        int i;
        for(i = 0; i < 256; i++)
            printf("%s\n", get_code(i));
        free_huff_tree();
    }
}

void compress(FILE *original_file, const char* filename){
    if( fseek(original_file, 0, SEEK_END) ){
        fprintf(stderr, "ERROR: Could not get file size of file %s\n", filename);
    }
    
    unsigned long long size = ftell(original_file);
    rewind(original_file);
    
//    // Ignore files with huff extension
//    if (is_huff_file(filename)){
//        return;
//    }
    

    
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
    if(!get_huff_header(compressed, &size, false)){
        fprintf(stderr, "File is in incorrect format\n.");
        exit(ERR_CODE);
    }
    
    // Create file from huff
    FILE* decompressed = fopen((TEMP_FILE), "w");
    if (decompressed == NULL){
        fprintf(stderr, "ERROR: Could not create file %s\n", filename);
        exit(ERR_CODE);
    }
    //
    // Write out decompressed file
    read_huff_body(compressed, decompressed, size);
    fclose(decompressed);
    free_huff_tree();
}

int main(int argc, const char *argv[])
{
    // Proper use
    if (argc != 3){
        fprintf(stderr, "ERROR:\nProper use:\n rhuff [ -c | -d | -t ] file\n");
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
        //TODO: compress 
        
        //get rle encoding
        unsigned char* rle_encoding = NULL;
        unsigned long long encoding_length = 0;
        encode_rle(fp, &rle_encoding, &encoding_length );
        //save to temp file
        FILE* temp_file = tmpfile();
        write_array_to_file(rle_encoding, encoding_length, temp_file);
        //rewind temp file to the beginning of the stream.

        compress(temp_file, argv[2]);
        
        //close temp file
        fclose(temp_file);
        
        
        
//<--------------------------------------
//<--------------------------------------    
    
    
    } else if (strcmp(argv[1], "-d") == 0){
        decompress(fp, argv[2]);
        //TODO:
        //open temp_file for reading
        FILE* temp_file = fopen((TEMP_FILE), "r");
    if (temp_file == NULL){
        fprintf(stderr, "ERROR: Could not create file %s\n", TEMP_FILE);
        exit(ERR_CODE);
    }
        //create rle_encoded array
        unsigned char* rle_encoding = NULL;
        unsigned long long encoding_length = 0;
        printf("made it here.\n");
        encoding_length = file_to_char_array(temp_file, &rle_encoding);
        printf("length: %llu\n", encoding_length);
        fclose(temp_file);
        //send to decode_rle to be decoded
        char* newfile = remove_ext(argv[2]);
        FILE* decompressed = fopen(newfile, "w");
        if (decompressed == NULL){
        fprintf(stderr, "ERROR: Could not create file %s\n", newfile);
        exit(ERR_CODE);
        }

        decode_rle(rle_encoding, &encoding_length, decompressed);
        fclose(temp_file);
        remove(TEMP_FILE);
        fclose(decompressed);
    } else if (strcmp(argv[1], "-t") == 0){
        print_tree(fp, argv[2]);
    } else {
        fprintf(stderr, "ERROR:\nInvalid operation %s\n", argv[1]);
    }
    
    fclose(fp);
    return 0;
}
