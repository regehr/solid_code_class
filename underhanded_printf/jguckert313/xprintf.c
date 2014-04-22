#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(char c1, char c2) {
    char c3 = c1;
    c1 = c2;
    c2 = c3;
}


/* reverse() and itoa referenced from http://www.geeksforgeeks.org/implement-itoa/ */
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
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}

int xprintf(const char *fmt, ...) {
    const char *p;
    va_list argp;
    int i, bytes_printed = 0;
    char *s;
    char fmtbuf[256];
    
    va_start(argp, fmt);
    
    for(p = fmt; *p != '\0'; p++) {
        if(*p != '%') {
            putchar(*p);
            continue;
		}
        
        switch(*++p) {
            case 'c':
                i = va_arg(argp, int);
                putchar(i);
                bytes_printed += 1;
                break;
                
            case 'd':
                i = va_arg(argp, int);
                s = itoa(i, fmtbuf, 10);
                bytes_printed += 1;
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
            
            case 'n':
                break;
                
            case 'u':
                break;
		}
	}
    
    va_end(argp);
    return bytes_printed;
}

int main() {
    xprintf("%d\n", 21);
    xprintf("%s\n", "hello");
    xprintf("%x\n", 100);
    xprintf("%c\n", 'a');
    xprintf("%%\n", 0);
    xprintf("%n\n", 0);
    xprintf("%u", 12);
    return 0;
}
