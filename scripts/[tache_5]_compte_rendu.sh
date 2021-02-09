#!/bin/bash

echo "---------------------------------------------"
echo "     Review remplissage EPS de contours      "
echo "---------------------------------------------"
make test_eps
make clean
for file in 'image1_poly.pbm' 'image2_poly.pbm' 'FranceRegions.pbm' 'Droopy_Wolf.pbm'
do
echo ""
echo "---------------------------------------------"
echo "Execution de ./test_eps images/tache_5/$file "
echo "---------------------------------------------"
./test_eps images/tache_5/$file 3
done
make clear