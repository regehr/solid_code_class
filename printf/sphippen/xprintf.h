#ifndef SPH_XPRINTF_H_
#define SPH_XPRINTF_H_

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

int xprintf(const char *, ...);
int xfprintf(FILE *, const char *, ...);

int xvprintf(const char *, va_list);
int xvfprintf(FILE *, const char *, va_list);

#ifdef __cplusplus
}
#endif

#endif // SPH_XPRITNF_H_
