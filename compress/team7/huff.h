#define EXT ".huff"
#define NUM "HUFF"

enum Flags
{
	COMPRESS,
	DECOMPRESS,
	DUMP,
	INVALID
};

/* 
	Compress the given file into a .huff file.
	Exits with -1 if given filename cannot be opened.
	Compressed file's name will be the given filename, concat'd
	with ".huff".
*/
void compress(FILE* file, char* filename);

/*
	Decompress the given file into its orginal form.
	Exits with -1 if given filename cannot be opened, or if the given
	file has improper internal .huff formatting.
	Decompressed file's name will be the given filename, without the
	".huff" extension.
*/
void decompress(FILE* file, char* filename);

/* 
	Dumps the given files encoded huff table.
	Exits with -1 if given filename cannot be opened, or if the given file
	has improper internal .huff formatting when given a .huff file.
*/
void dump(FILE* file, char* filename);

/* 
	Populates given table[] with the frequency of occurance the corresponding
	char appearing in the given file. With index 0 corresponding to ascii value 0.
*/
void create_freq_table(int table[], FILE* file, unsigned long long size);

/* Checks whether the given filename has the proper .huff extension. */
bool is_huff_type(char* filename);

/* Determines the size of the given file, in bytes. */
unsigned long long det_file_size(FILE* file);

/*
	Validates the given file is a .huff by checking the magic number, as well
	as comparing the content length (bytes 4-11) with the given size. If either
	of these checks fail, exits with -1.
	Otherwise, encodes given huff_table with the tree paths corresponding to the encoded
	table.
*/
void get_huff_table(char** huff_table, FILE* file, unsigned long long size);

/* Determines which flag we are given from the user. */
enum Flags determine_flag(char* user_flag);

/* Wrapper function for fopen. Performs check to ensure file is opened. */
FILE* open_file(char* filename, char* permission);
