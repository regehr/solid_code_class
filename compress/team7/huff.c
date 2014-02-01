#include <stdio.h>
#include <stdlib.h>

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
			break;
		case DECOMPRESS:
			break;
		case DUMP:
			create_table(table, filename);
			//TODO: write table info to stdout
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
 * or is not openable, the program exits
 *
 * Author: Thomas Gonsor
 */
void create_table(int table[], char* filename)
{
	//Local vars
	FILE* file;
	
	//Attempt to open the file
	file = fopen(filename, READ_BINARY);
	
	//Ensure we can open the file
	if(file == NULL)
	{
		printf("Unable to find/open the file: %s\n", filename);
		exit(-1);
	}
	
	//TODO: actually read file and populate table
}
