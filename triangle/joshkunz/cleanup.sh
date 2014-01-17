LINES=`wc -l "$1" | awk '{ print $1; }'`
if [[ "$LINES" -eq "2" ]]; then
    rm "$1"
else
    exit 1
fi

