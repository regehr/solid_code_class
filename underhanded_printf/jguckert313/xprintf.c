#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

extern char *itoa(int, char *, int);

void xprintf(const char *fmt, ...) {
    const char *p;
    va_list argp;
    int i;
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
            
            case 'n':
                break;
                
            case 'u':
                break;
		}
	}
    
    va_end(argp);
}

int main() {
    xprintf("%d\n", 12);
    return 0;
}
