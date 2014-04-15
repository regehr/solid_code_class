#include "xprintf.h"

void main() {
  int n;
  xprintf("a\n%d\n%d\n%10d\n%010d\n%u\n%x\n%c\n%s\n%n", 42, -10, 1, 5, 1234,
    0xabcdef5, 'c', "Hello", &n);
  xprintf("%d\n", n);
}