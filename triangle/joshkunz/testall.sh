OUTPUTS="../../triangle_outputs"
rm $OUTPUTS/*
find . -name triangle -print0 | xargs -0 -n1 -i bash joshkunz/testhelper.sh "{}" | awk -f joshkunz/compile.awk
echo "Removing passed tests"
find "$OUTPUTS" -maxdepth 1 -type f \! -name "cleanup.sh" -exec bash joshkunz/cleanup.sh {} \; -print
