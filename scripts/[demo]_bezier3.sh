#!/bin/bash

./scripts/\[demo\]_clean_demo.sh
echo "---------------------------------------------"
echo "               Demo bezier3                  "
echo "---------------------------------------------"
make test_simplification
make clean
for file in $(ls images/demo/*)
do
./test_simplification $file 3 3 3
done
make clear