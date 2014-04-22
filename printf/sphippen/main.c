#include "xprintf.h"

int main(int argc, char* argv[]) {
  int res = xprintf("%010d\n", -123);
  printf("%d\n", res);
  return 0;
}
