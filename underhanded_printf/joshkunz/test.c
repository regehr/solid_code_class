#include "xprintf.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define TRIALS 3

#define TP(fmt, ...) \
    printf("libc: " fmt "\n", ##__VA_ARGS__); \
    xprintf("  us: " fmt "\n", ##__VA_ARGS__)

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

int randint(int a, int b) {
    return (rand() % (max(a, b) - min(a, b))) + min(a, b);
}

int main() {
    srand(TRIALS);
    TP("%%");
    TP("%3c", 'b');
    TP("%04d", 13);
    TP("%s %20s.", "Hello", "World");
    int libc = -1;
    int us = -1;
    printf("abc%n (libc capturing %%n)\n", &libc);
    xprintf("abc%n (us capturing %%n)\n", &us);
    printf("libc: %d\n  us: %d\n", libc, us);

    TP("%0300d | %070d", -1346231289, 1346231289);
    for (int i = 0; i < TRIALS; i++) {
        int r = randint(0, INT_MAX);
        TP("%15d", r);
    }
    for (int i = 0; i < TRIALS; i++) {
        int r = randint(1234269834, -(INT_MIN + 1));
        TP("%d | %d", -r, r);
    }
    TP("%015d", INT_MIN);
    TP("%u", 324234224U);
    TP("%x", 0x1abcd9U);
    return 0;
}
