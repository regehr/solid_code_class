#include <stdio.h>
#include <stdarg.h>
#include "musl.h"

#define LEN 10000
char buf[LEN];

int main (void)
{
musl_snprintf(buf, LEN, "%x\n%c\n%e\n%e\n", -2147483649, '[', 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%u\n%e\n%lg\n", 1.79769313486e+308, 4294967296, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%f\n%ld\n%lf\n", 9223372036854775807, 1.79769313486e+308, 9223372036854775807, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%g\n%lg\n%lf\n", 'G', 2.22507385851e-308, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%f\n%c\n%e\n", 2.22507385851e-308, 1.79769313486e+308, 'V', 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%le\n%ld\n%s\n", 1.79769313486e+308, 1.79769313486e+308, 9223372036854775807, "completely");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%e\n%o\n%lf\n", 1.79769313486e+308, 1.79769313486e+308, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%f\n%u\n%lg\n", '!', 2.22507385851e-308, 4294967296, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%lf\n%le\n%e\n", 1.79769313486e+308, 1.79769313486e+308, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%u\n%d\n%s\n", 2147483647, 4294967296, 2147483647, "completely");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%u\n%le\n%le\n", 2.22507385851e-308, 0, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%f\n%s\n%o\n", '?', 2.22507385851e-308, "different", -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%f\n%f\n%g\n", 2.22507385851e-308, 2.22507385851e-308, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%lu\n%o\n%x\n", 2.22507385851e-308, 0, 2147483647, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%u\n%c\n%ld\n", -9223372036854775809, 0, 'E', 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lg\n%d\n%e\n", ']', 2.22507385851e-308, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%s\n%s\n%s\n", 18446744073709551616, "for", "different", "for");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%lg\n%e\n%ld\n", 1.79769313486e+308, 1.79769313486e+308, 2.22507385851e-308, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%le\n%x\n%ld\n", 18446744073709551616, 2.22507385851e-308, 2147483647, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%le\n%e\n%le\n", 18446744073709551616, 2.22507385851e-308, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%x\n%le\n%ld\n", 2147483647, 2147483647, 1.79769313486e+308, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%s\n%x\n%d\n", 1.79769313486e+308, "something", -2147483649, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%s\n%lu\n%x\n", 2.22507385851e-308, "and", 18446744073709551616, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%le\n%d\n%lu\n", -9223372036854775809, 2.22507385851e-308, -2147483649, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%s\n%f\n%lu\n", 18446744073709551616, "completely", 1.79769313486e+308, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%e\n%o\n%c\n", 2.22507385851e-308, 2.22507385851e-308, 2147483647, '0');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%f\n%lu\n%u\n", 2147483647, 1.79769313486e+308, 0, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%u\n%x\n%g\n", 2147483647, 0, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%f\n%lg\n%c\n", 2147483647, 1.79769313486e+308, 2.22507385851e-308, ';');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%c\n%lg\n%f\n", 1.79769313486e+308, '-', 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%g\n%d\n%e\n", 0, 1.79769313486e+308, 2147483647, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%u\n%ld\n%ld\n", "and", 4294967296, -9223372036854775809, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%ld\n%e\n%c\n", 2.22507385851e-308, -9223372036854775809, 1.79769313486e+308, 'n');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%d\n%lg\n%g\n", "for", 2147483647, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%s\n%f\n%lu\n", 1.79769313486e+308, "and", 2.22507385851e-308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%e\n%s\n%lu\n", 'r', 1.79769313486e+308, "for", 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%le\n%x\n%x\n", 2147483647, 1.79769313486e+308, -2147483649, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%s\n%ld\n%lu\n", -2147483649, "completely", 9223372036854775807, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%lu\n%x\n%f\n", -2147483649, 18446744073709551616, 2147483647, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%s\n%le\n%ld\n", 2.22507385851e-308, "something", 1.79769313486e+308, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%x\n%c\n%ld\n", 1.79769313486e+308, -2147483649, 'w', 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%d\n%lg\n%lu\n", -2147483649, 2147483647, 2.22507385851e-308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%le\n%c\n%o\n", 0, 2.22507385851e-308, 'x', -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%le\n%ld\n%c\n", 1.79769313486e+308, 1.79769313486e+308, -9223372036854775809, '(');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%e\n%c\n%d\n", '{', 2.22507385851e-308, '>', -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%ld\n%g\n%lu\n", 2.22507385851e-308, -9223372036854775809, 1.79769313486e+308, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%s\n%x\n%le\n", 2.22507385851e-308, "and", 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%e\n%ld\n%lu\n", -2147483649, 1.79769313486e+308, -9223372036854775809, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%f\n%x\n%o\n", "now", 1.79769313486e+308, 2147483647, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%le\n%lg\n%u\n", 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%le\n%c\n%s\n", 1.79769313486e+308, 1.79769313486e+308, 'F', "now");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%s\n%lu\n%u\n", 1.79769313486e+308, "completely", 0, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%le\n%d\n%ld\n", 4294967296, 2.22507385851e-308, -2147483649, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%ld\n%ld\n%s\n", 2.22507385851e-308, 9223372036854775807, -9223372036854775809, "different");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%o\n%e\n%ld\n", 1.79769313486e+308, 2147483647, 1.79769313486e+308, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%f\n%ld\n%g\n", 2.22507385851e-308, 1.79769313486e+308, 9223372036854775807, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%f\n%o\n%g\n", -2147483649, 2.22507385851e-308, 2147483647, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%g\n%s\n%lu\n", 2147483647, 1.79769313486e+308, "completely", 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%u\n%ld\n%lg\n", 18446744073709551616, 0, 9223372036854775807, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%ld\n%f\n%s\n", 1.79769313486e+308, -9223372036854775809, 2.22507385851e-308, "something");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%f\n%s\n%e\n", 2.22507385851e-308, 1.79769313486e+308, "and", 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%le\n%le\n%d\n", 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%d\n%s\n%lf\n", -2147483649, -2147483649, "different", 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%c\n%lu\n%f\n", 1.79769313486e+308, 'N', 18446744073709551616, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%s\n%f\n%d\n", 1.79769313486e+308, "now", 2.22507385851e-308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%lu\n%e\n%le\n", 2147483647, 0, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%f\n%u\n%f\n", "different", 2.22507385851e-308, 0, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%ld\n%lf\n%u\n", '3', 9223372036854775807, 2.22507385851e-308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%lf\n%g\n%f\n", 0, 1.79769313486e+308, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%d\n%ld\n%s\n", -2147483649, -2147483649, 9223372036854775807, "for");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%o\n%o\n%x\n", 2.22507385851e-308, 2147483647, -2147483649, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%s\n%lu\n%lf\n", 2.22507385851e-308, "different", 0, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%d\n%g\n%lu\n", 2.22507385851e-308, 2147483647, 2.22507385851e-308, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%s\n%c\n%f\n", 4294967296, "for", '\\', 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%lg\n%g\n%g\n", 2147483647, 2.22507385851e-308, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%u\n%g\n%u\n", 0, 0, 2.22507385851e-308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%e\n%d\n%d\n", 9223372036854775807, 1.79769313486e+308, 2147483647, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%d\n%lu\n%lf\n", 2.22507385851e-308, 2147483647, 0, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%lu\n%x\n%g\n", 1.79769313486e+308, 0, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%o\n%o\n%x\n", 18446744073709551616, 2147483647, 2147483647, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%d\n%o\n%d\n", 1.79769313486e+308, 2147483647, -2147483649, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%c\n%s\n%s\n", 9223372036854775807, 'u', "now", "different");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%c\n%f\n%le\n", 0, 'l', 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%lg\n%s\n%x\n", 2.22507385851e-308, 1.79769313486e+308, "completely", 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%lg\n%x\n%s\n", 2.22507385851e-308, 2.22507385851e-308, 2147483647, "something");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%lg\n%f\n%g\n", -2147483649, 2.22507385851e-308, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%lu\n%o\n%lu\n", "for", 18446744073709551616, -2147483649, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%le\n%f\n%u\n", 4294967296, 2.22507385851e-308, 2.22507385851e-308, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%lg\n%d\n%c\n", 2.22507385851e-308, 2.22507385851e-308, -2147483649, 'v');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%ld\n%o\n%ld\n", 18446744073709551616, -9223372036854775809, -2147483649, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%le\n%c\n%g\n", '^', 2.22507385851e-308, 'Q', 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%d\n%le\n%x\n", 2.22507385851e-308, -2147483649, 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%d\n%lf\n%o\n", 2.22507385851e-308, 2147483647, 2.22507385851e-308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%x\n%x\n%s\n", 1.79769313486e+308, -2147483649, 2147483647, "now");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%x\n%c\n%c\n", 0, 2147483647, 'i', 'b');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%le\n%o\n%s\n", 2.22507385851e-308, 1.79769313486e+308, 2147483647, "for");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%lu\n%lg\n%lf\n", 0, 0, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%lg\n%s\n%d\n", 2147483647, 1.79769313486e+308, "and", -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%x\n%s\n%ld\n", 18446744073709551616, -2147483649, "different", 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%lu\n%le\n%d\n", -9223372036854775809, 18446744073709551616, 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%o\n%x\n%lf\n", 2.22507385851e-308, -2147483649, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%c\n%lu\n%x\n", 2147483647, '^', 0, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%o\n%u\n%g\n", 2147483647, 2147483647, 0, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%e\n%c\n%c\n", 2147483647, 1.79769313486e+308, '7', '2');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%x\n%u\n%e\n", 1.79769313486e+308, 2147483647, 0, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%g\n%ld\n%s\n", -2147483649, 2.22507385851e-308, -9223372036854775809, "different");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%f\n%e\n%e\n", 1.79769313486e+308, 1.79769313486e+308, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%le\n%o\n%e\n", 1.79769313486e+308, 1.79769313486e+308, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%d\n%o\n%le\n", 2.22507385851e-308, -2147483649, 2147483647, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%ld\n%d\n%u\n", -2147483649, -9223372036854775809, 2147483647, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%u\n%f\n%o\n", 1.79769313486e+308, 0, 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%x\n%le\n%c\n", 9223372036854775807, 2147483647, 2.22507385851e-308, '%');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%lg\n%c\n%ld\n", 0, 2.22507385851e-308, 'Y', 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%lg\n%u\n%lf\n", -2147483649, 2.22507385851e-308, 4294967296, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%e\n%o\n%e\n", 1.79769313486e+308, 1.79769313486e+308, -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%c\n%lu\n%c\n", -9223372036854775809, 'p', 0, 'r');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%f\n%d\n%d\n", 2147483647, 2.22507385851e-308, -2147483649, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%lu\n%u\n%u\n", 2147483647, 18446744073709551616, 4294967296, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%u\n%e\n%u\n", 2147483647, 0, 1.79769313486e+308, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%e\n%ld\n%u\n", 2.22507385851e-308, 1.79769313486e+308, 9223372036854775807, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%ld\n%c\n%lg\n", 2147483647, -9223372036854775809, 'E', 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%e\n%c\n%f\n", 2.22507385851e-308, 2.22507385851e-308, '?', 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%x\n%lg\n%s\n", 1.79769313486e+308, 2147483647, 1.79769313486e+308, "and");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lu\n%le\n%f\n", '7', 18446744073709551616, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%u\n%x\n%d\n", '9', 4294967296, 2147483647, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%ld\n%f\n%f\n", 1.79769313486e+308, -9223372036854775809, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%ld\n%o\n%le\n", 18446744073709551616, -9223372036854775809, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%s\n%ld\n%o\n", 0, "completely", -9223372036854775809, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%e\n%c\n%e\n", "completely", 2.22507385851e-308, 'p', 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%ld\n%g\n%le\n", 1.79769313486e+308, 9223372036854775807, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%x\n%o\n%lu\n", 9223372036854775807, -2147483649, 2147483647, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%le\n%x\n%e\n", 2.22507385851e-308, 2.22507385851e-308, -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%o\n%lu\n%g\n", 'd', -2147483649, 18446744073709551616, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%d\n%le\n%lf\n", 2.22507385851e-308, -2147483649, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%f\n%e\n%d\n", -9223372036854775809, 1.79769313486e+308, 1.79769313486e+308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%d\n%u\n%o\n", 2147483647, 2147483647, 4294967296, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%lf\n%le\n%lg\n", 2.22507385851e-308, 2.22507385851e-308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%o\n%lg\n%lf\n", '$', 2147483647, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%e\n%lf\n%lf\n", 1.79769313486e+308, 1.79769313486e+308, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%le\n%le\n%o\n", 'q', 2.22507385851e-308, 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%le\n%c\n%d\n", 1.79769313486e+308, 2.22507385851e-308, 'b', -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%x\n%o\n%le\n", 2.22507385851e-308, -2147483649, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%le\n%lg\n%c\n", -2147483649, 1.79769313486e+308, 1.79769313486e+308, 'M');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%lu\n%e\n%e\n", 2147483647, 18446744073709551616, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%lg\n%g\n%c\n", 18446744073709551616, 1.79769313486e+308, 1.79769313486e+308, 'o');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%ld\n%s\n%ld\n", 1.79769313486e+308, 9223372036854775807, "something", 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%s\n%d\n%g\n", 18446744073709551616, "different", 2147483647, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%g\n%x\n%g\n", 0, 1.79769313486e+308, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%e\n%g\n%x\n", 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%s\n%e\n%u\n", 2147483647, "something", 1.79769313486e+308, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%lf\n%f\n%ld\n", -9223372036854775809, 2.22507385851e-308, 1.79769313486e+308, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%lu\n%c\n%e\n", -2147483649, 0, 'M', 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%lg\n%g\n%lf\n", -2147483649, 1.79769313486e+308, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%lg\n%u\n%e\n", 2.22507385851e-308, 2.22507385851e-308, 0, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%s\n%u\n%lu\n", 'd', "something", 4294967296, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%o\n%g\n%g\n", 1.79769313486e+308, 2147483647, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%lu\n%u\n%x\n", -2147483649, 0, 4294967296, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%u\n%lu\n%s\n", 2147483647, 0, 0, "different");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%u\n%d\n%d\n", 1.79769313486e+308, 4294967296, -2147483649, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%g\n%e\n%lg\n", 1.79769313486e+308, 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lg\n%x\n%lg\n", '\\', 2.22507385851e-308, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%f\n%f\n%f\n", "and", 2.22507385851e-308, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%o\n%le\n%ld\n", 1.79769313486e+308, -2147483649, 2.22507385851e-308, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%s\n%lg\n%x\n", 1.79769313486e+308, "and", 2.22507385851e-308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%ld\n%o\n%c\n", 2147483647, 9223372036854775807, -2147483649, '^');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%lu\n%e\n%u\n", 1.79769313486e+308, 18446744073709551616, 2.22507385851e-308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%u\n%ld\n%o\n", 1.79769313486e+308, 4294967296, 9223372036854775807, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lg\n%d\n%lf\n", 'd', 1.79769313486e+308, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%lu\n%f\n%d\n", 1.79769313486e+308, 0, 1.79769313486e+308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%g\n%s\n%f\n", 1.79769313486e+308, 1.79769313486e+308, "and", 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%s\n%e\n%ld\n", "different", "now", 2.22507385851e-308, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%ld\n%g\n%e\n", -2147483649, -9223372036854775809, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%u\n%lg\n%o\n", 2.22507385851e-308, 4294967296, 1.79769313486e+308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%g\n%lu\n%f\n", 9223372036854775807, 2.22507385851e-308, 18446744073709551616, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%g\n%x\n%f\n", 1.79769313486e+308, 1.79769313486e+308, 2147483647, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%s\n%le\n%ld\n", 2147483647, "and", 2.22507385851e-308, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%d\n%le\n%g\n", 2147483647, -2147483649, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%d\n%s\n%g\n", 4294967296, -2147483649, "and", 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%u\n%e\n%lu\n", 1.79769313486e+308, 0, 2.22507385851e-308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%lf\n%e\n%g\n", 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%c\n%e\n%ld\n", 2.22507385851e-308, '8', 2.22507385851e-308, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%c\n%lu\n%x\n", -2147483649, '*', 18446744073709551616, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%g\n%u\n%lf\n", -2147483649, 1.79769313486e+308, 0, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%lg\n%s\n%g\n", 4294967296, 1.79769313486e+308, "for", 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%ld\n%lu\n%le\n", 2147483647, -9223372036854775809, 18446744073709551616, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%g\n%c\n%f\n", 0, 2.22507385851e-308, 'H', 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lf\n%x\n%g\n", '@', 1.79769313486e+308, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%c\n%lg\n%f\n", 1.79769313486e+308, ' ', 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%lf\n%c\n%e\n", -2147483649, 2.22507385851e-308, 'P', 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%f\n%ld\n%f\n", 'V', 1.79769313486e+308, 9223372036854775807, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%c\n%x\n%g\n", 1.79769313486e+308, '\"', 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%e\n%e\n%u\n", '!', 2.22507385851e-308, 2.22507385851e-308, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%c\n%x\n%le\n", 4294967296, 'p', -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%g\n%lf\n%u\n", 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%ld\n%lu\n%lf\n", 's', 9223372036854775807, 18446744073709551616, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%f\n%o\n%e\n", 0, 1.79769313486e+308, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%e\n%ld\n%ld\n", -2147483649, 2.22507385851e-308, 9223372036854775807, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%o\n%lg\n%g\n", 1.79769313486e+308, 2147483647, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%lg\n%o\n%lf\n", 1.79769313486e+308, 2.22507385851e-308, -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%c\n%e\n%lg\n", 2.22507385851e-308, '\"', 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%ld\n%lf\n%u\n", 2.22507385851e-308, 9223372036854775807, 2.22507385851e-308, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%s\n%lu\n%lg\n", 2.22507385851e-308, "and", 0, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%lg\n%x\n%f\n", 1.79769313486e+308, 1.79769313486e+308, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%o\n%ld\n%ld\n", '\"', -2147483649, -9223372036854775809, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%lg\n%o\n%lu\n", 2.22507385851e-308, 1.79769313486e+308, -2147483649, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%lu\n%f\n%o\n", -9223372036854775809, 0, 2.22507385851e-308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%lf\n%lg\n%g\n", 1.79769313486e+308, 1.79769313486e+308, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%f\n%o\n%o\n", 1.79769313486e+308, 1.79769313486e+308, -2147483649, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%lu\n%c\n%lf\n", 0, 18446744073709551616, '>', 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%d\n%e\n%lg\n", 2.22507385851e-308, -2147483649, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%f\n%o\n%lg\n", 0, 2.22507385851e-308, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%o\n%le\n%c\n", 2147483647, 2147483647, 1.79769313486e+308, 'l');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%lu\n%s\n%g\n", 2.22507385851e-308, 18446744073709551616, "for", 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%lf\n%s\n%o\n", -2147483649, 2.22507385851e-308, "for", 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%g\n%u\n%c\n", 1.79769313486e+308, 2.22507385851e-308, 0, 'K');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%d\n%g\n%s\n", 1.79769313486e+308, -2147483649, 2.22507385851e-308, "for");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%g\n%f\n%u\n", 2.22507385851e-308, 1.79769313486e+308, 1.79769313486e+308, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%lf\n%lf\n%lg\n", 2.22507385851e-308, 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%x\n%g\n%lg\n", -9223372036854775809, 2147483647, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%u\n%ld\n%lf\n", 4294967296, 0, -9223372036854775809, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%lg\n%ld\n%o\n", 2.22507385851e-308, 2.22507385851e-308, 9223372036854775807, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%le\n%lf\n%ld\n", 2147483647, 2.22507385851e-308, 2.22507385851e-308, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%lf\n%d\n%lg\n", 18446744073709551616, 2.22507385851e-308, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%lu\n%le\n%u\n", 2.22507385851e-308, 18446744073709551616, 1.79769313486e+308, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%o\n%s\n%e\n", 2.22507385851e-308, -2147483649, "different", 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%ld\n%lf\n%x\n", 'V', -9223372036854775809, 2.22507385851e-308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%e\n%g\n%e\n", -2147483649, 2.22507385851e-308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%f\n%d\n%le\n", "completely", 2.22507385851e-308, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%le\n%c\n%le\n", "something", 2.22507385851e-308, '<', 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%ld\n%s\n%lg\n", 1.79769313486e+308, 9223372036854775807, "completely", 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%lu\n%s\n%s\n", 4294967296, 0, "completely", "and");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%lu\n%u\n%o\n", 2.22507385851e-308, 0, 0, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%s\n%le\n%le\n", 4294967296, "now", 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%lu\n%ld\n%c\n", 0, 0, 9223372036854775807, '~');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%x\n%lu\n%d\n", -2147483649, -2147483649, 0, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%s\n%d\n%d\n", 2.22507385851e-308, "completely", 2147483647, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%e\n%ld\n%x\n", 1.79769313486e+308, 2.22507385851e-308, -9223372036854775809, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%c\n%lf\n%ld\n", -2147483649, '+', 1.79769313486e+308, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%lf\n%x\n%e\n", 2.22507385851e-308, 1.79769313486e+308, -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%s\n%s\n%le\n", 0, "completely", "now", 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%le\n%e\n%o\n", 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%ld\n%f\n%o\n", 'h', 9223372036854775807, 1.79769313486e+308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%f\n%le\n%lu\n", 9223372036854775807, 1.79769313486e+308, 1.79769313486e+308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%e\n%d\n%lu\n", -9223372036854775809, 1.79769313486e+308, 2147483647, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%e\n%g\n%lf\n", 1.79769313486e+308, 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%x\n%c\n%f\n", 18446744073709551616, 2147483647, 'S', 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%e\n%d\n%ld\n", 18446744073709551616, 2.22507385851e-308, -2147483649, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lg\n%d\n%x\n", '5', 1.79769313486e+308, -2147483649, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%s\n%e\n%lg\n", 2147483647, "completely", 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%le\n%f\n%u\n", 'O', 2.22507385851e-308, 2.22507385851e-308, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%c\n%s\n%o\n", 1.79769313486e+308, '}', "for", -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%lf\n%u\n%e\n", -2147483649, 2.22507385851e-308, 0, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%g\n%d\n%lg\n", 2.22507385851e-308, 1.79769313486e+308, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%f\n%lg\n%s\n", "and", 2.22507385851e-308, 2.22507385851e-308, "something");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%ld\n%lf\n%f\n", 2.22507385851e-308, 9223372036854775807, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%f\n%lf\n%ld\n", 'j', 1.79769313486e+308, 1.79769313486e+308, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%d\n%c\n%lu\n", "something", 2147483647, ' ', 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%f\n%lu\n%lu\n", 0, 1.79769313486e+308, 18446744073709551616, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%e\n%u\n%d\n", 18446744073709551616, 2.22507385851e-308, 4294967296, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%lf\n%c\n%lf\n", 2.22507385851e-308, 1.79769313486e+308, 'J', 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%g\n%s\n%f\n", 4294967296, 1.79769313486e+308, "something", 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%d\n%f\n%x\n", 2.22507385851e-308, -2147483649, 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%e\n%lg\n%e\n", 2.22507385851e-308, 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%ld\n%x\n%lf\n", 2147483647, 9223372036854775807, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%u\n%e\n%lu\n", 0, 0, 1.79769313486e+308, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%le\n%x\n%g\n", 1.79769313486e+308, 2.22507385851e-308, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%x\n%g\n%u\n", 1.79769313486e+308, -2147483649, 1.79769313486e+308, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%ld\n%lg\n%lf\n", 2147483647, -9223372036854775809, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%o\n%f\n%s\n", 2147483647, -2147483649, 2.22507385851e-308, "and");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%c\n%g\n%u\n", "different", 'j', 2.22507385851e-308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%s\n%s\n%lu\n", 1.79769313486e+308, "and", "something", 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%ld\n%e\n%le\n", 2.22507385851e-308, 9223372036854775807, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%c\n%s\n%o\n", 1.79769313486e+308, 'P', "something", 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%d\n%u\n%e\n", ']', 2147483647, 0, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%x\n%lg\n%f\n", -2147483649, 2147483647, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%u\n%c\n%lg\n", 2.22507385851e-308, 4294967296, 'o', 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%c\n%o\n%lg\n", -2147483649, 'D', 2147483647, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%le\n%ld\n%le\n", 9223372036854775807, 1.79769313486e+308, -9223372036854775809, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%e\n%u\n%g\n", "something", 2.22507385851e-308, 0, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%lu\n%o\n%e\n", 2147483647, 0, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%le\n%le\n%c\n", 2.22507385851e-308, 2.22507385851e-308, 1.79769313486e+308, 'M');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%lg\n%s\n%f\n", 1.79769313486e+308, 1.79769313486e+308, "different", 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%le\n%f\n%le\n", 18446744073709551616, 2.22507385851e-308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%o\n%s\n%d\n", 1.79769313486e+308, 2147483647, "and", 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%g\n%f\n%c\n", 0, 1.79769313486e+308, 2.22507385851e-308, 'P');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%u\n%lg\n%s\n", 1.79769313486e+308, 0, 2.22507385851e-308, "completely");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%g\n%c\n%lf\n", "completely", 2.22507385851e-308, 'V', 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%e\n%g\n%c\n", 1.79769313486e+308, 1.79769313486e+308, 2.22507385851e-308, '+');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%e\n%g\n%s\n", 1.79769313486e+308, 2.22507385851e-308, 1.79769313486e+308, "now");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%lu\n%o\n%le\n", 18446744073709551616, 18446744073709551616, -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%le\n%lf\n%f\n", -2147483649, 2.22507385851e-308, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%s\n%e\n%u\n", 1.79769313486e+308, "completely", 1.79769313486e+308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%x\n%le\n%f\n", -2147483649, -2147483649, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%d\n%o\n%d\n", 18446744073709551616, 2147483647, 2147483647, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%o\n%c\n%le\n", 1.79769313486e+308, -2147483649, 'U', 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%le\n%lf\n%c\n", 'Q', 1.79769313486e+308, 1.79769313486e+308, '2');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%lg\n%e\n%le\n", "now", 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%c\n%g\n%le\n", 0, 'o', 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%o\n%g\n%x\n", 2147483647, 2147483647, 2.22507385851e-308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%u\n%g\n%lf\n", 2147483647, 4294967296, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%x\n%f\n%o\n", 2.22507385851e-308, -2147483649, 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%le\n%lg\n%lg\n", -9223372036854775809, 1.79769313486e+308, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%ld\n%lf\n%o\n", 2147483647, 9223372036854775807, 1.79769313486e+308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%lu\n%lu\n%f\n", 2147483647, 0, 18446744073709551616, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%s\n%o\n%o\n", -2147483649, "now", -2147483649, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%x\n%c\n%le\n", 0, 2147483647, 'o', 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%f\n%g\n%d\n", "now", 2.22507385851e-308, 2.22507385851e-308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%lf\n%f\n%f\n", 1.79769313486e+308, 1.79769313486e+308, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%le\n%g\n%lf\n", 0, 1.79769313486e+308, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%x\n%u\n%e\n", 2.22507385851e-308, 2147483647, 4294967296, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%c\n%x\n%x\n", 1.79769313486e+308, '\'', 2147483647, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%g\n%lu\n%x\n", 2147483647, 2.22507385851e-308, 0, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%lu\n%lu\n%x\n", 1.79769313486e+308, 18446744073709551616, 18446744073709551616, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%e\n%u\n%c\n", 1.79769313486e+308, 2.22507385851e-308, 4294967296, '#');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%x\n%f\n%d\n", -2147483649, 2147483647, 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%lu\n%le\n%e\n", 1.79769313486e+308, 0, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%s\n%d\n%e\n", 2147483647, "something", 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%lg\n%ld\n%x\n", 2147483647, 1.79769313486e+308, 9223372036854775807, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%o\n%lf\n%f\n", 'w', 2147483647, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%lg\n%ld\n%g\n", -2147483649, 2.22507385851e-308, -9223372036854775809, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%g\n%o\n%x\n", 1.79769313486e+308, 1.79769313486e+308, -2147483649, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%le\n%f\n%le\n", 1.79769313486e+308, 1.79769313486e+308, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%f\n%x\n%lf\n", 4294967296, 1.79769313486e+308, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%f\n%u\n%c\n", -9223372036854775809, 2.22507385851e-308, 4294967296, 'M');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%d\n%e\n%lu\n", 18446744073709551616, -2147483649, 1.79769313486e+308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%lg\n%x\n%lg\n", 2147483647, 2.22507385851e-308, -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%e\n%x\n%x\n", -2147483649, 1.79769313486e+308, 2147483647, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%e\n%x\n%u\n", 1.79769313486e+308, 2.22507385851e-308, -2147483649, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%s\n%c\n%lg\n", -2147483649, "and", 'i', 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%x\n%x\n%lg\n", 2147483647, 2147483647, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%d\n%x\n%g\n", 2.22507385851e-308, -2147483649, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%d\n%g\n%lg\n", 1.79769313486e+308, -2147483649, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%c\n%lu\n%u\n", 4294967296, '^', 0, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%d\n%g\n%f\n", 'n', -2147483649, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%c\n%s\n%d\n", 2147483647, 'y', "something", 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%s\n%ld\n%s\n", 1.79769313486e+308, "different", 9223372036854775807, "now");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%x\n%lg\n%s\n", 1.79769313486e+308, -2147483649, 2.22507385851e-308, "different");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%lg\n%x\n%s\n", -9223372036854775809, 2.22507385851e-308, -2147483649, "completely");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%e\n%e\n%f\n", -2147483649, 2.22507385851e-308, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%lf\n%f\n%u\n", 18446744073709551616, 2.22507385851e-308, 1.79769313486e+308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%x\n%x\n%s\n", 2147483647, 2147483647, 2147483647, "and");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%d\n%o\n%d\n", 2.22507385851e-308, -2147483649, -2147483649, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%ld\n%lf\n%x\n", 0, 9223372036854775807, 1.79769313486e+308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%o\n%ld\n%c\n", 1.79769313486e+308, 2147483647, -9223372036854775809, '(');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%lf\n%ld\n%lf\n", 2147483647, 1.79769313486e+308, -9223372036854775809, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%lg\n%x\n%g\n", 4294967296, 2.22507385851e-308, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%u\n%lg\n%lu\n", 0, 4294967296, 2.22507385851e-308, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%g\n%d\n%c\n", -2147483649, 2.22507385851e-308, 2147483647, ',');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%d\n%s\n%g\n", "different", 2147483647, "completely", 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%lu\n%u\n%ld\n", 2.22507385851e-308, 18446744073709551616, 0, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%lg\n%c\n%o\n", 1.79769313486e+308, 2.22507385851e-308, 'i', 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%lf\n%s\n%g\n", 0, 2.22507385851e-308, "different", 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%lu\n%o\n%ld\n", -9223372036854775809, 18446744073709551616, 2147483647, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%o\n%c\n%d\n", -2147483649, 2147483647, ';', 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%g\n%s\n%o\n", 2.22507385851e-308, 1.79769313486e+308, "completely", 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%u\n%d\n%ld\n", 'J', 4294967296, 2147483647, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%u\n%x\n%u\n", 2147483647, 4294967296, 2147483647, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%e\n%o\n%le\n", -9223372036854775809, 1.79769313486e+308, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%ld\n%f\n%c\n", 1.79769313486e+308, -9223372036854775809, 1.79769313486e+308, 'L');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%c\n%s\n%ld\n", 0, 'Z', "and", -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%lu\n%lg\n%d\n", 1.79769313486e+308, 18446744073709551616, 1.79769313486e+308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%d\n%c\n%g\n", 1.79769313486e+308, 2147483647, '+', 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%o\n%c\n%s\n", 2.22507385851e-308, 2147483647, 't', "for");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%o\n%x\n%f\n", 1.79769313486e+308, -2147483649, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%s\n%lf\n%g\n", 9223372036854775807, "and", 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%lu\n%lf\n%f\n", -9223372036854775809, 18446744073709551616, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%lf\n%lf\n%c\n", 2.22507385851e-308, 1.79769313486e+308, 1.79769313486e+308, '4');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%x\n%lf\n%o\n", 2.22507385851e-308, 2147483647, 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%lg\n%le\n%d\n", 2.22507385851e-308, 2.22507385851e-308, 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%ld\n%s\n%s\n", 2.22507385851e-308, -9223372036854775809, "for", "completely");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%ld\n%c\n%u\n", '@', 9223372036854775807, 'I', 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%lg\n%c\n%lg\n", "and", 2.22507385851e-308, 'u', 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%lf\n%u\n%lf\n", -2147483649, 1.79769313486e+308, 4294967296, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%ld\n%o\n%f\n", -2147483649, -9223372036854775809, 2147483647, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%ld\n%g\n%f\n", 2.22507385851e-308, 9223372036854775807, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%o\n%f\n%s\n", 18446744073709551616, -2147483649, 1.79769313486e+308, "something");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%d\n%f\n%d\n", "completely", 2147483647, 1.79769313486e+308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%ld\n%e\n%le\n", 2.22507385851e-308, 9223372036854775807, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%u\n%lu\n%f\n", ']', 0, 18446744073709551616, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%d\n%ld\n%lu\n", -2147483649, 2147483647, 9223372036854775807, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%d\n%f\n%le\n", 2.22507385851e-308, 2147483647, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%lu\n%lg\n%ld\n", "and", 18446744073709551616, 1.79769313486e+308, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%s\n%c\n%le\n", 2.22507385851e-308, "different", '1', 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%c\n%x\n%g\n", '9', 'q', 2147483647, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%u\n%lg\n%o\n", 2.22507385851e-308, 0, 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%le\n%u\n%x\n", 1.79769313486e+308, 2.22507385851e-308, 0, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%c\n%s\n%s\n", 2.22507385851e-308, '.', "and", "for");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%x\n%x\n%le\n", 1.79769313486e+308, -2147483649, 2147483647, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%d\n%f\n%u\n", 2.22507385851e-308, -2147483649, 1.79769313486e+308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%ld\n%s\n%lu\n", 'N', 9223372036854775807, "for", 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%lu\n%f\n%u\n", 2.22507385851e-308, 18446744073709551616, 2.22507385851e-308, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%c\n%s\n%lg\n", "and", 'O', "now", 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%lg\n%o\n%x\n", 1.79769313486e+308, 1.79769313486e+308, -2147483649, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%e\n%lg\n%le\n", 0, 1.79769313486e+308, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%lg\n%c\n%e\n", 18446744073709551616, 1.79769313486e+308, '}', 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%lf\n%ld\n%lg\n", 2147483647, 1.79769313486e+308, -9223372036854775809, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%c\n%s\n%u\n", 2.22507385851e-308, '1', "completely", 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%x\n%s\n%g\n", 2.22507385851e-308, -2147483649, "different", 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%d\n%le\n%f\n", 2147483647, -2147483649, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%o\n%g\n%f\n", -2147483649, 2147483647, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%lf\n%e\n%u\n", 2147483647, 1.79769313486e+308, 1.79769313486e+308, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%lg\n%ld\n%e\n", 0, 1.79769313486e+308, -9223372036854775809, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%le\n%d\n%ld\n", 0, 1.79769313486e+308, 2147483647, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%x\n%f\n%c\n", 1.79769313486e+308, -2147483649, 2.22507385851e-308, '{');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%ld\n%o\n%e\n", 'i', -9223372036854775809, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lg\n%f\n%e\n", ' ', 1.79769313486e+308, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%lf\n%u\n%f\n", 18446744073709551616, 2.22507385851e-308, 0, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%g\n%s\n%u\n", "now", 2.22507385851e-308, "and", 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%x\n%s\n%ld\n", 1.79769313486e+308, -2147483649, "something", 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%e\n%s\n%s\n", 2.22507385851e-308, 2.22507385851e-308, "and", "completely");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%f\n%x\n%e\n", 1.79769313486e+308, 2.22507385851e-308, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%f\n%lf\n%lu\n", 1.79769313486e+308, 1.79769313486e+308, 2.22507385851e-308, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%c\n%c\n%lf\n", 2.22507385851e-308, '&', '[', 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%u\n%lg\n%g\n", 1.79769313486e+308, 4294967296, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%ld\n%o\n%e\n", 2.22507385851e-308, 9223372036854775807, -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%f\n%lf\n%le\n", 1.79769313486e+308, 2.22507385851e-308, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%lf\n%e\n%s\n", 1.79769313486e+308, 1.79769313486e+308, 1.79769313486e+308, "now");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%o\n%d\n%lu\n", -9223372036854775809, 2147483647, -2147483649, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%lg\n%d\n%d\n", 4294967296, 2.22507385851e-308, 2147483647, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%ld\n%e\n%g\n", 1.79769313486e+308, 9223372036854775807, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%o\n%s\n%lg\n", 2147483647, 2147483647, "now", 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%x\n%e\n%c\n", 4294967296, -2147483649, 2.22507385851e-308, '\\');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%g\n%d\n%f\n", 1.79769313486e+308, 2.22507385851e-308, 2147483647, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%u\n%f\n%o\n", 2.22507385851e-308, 0, 2.22507385851e-308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%x\n%e\n%lg\n", 2.22507385851e-308, -2147483649, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%s\n%o\n%c\n", 0, "for", -2147483649, '*');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%lf\n%e\n%le\n", 2.22507385851e-308, 1.79769313486e+308, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%f\n%lg\n%o\n", 4294967296, 1.79769313486e+308, 1.79769313486e+308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%lu\n%c\n%x\n", 2.22507385851e-308, 18446744073709551616, 'f', -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%lu\n%s\n%o\n", 4294967296, 0, "something", 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%lu\n%s\n%x\n", 2.22507385851e-308, 18446744073709551616, "now", 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%e\n%le\n%c\n", 2.22507385851e-308, 2.22507385851e-308, 1.79769313486e+308, '[');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%lu\n%ld\n%lf\n", 2147483647, 0, 9223372036854775807, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%lf\n%d\n%o\n", "for", 1.79769313486e+308, 2147483647, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%ld\n%c\n%le\n", "for", -9223372036854775809, '=', 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%f\n%x\n%le\n", 2.22507385851e-308, 2.22507385851e-308, -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%d\n%c\n%f\n", 2.22507385851e-308, -2147483649, 'v', 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%e\n%lg\n%o\n", 2147483647, 2.22507385851e-308, 2.22507385851e-308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%le\n%g\n%x\n", '%', 2.22507385851e-308, 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%o\n%u\n%f\n", 2147483647, 2147483647, 0, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%e\n%ld\n%o\n", 0, 1.79769313486e+308, 9223372036854775807, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%lu\n%f\n%f\n", 2.22507385851e-308, 18446744073709551616, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%d\n%le\n%u\n", 2.22507385851e-308, 2147483647, 2.22507385851e-308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%s\n%ld\n%lf\n", 1.79769313486e+308, "and", 9223372036854775807, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%s\n%f\n%c\n", 2147483647, "something", 2.22507385851e-308, '#');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%lg\n%g\n%ld\n", -9223372036854775809, 2.22507385851e-308, 1.79769313486e+308, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%lf\n%g\n%u\n", 2.22507385851e-308, 1.79769313486e+308, 2.22507385851e-308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%lu\n%g\n%e\n", 2.22507385851e-308, 18446744073709551616, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%lu\n%c\n%d\n", -2147483649, 0, 'W', 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%g\n%c\n%lg\n", 0, 1.79769313486e+308, 'M', 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%lu\n%g\n%x\n", 2147483647, 0, 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%x\n%o\n%lu\n", 0, -2147483649, -2147483649, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%ld\n%s\n%s\n", -2147483649, 9223372036854775807, "something", "completely");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%u\n%g\n%e\n", 4294967296, 4294967296, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%lg\n%u\n%lf\n", 2.22507385851e-308, 2.22507385851e-308, 4294967296, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%g\n%lu\n%d\n", 2.22507385851e-308, 1.79769313486e+308, 18446744073709551616, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%le\n%x\n%d\n", 2.22507385851e-308, 2.22507385851e-308, -2147483649, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%lf\n%o\n%o\n", 2147483647, 2.22507385851e-308, 2147483647, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%s\n%x\n%u\n", 1.79769313486e+308, "different", -2147483649, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%d\n%x\n%lg\n", 1.79769313486e+308, -2147483649, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%ld\n%lu\n%o\n", 2147483647, 9223372036854775807, 18446744073709551616, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%e\n%lf\n%le\n", 9223372036854775807, 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%s\n%f\n%lf\n", 1.79769313486e+308, "and", 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%lf\n%x\n%e\n", -2147483649, 1.79769313486e+308, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%c\n%le\n%u\n", 2.22507385851e-308, '3', 2.22507385851e-308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%d\n%o\n%lf\n", 1.79769313486e+308, -2147483649, -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%x\n%x\n%ld\n", "and", -2147483649, 2147483647, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%x\n%o\n%le\n", 0, 2147483647, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%c\n%e\n%lf\n", -2147483649, 't', 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%lg\n%lf\n%u\n", 2.22507385851e-308, 1.79769313486e+308, 2.22507385851e-308, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%lg\n%d\n%lf\n", -9223372036854775809, 1.79769313486e+308, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%s\n%o\n%x\n", 'u', "now", 2147483647, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%s\n%le\n%lu\n", 4294967296, "now", 1.79769313486e+308, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%ld\n%ld\n%ld\n", 2.22507385851e-308, -9223372036854775809, 9223372036854775807, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%ld\n%lf\n%d\n", 2.22507385851e-308, -9223372036854775809, 1.79769313486e+308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%d\n%e\n%d\n", 2.22507385851e-308, 2147483647, 1.79769313486e+308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%o\n%o\n%s\n", 2147483647, -2147483649, -2147483649, "and");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%lf\n%s\n%e\n", 2147483647, 1.79769313486e+308, "completely", 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%s\n%o\n%ld\n", 9223372036854775807, "different", -2147483649, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lu\n%s\n%le\n", '<', 0, "something", 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%lf\n%x\n%d\n", 2.22507385851e-308, 1.79769313486e+308, -2147483649, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%g\n%s\n%x\n", 2147483647, 1.79769313486e+308, "now", 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%le\n%f\n%c\n", 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308, 'd');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%x\n%e\n%le\n", 1.79769313486e+308, -2147483649, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%o\n%d\n%o\n", 2.22507385851e-308, -2147483649, 2147483647, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%c\n%u\n%e\n", 1.79769313486e+308, 'n', 0, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%x\n%d\n%c\n", 2147483647, -2147483649, -2147483649, 'k');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%u\n%x\n%f\n", "different", 4294967296, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%le\n%lg\n%d\n", 2.22507385851e-308, 2.22507385851e-308, 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lu\n%g\n%ld\n", '<', 18446744073709551616, 2.22507385851e-308, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%x\n%u\n%s\n", -2147483649, 2147483647, 4294967296, "for");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%f\n%u\n%le\n", 1.79769313486e+308, 2.22507385851e-308, 4294967296, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%lg\n%x\n%le\n", 1.79769313486e+308, 1.79769313486e+308, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%s\n%s\n%e\n", 1.79769313486e+308, "something", "and", 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%o\n%ld\n%ld\n", 1.79769313486e+308, -2147483649, 9223372036854775807, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%c\n%f\n%lf\n", 4294967296, 'k', 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%o\n%lf\n%lg\n", -2147483649, 2147483647, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%f\n%x\n%g\n", 1.79769313486e+308, 2.22507385851e-308, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%ld\n%s\n%d\n", 2.22507385851e-308, 9223372036854775807, "something", 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%o\n%lu\n%ld\n", 2.22507385851e-308, 2147483647, 0, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%x\n%le\n%d\n", "different", 2147483647, 1.79769313486e+308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%x\n%d\n%u\n", 1.79769313486e+308, -2147483649, 2147483647, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%le\n%f\n%lf\n", '3', 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%e\n%lg\n%f\n", 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%c\n%o\n%lg\n", -2147483649, '0', -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%g\n%ld\n%g\n", 2.22507385851e-308, 1.79769313486e+308, -9223372036854775809, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%s\n%c\n%e\n", 2.22507385851e-308, "completely", '+', 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%x\n%x\n%e\n", -2147483649, 2147483647, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%f\n%u\n%lg\n", 1.79769313486e+308, 1.79769313486e+308, 4294967296, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%u\n%le\n%lg\n", -2147483649, 0, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%lg\n%lg\n%le\n", 18446744073709551616, 2.22507385851e-308, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%u\n%g\n%e\n", 1.79769313486e+308, 4294967296, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%g\n%ld\n%e\n", 1.79769313486e+308, 2.22507385851e-308, 9223372036854775807, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%le\n%s\n%e\n", 4294967296, 1.79769313486e+308, "completely", 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%s\n%d\n%x\n", -9223372036854775809, "for", -2147483649, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%s\n%lf\n%x\n", '8', "and", 1.79769313486e+308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%x\n%g\n%le\n", 1.79769313486e+308, 2147483647, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%e\n%f\n%f\n", "now", 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%f\n%f\n%x\n", 0, 2.22507385851e-308, 1.79769313486e+308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%f\n%lu\n%d\n", 2147483647, 1.79769313486e+308, 0, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%c\n%x\n%lg\n", 1.79769313486e+308, 'I', 2147483647, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%o\n%u\n%x\n", 1.79769313486e+308, 2147483647, 4294967296, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%lf\n%s\n%e\n", 1.79769313486e+308, 2.22507385851e-308, "now", 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%f\n%le\n%o\n", 2147483647, 2.22507385851e-308, 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%x\n%g\n%u\n", 1.79769313486e+308, -2147483649, 2.22507385851e-308, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%d\n%g\n%f\n", -9223372036854775809, 2147483647, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%lg\n%u\n%ld\n", -2147483649, 1.79769313486e+308, 4294967296, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%c\n%c\n%lu\n", 0, 'K', ',', 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%c\n%c\n%g\n", 2147483647, '}', 'T', 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%lg\n%g\n%d\n", "completely", 2.22507385851e-308, 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%le\n%x\n%lg\n", 1.79769313486e+308, 2.22507385851e-308, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%g\n%le\n%o\n", -9223372036854775809, 1.79769313486e+308, 2.22507385851e-308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%c\n%le\n%c\n", -2147483649, 'F', 1.79769313486e+308, 'T');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%lu\n%ld\n%d\n", 18446744073709551616, 0, 9223372036854775807, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%g\n%f\n%lf\n", "something", 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%d\n%f\n%e\n", 2147483647, -2147483649, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%d\n%lf\n%lf\n", 2.22507385851e-308, -2147483649, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%d\n%u\n%d\n", 0, 2147483647, 4294967296, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%x\n%f\n%f\n", 2147483647, -2147483649, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%e\n%le\n%g\n", 0, 2.22507385851e-308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%f\n%le\n%f\n", 1.79769313486e+308, 2.22507385851e-308, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%c\n%le\n%x\n", 1.79769313486e+308, 'K', 1.79769313486e+308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%f\n%s\n%u\n", "completely", 1.79769313486e+308, "different", 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%c\n%e\n%le\n", 2.22507385851e-308, '#', 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%s\n%f\n%g\n", 0, "and", 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%d\n%c\n%o\n", 1.79769313486e+308, 2147483647, '=', 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%lg\n%lu\n%x\n", 18446744073709551616, 1.79769313486e+308, 0, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%g\n%u\n%f\n", -9223372036854775809, 2.22507385851e-308, 4294967296, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%u\n%o\n%ld\n", '6', 4294967296, 2147483647, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%d\n%ld\n%c\n", 1.79769313486e+308, -2147483649, -9223372036854775809, ' ');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%g\n%d\n%lg\n", ']', 2.22507385851e-308, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%s\n%e\n%e\n", 1.79769313486e+308, "something", 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%o\n%lg\n%ld\n", 1.79769313486e+308, 2147483647, 2.22507385851e-308, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%f\n%s\n%c\n", 1.79769313486e+308, 2.22507385851e-308, "now", 'E');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%le\n%s\n%f\n", -2147483649, 1.79769313486e+308, "different", 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lu\n%o\n%lf\n", 'D', 18446744073709551616, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lg\n%d\n%d\n", '|', 1.79769313486e+308, -2147483649, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lu\n%d\n%lf\n", 'x', 18446744073709551616, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%ld\n%lg\n%lg\n", 2147483647, 9223372036854775807, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%u\n%le\n%s\n", 1.79769313486e+308, 4294967296, 1.79769313486e+308, "completely");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%f\n%s\n%u\n", 2.22507385851e-308, 2.22507385851e-308, "for", 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%x\n%u\n%f\n", 1.79769313486e+308, -2147483649, 0, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%le\n%lu\n%o\n", -9223372036854775809, 1.79769313486e+308, 18446744073709551616, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%c\n%d\n%lu\n", -2147483649, '+', -2147483649, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%s\n%lu\n%c\n", 2.22507385851e-308, "now", 18446744073709551616, '!');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%lg\n%u\n%e\n", 1.79769313486e+308, 1.79769313486e+308, 0, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%le\n%le\n%lf\n", 2.22507385851e-308, 2.22507385851e-308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%f\n%lf\n%lg\n", "for", 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lu\n%lf\n%lu\n", '7', 18446744073709551616, 1.79769313486e+308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%lu\n%d\n%f\n", 2.22507385851e-308, 0, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%f\n%u\n%g\n", 2147483647, 1.79769313486e+308, 4294967296, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%c\n%x\n%ld\n", -9223372036854775809, 'm', 2147483647, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%c\n%e\n%d\n", 1.79769313486e+308, 'm', 1.79769313486e+308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%lf\n%e\n%d\n", -2147483649, 2.22507385851e-308, 1.79769313486e+308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%e\n%f\n%ld\n", 'f', 1.79769313486e+308, 1.79769313486e+308, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%f\n%lf\n%u\n", "something", 2.22507385851e-308, 2.22507385851e-308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%ld\n%f\n%g\n", 1.79769313486e+308, 9223372036854775807, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%lf\n%s\n%lu\n", -2147483649, 2.22507385851e-308, "something", 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%d\n%x\n%ld\n", 1.79769313486e+308, -2147483649, 2147483647, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%le\n%g\n%lg\n", -2147483649, 2.22507385851e-308, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%u\n%d\n%s\n", 1.79769313486e+308, 4294967296, 2147483647, "different");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%g\n%ld\n%o\n", 1.79769313486e+308, 1.79769313486e+308, -9223372036854775809, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%s\n%lu\n%s\n", 1.79769313486e+308, "different", 0, "for");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%f\n%ld\n%s\n", 2.22507385851e-308, 2.22507385851e-308, 9223372036854775807, "different");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%lg\n%f\n%g\n", 1.79769313486e+308, 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%d\n%lu\n%u\n", '!', 2147483647, 18446744073709551616, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%lg\n%c\n%f\n", 1.79769313486e+308, 1.79769313486e+308, 'N', 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%s\n%f\n%le\n", 1.79769313486e+308, "something", 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%x\n%g\n%c\n", -2147483649, -2147483649, 1.79769313486e+308, '>');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%lf\n%c\n%lg\n", "completely", 2.22507385851e-308, 'O', 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%lg\n%x\n%o\n", 9223372036854775807, 2.22507385851e-308, 2147483647, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%lf\n%ld\n%e\n", -2147483649, 1.79769313486e+308, 9223372036854775807, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%s\n%u\n%g\n", 'Q', "now", 4294967296, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%ld\n%lf\n%u\n", 'M', -9223372036854775809, 1.79769313486e+308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%d\n%x\n%s\n", -2147483649, 2147483647, -2147483649, "for");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%s\n%d\n%c\n", 2.22507385851e-308, "now", 2147483647, '>');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%o\n%le\n%u\n", 2.22507385851e-308, 2147483647, 1.79769313486e+308, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%f\n%c\n%e\n", 9223372036854775807, 1.79769313486e+308, '!', 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%c\n%ld\n%d\n", 2.22507385851e-308, 'K', 9223372036854775807, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%lg\n%s\n%s\n", 2147483647, 2.22507385851e-308, "and", "for");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%lu\n%o\n%lf\n", -2147483649, 0, -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%lu\n%lu\n%lg\n", 2.22507385851e-308, 0, 18446744073709551616, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%s\n%lg\n%ld\n", 2.22507385851e-308, "now", 1.79769313486e+308, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%ld\n%o\n%ld\n", 1.79769313486e+308, 9223372036854775807, -2147483649, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%g\n%c\n%lf\n", "different", 2.22507385851e-308, 'B', 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%ld\n%lu\n%g\n", 0, -9223372036854775809, 18446744073709551616, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%s\n%lg\n%le\n", 2.22507385851e-308, "and", 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%d\n%lf\n%ld\n", 1.79769313486e+308, -2147483649, 1.79769313486e+308, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%le\n%le\n%x\n", 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%le\n%f\n%o\n", -9223372036854775809, 1.79769313486e+308, 2.22507385851e-308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%u\n%c\n%u\n", -9223372036854775809, 0, '{', 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%c\n%lg\n%f\n", 2.22507385851e-308, '}', 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%lu\n%d\n%d\n", 2147483647, 0, -2147483649, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%le\n%o\n%e\n", 18446744073709551616, 1.79769313486e+308, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%e\n%c\n%s\n", 1.79769313486e+308, 1.79769313486e+308, '}', "now");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%g\n%ld\n%e\n", 9223372036854775807, 2.22507385851e-308, 9223372036854775807, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%le\n%f\n%d\n", 1.79769313486e+308, 1.79769313486e+308, 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%d\n%o\n%x\n", 'b', 2147483647, -2147483649, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%x\n%e\n%e\n", 1.79769313486e+308, 2147483647, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%s\n%c\n%c\n", 'k', "completely", 'm', ']');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%le\n%lu\n%x\n", 1.79769313486e+308, 1.79769313486e+308, 18446744073709551616, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%g\n%o\n%lf\n", 1.79769313486e+308, 1.79769313486e+308, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%f\n%x\n%lu\n", 2147483647, 2.22507385851e-308, -2147483649, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%e\n%ld\n%x\n", 1.79769313486e+308, 1.79769313486e+308, 9223372036854775807, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%lg\n%x\n%d\n", 1.79769313486e+308, 2.22507385851e-308, -2147483649, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%o\n%e\n%c\n", "and", -2147483649, 1.79769313486e+308, '\'');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%c\n%d\n%f\n", 1.79769313486e+308, 'L', -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%u\n%x\n%f\n", 9223372036854775807, 0, 2147483647, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%d\n%s\n%e\n", -2147483649, 2147483647, "completely", 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%ld\n%lf\n%le\n", -9223372036854775809, 9223372036854775807, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%s\n%g\n%o\n", 2.22507385851e-308, "and", 1.79769313486e+308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%g\n%o\n%s\n", "for", 2.22507385851e-308, -2147483649, "and");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%g\n%s\n%c\n", -9223372036854775809, 2.22507385851e-308, "for", '1');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%s\n%le\n%c\n", 2.22507385851e-308, "now", 1.79769313486e+308, '[');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%le\n%lg\n%e\n", '\"', 2.22507385851e-308, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%lu\n%d\n%le\n", 9223372036854775807, 18446744073709551616, 2147483647, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%s\n%lf\n%d\n", 2.22507385851e-308, "different", 1.79769313486e+308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%c\n%u\n%ld\n", 2147483647, 'K', 0, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%d\n%s\n%o\n", 2.22507385851e-308, -2147483649, "for", -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%d\n%s\n%x\n", 18446744073709551616, -2147483649, "something", -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%c\n%x\n%e\n", -2147483649, 'L', -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%s\n%x\n%g\n", 0, "now", -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%x\n%f\n%d\n", 2.22507385851e-308, 2147483647, 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%lu\n%e\n%lu\n", 1.79769313486e+308, 18446744073709551616, 2.22507385851e-308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%lg\n%x\n%ld\n", 2.22507385851e-308, 2.22507385851e-308, 2147483647, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%s\n%x\n%lu\n", 0, "and", -2147483649, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%ld\n%x\n%u\n", 1.79769313486e+308, -9223372036854775809, -2147483649, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%d\n%c\n%c\n", "something", -2147483649, 'H', 'w');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%le\n%x\n%f\n", 18446744073709551616, 2.22507385851e-308, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%lf\n%x\n%e\n", -2147483649, 2.22507385851e-308, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%o\n%o\n%lf\n", 2147483647, 2147483647, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%g\n%o\n%g\n", 2.22507385851e-308, 1.79769313486e+308, 2147483647, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%lu\n%ld\n%d\n", 1.79769313486e+308, 0, 9223372036854775807, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%lg\n%f\n%lf\n", 2.22507385851e-308, 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%d\n%o\n%lg\n", 1.79769313486e+308, -2147483649, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%f\n%s\n%ld\n", 1.79769313486e+308, 2.22507385851e-308, "something", -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%f\n%lg\n%e\n", 2.22507385851e-308, 1.79769313486e+308, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%lf\n%lf\n%x\n", -2147483649, 1.79769313486e+308, 1.79769313486e+308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%f\n%lu\n%e\n", 0, 1.79769313486e+308, 18446744073709551616, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%le\n%c\n%lu\n", 9223372036854775807, 1.79769313486e+308, '{', 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%lf\n%x\n%f\n", 2.22507385851e-308, 1.79769313486e+308, -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%c\n%lu\n%g\n", 2.22507385851e-308, '8', 18446744073709551616, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%g\n%f\n%le\n", 2147483647, 2.22507385851e-308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%g\n%e\n%e\n", 2.22507385851e-308, 1.79769313486e+308, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%x\n%ld\n%d\n", 2.22507385851e-308, -2147483649, 9223372036854775807, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%lg\n%x\n%o\n", "something", 2.22507385851e-308, 2147483647, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%g\n%ld\n%s\n", "for", 2.22507385851e-308, -9223372036854775809, "for");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%o\n%d\n%g\n", 1.79769313486e+308, -2147483649, -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%ld\n%lg\n%s\n", 2147483647, 9223372036854775807, 2.22507385851e-308, "and");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%ld\n%s\n%f\n", 2147483647, -9223372036854775809, "different", 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lf\n%lg\n%lf\n", 'z', 1.79769313486e+308, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%x\n%lg\n%f\n", '|', -2147483649, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%f\n%le\n%lg\n", "different", 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%lf\n%le\n%lg\n", 2.22507385851e-308, 2.22507385851e-308, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%lf\n%g\n%ld\n", 2.22507385851e-308, 1.79769313486e+308, 2.22507385851e-308, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%le\n%d\n%s\n", -9223372036854775809, 2.22507385851e-308, -2147483649, "for");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%ld\n%ld\n%lg\n", 2.22507385851e-308, 9223372036854775807, 9223372036854775807, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%x\n%c\n%le\n", 2.22507385851e-308, 2147483647, '1', 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%d\n%ld\n%s\n", 2.22507385851e-308, -2147483649, -9223372036854775809, "for");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lg\n%s\n%lg\n", '}', 1.79769313486e+308, "and", 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%f\n%lu\n%lu\n", 1.79769313486e+308, 2.22507385851e-308, 18446744073709551616, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%le\n%le\n%e\n", -2147483649, 2.22507385851e-308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%c\n%f\n%le\n", 1.79769313486e+308, '@', 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%s\n%lg\n%lf\n", 1.79769313486e+308, "now", 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%f\n%lu\n%o\n", 1.79769313486e+308, 1.79769313486e+308, 0, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%x\n%s\n%u\n", 2147483647, 2147483647, "completely", 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%x\n%le\n%e\n", -9223372036854775809, -2147483649, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%d\n%c\n%d\n", 2.22507385851e-308, 2147483647, 'K', 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%u\n%lg\n%d\n", 4294967296, 0, 1.79769313486e+308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%s\n%e\n%lu\n", -2147483649, "completely", 1.79769313486e+308, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%e\n%u\n%le\n", 2.22507385851e-308, 2.22507385851e-308, 4294967296, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%lg\n%lu\n%u\n", -2147483649, 1.79769313486e+308, 0, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%lu\n%f\n%e\n", 1.79769313486e+308, 0, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%o\n%ld\n%f\n", 2.22507385851e-308, -2147483649, -9223372036854775809, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%c\n%lf\n%le\n", 2.22507385851e-308, 'B', 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%o\n%d\n%le\n", -2147483649, -2147483649, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%e\n%le\n%le\n", 1.79769313486e+308, 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%lg\n%lg\n%lu\n", 2.22507385851e-308, 2.22507385851e-308, 1.79769313486e+308, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%o\n%le\n%lg\n", 1.79769313486e+308, 2147483647, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lf\n%lu\n%f\n", 'h', 2.22507385851e-308, 0, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%le\n%s\n%lg\n", "something", 2.22507385851e-308, "for", 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%ld\n%u\n%x\n", 2.22507385851e-308, -9223372036854775809, 0, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%ld\n%e\n%f\n", 18446744073709551616, -9223372036854775809, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%lg\n%f\n%lu\n", "for", 1.79769313486e+308, 1.79769313486e+308, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%le\n%x\n%o\n", 1.79769313486e+308, 2.22507385851e-308, 2147483647, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%lf\n%f\n%o\n", 2.22507385851e-308, 1.79769313486e+308, 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%c\n%lg\n%f\n", -2147483649, '0', 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%s\n%e\n%u\n", 2147483647, "different", 1.79769313486e+308, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%s\n%lu\n%s\n", 18446744073709551616, "completely", 18446744073709551616, "different");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%lg\n%le\n%lg\n", 2147483647, 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%lf\n%e\n%f\n", 1.79769313486e+308, 1.79769313486e+308, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%ld\n%lu\n%e\n", 1.79769313486e+308, -9223372036854775809, 0, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%le\n%s\n%c\n", 1.79769313486e+308, 1.79769313486e+308, "and", '}');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%x\n%g\n%g\n", 1.79769313486e+308, 2147483647, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%d\n%le\n%x\n", 2.22507385851e-308, -2147483649, 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%d\n%g\n%f\n", 1.79769313486e+308, 2147483647, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%f\n%g\n%c\n", 2147483647, 1.79769313486e+308, 1.79769313486e+308, '_');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%u\n%u\n%le\n", 1.79769313486e+308, 0, 0, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%d\n%lf\n%c\n", 2147483647, 2147483647, 1.79769313486e+308, 'Z');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%f\n%lf\n%lu\n", 2.22507385851e-308, 1.79769313486e+308, 1.79769313486e+308, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%le\n%c\n%le\n", 2.22507385851e-308, 1.79769313486e+308, 'a', 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%le\n%lg\n%u\n", '5', 1.79769313486e+308, 1.79769313486e+308, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%g\n%d\n%f\n", 2.22507385851e-308, 1.79769313486e+308, -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%e\n%u\n%lg\n", 2.22507385851e-308, 1.79769313486e+308, 4294967296, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%o\n%d\n%lf\n", 4294967296, -2147483649, 2147483647, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%lg\n%o\n%d\n", 2147483647, 1.79769313486e+308, 2147483647, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%c\n%e\n%lu\n", 2.22507385851e-308, '\"', 1.79769313486e+308, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%lu\n%lu\n%e\n", 2.22507385851e-308, 18446744073709551616, 18446744073709551616, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%c\n%le\n%u\n", 0, '4', 1.79769313486e+308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%c\n%s\n%le\n", 1.79769313486e+308, ')', "and", 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%f\n%o\n%lf\n", 1.79769313486e+308, 1.79769313486e+308, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%lg\n%u\n%lu\n", 2.22507385851e-308, 1.79769313486e+308, 4294967296, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%lf\n%o\n%e\n", 2.22507385851e-308, 1.79769313486e+308, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%lu\n%u\n%x\n", 1.79769313486e+308, 0, 4294967296, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%g\n%ld\n%lf\n", 0, 1.79769313486e+308, -9223372036854775809, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%e\n%e\n%le\n", 0, 1.79769313486e+308, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%o\n%u\n%s\n", 1.79769313486e+308, -2147483649, 0, "different");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%f\n%s\n%lu\n", 'D', 1.79769313486e+308, "different", 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%lg\n%lu\n%u\n", 2147483647, 1.79769313486e+308, 18446744073709551616, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%c\n%u\n%d\n", -2147483649, 'i', 0, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%u\n%c\n%le\n", 2.22507385851e-308, 4294967296, '}', 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%c\n%c\n%lf\n", 1.79769313486e+308, 'h', 'L', 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%f\n%le\n%u\n", -2147483649, 1.79769313486e+308, 2.22507385851e-308, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lf\n%u\n%g\n", 'b', 1.79769313486e+308, 4294967296, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%c\n%f\n%f\n", 9223372036854775807, '?', 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%lf\n%x\n%lf\n", -9223372036854775809, 1.79769313486e+308, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%lf\n%lg\n%lu\n", 2147483647, 1.79769313486e+308, 2.22507385851e-308, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%g\n%s\n%o\n", 2147483647, 1.79769313486e+308, "now", 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%g\n%lf\n%d\n", 4294967296, 1.79769313486e+308, 2.22507385851e-308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%ld\n%le\n%g\n", 1.79769313486e+308, -9223372036854775809, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%lg\n%lf\n%o\n", 2.22507385851e-308, 1.79769313486e+308, 1.79769313486e+308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%f\n%o\n%c\n", 1.79769313486e+308, 1.79769313486e+308, 2147483647, 'V');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%o\n%x\n%lu\n", 18446744073709551616, 2147483647, 2147483647, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%u\n%lu\n%ld\n", 1.79769313486e+308, 4294967296, 18446744073709551616, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%d\n%e\n%d\n", '*', 2147483647, 1.79769313486e+308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%e\n%x\n%le\n", 0, 2.22507385851e-308, -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%s\n%f\n%d\n", 2147483647, "now", 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%g\n%lg\n%o\n", 4294967296, 1.79769313486e+308, 1.79769313486e+308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%ld\n%o\n%g\n", 'q', -9223372036854775809, -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%g\n%le\n%lf\n", 2.22507385851e-308, 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%f\n%c\n%c\n", 1.79769313486e+308, 2.22507385851e-308, '>', 's');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%s\n%c\n%x\n", 2.22507385851e-308, "something", '-', 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%le\n%lg\n%le\n", -2147483649, 1.79769313486e+308, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%d\n%s\n%s\n", 4294967296, 2147483647, "and", "something");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%s\n%lf\n%f\n", 1.79769313486e+308, "different", 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%ld\n%lf\n%x\n", 2.22507385851e-308, -9223372036854775809, 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%lg\n%le\n%d\n", 2147483647, 1.79769313486e+308, 1.79769313486e+308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%le\n%x\n%f\n", '\'', 2.22507385851e-308, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%lg\n%ld\n%d\n", 2147483647, 1.79769313486e+308, 9223372036854775807, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%x\n%lg\n%le\n", 1.79769313486e+308, 2147483647, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%lf\n%o\n%e\n", 18446744073709551616, 2.22507385851e-308, -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%le\n%ld\n%lg\n", 0, 1.79769313486e+308, 9223372036854775807, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%o\n%c\n%lu\n", 9223372036854775807, -2147483649, '}', 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%x\n%c\n%g\n", 1.79769313486e+308, -2147483649, 'Z', 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%ld\n%ld\n%le\n", 1.79769313486e+308, 9223372036854775807, -9223372036854775809, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%f\n%g\n%lg\n", 0, 2.22507385851e-308, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%o\n%ld\n%ld\n", 1.79769313486e+308, 2147483647, -9223372036854775809, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%lf\n%lu\n%d\n", 2.22507385851e-308, 2.22507385851e-308, 0, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%e\n%ld\n%s\n", '*', 2.22507385851e-308, -9223372036854775809, "for");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%lf\n%u\n%le\n", 1.79769313486e+308, 2.22507385851e-308, 0, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%c\n%e\n%le\n", -2147483649, 'L', 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%f\n%o\n%s\n", 2.22507385851e-308, 1.79769313486e+308, 2147483647, "completely");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%c\n%lu\n%lf\n", 1.79769313486e+308, ';', 0, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%g\n%c\n%x\n", 9223372036854775807, 1.79769313486e+308, 'd', 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%c\n%d\n%lf\n", 0, 'o', 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%ld\n%e\n%lf\n", 4294967296, -9223372036854775809, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%c\n%lf\n%d\n", -2147483649, '#', 1.79769313486e+308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%ld\n%e\n%ld\n", 1.79769313486e+308, -9223372036854775809, 2.22507385851e-308, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%lg\n%s\n%u\n", 18446744073709551616, 2.22507385851e-308, "different", 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%f\n%lu\n%c\n", "different", 2.22507385851e-308, 18446744073709551616, '-');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%s\n%e\n%g\n", "now", "and", 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%s\n%lg\n%lf\n", -2147483649, "and", 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%f\n%o\n%f\n", 2.22507385851e-308, 2.22507385851e-308, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%le\n%x\n%s\n", 1.79769313486e+308, 1.79769313486e+308, -2147483649, "completely");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%s\n%o\n%g\n", 2.22507385851e-308, "for", 2147483647, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%x\n%lf\n%s\n", 0, 2147483647, 2.22507385851e-308, "now");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%o\n%lf\n%s\n", 2.22507385851e-308, -2147483649, 2.22507385851e-308, "something");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%o\n%o\n%lg\n", 2.22507385851e-308, 2147483647, 2147483647, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%u\n%x\n%lu\n", 1.79769313486e+308, 0, -2147483649, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%lf\n%lf\n%e\n", "different", 1.79769313486e+308, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%o\n%lf\n%lf\n", 2.22507385851e-308, 2147483647, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%s\n%le\n%c\n", -2147483649, "now", 1.79769313486e+308, '!');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%lf\n%lf\n%lu\n", 2147483647, 2.22507385851e-308, 1.79769313486e+308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%f\n%e\n%s\n", 2.22507385851e-308, 1.79769313486e+308, 1.79769313486e+308, "something");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%u\n%f\n%lf\n", 18446744073709551616, 0, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%c\n%s\n%lu\n", 2.22507385851e-308, '[', "different", 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%ld\n%lf\n%u\n", 1.79769313486e+308, 9223372036854775807, 2.22507385851e-308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%u\n%ld\n%e\n", 'p', 0, -9223372036854775809, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%s\n%c\n%o\n", -2147483649, "completely", '5', 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%e\n%f\n%lf\n", 2.22507385851e-308, 2.22507385851e-308, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%f\n%ld\n%g\n", "now", 2.22507385851e-308, -9223372036854775809, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%g\n%f\n%e\n", -2147483649, 2.22507385851e-308, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%lf\n%o\n%g\n", -2147483649, 1.79769313486e+308, 2147483647, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%le\n%s\n%ld\n", '$', 1.79769313486e+308, "something", 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lu\n%lf\n%s\n", 't', 0, 2.22507385851e-308, "for");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%ld\n%ld\n%c\n", 2.22507385851e-308, -9223372036854775809, -9223372036854775809, 'Z');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%f\n%s\n%s\n", 1.79769313486e+308, 1.79769313486e+308, "now", "different");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lg\n%ld\n%d\n", 'h', 2.22507385851e-308, -9223372036854775809, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%g\n%lf\n%x\n", 1.79769313486e+308, 1.79769313486e+308, 1.79769313486e+308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%s\n%s\n%f\n", 2.22507385851e-308, "completely", "now", 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%x\n%e\n%e\n", 2.22507385851e-308, 2147483647, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%lg\n%lg\n%x\n", 1.79769313486e+308, 1.79769313486e+308, 1.79769313486e+308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%d\n%f\n%x\n", 1.79769313486e+308, -2147483649, 1.79769313486e+308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%o\n%x\n%u\n", 0, 2147483647, 2147483647, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%d\n%le\n%u\n", 2.22507385851e-308, -2147483649, 1.79769313486e+308, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lf\n%x\n%le\n", ':', 1.79769313486e+308, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%c\n%e\n%lu\n", 2147483647, 'n', 2.22507385851e-308, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%u\n%d\n%x\n", 9223372036854775807, 0, 2147483647, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%lu\n%u\n%ld\n", 1.79769313486e+308, 18446744073709551616, 0, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%c\n%f\n%ld\n", "and", '?', 2.22507385851e-308, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%g\n%x\n%s\n", 'h', 1.79769313486e+308, 2147483647, "completely");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%d\n%c\n%x\n", 1.79769313486e+308, -2147483649, ':', -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%c\n%c\n%e\n", 2.22507385851e-308, '_', '2', 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%c\n%lu\n%s\n", 2.22507385851e-308, ';', 0, "completely");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%le\n%x\n%d\n", -2147483649, 1.79769313486e+308, 2147483647, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%x\n%e\n%ld\n", 2.22507385851e-308, -2147483649, 2.22507385851e-308, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%d\n%o\n%d\n", 2.22507385851e-308, -2147483649, -2147483649, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%ld\n%x\n%e\n", -9223372036854775809, -9223372036854775809, -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%c\n%s\n%d\n", 1.79769313486e+308, '|', "different", 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%lu\n%lg\n%lf\n", 2147483647, 0, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%x\n%lf\n%lg\n", 2.22507385851e-308, -2147483649, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%c\n%x\n%lf\n", 1.79769313486e+308, ':', 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%d\n%u\n%d\n", "different", 2147483647, 0, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%g\n%s\n%lg\n", 0, 2.22507385851e-308, "different", 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%lf\n%lu\n%lu\n", 1.79769313486e+308, 1.79769313486e+308, 18446744073709551616, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%g\n%f\n%le\n", 'c', 2.22507385851e-308, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%lf\n%s\n%lf\n", 2147483647, 2.22507385851e-308, "something", 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%le\n%lg\n%ld\n", 2.22507385851e-308, 1.79769313486e+308, 1.79769313486e+308, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%g\n%s\n%x\n", -2147483649, 2.22507385851e-308, "something", 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%lu\n%ld\n%u\n", 2147483647, 0, 9223372036854775807, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%d\n%c\n%d\n", 2147483647, 2147483647, '[', -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lg\n%c\n%le\n", 'O', 1.79769313486e+308, '+', 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%g\n%f\n%u\n", 2.22507385851e-308, 1.79769313486e+308, 2.22507385851e-308, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%c\n%x\n%c\n", 1.79769313486e+308, '~', 2147483647, ':');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%le\n%o\n%c\n", "something", 2.22507385851e-308, 2147483647, 'v');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%d\n%le\n%u\n", 18446744073709551616, 2147483647, 1.79769313486e+308, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%o\n%u\n%e\n", 'E', 2147483647, 0, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%f\n%lf\n%o\n", 0, 2.22507385851e-308, 2.22507385851e-308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%u\n%ld\n%lu\n", 1.79769313486e+308, 4294967296, -9223372036854775809, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%s\n%ld\n%lg\n", -2147483649, "and", 9223372036854775807, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%g\n%s\n%x\n", 2.22507385851e-308, 2.22507385851e-308, "different", 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%lu\n%f\n%x\n", 1.79769313486e+308, 0, 1.79769313486e+308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%d\n%c\n%lf\n", 9223372036854775807, 2147483647, 'x', 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%d\n%lf\n%x\n", 1.79769313486e+308, -2147483649, 1.79769313486e+308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%lu\n%g\n%d\n", 4294967296, 0, 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%f\n%f\n%ld\n", 2147483647, 1.79769313486e+308, 2.22507385851e-308, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%lf\n%s\n%le\n", 2.22507385851e-308, 2.22507385851e-308, "something", 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%d\n%lg\n%ld\n", 2.22507385851e-308, 2147483647, 1.79769313486e+308, -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%lf\n%le\n%u\n", 2147483647, 1.79769313486e+308, 1.79769313486e+308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%lg\n%c\n%le\n", 1.79769313486e+308, 1.79769313486e+308, 'S', 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%o\n%le\n%s\n", 2147483647, 2147483647, 2.22507385851e-308, "now");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%lf\n%d\n%u\n", 1.79769313486e+308, 2.22507385851e-308, 2147483647, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%c\n%o\n%lf\n", -2147483649, 'A', -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%s\n%u\n%f\n", 2147483647, "something", 4294967296, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%e\n%f\n%lu\n", -2147483649, 2.22507385851e-308, 2.22507385851e-308, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%s\n%d\n%lf\n", 2.22507385851e-308, "completely", -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%c\n%ld\n%f\n", -2147483649, '3', -9223372036854775809, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%s\n%ld\n%f\n", 0, "something", -9223372036854775809, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%u\n%f\n%d\n", 2147483647, 4294967296, 2.22507385851e-308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%o\n%lf\n%d\n", 0, 2147483647, 1.79769313486e+308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%f\n%e\n%le\n", '-', 1.79769313486e+308, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%ld\n%lf\n%lu\n", '`', -9223372036854775809, 2.22507385851e-308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%e\n%x\n%c\n", 2.22507385851e-308, 1.79769313486e+308, -2147483649, 'a');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%lg\n%le\n%lu\n", "now", 1.79769313486e+308, 1.79769313486e+308, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%lg\n%g\n%x\n", 2147483647, 1.79769313486e+308, 1.79769313486e+308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%c\n%lg\n%x\n", 1.79769313486e+308, '5', 2.22507385851e-308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%u\n%ld\n%g\n", 2.22507385851e-308, 0, 9223372036854775807, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%c\n%g\n%le\n", '[', 'Y', 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%ld\n%u\n%e\n", 4294967296, 9223372036854775807, 0, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%lu\n%lf\n%g\n", 18446744073709551616, 0, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%g\n%x\n%o\n", 1.79769313486e+308, 1.79769313486e+308, 2147483647, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%d\n%g\n%f\n", "something", -2147483649, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%u\n%le\n%g\n", 1.79769313486e+308, 4294967296, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%ld\n%ld\n%f\n", -2147483649, -9223372036854775809, -9223372036854775809, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%x\n%f\n%u\n", 0, 2147483647, 2.22507385851e-308, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%g\n%x\n%lg\n", '[', 1.79769313486e+308, 2147483647, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%d\n%d\n%lf\n", 0, -2147483649, -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%x\n%x\n%o\n", 0, 2147483647, -2147483649, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%x\n%x\n%f\n", -2147483649, -2147483649, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%o\n%le\n%lg\n", 2147483647, -2147483649, 2.22507385851e-308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%ld\n%lg\n%s\n", 18446744073709551616, 9223372036854775807, 1.79769313486e+308, "now");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%lf\n%o\n%c\n", "different", 2.22507385851e-308, 2147483647, 'f');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%d\n%u\n%c\n", 2.22507385851e-308, 2147483647, 4294967296, 'e');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%c\n%o\n%f\n", -2147483649, 'l', 2147483647, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%u\n%x\n%x\n", 2.22507385851e-308, 4294967296, 2147483647, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%lg\n%d\n%f\n", 2.22507385851e-308, 1.79769313486e+308, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%f\n%g\n%o\n", 2.22507385851e-308, 1.79769313486e+308, 1.79769313486e+308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%s\n%s\n%d\n", 2.22507385851e-308, "something", "now", 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%u\n%lf\n%u\n", 2.22507385851e-308, 4294967296, 1.79769313486e+308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%lf\n%f\n%d\n", 0, 1.79769313486e+308, 2.22507385851e-308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%lg\n%s\n%s\n", -9223372036854775809, 2.22507385851e-308, "something", "different");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%x\n%g\n%u\n", 4294967296, 2147483647, 2.22507385851e-308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%s\n%lu\n%u\n", 2147483647, "different", 18446744073709551616, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%c\n%lu\n%s\n", 2.22507385851e-308, 'f', 0, "different");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%ld\n%f\n%x\n", -2147483649, 9223372036854775807, 2.22507385851e-308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%d\n%u\n%x\n", 1.79769313486e+308, -2147483649, 4294967296, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%lg\n%lf\n%u\n", 2.22507385851e-308, 2.22507385851e-308, 2.22507385851e-308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%le\n%s\n%x\n", 2.22507385851e-308, 1.79769313486e+308, "now", 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%x\n%u\n%u\n", 0, 2147483647, 4294967296, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%g\n%e\n%ld\n", 2.22507385851e-308, 1.79769313486e+308, 2.22507385851e-308, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%lf\n%d\n%x\n", 2.22507385851e-308, 1.79769313486e+308, 2147483647, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%s\n%lg\n%lf\n", 18446744073709551616, "now", 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%g\n%lu\n%le\n", 0, 2.22507385851e-308, 18446744073709551616, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%s\n%f\n%lg\n", 18446744073709551616, "different", 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%lu\n%c\n%lu\n", 1.79769313486e+308, 18446744073709551616, '*', 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%lg\n%s\n%lf\n", 1.79769313486e+308, 2.22507385851e-308, "something", 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%g\n%e\n%lu\n", -9223372036854775809, 1.79769313486e+308, 2.22507385851e-308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%lg\n%f\n%lg\n", 4294967296, 2.22507385851e-308, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%le\n%d\n%e\n", 1.79769313486e+308, 1.79769313486e+308, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%f\n%ld\n%lf\n", 2.22507385851e-308, 2.22507385851e-308, -9223372036854775809, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lg\n%c\n%ld\n", 'x', 1.79769313486e+308, '\'', -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%x\n%lu\n%lg\n", 1.79769313486e+308, 2147483647, 0, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%u\n%s\n%x\n", 1.79769313486e+308, 0, "and", 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%d\n%u\n%lu\n", 18446744073709551616, -2147483649, 4294967296, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%d\n%u\n%f\n", 2.22507385851e-308, 2147483647, 4294967296, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%ld\n%lu\n%lf\n", 9223372036854775807, 9223372036854775807, 18446744073709551616, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%o\n%f\n%e\n", 0, -2147483649, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%lu\n%f\n%ld\n", 2.22507385851e-308, 0, 2.22507385851e-308, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%s\n%x\n%f\n", 2.22507385851e-308, "completely", 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%lu\n%g\n%d\n", 1.79769313486e+308, 18446744073709551616, 2.22507385851e-308, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%f\n%le\n%lu\n", 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%x\n%o\n%lg\n", "for", 2147483647, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%ld\n%u\n%le\n", 2.22507385851e-308, 9223372036854775807, 0, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%x\n%lf\n%s\n", 2147483647, -2147483649, 2.22507385851e-308, "now");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lg\n%d\n%u\n", 'G', 2.22507385851e-308, 2147483647, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%s\n%g\n%s\n", 2147483647, "something", 1.79769313486e+308, "different");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%d\n%e\n%lf\n", 2147483647, 2147483647, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%f\n%g\n%ld\n", 2.22507385851e-308, 2.22507385851e-308, 2.22507385851e-308, 9223372036854775807);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%ld\n%lg\n%u\n", 2147483647, -9223372036854775809, 1.79769313486e+308, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%x\n%u\n%f\n", 1.79769313486e+308, 2147483647, 0, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%c\n%f\n%lg\n", 2.22507385851e-308, '4', 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%g\n%c\n%ld\n", 2.22507385851e-308, 2.22507385851e-308, 'Q', -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%c\n%o\n%s\n", 2147483647, '?', -2147483649, "completely");
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%e\n%u\n%u\n", 2147483647, 2.22507385851e-308, 4294967296, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%lg\n%x\n%g\n", 2.22507385851e-308, 2.22507385851e-308, -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%le\n%f\n%ld\n%f\n", 2.22507385851e-308, 1.79769313486e+308, -9223372036854775809, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%lf\n%o\n%g\n", -2147483649, 2.22507385851e-308, -2147483649, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%g\n%e\n%lf\n", 0, 2.22507385851e-308, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%ld\n%d\n%e\n", 9223372036854775807, 9223372036854775807, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%f\n%c\n%le\n", 0, 2.22507385851e-308, 'A', 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%ld\n%o\n%lf\n", 'Q', -9223372036854775809, -2147483649, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%e\n%g\n%lu\n", 18446744073709551616, 1.79769313486e+308, 2.22507385851e-308, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%e\n%e\n%lg\n", 'f', 2.22507385851e-308, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%lg\n%x\n%c\n", 1.79769313486e+308, 1.79769313486e+308, -2147483649, '7');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%s\n%o\n%lf\n", -2147483649, "different", 2147483647, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%lf\n%x\n%u\n", 9223372036854775807, 1.79769313486e+308, -2147483649, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%ld\n%le\n%f\n", 1.79769313486e+308, 9223372036854775807, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%lg\n%u\n%x\n", 1.79769313486e+308, 1.79769313486e+308, 0, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%lu\n%c\n%f\n", 1.79769313486e+308, 0, '6', 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%u\n%ld\n%e\n", 0, 4294967296, 9223372036854775807, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%u\n%le\n%e\n%e\n", 4294967296, 1.79769313486e+308, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%x\n%d\n%u\n", 0, -2147483649, -2147483649, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%g\n%lg\n%lf\n", 1.79769313486e+308, 1.79769313486e+308, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%e\n%g\n%lf\n", 1.79769313486e+308, 1.79769313486e+308, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%ld\n%f\n%lg\n", 1.79769313486e+308, -9223372036854775809, 1.79769313486e+308, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%d\n%x\n%e\n", 18446744073709551616, 2147483647, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%lf\n%d\n%x\n", 2.22507385851e-308, 2.22507385851e-308, -2147483649, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%d\n%u\n%u\n", "now", 2147483647, 4294967296, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%lg\n%s\n%ld\n", 1.79769313486e+308, 2.22507385851e-308, "different", -9223372036854775809);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%u\n%e\n%f\n", 2.22507385851e-308, 0, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%c\n%lf\n%lu\n", 1.79769313486e+308, 'J', 2.22507385851e-308, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%o\n%lg\n%g\n%c\n", -2147483649, 1.79769313486e+308, 1.79769313486e+308, 'T');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%f\n%x\n%lf\n", "and", 2.22507385851e-308, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%g\n%g\n%lg\n", 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%f\n%lu\n%f\n", '2', 1.79769313486e+308, 18446744073709551616, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%g\n%g\n%lg\n%o\n", 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lg\n%lg\n%lu\n%d\n", 2.22507385851e-308, 1.79769313486e+308, 0, -2147483649);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%g\n%lg\n%c\n", 2147483647, 1.79769313486e+308, 1.79769313486e+308, '=');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%f\n%f\n%g\n%lu\n", 1.79769313486e+308, 2.22507385851e-308, 1.79769313486e+308, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%o\n%le\n%f\n", 1.79769313486e+308, 2147483647, 1.79769313486e+308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%x\n%o\n%d\n%lu\n", -2147483649, -2147483649, -2147483649, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%s\n%lf\n%d\n%lf\n", "and", 1.79769313486e+308, 2147483647, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%ld\n%d\n%x\n%c\n", 9223372036854775807, 2147483647, -2147483649, '?');
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%d\n%e\n%o\n", '^', 2147483647, 1.79769313486e+308, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lu\n%g\n%lu\n%u\n", 18446744073709551616, 1.79769313486e+308, 0, 4294967296);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%lu\n%u\n%x\n", '2', 0, 4294967296, 2147483647);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%c\n%d\n%lu\n%lu\n", '/', -2147483649, 18446744073709551616, 18446744073709551616);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%lf\n%g\n%lg\n%f\n", 1.79769313486e+308, 2.22507385851e-308, 2.22507385851e-308, 1.79769313486e+308);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%d\n%le\n%d\n%u\n", -2147483649, 1.79769313486e+308, -2147483649, 0);
printf("%s\n", buf);

musl_snprintf(buf, LEN, "%e\n%ld\n%x\n%f\n", 1.79769313486e+308, -9223372036854775809, 2147483647, 2.22507385851e-308);
printf("%s\n", buf);

return 0;
}
