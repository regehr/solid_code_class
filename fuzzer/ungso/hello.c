#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void print_int(int i);
void print_str(char *s);
void print_float(float f);

int main(int argc, char **argv){

  assert(argc > 1);

  char *fmt = argv[1];
  char *str = argv[2];
  
  if (!strcmp(fmt, "-i"))
    print_int(atoi(str));
  
  else if (!strcmp(fmt, "-s"))
    print_str(str);

  else if (!strcmp(fmt, "-f"))
    print_float(atof(str));

}


void print_int(int i){
  printf("%i\n", i);
}


void print_str(char *s){
  printf("%s\n", s);
}

void print_float(float f){
  printf("%f\n", f);
}
