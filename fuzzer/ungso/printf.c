//Implements printf by C.M. 4/8/2014

int printf(const char *format, ...);


int printf(const char *format, ...){
	int ret;
	va_list ap;
	va_start(ap, fmt);
	ret = cm_printf(fmt, ap);
	va_end(ap);
	return ret;
}


int cm_printf(const char *format, va_list ap){




}
