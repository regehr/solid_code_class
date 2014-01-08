#!/usr/bin/env bash

# Compares to implementations output

RAND_FILE=".tmp_input"
RAND_CHECKS="1000"
echo "
from random import randrange as rr;
for x in range($RAND_CHECKS):
    print ' '.join(str(rr((2 ** 31) - 1)) for x in range(6))" | \
    python - > "$RAND_FILE"

diff <(cat $RAND_FILE | xargs -n6 $1) <(cat $RAND_FILE | xargs -n6 $2)

rm "$RAND_FILE"
