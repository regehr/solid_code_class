#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>


/* A utility function to reverse a string  */
/* implementation from www.geeksforgeeks.org/implement-itoa */
void swap(char a, char b) {
	
		char index = a;
		b = a;
		a = index;
		
}
void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(*(str+start), *(str+end));
		
        start++;
        end--;
    }
}

/* implementation from www.geeksforgeeks.org/implement-itoa */
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;
 
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
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
        str[i++] = '-';
 
    	str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
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
			s = itoa(i, fmtbuf, 10);
			fputs(s, stdout);
			break;

		case 's':
			s = va_arg(argp, char *);
			fputs(s, stdout);
			break;

		case 'x':
			i = va_arg(argp, int);
			s = itoa(i, fmtbuf, 16);
			fputs(s, stdout);
			break;

		case '%':
			putchar('%');
			break;
		}
	}

va_end(argp);
}

int main(void) {
	xprintf("%d\n", 22);
}