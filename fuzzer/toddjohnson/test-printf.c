#include <stdio.h>
#include <stdarg.h>
#include "musl.h"
#define LEN 10000
char buf[LEN];
int main(void){
musl_snprintf (buf, LEN, "%s" ,   " Hello World \n " );
printf("%s", buf);return 0;
}