#include "../interfaces/robot.h"

int main(int argc, char * argv[]) {

   //> Verification du nombre d'arguments
   if (argc != 2) {
      ERREUR_FATALE("[Erreur]\ttest__multiples_contours/main\tNombre d'argument incorrect, une image attendue.");
   }

   //> Chargement de notre image au format PBM
   Image I = lire_fichier_image(argv[1]);

   //> Recherche du point de depart pour determiner le contour
   determiner_contour(I, 0);

   return 0;
}