#include <stdio.h>
#include <stdarg.h>
#include "musl.h"

int musl_snprintf(char *restrict s, size_t n, const char *restrict fmt, ...)
{
	int ret;
	va_list ap;
	va_start(ap, fmt);
	ret = musl_vsnprintf(s, n, fmt, ap);
	va_end(ap);
	return ret;
}

