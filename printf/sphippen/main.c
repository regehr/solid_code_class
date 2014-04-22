#include "xprintf.h"

int main(int argc, char* argv[]) {
  int res = xprintf("%10x\n", 123U);
  printf("%d\n", res);
  return 0;
}
