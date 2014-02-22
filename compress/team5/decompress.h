#ifndef DECOMPRESS_H
#define DECOMPRESS_H

extern int CHECK_REP;

void decompress(FILE *input, char* filename);
void build_children_if_null (huff_tree *);

#endif