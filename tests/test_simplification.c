#include "../interfaces/simplification.h"
#include "../interfaces/eps.h"

int main (int argc, char * argv[]) {
    
    //> Verification du nombre d'arguments
    if (argc != 4) {
        ERREUR_FATALE("[Erreur]\ttest__multiples_contours/main\tNombre d'argument incorrect, une image, un mode (1-3) et une simplification (0-1) attendus.");
    }

    //> Recuperation de l'image
    Image I = lire_fichier_image(argv[1]);

    //> Affichage de l'image a l'ecran
    //? ecrire_image(I); printf("\n");

    //> Affichage du masque de l'image a l'ecran
    //? ecrire_masque(I); printf("\n");

    //> Calcul des multiples contours
    determiner_contour(I, atoi(argv[3]));
    
    //> Affichage du nombre de contours et segments a l'ecran
    debug_contour(I);

    //> Affichage du format .eps du contours
    creer_eps(I, atoi(argv[2]));  

    return 0;
}