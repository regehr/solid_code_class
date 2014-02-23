#ifndef COMPRESS_H
#define COMPRESS_H

extern int CHECK_REP;

void compress(FILE *input, char* filename, unsigned long long length);
char *get_new_name (char *filename);

#endif