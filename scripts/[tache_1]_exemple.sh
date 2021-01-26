#!/bin/bash

echo "---------------------------------------------"
echo "        Review exemple de la tache 1         "
echo "---------------------------------------------"
make test_image
make clean
echo ""
echo "---------------------------------------------"
echo "Execution de ./test_image images/tache_1/2.pbm"
echo "---------------------------------------------"
./test_image images/tache_1/2.pbm
make clear