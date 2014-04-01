import random
import string
import uuid

ARBITRARILY_HIGH = 100


def printf(flag,width,precision,length,specifier,arg):
    return 'printf("%{flag}{width}{precision}{length}{specifier}\\n", {arg});\n'.format \
        (flag=flag, width=width, precision=precision, length=length, specifier=specifier, arg=arg)

signed    = ['d', 'i']
unsigned  = ['u', 'o', 'X', 'x', 'p']
floaty    = ['f', 'F', 'E', 'e', 'g', 'G', 'a', 'A']


flags     = ['-', '+', ' ', '#', '0']
width     = [i for i in range(20)]
length    = ['h', 'hh', 'l', 'll', 'j', 'z']
precision = ['.' + str(i) for i in range(16)]
precision.append('.')


def printf_generator():
    #yield r'printf("%%\n");'
    for i in xrange(ARBITRARILY_HIGH):
        _int = random.randint(-2147483648, 2147483647)
        _uint = random.randint(0, 2 ** 32)
        _float = random.uniform(-2**31, 2**31)
        _small = random.triangular()            
        for f in flags:
            width_str = str(random.randint(0, 20)) + ', ' + str(_int)
            yield printf(f, '*', '', '', 'i', width_str)
            for w in width:
                yield printf(f, w, '*', '', 'i', width_str)
                for p in precision:
                    rand_str = uuid.uuid4().hex
                    yield printf(f, w, p, '', 's', '"'+rand_str+'"')
                    for s in signed:
                        yield printf(f, w, p, '', s, _int)
                        yield printf(f, w, p, 't', s, _int)
                        yield printf(f, w, p, 'z', s, _int)
                        yield printf(f, w, p, 'j', s, _int)
                        yield printf(f, w, p, 'll', s, _int)
                        yield printf(f, w, p, 'l', s, _int)
                        yield printf(f, w, p, 'h', s, _int)
                        yield printf(f, w, p, 'hh', s, _int)
                    for s in unsigned:
                        yield printf(f, w, p, '', s, _uint)
                        if s == 'p': continue
                        yield printf(f, w, p, 't', s, _uint)
                        yield printf(f, w, p, 'z', s, _int)
                        yield printf(f, w, p, 'j', s, _int)
                        yield printf(f, w, p, 'll', s, _int)
                        yield printf(f, w, p, 'l', s, _int)
                        yield printf(f, w, p, 'h', s, _int)
                        yield printf(f, w, p, 'hh', s, _int)
                    for s in floaty:
                        yield printf(f, w, p, '', s, _float)
                        yield printf(f, w, p, '', s, _small)
                        yield printf(f, w, p, 'L', s, abs(_float))
                        yield printf(f, w, p, 'L', s, abs(_small))
                    for c in string.letters:
                        yield printf(f, w, p, '', 'c', "'"+c+"'")
                    for c in string.digits:
                        yield printf(f, w, p, '', 'c', "'"+c+"'")
            print 'here'

    yield r'printf("%d\n", 42.0);'


