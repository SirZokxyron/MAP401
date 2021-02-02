#include "../interfaces/eps.h"

int main (int argc, char * argv[]) {

    //> Verification du nombre d'arguments
    if (argc != 2) {
        ERREUR_FATALE("[Erreur]\ttest_eps/main\tNombre d'argument incorrect, une image et un mode (1-3) attendue.");
    }

    //> Chargement de notre image au format PBM
    Image I = lire_fichier_image(argv[1]);

    //> Recherche du point de depart pour determiner le contour
    determiner_contour(I);

    //> Creer le fichier .eps correpondant
    creer_eps(I, atoi(argv[2]));

    return 0;
}