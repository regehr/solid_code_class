#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include "huff_table.h"

#define CHAR_RANGE 257

/* Write the header information for huffman encoding to the file. */
void write_header (FILE *output, char **huff_table, uint64_t length)
{
	int i, write_status;
	char *magic_number = "HUFF";
	
	write_status = fwrite(magic_number, 1, strlen(magic_number), output);
	if (write_status != strlen(magic_number)) {
		printf("Magic number failed to write.\n");
		exit(255);
	}
	
	write_status = fwrite(&length, sizeof(uint64_t), 1, output);
	if (write_status != 1) {
		printf("Length failed to write.\n");
		exit(255);
	}

	// Write table to the output
	for (i = 0; i < CHAR_RANGE; i++) {
		write_status = fprintf(output, "%s\n", huff_table[i]);

		if (write_status < 0) {
			printf("Failed to write encoding table.\n");
			exit(255);
		}
	}
}

/* Create a long string of 0's and 1's in the order of the file. */
void compress_contents (FILE *input, FILE *output, char **huff_table)
{
	int bitc = 0, i, bitout;
	char current, character;
	char *temp = NULL;

	while ((character = fgetc(input)) != EOF) {
		temp = huff_table[(int)character];
		i = 0;

		while (temp[i] != '\0') {
			bitout = temp[i] - '0'; // Thanks SO :)
			current = (current & ~(1 << bitc)) | bitout << bitc;

			bitc++;
			i++;
			if (bitc == 8) {
				bitc = 0;
				fwrite(&current, 1, 1, output);
			}
		}
	}

	// Pad last bit
	for (; bitc < 8; bitc++) {
		current = (current & ~(1 << bitc)) | 0 << bitc;
	}
	fwrite(&current, 1, 1, output);
}

/* Remove the extension from the file that we are compressing. */
char *get_new_name (char *filename) 
{
	int length = strlen(filename);
	char *name = malloc(length + 6);
	name = strcpy(name, filename);

	if (name == NULL) {
		printf("Failed to get new name.\n");
		exit(255);
	}

	strcat(name, ".huff");
	return name;
}

/* Take in a file and compress it. */
void compress (FILE *input, char *filename, uint64_t length)
{
	int character, frequencies[CHAR_RANGE] = { 0 };
	char **huff_table;

	// Build huff table
	while ((character = fgetc(input)) != EOF) {
	    frequencies[character]++;
	}
	rewind(input);
	huff_table = build_huff_table(frequencies);

	// Get pointer to output file
	char *new_name = get_new_name(filename);
	FILE *output = fopen(new_name, "w");
	
	// Write out the header and the actual compressed file contents
	write_header(output, huff_table, length);
	compress_contents(input, output, huff_table);
	printf("Past contents?\n");
	fclose(output);

	// Clean up
	free(new_name);
	free_huff_table(huff_table);
}