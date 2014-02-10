#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "huff.h"
#include "huff_table.h"

/*
 * "Do something reasonable." ~ A Certain Professor
 */
int main(int argc, char* argv[])
{
	//Initial check for correct arg count
	if(argc != 3)
	{
		printf("Invalid number of parameters. Huff requires a flag (-c, -d, -t), and a filename as parameters.\n");
		return ERR;
	}
	
	//Determine flag and filename
	enum Flags given_flag = determine_flag(argv[1]);
	char* filename = argv[2];
	
	FILE* file = open_file(filename, "r");
	
	switch(given_flag)
	{
		case COMPRESS:
			compress(file, filename);
			break;
		case DECOMPRESS:
			decompress(file, filename);
			break;
		case DUMP:
			dump(file, filename);
			break;
		case INVALID:
			printf("Invalid flag given. Expected one of the following: -c, -d, -t.\n");
			return ERR;
	}
	
	fclose(file);
	
	return 0;
}

FILE* open_file(char* filename, char* permission)
{
	//Attempt to open the file
	FILE* file = fopen(filename, permission);
	
	//Ensure we can open the file
	if(file == NULL)
	{
		printf("Unable to open file: %s, with given permission: %s\n", filename, permission);
		exit(ERR);
	}
	
	return file;
}

void compress(FILE* file, char* filename)
{
	//Check if file is already a .huff
	if(is_huff_type(filename))
		return;
		
	//Cat filename with extension
	strcat(filename, EXT);
	
	//Open the file
	FILE* comp_file = open_file(filename, "w");
	
	unsigned long long size = det_file_size(file);
	
	int i;
	int freq_table[256];
	for(i = 0; i < 256; i++)
		freq_table[i] = 0;
	
	//Determine frequency/encoding tables
	create_freq_table(freq_table, file, size);	
        huff_node* huff_tree = create_huff_tree_from_frequency(freq_table);
	char** encoded_table = get_encoding(huff_tree);
        
	
	assert(encoded_table != NULL);
	
	//Write data
	write_compressed_file(comp_file, file, encoded_table, size);
	
	//Close the file
	fclose(comp_file);
        
        //free memory
        destroy_huff_tree(huff_tree);
        free(encoded_table);
}

void decompress(FILE* file, char* filename)
{
	//Check if file isnt a .huff
	if(!is_huff_type(filename))
		printf("Given file is not a .huff\n");
		
        char** encoding = 0;
	//TODO:Get huff table
        huff_node* huff_tree = create_huff_tree_from_encoding(encoding);
	
	//TODO:Decode data based on table
            // 0 for zero bit, true for one bit
            int one_bit = 1;
            //get_next_character return -1 if another bit is needed
            //otherwise it will return 0 - 255
            int result = get_next_character(huff_tree, one_bit);
            while(result == -1){
                //TODO set one_bit
                result = get_next_character(huff_tree, one_bit);
            }
	
	//TODO:Open new file
	
	//TODO:Write decompressed data to file
	
	//TODO:Close the file
}

void dump(FILE* file, char* filename)
{
	char** encoded_table = NULL;
	int i;		
	unsigned long long file_size = det_file_size(file);
	
	//Check if file is .huff
	if(is_huff_type(filename))
	{
		file_size = det_file_size(file);
		get_huff_table(encoded_table, file, &file_size);
	}
	else
	{
		int freq_table[256];
		for(i = 0; i < 256; i++)
			freq_table[i] = 0;
			
		create_freq_table(freq_table, file, file_size);
		
		//for(i = 0; i < 256; i++)
		//	printf("%i\n", freq_table[i]);
		
		encoded_table = get_encoding(create_huff_tree_from_frequency(freq_table));
	}
	
	assert(encoded_table != NULL);

	for(i = 0; i < 256; i++)
		printf("%s\n", encoded_table[i]);
}

void create_freq_table(int table[], FILE* file, unsigned long long size)
{
	unsigned long long i;
	char c;
	
	for(i = 0; i < size; i++)
	{
		c = fgetc(file);
		table[(int)c]++;
	}
}

bool is_huff_type(char* filename)
{
	//Last occurance of "."
	char* file_type = strrchr(filename, '.');
	
	//Error check
	if(file_type == NULL)
		return false;
		
	//Compare with huff extension
	return (strcmp(file_type, EXT) == 0);
}

unsigned long long det_file_size(FILE* file)
{
	//Go to end
	fseek(file, 0L, SEEK_END);
	
	//Count bytes
	unsigned long long file_length = ftell(file);
	
	//Rewind file
	rewind(file);
	
	return file_length;
}

void get_huff_table(char** huff_table, FILE* file, unsigned long long* size)
{
	char* magic_num = "";
	
	//Read magic number
	fread(magic_num, 4, 1, file);
	
	//If not the proper number
	if(strcmp(magic_num, NUM) != 0)
	{
		printf("Improper huff magic number.\n");
		exit(ERR);
	}
	
	//Get huff length
	int res = fread(size, 8, 1, file);
	
	//Check that we read a file length
	if(res != 1)
	{
		printf("Improper huff uncompressed file length.\n");
		exit(ERR);
	}
	
	//Generate the encoded table
	char max_line_length[258]; //258 since max length is 256, plus 2 for the \n
	int i;
	
	for(i = 0; i < 256; i++)
	{
		fgets(max_line_length, 258, file);
		
		if(max_line_length == NULL)
		{
			printf("Improper huff encoding table.\n");
			exit(ERR);
		}
		
		huff_table[i] = max_line_length;
	}
}

enum Flags determine_flag(char* user_flag)
{
	if(strcmp(user_flag, "-c") == 0)
		return COMPRESS;
	else if(strcmp(user_flag, "-d") == 0)
		return DECOMPRESS;
	else if(strcmp(user_flag, "-t") == 0)
		return DUMP;
	else
		return INVALID;
}

void write_compressed_file(FILE* comp_file, FILE* orig_file, char** encoded_table, unsigned long long file_size)
{
	int res;
	//Write magic number
	//Apparently fprintf is used for strings?
	res = fprintf(comp_file, NUM);
	assert(res > 0 && "Error occured when writing magic number to file.");
	
	//Write file size
	//And fwrite is for binary data >.>
	res = fwrite(&file_size, 8, 1, comp_file);
	assert(res != 8 && "Error occured when writing length to file.");
	
	//Write encoded table
	//Also, fputs apparently appends "\n" for you, what the hell C
	int i;
	for(i = 0; i < 256; i++)
	{
		res = fputs(encoded_table[i], comp_file);
		assert(res > 0 && "Error occured when writing huff table to file.");
	}
	
	//Write compressed data
	rewind(orig_file);
	
	int curr_char;
	char* encoded_char;
	curr_char = fgetc(orig_file);
	
	while(curr_char != EOF)
	{
		encoded_char = encoded_table[(int)curr_char];
		
		int write_res = fputs(encoded_char, comp_file);
		assert(write_res != EOF && "Error occured when writing huff body.");
		
		curr_char = fgetc(orig_file);
	}
}
