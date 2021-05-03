#!/bin/bash

./scripts/\[demo\]_clean_demo.sh
echo "---------------------------------------------"
echo "               Demo bezier2                  "
echo "---------------------------------------------"
make test_simplification
make clean
for file in $(ls images/demo/*)
do
echo ./test_simplification $file 3 2 2
./test_simplification $file 3 2 2
done
make clear