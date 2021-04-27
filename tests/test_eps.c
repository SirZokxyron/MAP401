#include "../interfaces/eps.h"

//! Test pour la simplification par distance seuil
int main (int argc, char * argv[]) {

    //> Verification du nombre d'arguments
    if (argc != 3) {
        ERREUR_FATALE("[Erreur]\ttest_eps/main\tNombre d'argument incorrect, une image et un mode (1-3) attendu.");
    }

    //> Chargement de notre image au format PBM
    Image I = lire_fichier_image(argv[1]);

    //> Recherche du point de depart pour determiner le contour
    determiner_contour(I, 0);

    //> Creer le fichier .eps correpondant
    creer_eps(I, atoi(argv[2]));

    return 0;
}