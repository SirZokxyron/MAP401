#include "../interfaces/robot.h"
#include "../interfaces/eps.h"

int main (int argc, char * argv[]) {
    
    //> Verification du nombre d'arguments
    if (argc != 3) {
        ERREUR_FATALE("[Erreur]\ttest__multiples_contours/main\tNombre d'argument incorrect, 2 arguments attendus.");
    }

    //> Recuperation de l'image
    Image I = lire_fichier_image(argv[1]);

    //> Affichage de l'image a l'ecran
    //? ecrire_image(I); printf("\n");

    //> Affichage du masque de l'image a l'ecran
    //? ecrire_masque(I); printf("\n");

    //> Calcul des multiples contours
    determiner_contour(I);
    debug_contour(I);

    //> Affichage du format .eps du contours
    creer_eps(I, atoi(argv[2]));

    return 0;
}