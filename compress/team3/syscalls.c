#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

/* stdio.h */

FILE *xfopen(const char *filename, const char *mode)
{
    FILE *result = fopen(filename, mode);
    if (result != NULL) return result;
    perror(NULL);
    exit(-1);
}

size_t xfread(void *ptr, size_t size, size_t count, FILE *stream)
{
    size_t result = fread(ptr, size, count, stream);
    if (ferror(stream) == 0) return result;
    fprintf(stderr, "An error occurred while reading from a file.\n");
    exit(-1);
}

void xfseek(FILE *stream, long int offset, int origin)
{
    int result = fseek(stream, offset, origin);
    if (result == 0) return;
    fprintf(stderr, "An error occurred while seeking in a file.\n");
    exit(-1);
}

long int xftell(FILE *stream)
{
    long int result = ftell(stream);
    if (result != -1L) return result;
    perror(NULL);
    exit(-1);
}

void xfwrite(const void *ptr, size_t size, size_t count, FILE *stream)
{
    fwrite(ptr, size, count, stream);
    if (ferror(stream) == 0) return;
    fprintf(stderr, "An error occurred while writing to a file.\n");
    exit(-1);
}

FILE *xtmpfile()
{
    FILE *result = tmpfile();
    if (result != NULL) return result;
    fprintf(stderr, "An error occurred while creating a temporary file.\n");
    exit(-1);
}


/* stdlib.h */

 void *xmalloc(size_t size)
 {
    void *result = malloc(size);
    if (result != NULL) return result;
    fprintf(stderr, "An error occurred while allocating memory.\n");
    exit(-1);
 }
