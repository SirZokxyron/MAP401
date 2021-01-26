#!/bin/bash

echo "---------------------------------------------"
echo "      Review cas de recherche contours       "
echo "---------------------------------------------"
make test_contours
make clean
for file in $(ls images/tache_3/*)
do
echo ""
echo "---------------------------------------------"
echo "      Execution de ./test_contours $file        "
echo "---------------------------------------------"
./test_contours $file
done
make clear