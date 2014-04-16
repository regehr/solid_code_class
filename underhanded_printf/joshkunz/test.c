#include "xprintf.h"
#include <stdio.h>
#include <limits.h>

#define TP(fmt, ...) \
    printf("libc: " fmt ", ", ##__VA_ARGS__); \
    xprintf("us: " fmt "\n", ##__VA_ARGS__)

int main() {
    TP("%%");
    TP("%3c", 'b');
    TP("%s", "Hello");
    TP("%4d", 13);
    TP("%04d", 13);
    TP("%4d", -13);
    TP("%04d", -13);
    TP("%015d", INT_MIN);
    TP("%u", 324234224U);
    TP("%x", 0x1abcd9U);

    int libc = -1;
    int us = -1;
    printf("abc%n\n", &libc);
    xprintf("abc%n\n", &us);
    printf("libc: %d, us: %d\n", libc, us);
    return 0;
}
