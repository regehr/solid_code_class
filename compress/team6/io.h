#ifndef IO_H
#define IO_H

void write_compressed_file(unsigned char* file_pointer, unsigned long long file_length, char* filename, char* mapping);
void write_decompressed_file(unsigned char* file_pointer, unsigned long long file_length, char* filename, char* mapping, unsigned long long start_of_compressed);
int check_format(unsigned char* file_pointer, unsigned long long file_length, char* filename);
char* get_mapping_from_file(unsigned char* file_pointer, unsigned long long file_length, unsigned long long* start_of_compressed);

#endif
