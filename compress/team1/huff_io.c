#include "huff_io.h"

bool is_huff_file(const char* filename){
   const char *dot = strrchr(filename, '.');
   if(!dot || dot == filename) return false;
   return strcmp(HUFF_EXT, dot) == 0;
}

static void read_body_error(){
   fprintf(stderr, "ERROR: Error while reading body from file.\n");
   exit(ERR_CODE);
}

static void read_header_error(){
   fprintf(stderr, "ERROR: Error while reading header from file.\n");
   exit(ERR_CODE);
}

static void write_header_error(){
   fprintf(stderr, "ERROR: Error while writing header to file.\n");
   exit(ERR_CODE);
}

static void write_body_error(){
   fprintf(stderr, "ERROR: Error while writing body to file.\n");
   exit(ERR_CODE);
}

char* remove_ext(const char* mystr) {
   char *retstr;
   char *lastdot;
   if (mystr == NULL)
      return NULL;
   if ((retstr = malloc (strlen (mystr) + 1)) == NULL){
      fprintf(stderr, "Malloc Error.\n");
      exit(ERR_CODE);
   }
   strcpy (retstr, mystr);
   lastdot = strrchr (retstr, '.');
   if (lastdot != NULL)
      *lastdot = '\0';
   return retstr;
}

bool get_huff_header(FILE* file, unsigned long long* size){
   int num_string = 256;
   int str_length = 257;
   char magic[5];
   char* huff_table[num_string];
    
   // Init array
   int i;
   for (i = 0; i < num_string; i++){
      huff_table[i] =  malloc(str_length);
      if (huff_table[i] == NULL){
	 read_header_error();
      }
   }
    
   // Read magic number
   magic[0] = fgetc(file);
   magic[1] = fgetc(file);
   magic[2] = fgetc(file);
   magic[3] = fgetc(file);
   magic[4] = '\0';
   if (ferror(file)){
      read_header_error();
   }
   if(strcmp(magic, MAGIC_NUM) != 0){
      return false;
   }
    
   // Read content length
   if (fread(size, sizeof(size), 1, file) != 1){
      read_header_error();
   }
    
   // Read huff table
   int j;
   for (i = 0; i < num_string; i++){
      char line[str_length];
      for(j = 0; j < str_length; j++){
	 int c = fgetc(file);
	 if (ferror(file)){
	    read_header_error();
	 } else if (c != '\n'){
	    line[j] = c;
	 } else {
	    line[j] = '\0';
	    break;
	 }
      }
      strcpy(huff_table[i], line);
   }
   build_tree_tbl(huff_table);
    
//    for (i = 0; i < 256; i++){
//        printf("%s\n", huff_table[i]);
//    }
    
   // free mem
   for (i = 0; i < num_string; i++){
      free(huff_table[i]);
   }
    
   return true;
}

/**
 *	Gets the character frequencies from the file given and outputs them to the integer array.
 * 	The array must be a length of 256. Returns 0 if the operation succeded.
 */
static void get_frequencies(FILE* file, uint64_t* frequencies){
   int c;
   do {
      c = fgetc(file);
      if (c != EOF){
	 frequencies[c]++;
      } else if (ferror(file)){
	 fprintf(stderr, "ERROR: Error while reading characters from file\n");
	 exit(ERR_CODE);
      }
   } while(c != EOF);
}

void gen_huff_tree(FILE* file){
   uint64_t frequencies[256];
    
   // Initialize frequencies
   int i;
   for (i = 0; i < 256; i++){
      frequencies[i] = 0;
   }
   get_frequencies(file, frequencies);
   gen_tree_frq(frequencies);
}

unsigned long long get_file_size(const char* filename){
   struct stat st;
   stat(filename, &st);
   return (unsigned long long)st.st_size;
}

void write_huff_header(FILE* file, unsigned long long filesize){
    
   // Write magic number
   if (fprintf(file, MAGIC_NUM) < 0){
      write_header_error();
   }
    
   // Write the length out
   if (fwrite(&filesize, sizeof(filesize), 1, file) != 1){
      write_header_error();
   }
    
   // Write huff_table
   int i;
   for (i = 0; i < 256; i++){
      if (fputs(get_code(i), file) 	== EOF
	  || fputc('\n', file) 		== EOF)
      {
	 write_header_error();
      }
   }
}

void write_huff_body(FILE* original, FILE* newfile, unsigned long long size){
   rewind(original);
    
   // Create a read-in buffer for each huff code.
   char read_buffer[257];
   // Zero it out.
   memset(read_buffer, 0, sizeof(read_buffer));
   // Create a count of how many bits have been read from the buffer.
   int input_bits_read = 0;
    
   // Create a write-out buffer to write to file.
   char write_buffer[32];
   // Zero it out.
   memset(write_buffer, 0, sizeof(write_buffer));
   // Create a count of how many bits are in the write buffer.
   int write_buffer_size;
    
    
   // Read character and output corresponding encoding
   int c;
   do {
      c = fgetc(original);
      if (c != EOF){
	 strcpy(read_buffer, get_code(c));
	 input_bits_read = 0;
            
	 // While there are still input bits to read, or while the write buffer is not full.
	 while (input_bits_read < strlen(read_buffer) && write_buffer_size < 256)
	 {
	    write_buffer[write_buffer_size / 8] = write_buffer[write_buffer_size / 8] | ((read_buffer[input_bits_read] - 48) << (7 - write_buffer_size % 8));
	    write_buffer_size++;
	    input_bits_read++;
	 }
            
	 if (write_buffer_size == 256) // Buffer is full.
	 {
	    // Write it to the new file.
	    fprintf(newfile, "%s", write_buffer);
	    // Empty the buffer.
	    memset(write_buffer, 0, sizeof(write_buffer));
	    write_buffer_size = 0;
	 }
            
	 if (strlen(read_buffer) - input_bits_read > 0) // Still data in read buffer.
	 {
	    for (int i = 0; input_bits_read < strlen(read_buffer); i++)
	    {
	       assert(write_buffer_size < 257);
	       write_buffer[i / 8] = write_buffer[i / 8] | (read_buffer[i] - 48) >> (i % 8);
	       write_buffer_size++;
	       input_bits_read++;
	    }
	 }
	 assert(input_bits_read == strlen(read_buffer));
	 input_bits_read = 0;
      } else if (ferror(original)){
	 write_body_error();
      }
   } while (c != EOF);
    
   if (write_buffer_size > 0) // Buffer ins't empty.
   {
      fprintf(newfile, "%s", write_buffer);
      memset(write_buffer, 0, sizeof(write_buffer));
   }    
}

void read_huff_body(FILE* compressed, FILE* decompressed, unsigned long long size){
    
   unsigned long long codes_read = 0;
   // Read characters and write to decompresed file
   char c;
   do {
      char in, out;
      int c, i = 0;
      unsigned long long bytes_read = size;
      char in, out;
      while (bytes_read != 0 && c != EOF){
	 c = fgetc(compressed);
	 if (c != EOF){
            // Loop throught the bits of a byte
            for (i = 7; i >= 0; i--){
	       in = (c >> i) & 0x01;
	       if (get_char(in, &out)){
		  //printf("%c\n", out);
		  if(fputc(out, decompressed) == EOF){
		     read_body_error();
		  }
		  if (++codes_read == size) // Don't read any buffer data.
		     break;
		  bytes_read--;
	       }
            }
	 } else if (ferror(compressed)){
            read_body_error();
	 }
      }
   }

