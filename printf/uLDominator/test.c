#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int i = 0;
	xprintf("%d\n", 35);
	xprintf("%c\n", 'a');
	xprintf("%s\n", "test");
	xprintf("%x\n", 10);
	xprintf("%%\n");
	xprintf("Print 7%n\n", &i);
	printf("Returned: %i\n", i);
	xprintf("%u\n", 4294967294);
}