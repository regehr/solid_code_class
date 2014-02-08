#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "huff_table.h"

#define CHAR_RANGE 257

unsigned long long get_size(char** huff_table, unsigned char* fp, int frequencies[]) {
	
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

void compress(FILE *input, char* filename, unsigned long long length, unsigned char* fp) {
	int character, frequencies[CHAR_RANGE] = { 0 };
	char **huff_table;
	
	if(length == 0) {
		printf("length = 0");	
	}
		
	/* calculate character frequencies. */
	while((character = fgetc(input)) != EOF) {
	    frequencies[character]++;
	}
	
	huff_table = build_huff_table(frequencies);

	unsigned long long size = get_size(huff_table, fp, frequencies);
 	
 	printf("%llu size \n", size);
 	
 	char* string = malloc(size*sizeof(char));
 	if(string == NULL) {
 		printf("Malloc failed \n");
    	exit(255);
 	}
 	
 	rewind(input);
	character = 0;
	string = get_string(string, input, character, huff_table);
 	
 	printf("%s \n", string);
}