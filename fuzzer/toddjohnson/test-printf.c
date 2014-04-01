#include <stdio.h>
#include <stdarg.h>
#include "musl.h"
#define LEN 10000
char buf[LEN];
int main(int argc, const char *argv[]) {
musl_snprintf(buf, LEN, "%le" , 4909491458504163264);
printf("%s", buf);return 0;
}