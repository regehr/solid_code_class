#include "xprintf.h"

char *itoa(int num)
{
	static char buff[20] = {};
	int i = 0, temp_num = num, length = 0;
	char *string = buff;
	
	if(num >= 0) 
	{
		while(temp_num) 
		{
			temp_num /= 10;
			length++;
		}
		for(i = 0; i < length; i++) 
		{
		 	buff[(length-1)-i] = '0' + (num % 10);
			num /= 10;
		}
		buff[i] = '\0';
	}	
	else
		return "Unsupported Number";
	
	return string;
}


void xprintf(const char *fmt, ...)
{
const char *p;
va_list argp;
int i;
char *s;
char fmtbuf[256];

va_start(argp, fmt);

for(p = fmt; *p != '\0'; p++)
	{
	if(*p != '%')
		{
		putchar(*p);
		continue;
		}

	switch(*++p)
		{
		case 'c':
			i = va_arg(argp, int);
			putchar(i);
			break;

		case 'd':
			i = va_arg(argp, int);
			s = itoa(i);
			fputs(s, stdout);
			break;

		case 's':
			s = va_arg(argp, char *);
			fputs(s, stdout);
			break;

		case 'x':
			i = va_arg(argp, int);
			s = itoa(i);
			fputs(s, stdout);
			break;

		case '%':
			putchar('%');
			break;
		}
	}

va_end(argp);
}
