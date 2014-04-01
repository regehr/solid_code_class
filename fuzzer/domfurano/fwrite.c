#include "musl.h"

#define F_NOWR 8
#define F_ERR 32
#define F_ERR 32

int __towrite(MUSL_FILE *f)
{
	f->mode |= f->mode-1;
	if (f->flags & (F_NOWR)) {
		f->flags |= F_ERR;
		return EOF;
	}
	/* Clear read buffer (easier than summoning nasal demons) */
	f->rpos = f->rend = 0;

	/* Activate write through the buffer. */
	f->wpos = f->wbase = f->buf;
	f->wend = f->buf + f->buf_size;

	return 0;
}

size_t __fwritex(const unsigned char *restrict s, size_t l, MUSL_FILE *restrict f)
{
	size_t i=0;

	if (!f->wend && __towrite(f)) return 0;

	if (l > f->wend - f->wpos) return f->write(f, s, l);

	if (f->lbf >= 0) {
		/* Match /^(.*\n|)/ */
		for (i=l; i && s[i-1] != '\n'; i--);
		if (i) {
			if (f->write(f, s, i) < i)
				return i;
			s += i;
			l -= i;
		}
	}

	memcpy(f->wpos, s, l);
	f->wpos += l;
	return l+i;
}

/*
size_t fwrite(const void *restrict src, size_t size, size_t nmemb, MUSL_FILE *restrict f)
{
	size_t k, l = size*nmemb;
	if (!l) return l;
	// FLOCK(f);
	k = __fwritex(src, l, f);
	// FUNLOCK(f);
	return k==l ? nmemb : k/size;
}

*/
