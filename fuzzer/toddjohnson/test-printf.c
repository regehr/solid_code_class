#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include "musl.h"
#define LEN 10000
char buf[LEN];
int main(int argc, const char *argv[]) {
musl_snprintf(buf, LEN, "%c %03d %c %.3f %6.3f %e %5.3s %.d %+i %#x %u %o %g %% %a %-l % ll %p %ls %+ld %lu %5lf %-lg %le %h %#010X %z %i %i %l %ll %llu %hu %c %i %i %c %s" , 'e',7,14,330.517733558,330.517733558,12345678.0,"vkzubBeesu",7,14,0x7ff9L,14,026152006227L,7,'%',0xbaL,7,7,7,3,7,7,330.517733558,3.141592,12345678.0,3,0x7ff9L,14,14,14,-12,-12,7,7,69,4294967295,-4294967297, 'c ' + 65 ,  " Hello World \n " );
printf("%s", buf);return 0;
}