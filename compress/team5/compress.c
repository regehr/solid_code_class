#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "huff_table.h"

#define CHAR_RANGE 257

unsigned long long get_size(char** huff_table, int frequencies[]) {
	
	unsigned long long size = 0;
	int i;
	for(i = 0; i < 257; i++) {
		if(frequencies[i] != 0) {
			size += frequencies[i] * strlen(huff_table[i]);
		}	
	}
	return size;
}

char *get_string(char* string, FILE *input, int character, char** huff_table) {
	unsigned long long index = 0;
 	while((character = fgetc(input)) != EOF) {
 		char * temp = huff_table[character];
 		
 		unsigned long long j = 0;	
 		while(temp[j] != '\0'){
 			string[index++] = temp[j++];
 		}		
 	}
 	
 	return string;
}

char *get_new_name(char* filename) {

	int length = strlen(filename);
	int end = 0;
	
	int i = length - 1;
	for(; i > 0; i--) {
		if(filename[i] == '.') {
			end = i;
		}
	}
	
	int size = end + 6;
	char *name = malloc(size*sizeof(char));
	int limit = size - 6;
	
	for(i = 0; i < limit; i++) {
		name[i] = filename[i];	
	}
	
	strcat(name, ".huff");
	
	return name;
}

void compress(FILE *input, char* filename, unsigned long long length) {
	int character, frequencies[CHAR_RANGE] = { 0 };
	char **huff_table;
	
	/* calculate character frequencies. */
	while((character = fgetc(input)) != EOF) {
	    frequencies[character]++;
	}
	
	huff_table = build_huff_table(frequencies);

	unsigned long long size = get_size(huff_table, frequencies);
 	
 	char* string = malloc(size*sizeof(char));
 	if(string == NULL) {
 		printf("Malloc failed \n");
    	exit(255);
 	}
 	
 	rewind(input);
	character = 0;
	string = get_string(string, input, character, huff_table);
	
	unsigned char* bytes = malloc(((size/8)+1)*sizeof(unsigned char));
	if(bytes == NULL) {
		printf("Malloc failed \n");
		exit(255);
	}
	
	int i;
	for(i = 0; i < size/8; i++) {
		char temp[9] = {0};
		
		int j = 0;
		for(; j < 8; j++) {
			temp[j] = string[(i*8) + j];	
		}
		
		bytes[i] = (unsigned char)(strtol(temp, NULL, 2) & 0xFF);;
	}
	
	i = 0;
	int end = size%8;
	int shift = 8 - end;
	char final[9] = {0};
	
	for(; i < end; i++) {
		final[i] = string[(size - end) + i];	
	}
	
	unsigned char endString = (unsigned char)(strtol(final, NULL, 2) & 0xFF);
	
	bytes[size/8] = endString << shift;
	
	char* newName = get_new_name(filename);
	
	FILE *output = fopen(newName, "w");
	
	char *magicNumber = "HUFF";
	
	if(fwrite(magicNumber, sizeof(char), strlen(magicNumber), output) != strlen(magicNumber)) {
		printf("Write failure magic\n");
		exit(255);
	}
	
	if(fwrite(&length, sizeof(unsigned long long), 1, output) != 1) {
		printf("Write failure \n");
		exit(255);
	}
	
	if(fwrite(string, sizeof(char), strlen(string), output) != strlen(string)) {
		printf("Write failure \n");
		exit(255);
	}
	
	if(fwrite(bytes, sizeof(unsigned char), (size/8) + 1, output) != (size/8)+1) {
		printf("Write failure \n");
		exit(255);
	}
	
	fclose(output);
	free(bytes);
	free(string);

}