RESULTS="results"
NAME=`echo "$1" | sed -E 's|./([^/]*)/triangle|\1|'`

python27 joshkunz/test.py --file joshkunz/outputs.text "$1" > "$RESULTS/$NAME"
