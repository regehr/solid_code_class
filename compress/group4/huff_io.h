/*
 * Utilities for handling I/O.  This parses user input from stdin, reads files,
 * and writes to files safely.  
 *
 * Jonathon McDonald, Lynn Gao, Taylor Stapleton
 */

typedef enum {
    COMPRESS,
    DECOMPRESS,
    TABLE,
    UNHANDLED
} flags;

flags parse_args (char *[], char **);
int compare (const void *, const void *);
void build_table (char *, struct frequency []);
void dump_table (char *, struct frequency []);
int is_huff (void *, char *);
int huff_ext (char *);
void build_from_normal (void *, struct frequency []);
void build_from_huff (void *, struct frequency []);
char * new_string (int);
void decompress (char *, struct frequency []);
char get_bit (unsigned char, int);