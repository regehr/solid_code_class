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
		return -1;
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
			return -1;
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
		exit(-1);
	}
	
	return file;
}

void compress(FILE* file, char* filename)
{
	//Check if file is already a .huff
	if(is_huff_file(filename))
		return;
		
	//Cat filename with extension
	strcat(filename, EXT);
	
	//Open the file
	FILE* comp_file = open_file(filename, "w");
	
	//TODO:Write magic number
	
	//TODO:Write length
	
	//TODO:Write table
	
	//TODO:Write compressed file
	
	//TODO:Close the file
}

//TODO: finish me!
void decompress(FILE* file, char* filename)
{
	//Check if file isnt a .huff
	if(!is_huff_file(filename))
		Printf("Given file is not a .huff\n");
		
	//TODO:Get huff table
	
	//TODO:Decode data based on table
	
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
		get_huff_table(encoded_table, file, file_size);
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
		printf("%s", encoded_table[i]);
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
	
	//assert(seek_res && "Failed to rewind the given file after determining length.");
	
	return file_length;
}

void get_huff_table(char** huff_table, FILE* file, unsigned long long size)
{
	char* magic_num = "";
	
	//Read magic number
	fread(magic_num, 4, 1, file);
	
	//If not the proper number
	if(strcmp(magic_num, NUM) != 0)
	{
		printf("Improper huff magic number.\n");
		exit(-1);
	}
	
	//Get huff length
	unsigned long long res = 0;
	fread(&res, 8, 1, file);
	
	//Check that sizes match
	if(res != size)
	{
		printf("Size mismatch of huff length.\n");
		exit(-1);
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
			exit(-1);
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
