#!/bin/bash

echo "---------------------------------------------"
echo "         Compte rendu de la tache 8          "
echo "---------------------------------------------"
make test_simplification
make clean
for mode in $(echo 0 1 2 3)
do
	for file in 'Asterix3.pbm' 'lettre-L-cursive.pbm' 'Picasso-ColombesDeLaPaix.pbm'
	do
		echo ""
		echo "---------------------------------------------"
		echo "Execution de ./test_simplification images/tache_8/"$file 3 $mode $mode
		echo "---------------------------------------------"
		./test_simplification images/tache_8/$file 3 $mode $mode
	done
done
make clear