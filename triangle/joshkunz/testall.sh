find . -name triangle -print0 | xargs -0 -n1 -i bash joshkunz/testhelper.sh "{}" | awk -f joshkunz/compile.awk | sort -rn
