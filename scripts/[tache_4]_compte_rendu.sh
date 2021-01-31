#!/bin/bash

echo "---------------------------------------------"
echo "     Review cas d'ecriture au format eps     "
echo "---------------------------------------------"
make test_eps
make clean
for file in $(ls images/tache_4/*)
do
echo ""
echo "---------------------------------------------"
echo "      Execution de ./test_eps $file          "
echo "---------------------------------------------"
if [ $file == 'images/tache_4/chat.pbm' ] || [ $file == 'images/tache_4/image_ex_poly.pbm' ]
then
./test_eps $file 1
./test_eps $file 2
fi
./test_eps $file 3
done
make clear