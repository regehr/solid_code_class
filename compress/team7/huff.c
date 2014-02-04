#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "huff_table.h"

#define READ_BINARY "rb"

//Enum used to determine the operation for the program
enum Flags
{
	COMPRESS,
	DECOMPRESS,
	DUMP,
	INVALID
};

//Forward declarations
enum Flags determine_flag(char* user_flag);
void create_table(int table[], char* filename);
long long det_file_size(FILE *file);
void print_table(int table[]);


int main(int argc, char* argv[])
{
	//Local vars
	enum Flags given_flag;
	int i, table[256];
	char* filename;
	
	//Initial check for correct arg count
	if(argc != 3)
	{
		printf("Invalid number of parameters. Huff requires a flag (-c, -d, -t), and a filename as parameters.\n");
		return -1;
	}
	
	//Determine flag and filename
	given_flag 	= determine_flag(argv[1]);
	filename 	= argv[2];
	
	//Zero out table entries
	for(i = 0; i < 256; i++)
		table[i] = 0;
	
	switch(given_flag)
	{
		case COMPRESS:
			//TODO: compress the file
			break;
		case DECOMPRESS:
			//TODO: decompress the file
			break;
		case DUMP:
			//TODO: need to check whether its a .huff file or not
			create_table(table, filename);
			print_table(table);
			break;
		case INVALID:
			printf("Invalid flag given. Expected one of the following: -c, -d, -t.\n");
			return -1;
	}
	
	return 0;
}

/* 
 * Compares given string with the list of supported flags.
 * Returns the enum value that corresponds to the given flag.
 * 
 * Author: Thomas Gonsor
 */
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

/*
 * Populates given table with the char frequencies in
 * file with the given filename. If the file doesn't exist
 * or is not openable, the program exits. THIS DOES NOT SORT
 * THE TABLE. ASSUMES TABLE HAS ALREADY BEEN ZEROED.
 *
 * Author: Thomas Gonsor
 */
void create_table(int table[], char* filename)
{
	//Local vars
	FILE* file;
	char curr_char;
	int i, read_ret;
	long long file_length;
	
	//Attempt to open the file
	file = fopen(filename, READ_BINARY);
	
	//Ensure we can open the file
	if(file == NULL)
	{
		printf("Unable to find/open the file: %s\n", filename);
		exit(-1);
	}
	
	//Determine size of file
	det_file_size(file);
	
	//Beginning populating frequency table
	for(i = 0; i < file_length; i++)
	{
		//Ensure we don't encounter an error
		read_ret = fread(&curr_char, 1, 1, file);
		
		//If not 1, we didn't read anything else
		if(read_ret != 1)
			break;
		
		//Casting char correctly converts to its ascii value
		//So we increment that index
		table[(int)curr_char]++;
	}
	
	//Close the file
	fclose(file);
}

long long det_file_size(FILE* file)
{
	long long length;
	
	//Go to end, determine curr pos, then return to start
	fseek(file, 0L, SEEK_END);
	length = ftell(file);
	rewind(file);
	
	return length;
}

/*
 * Prints the given table, who's size is assumed to be 256,
 * to stdout.
 *
 * Author: Thomas Gonsor
 */
void print_table(int table[])
{
	//Local vars
	int i;
	
	//Print frequency table to stdout
	for(i = 0; i < 256; i++)
	{
		printf("ascii(%u) -> %u\n", i, table[i]);
	}
}
