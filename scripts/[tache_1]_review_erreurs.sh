#!/bin/bash

echo "---------------------------------------------"
echo "    Review gestion erreurs de la tache 1     "
echo "---------------------------------------------"
make test_image
make clean
for file in $(ls images/tache_1/[e*)
do
echo ""
echo "---------------------------------------------"
echo "      Execution de ./test_image $file        "
echo "---------------------------------------------"
./test_image $file
done
make clear