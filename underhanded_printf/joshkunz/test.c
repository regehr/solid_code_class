#include "xprintf.h"
#include <stdio.h>

int main() {
    printf("%d\n", -13 % 10);
    xprintf("Should print '%%': %%\n"
            "Should print  'b': %c\n"
            "Should print 'Hello': %s\n"
            "Should print '13': %d\n"
            "Should print '-13': %d\n", 'b', "Hello", 13, -13);
    return 0;
}
