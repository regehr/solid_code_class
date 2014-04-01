#include <stdio.h>
#include <stdarg.h>
#include "musl.h"

#define LEN 10000
char buf[LEN];

int main (void)
{

    // THIS IS JOHN'S TEST CODE, DELETE IT AND PUT YOUR CODE HERE
    /* musl_snprintf (buf, LEN, "hello %d\n", 10); */
    /* printf ("%s", buf); */

    system("./new_fuzz.py");
    

    return 0;
}
