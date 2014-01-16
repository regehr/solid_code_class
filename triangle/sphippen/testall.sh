#!/bin/sh

# Compile everyone's code
cd ..
perl compile_all.pl
cd sphippen

# Move my impl. so it doesn't get clobbered
mv ./triangle ./triangle2

PASSED=()
FAILED=()

# Copy in other people's programs and run the test script on them
for f in ../*/triangle ../sphippen/triangle2
do
  [[ -f "$f" ]] || continue
  NAME=$(basename $(dirname "$f"))
  cp -- "$f" ./triangle
  echo "Testing $NAME..."
  python3 test.py
  RESULTSNAME="testresults-$NAME.txt"
  if [ -f "testresults.txt" ]; then
    FAILED+=("$NAME")
    mv -- testresults.txt "$RESULTSNAME"
  else
    PASSED+=("$NAME")
  fi
  rm -f ./triangle
done

# Move my impl back
mv ./triangle2 ./triangle

# Print results
echo
echo "Passed:"
for name in ${PASSED[@]}
do
  echo $name
done | sort -f
echo
echo "Failed:"
for name in ${FAILED[@]}
do
  echo $name
done | sort -f
