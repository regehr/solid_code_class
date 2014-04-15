#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void reverse(char s[])
{
    int i, j;
    char c;
    
    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int pad(int i)
{
    int j;
    for(j = 0; j < abs(i); j++)
    	(i < 0) ? putchar(' ') : putchar('0');
    return i;
}

char* itoa(int n, char s[], int base)
{
    int i, sign, nextValue;
    
    if (base < 2 || base > 32)
        return s;
    
    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    
    i = 0;
    
    do {       /* generate digits in reverse order */
        nextValue = n % base;
        if (nextValue < 10)
        {
            s[i++] = nextValue + '0';   /* get next digit */
        }
        else
        {
            s[i++] = nextValue - 10 + 'a'; // 10 to 16 should be a + 0 to a + 5.
        }
    } while ((n /= base) > 0);     /* delete it */
    
    if (sign < 0)
        s[i++] = '-';
    
    s[i] = '\0';
    reverse(s);
    
    return s;
}

char* itoaUnsigned(unsigned int n, char s[])
{
    int i;
    
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    
    s[i] = '\0';
    reverse(s);
    
    return s;
}

int xprintf(const char *fmt, ...)
{
    const char *p = NULL;
    va_list argp;
    char *s = NULL;
    char fmtbuf[256];
    int* ptr = NULL;
    int bytes_printed = 0;
    int i = 0;
    int width = 0;
    unsigned int u;
    va_start(argp, fmt);
    
    for(p = fmt; *p != '\0'; p++)
    {
        if(*p != '%' && width == 0)
        {
            putchar(*p);
            bytes_printed += 1;
            continue;
        }
        
        switch(*++p)
        {
            case 'c':
                i = va_arg(argp, int);
                putchar(i);
                bytes_printed += 1;
                break;
            case 'd':
                i = va_arg(argp, int);
                s = itoa(i, fmtbuf, 10);
                if (width != 0){
	                pad(width);
                    width = 0;
                }
                fputs(s, stdout);
                bytes_printed += strlen(s);
                break;
            case 's':
                s = va_arg(argp, char *);
                fputs(s, stdout);
                bytes_printed += strlen(s);
                break;
            case 'x':
                i = va_arg(argp, int);
                s = itoa(i, fmtbuf, 16);
                fputs(s, stdout);
                bytes_printed += strlen(s);
                break;
            case 'u':
                u = va_arg(argp, unsigned int);
                s = itoaUnsigned(i, fmtbuf);
                fputs(s, stdout);
                bytes_printed += strlen(s);
                break;
            case 'n':
                ptr = va_arg(argp, int*);
                *ptr = bytes_printed;
                break;
            case '0':
                width = atoi(p);
                int a = 0;
                if(width != 0)
                    p += (int) floor(log10(abs(width)));
                else
                    p++;
                break;
            case '%':
                putchar('%');
                break;
            default:
                return -1;
                break;
        }
    }
    
    va_end(argp);
    return bytes_printed;
}

int main()
{
    xprintf("Hello %s\n", "Class");
    xprintf("Hello %011d\n", 10);
    return 0;
}