#include "robot.h"

int main(int argc, char * argv[]) {

   // Chargement de notre image au format PBM
   Image I = lire_fichier_image(argv[1]);

   // Recherche du point de depart pour determiner le contour
   determiner_contour(I);

   return 0;
}