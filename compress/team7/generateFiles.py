#! /usr/bin/env python

import os
import random
import sys

def main():
    with open('files/chars.txt', 'w+') as f:
        for i in range(256):
            f.write(chr(i))

    return 0

if __name__ == '__main__':
    sys.exit(main())
