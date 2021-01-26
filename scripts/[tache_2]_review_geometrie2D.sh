#!/bin/bash

echo "---------------------------------------------"
echo "       Review paquetage de la tache 2        "
echo "---------------------------------------------"
make test_geometrie
make clean
echo ""
echo "---------------------------------------------"
echo "       Execution de ./test_geometrie         "
echo "---------------------------------------------"
./test_geometrie
make clear