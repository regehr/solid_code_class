#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

//Taken from: http://www.geeksforgeeks.org/implement-itoa/
/* A utility function to reverse a string  */
void reverse(char str[], int length)
{
	int start = 0;
	int end = length -1;
	while (start < end)
	{
		//swap elements
		char index = *(str+start);
		*(str+start) = *(str+end);
		*(str+end) = index;
		
		start++;
		end--;
	}
}

//Taken from: http://www.geeksforgeeks.org/implement-itoa/
// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
	int i = 0;
	bool isNegative = false;

	/* Handle 0 explicitly, otherwise empty string is printed for 0 */
	if (num == 0)
	{
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}

	// In standard itoa(), negative numbers are handled only with 
	// base 10. Otherwise numbers are considered unsigned.
	if (num < 0 && base == 10)
	{
		isNegative = true;
		num = -num;
	}

	// Process individual digits
	while (num != 0)
	{
		int rem = num % base;
		str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
		num = num/base;
	}

	// If number is negative, append '-'
	if (isNegative)
	{
		str[i++] = '-';	
	}

	str[i] = '\0'; // Append string terminator

	// Reverse the string
	reverse(str, i);

	return str;
}

char* uitoa(unsigned int num, char* str, int base)
{
	int i = 0;
	bool isNegative = false;

	/* Handle 0 explicitly, otherwise empty string is printed for 0 */
	if (num == 0)
	{
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}

	// In standard itoa(), negative numbers are handled only with 
	// base 10. Otherwise numbers are considered unsigned.
	if (num < 0 && base == 10)
	{
		isNegative = true;
		num = -num;
	}

	// Process individual digits
	while (num != 0)
	{
		int rem = num % base;
		str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
		num = num/base;
	}

	// If number is negative, append '-'
	if (isNegative)
	{
		str[i++] = '-';	
	}

	str[i] = '\0'; // Append string terminator

	// Reverse the string
	reverse(str, i);

	return str;
}

//TODO LIST:
// 1. Support 0 flag
// 2. Support field width digit string
void xprintf(const char *fmt, ...)
{
	const char *p;
	va_list argp;
	int i, count = 0;
	int *ip;
	unsigned int ui;
	char *s;
	char fmtbuf[256];

	va_start(argp, fmt);

	for(p = fmt; *p != '\0'; p++)
	{
		if(*p != '%')
		{
			putchar(*p);
			count++;
			continue;
		}

		switch(*++p)
		{
			//Char
			case 'c':
				i = va_arg(argp, int);
				putchar(i);
				break;

			//Int (base 10)
			case 'd':
				i = va_arg(argp, int);
				s = itoa(i, fmtbuf, 10);
				fputs(s, stdout);
				break;

			//String
			case 's':
				s = va_arg(argp, char *);
				fputs(s, stdout);
				break;

			//Int (base 16)
			case 'x':
				i = va_arg(argp, int);
				s = itoa(i, fmtbuf, 16);
				fputs(s, stdout);
				break;

			//ugh
			case '%':
				putchar('%');
				break;
				
			//Unsigned Int (base 10)
			case 'u':
				ui = va_arg(argp, int);
				s = uitoa(ui, fmtbuf, 10);
				fputs(s, stdout);
				break;
				
			//Nothing printed case
			//Argument is a pointer to a signed int
			//Store number of chars written so far in argument
			case 'n':
				ip = va_arg(argp, int*);
				*ip = count;
				break;
		}
	}

	va_end(argp);
}