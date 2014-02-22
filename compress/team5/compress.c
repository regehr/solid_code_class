#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "huff_table.h"

#define CHAR_RANGE 257

/* get the size that our string of 0's and 1's is going to be */
unsigned long long get_size (char** huff_table, int frequencies[])
{
	
	unsigned long long size = 0;
	int i;
	for (i = 0; i < 257; i++) {
		if (frequencies[i] != 0) {
			size += frequencies[i] * strlen(huff_table[i]);
		}	
	}
	return size;
}

/* create a long string of 0's and 1's in the order of the file */
void write_out_compressed (FILE *input, FILE *output, char** huff_table)
{
	int bit_counter = 0;
	char current, character;

	while ((character = fgetc(input)) != EOF) {
		char * temp = huff_table[(int)character];

		int j = 0;
		while (temp[j] != '\0') {
			if (temp[j] == '1') {
				current = (current & ~(1 << bit_counter)) | 1 << bit_counter;
			} else {
				current = (current & ~(1 << bit_counter)) | 0 << bit_counter;
			}

			bit_counter++;
			j++;
			if (bit_counter == 8) {
				bit_counter = 0;
				fwrite(&current, 1, 1, output);
			}
		}
	}

	// Pad last bit
	for (; bit_counter < 8; bit_counter++) {
		current = (current & ~(1 << bit_counter)) | 0 << bit_counter;
	}
	fwrite(&current, 1, 1, output);
}

/* remove the extension from the file that we are compressing */
char *get_new_name (char* filename) 
{
	int length = strlen(filename);
	int end = 0;
	
	/* start from the back and stop at the first '.' */
	int i = length - 1;
	for (; i > 0; i--) {
		if (filename[i] == '.') {
			end = i;
		}
	}
	
	printf("%i \n", end);
	int size = end + 6;
	char *name = malloc(size*sizeof(char));
	
	for (i = 0; i < end; i++) {
		name[i] = filename[i];
	}

	// Append trailing nullspace so strcat works properly
	name[end] = '\0';
	strcat(name, ".huff");
	
	return name;
}

/* Take in a file and compress it. */
void compress (FILE *input, char* filename, unsigned long long length)
{
	int character, frequencies[CHAR_RANGE] = { 0 };
	int i;
	char **huff_table;

	for (i = 0; i < CHAR_RANGE; i++) {
		frequencies[i] = 0;
	}
	
	/* calculate character frequencies. */
	while ((character = fgetc(input)) != EOF) {
	    frequencies[character]++;
	}
	
	/* get the huff table */
	huff_table = build_huff_table(frequencies);

 	/* create the string */
 	rewind(input);

	/* get rid of the old files extension */
	char* newName = get_new_name(filename);
	
	/* create a new file to write to */
	FILE *output = fopen(newName, "w");
	
	char *magicNumber = "HUFF";
	
	if (fwrite(magicNumber, sizeof(char), strlen(magicNumber), output) != strlen(magicNumber)) {
		printf("Write failure magic\n");
		exit(255);
	}
	
	if (fwrite(&length, sizeof(unsigned long long), 1, output) != 1) {
		printf("Write failure \n");
		exit(255);
	}

	// Write table to the output
	for (i = 0; i < CHAR_RANGE; i++) {
		fprintf(output, "%s\n", huff_table[i]);
	}
	
	write_out_compressed(input, output, huff_table);
	
	fclose(output);
}