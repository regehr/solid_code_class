#include "xprintf.h"

int main(int argc, char* argv[]) {
  int n = 0;
  int res = xprintf("Hello, %s!%n\n", "world", &n);
  printf("%d, %d\n", res, n);
  return 0;
}
