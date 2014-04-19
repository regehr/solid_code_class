/*
 * test.c
 *
 * Jonathon McDonald - <jmcdonald.ut@gmail.com>
 */
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "xprintf.h"

int main (int argc, const char *argv[])
{
    // Basic printf
    xprintf("Hello world!\n");

    // Decimal
    xprintf("Hello world, I am %d.\n", 23);

    // Negative decimal
    xprintf("No not %d, but rather %d!\n", -23, 23);

    // Hex (should be 17FCE)
    xprintf("I'm hoping that %x is 0x17FCE.\n", 98254);

    // Unsigned
    xprintf("And I'm also hoping that %u represents my bank account.\n",  2147483647);

    // Character
    xprintf("I am a %c student, see what I did thar?\n", 'A');

    // Percent sign
    xprintf("50%% of all students fail to use xprintf.\n");

    // N count, should be 9
    int x = 0;
    xprintf("123456 8?%n\n", &x);

    // Print out that int!
    xprintf("So it should be 9: %d.\n", x);
    xprintf("Where's %s?  He's all %s style.\n", "Waldo", "CIA");

    // Pad a bit
    xprintf("%c%1c%1c%1c%1c\n", 'H', 'e', 'l', 'l', 'o');

    // Zero pad
    xprintf("%c%01c%01c%01c%01c\n", 'H', 'e', 'l', 'l', 'o');

    // Print out int min
    xprintf("%d\n", INT_MIN);
	return 0;
}