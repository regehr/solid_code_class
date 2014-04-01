#include <stdio.h>
#include <stdarg.h>
#include "musl.h"
#define LEN 10000
char buf[LEN];
int main(int argc, const char *argv[]) {
musl_snprintf(buf, LEN, "%le" , 11515086381590466148);
printf("%s", buf);return 0;
}