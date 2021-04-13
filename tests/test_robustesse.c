#include "../interfaces/simplification.h"
#include "../interfaces/eps.h"

int main (int argc, char * argv[]) {
    
    //> Verification du nombre d'arguments
    if (argc != 2) {
        ERREUR_FATALE("[Erreur]\ttest_robustesse/main\tNombre d'argument incorrect, une image attendue.");
    }

    //> Recuperation de l'image
    Image I = lire_fichier_image(argv[1]);

    //> Calcul des multiples contours
    determiner_contour(I, 1);

    return 0;
}