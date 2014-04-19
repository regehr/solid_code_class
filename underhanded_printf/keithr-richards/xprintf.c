
#include "xprintf.h"

#include <stdarg.h>
#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include <assert.h>

void reverse( char *buffer, int size )
{
    int i;
    for ( i = 0; i < size / 2; i++ )
    {
	char tmp = buffer[i];
	buffer[i] = buffer[size - i - 1];
	buffer[size - i - 1] = tmp;
    }
}

int process_ints( char *character, va_list args)
{
    int padding = *character == '0';
    if ( padding ) character++;

    int is_signed = *character == 'd';
    int base = *character == 'x' ? 16 : 10;
    int arg = va_arg( args, int );
    char buffer[11 + 1];
    int i = 0;

    if ( arg == 0 )
    {
	buffer[i++] = '0';
    }
    if ( is_signed && arg < 0 ) 
    {
	arg = arg ^ 0xffffffff;
	arg++;
	buffer[i++] = '-';
	arg = arg & 0x7fffffff;
    }

    while ( arg > 0 )
    {
	int rem = arg % base;
	buffer[ i++ ] = rem > 9 ? ( char ) ( 87 + rem) : ( char ) ( 48 + rem );
	arg /= base;
    }
    assert( i < 12 );
    while ( padding && i < 12 )
    {
	buffer[i++] = '0';
    }

    buffer[i] = '\0';
    reverse( buffer, i );
    fputs( buffer, stdout );
    return i;
}

int process_strings( char *character, va_list args )
{
    if ( *character == 'c' )
    {
	char * arg = va_arg( args, char * );
	putchar( *arg );
	return 1;
    }
    else if ( *character == 's' )
    {
	char * arg = va_arg( args, char * );
	int bytes_written = 0;
	while ( *arg )
	{
	    putchar( *arg++ );
	    bytes_written++;
	}
	return bytes_written;
    }
    else if ( *character == '%' )
    {
	putchar( '%' );
	return 1;
    }
    return 0;
}
    
int xprintf( char *format_string, ... )
{
    va_list args;
    va_start( args, format_string );
    int num_bytes_written = 0;

    for ( ; *format_string; format_string++ )
    {
	if ( *format_string == '%' )
	{
	    // handle n seperatly
	    if ( *format_string == 'n' )
	    {
		int *arg = va_arg( args, int * );
		*arg = num_bytes_written;
		continue;
	    }

	    // check for both cases and process them as necessary
	    num_bytes_written += process_strings( ++format_string, args );
	    num_bytes_written += process_ints( format_string, args );
	    
	    // handle the case where we specified padding
	    if ( *format_string == '0' )
	    {
		format_string++;
	    }
	}
	else
	{
	    putchar( *format_string );
	    num_bytes_written++;
	}
    }
    va_end( args );
    return num_bytes_written;
}
