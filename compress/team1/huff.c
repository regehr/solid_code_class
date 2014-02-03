/*
 *
 */

#include "huff_table.h"

int main(int argc, const char *argv[])
{
    
    FILE *file;
    file = fopen(argv[1], "r");
    if (file == NULL || file == 0)
        return -1; /* Need error message. */
    
    char *huff_table[256];
    uint64_t frequencies[256];
    

    // I had that function setup initially to accept a filestream,
// but I think it would be a better idea to keep the file stuff separate
// in here. Also that function takes an array of node pointers which would
// also break the modularity.
    
// You could do something like this to read each character from the file.
    int c;
    do {
        c = fgetc(file); /* Get the next character from the file stream. */
        if (c != EOF)
            frequencies[c]++; /* Increment the frequency of specific character. */
    } while (c != EOF); /* May have to check errno here e.g. (... && ferror(file) == 0) */
    
    // Andres, if you pass me a sorted array of frequencies and an empty char * array
    // here, I will give you a sorted array of char *s representing
    // the huff table coding.
    gen_huff_table(frequencies, huff_table);
    
    return 0;
}
