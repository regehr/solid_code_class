#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include "musl.h"
#define LEN 10000
char buf[LEN];
int main(int argc, const char *argv[]) {
musl_snprintf(buf, LEN, "%c %d %f %e %s %d %i %x %u %o %g %% %a %l %ll %p" , 'W',14,340.563716465,12345678.0,"njyTfYvPOq",14,14,0x9f3aL,14,013463373556L,14,'%',0xc,14,14,14);
printf("%s", buf);return 0;
}