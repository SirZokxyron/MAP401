#!/bin/bash

./scripts/\[demo\]_clean_demo.sh
echo "---------------------------------------------"
echo "               Demo segments                 "
echo "---------------------------------------------"
make test_simplification
make clean
for file in $(ls images/demo/*)
do
echo ./test_simplification $file 3 1 1
./test_simplification $file 3 1 1
done
make clear