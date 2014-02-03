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
    
    
    // Andres, if you pass me a sorted array of frequencies and an empty char * array
    // here, I will give you a sorted array of char *s representing
    // the huff table coding.
    gen_huff_table(frequencies, huff_table);
    
    return 0;
}
