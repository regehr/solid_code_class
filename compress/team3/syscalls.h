#ifndef syscalls_h
#define syscalls_h

/* stdio.h */
FILE *xfopen(const char *filename, const char *mode);
size_t xfread(void *ptr, size_t size, size_t count, FILE *stream);
void xfseek(FILE *stream, long int offset, int origin);
long int xftell(FILE *stream);
void xfwrite(const void *ptr, size_t size, size_t count, FILE *stream);
FILE *xtmpfile();

/* stdlib.h */
void *xmalloc(size_t size);

#endif
