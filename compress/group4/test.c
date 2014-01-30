#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	printf("%d\n" , atoi(argv[2]));
	if(atoi(argv[2]) == 0)
	{
		return 0;
	}
	else
	{
		printf("error\n");
		exit(1);
	}
}
