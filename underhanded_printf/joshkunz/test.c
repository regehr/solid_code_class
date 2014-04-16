#include "xprintf.h"
#include <stdio.h>
#include <limits.h>

int main() {
    int x = -1;
    xprintf("abc%n (for %%n modfier)\n"
            "Should print '%%': '%%'\n"
            "Should print '  b': '%3c'\n"
            "Should print 'Hello': '%s'\n"
            "Should print '  13': '%4d'\n"
            "Should print '-13': '%d'\n"
            "Should print '-2147483648': '%d'\n"
            "Should print '3242342142': '%u'\n"
            "Should print '1234cde': '%x'\n",
            &x, 'b', "Hello", 13, -13, INT_MIN, 3242342142U, 0x1234cdeU);
    printf("Should print (%%n) '3': '%d'\n", x);
    return 0;
}
