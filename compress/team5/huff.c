#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <time.h>

void compress_file (const char *fn)
{
  int fd = open (fn, O_RDWR);
  if (fd == -1) {
    printf ("oops -- couldn't open '%s'\n", fn);
    exit (-1);
  }
  int res;
  off_t len;
  {
    struct stat sb;
    res = fstat(fd, &sb);
    assert (res != -1);
    len = sb.st_size;
  }
  char *base = (char *)mmap (NULL, len, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
  assert (base != MAP_FAILED);

  res = munmap (base, len);
  assert (res == 0);

  res = close (fd);
  assert (res == 0);
}

int main (int argc, char *argv[])
{
  srand (getpid() + time (NULL));
  
  if (argc != 3) {
    exit (-1);
  }
  
  const char *compress = "-c";

  if(argv[1] == compress) {
  	printf("compress");	
  }
  
  return 0;
}

