#include <stdio.h>
#include <assert.h>

int main(int argc, char **argv){

  assert(argc > 1);
  char *in = argv[1];
  printf("%s\n", in);


}
