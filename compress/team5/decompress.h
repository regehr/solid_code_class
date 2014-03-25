#ifndef DECOMPRESS_H
#define DECOMPRESS_H

extern int CHECK_REP;

void decompress(FILE *, FILE *);
void build_children_if_null (huff_tree **);
char *get_decompressed_file_name (char *);

#endif