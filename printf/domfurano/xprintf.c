#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

/* Invalid for ints outside range INT_MIN + 1 to INT_MAX. */
static char* itoa(int, char *, int);

static void set_buf(char *, char, int);

static int buf_len(char *);

static int eval_width(char *, int *, char*, int);

static void reverse_string(char *, int);

static int xfputc(int, FILE *);

static int xfputs(const char *, FILE *);

static void * xmalloc(size_t);

static int xprintf(const char *, ...);

/* Converts width string to int.
 * Invalid for widths greater than INT_MAX.*/
static int width_to_int(char *);

int main()
{
    printf("printf:  %d\n", 10);
    xprintf("xprintf: %d\n", 10);
    printf("printf:  %10s\n", "foo");
    xprintf("xprintf: %10s\n", "foo");
    printf("printf:  %023x\n", 5000);
    xprintf("xprintf: %023x\n", 5000);
}

static int xprintf(const char *fmt, ...)
{
	const char *p; /* Current character in format string. */
    int chars_written = 0; /* Number of characters written. */

    int i; /* Storage for argument. */
    char *s; /* Pointer to converted string from argument. */
    char fmtbuf[256]; /* Buffer for conversion specifiers. */
    
    int width_specifer_found = 0; /* Width specifier found in format string boolean. */
    char widthbuf[256]; /* Buffer for padding width specifier. */
    int widthbuf_pos = 0; /* Position of width buffer. */
    char padding = ' '; /* Padding type. */
    
    int *n; /* Pointer for n format specifier. */
    
    int flag_found = 0; /* '0' flag found boolean. */
    
    va_list argp; /* Argument pointer. */
    va_start(argp, fmt);
    
	for (p = fmt; *p != '\0'; p++)
    {
		if (*p != '%' && !width_specifer_found && !flag_found)
        {
			xfputc(*p, stdout);
            chars_written++;
            flag_found = 0;
            width_specifer_found = 0;
			continue;
        }
        
        /*  *p == '%'  */
        
        /* Only advance argument pointer if a width specifier or a
         * flag has not been found. */
        if (!width_specifer_found && !flag_found)
        {
            p++;
        }
        
		switch (*p)
        {
			case 'd':
                /* Save argument. */
                i = va_arg(argp, int);
                /* Covert argument to string. */
                s = itoa(i, fmtbuf, 10);
                /* Evaluate width specification, if any. */
                chars_written += eval_width(widthbuf, &widthbuf_pos, &padding, buf_len(s));
                /* Covert argument to string again. */
                s = itoa(i, fmtbuf, 10);
                /* Output formatted string. */
                xfputs(s, stdout);
                /* Update number of characters written. */
                chars_written += buf_len(s);
                /* Clear flags. */
                flag_found = 0;
                width_specifer_found = 0;
				break;
                
			case 's':
                /* Save string argument. */
                s = va_arg(argp, char *);
                chars_written += eval_width(widthbuf, &widthbuf_pos, &padding, buf_len(s));
                xfputs(s, stdout);
                chars_written += buf_len(s);
                flag_found = 0;
                width_specifer_found = 0;
				break;
                
			case 'u':
                i = va_arg(argp, int);
                s = itoa(i, fmtbuf, 10);
                chars_written += eval_width(widthbuf, &widthbuf_pos, &padding, buf_len(s));
                xfputs(s, stdout);
                chars_written += buf_len(s);
                flag_found = 0;
                width_specifer_found = 0;
				break;
                
			case 'c':
                i = va_arg(argp, int);
                chars_written += eval_width(widthbuf, &widthbuf_pos, &padding, 1);
                xfputc(i, stdout);
                chars_written += 1;
                flag_found = 0;
                width_specifer_found = 0;
				break;
                
			case 'x':
                i = va_arg(argp, int);
                s = itoa(i, fmtbuf, 16);
                chars_written += eval_width(widthbuf, &widthbuf_pos, &padding, buf_len(s));
                xfputs(s, stdout);
                chars_written += buf_len(s);
                flag_found = 0;
                width_specifer_found = 0;
				break;
                
            case 'n':
                n = va_arg(argp, int *);
                *n = chars_written;
                flag_found = 0;
                width_specifer_found = 0;
				break;
                
            case '%':
                xfputc(*p, stdout);
                chars_written++;
                flag_found = 0;
                width_specifer_found = 0;
                break;
                
            case '0':
                if (!width_specifer_found)
                {
                    flag_found = 1;
                    padding = '0';
                    break;
                }
                
            default:
                width_specifer_found = 1;
                widthbuf[widthbuf_pos++] = *p;
                break;
        }
    }
    va_end(argp);
    return chars_written;
}

/* Convert integer to string. Only valid for base 2 through 16. */
static char* itoa(int value, char* buf, const int base)
{
    /* Check for invalid base. */
    if (base < 2 || base > 16)
    {
        return buf;
    }
    
    /* value = 0 is a special case. */
    if (value == 0)
    {
        buf[0] = '0';
        buf[1] = '\0';
        return buf;
    }
    
    /* Check if value is negative. */
    int is_negative = 0;
    if (value < 0)
    {
        is_negative = 1;
        value = -value;
    }
    
    /* Write mapped char to buffer. */
    int i = 0;
    while (value)
    {
        buf[i++] = "0123456789abcdef"[value % base];
        value /= base;
    }
    
    /* Append '-' if value was negative. */
    if (is_negative)
    {
        buf[i++] = '-';
    }
    
    /* Append terminating null char. */
    buf[i++] = '\0';
    
    /* Reverse buf in place. */
    reverse_string(buf, i - 2);
    
    return buf;
}

static int eval_width(char *widthbuf, int *length, char *padding, int output_len)
{
    if (width_to_int(widthbuf) > output_len)
    {
        /* Add terminator to width buffer. */
        widthbuf[++(*length)] = '\0';
        /* Convert width to integer. */
        int width = width_to_int(widthbuf);
        /* Clear width buffer. */
        set_buf(widthbuf, '\0', 256);
        
        /* Subtract output from width padding. */
        width -= output_len;
        
        /* If the padding is longer than the output length. */
        if (width > 0)
        {
            /* Create a string long enough to hold width padding and null terminator. */
            char *width_str = (char *)xmalloc(width + 1);
            
            /* Build width string. */
            int i;
            for (i = 0; i < width; i++)
            {
                width_str[i] = *padding;
            }
            width_str[i] = '\0';
            
            /* Output width string. */
            xfputs(width_str, stdout);
            free(width_str);
        }
        *length = 0;
        *padding = ' ';
        return width;
    }
    return 0;
}

static int buf_len(char *buf)
{
    int length = 0;
    while (*(buf++) != '\0')
    {
        length++;
    }
    return length;
}

static void set_buf(char *buf, char value, int num)
{
    while (num--)
    {
        *(buf++) = value;
    }
}

static int pow(int base, int exp)
{
    if (exp == 0)
    {
        return 1;
    }
    int product = base;
    for (; exp > 1; exp--)
    {
        product *= base;
    }
    return product;
}

static int width_to_int(char *width_buf)
{
    int width = 0;
    for (int pos = buf_len(width_buf) - 1; *width_buf != '\0'; pos--)
    {
        width += pow(10, pos) * (*(width_buf++) - '0');
    }
    return width;
}

static void reverse_string(char *s, int s_end)
{
    int s_start = 0;
    while (s_start < s_end)
    {
        char temp = s[s_start];
        s[s_start++] = s[s_end];
        s[s_end--] = temp;
    }
}

static void * xmalloc(size_t size)
{
    void * out = malloc(size);
    if (out == NULL)
    {
        exit(-1);
    }
    return out;
}

static int xfputc(int character, FILE *stream)
{
    int put_character = fputc(character, stream);
    if (put_character == EOF)
    {
        exit(-1);
    }
    return put_character;
}

static int xfputs(const char * str, FILE *stream)
{
    int put_string = fputs(str, stream);
    if (put_string == EOF)
    {
        exit(-1);
    }
    return put_string;
}
