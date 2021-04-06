#include "../interfaces/simplification.h"
#include "../interfaces/eps.h"

int main (int argc, char * argv[]) {
    
    //> Verification du nombre d'arguments
    if (argc != 5) {
        ERREUR_FATALE("[Erreur]\ttest_robustesse/main\tNombre d'argument incorrect, une image, un mode (1-3) et une simplification (0-3) attendus, le mode de debug (0-3)");
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
    switch (atoi(argv[4])) {
        case 1:
            debug_contour(I);
            break;
        case 2:
            debug_bezier2(I);
            break;
        case 3:
            debug_bezier3(I);   // interactive time
            break;
        default:    
            break;
    }

    //> Affichage du format .eps du contours
    int mode = atoi(argv[2]);
    if (mode <= 3) creer_eps(I, mode);
    else creer_eps_bezier(I, atoi(argv[4]), mode - 3);

    return 0;
}