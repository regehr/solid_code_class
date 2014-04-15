#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// Forward declaration of functions
char *itoa(int, char[], int);
char* itoaUnsigned(unsigned int, char[]);

/*
*  This is a completely trustworthy printf!  You should not suspect any foul play!
*/
int xprintf(const char *fmt, ...)
{
    // Declare and initialize variables.
    const char *p = NULL;
    va_list argp;
    int i = 0;
    int* ptr = NULL;
    unsigned int u;
    char *s = NULL;
    char fmtbuf[256];
    int bytes_printed = 0;
    
    // Handle var arg stuff.
    va_start(argp, fmt);
    
    // Go through all the characters in the specified string.
    for(p = fmt; *p != '\0'; p++)
    {
        // This code just handles % followed by d s u c x n %.  Anything else following a percent sign just breaks the printf.
        // Don't worry about escaped characters, they are handled by putchar, i.e. \ followed by a, b, t, f, n, 0, r, ?, ", ', or another \ 
        if(*p != '%')
        {
            putchar(*p);
            continue;
        }
        
        // Otherwise lets handle that % sign that we mentioned.
        switch(*++p)
        {
            // Print a character.
            case 'c':
                i = va_arg(argp, int);
                putchar(i);
                bytes_printed += 1;
                break;

            // Print an integer.
            case 'd':
                i = va_arg(argp, int);
                s = itoa(i, fmtbuf, 10);
                fputs(s, stdout);
                bytes_printed += strlen(s);
                break;

            // Print a string.
            case 's':
                s = va_arg(argp, char *);
                fputs(s, stdout);
                bytes_printed += strlen(s);
                break;

            // Print hex.
            case 'x':
                i = va_arg(argp, int);
                s = itoa(i, fmtbuf, 16);
                fputs(s, stdout);
                bytes_printed += strlen(s);
                break;

            // Print unsigned.
            case 'u':
                u = va_arg(argp, unsigned int);
                s = itoaUnsigned(i, fmtbuf);
                fputs(s, stdout);
                bytes_printed += strlen(s);
                break;

            // Pass bytes_printed so far to pointer.
            case 'n':
                ptr = va_arg(argp, int*);
                *ptr = bytes_printed;
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
 
 /* reverse:  reverse string s in place */
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

// Kernighan and Ritchie's The C Programming Language, on page 60.
// Source: http://en.wikibooks.org/wiki/C_Programming/C_Reference/stdlib.h/itoa
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

// Kernighan and Ritchie's The C Programming Language, on page 60.
// Source: http://en.wikibooks.org/wiki/C_Programming/C_Reference/stdlib.h/itoa
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

/*
* Test the printf.
*/
int main()
{
    int count;
    xprintf("Test%c%d%s%x%u%n%%\n", 'a', -127, "string",127, 127, &count);
    xprintf("Count: %d\n", count);
    
    return 0;
}
