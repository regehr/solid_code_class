/*
 * utils.c
 *
 * Jonathon McDonald - <jmcdonald.ut@gmail.com>
 */
#include <limits.h>
#include <stdlib.h>

#include "utils.h"

/* Converts integer to appropriate base and outputs to buff */
char * itoa (int input, char *buff, int radix)
{
	int is_signed = 0, div = 0, rem = 0, si = 0, ci = 0;
	char hex[] = { 'a', 'b', 'c', 'd', 'e', 'f' }, tmp[16] = { 0 };
	char *str = xmalloc(16);
	(*str) = 0;

	if (INT_MIN == input) {
		input = MIN_FIX;
		radix = radix < 16 ? 16 : radix;
	}

	is_signed = input < 0 && radix == 10;
	div = (input < 0) ? -input : input;
	do {
		rem = div % radix;
		div = div / radix;

		tmp[ci++] = (rem > 9) ? hex[(rem - 10)] : (char)(rem + 48);
	} while (div != 0);

	if (is_signed) {
		tmp[ci++] = '-';
	}

	do {
		ci--;
		str[si++] = tmp[ci];
	} while (ci > 0);

	str[si++] = '\0';
	if (si > 16) {
		exit(2);
	}
	
	return str;
}

/* Allocates memory, or errors out on failure */
void * xmalloc (size_t size)
{
	void *ptr = malloc(size);
	if (NULL == ptr) {
		exit(3);
	}

	return ptr;
}