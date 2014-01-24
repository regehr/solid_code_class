RESULTS="../../triangle_outputs"
NAME=`echo "$1" | sed -E 's|./([^/]*)/triangle|\1|'`
TESTFILE="joshkunz/outputs.text"

python27 joshkunz/test.py --file "$TESTFILE" "$1" > "$RESULTS/$NAME"
python27 joshkunz/test.py --quiet --file "$TESTFILE" "$1"
#python27 joshkunz/test.py --file "$TESTFILE" "$1"
