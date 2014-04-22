#include "xprintf.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define TRIALS 3

#define TP0(fmt) \
    printf("libc: " fmt "\n"); \
   xprintf("  us: " fmt "\n")

#define TP(fmt, ...) \
    printf("libc: " fmt "\n", __VA_ARGS__); \
   xprintf("  us: " fmt "\n", __VA_ARGS__)

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

int randint(int a, int b) {
    return (rand() % (max(a, b) - min(a, b))) + min(a, b);
}

int main() {
    srand(TRIALS);
    TP0("%%");
    TP("%015d", -5);
    TP("%15d", -77);
    TP("%015d", -934693128);
    TP("%15d", -900823482);
    TP("%0300d | %070d", -134623128, 134623128);
    TP("%3c", 'b');
    TP("%04d", 13);
    TP("%s %20s.", "Hello", "World");
    int libc = -1;
    int us = -1;
    printf("abc%n (libc capturing %%n)\n", &libc);
    xprintf("abc%n (us capturing %%n)\n", &us);
    printf("libc: %d\n  us: %d\n", libc, us);
    for (int i = 0; i < TRIALS; i++) {
        int r = randint(0, INT_MAX);
        TP("%15d", r);
    }
    TP("%u", 324234224U);
    TP("%x", 0x1abcd9U);
    return 0;
}
