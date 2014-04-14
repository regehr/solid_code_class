#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	xprintf("%d\n", 35);
	xprintf("%c\n", 'a');
	xprintf("%s\n", "test");
	xprintf("%x\n", 10);
	xprintf("%%\n");
}