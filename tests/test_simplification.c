#include "../interfaces/simplification.h"
#include "../interfaces/eps.h"

int main (int argc, char * argv[]) {
    
    //> Verification du nombre d'arguments
    if (argc != 5) {
        ERREUR_FATALE("[Erreur]\ttest_simplification/main\tNombre d'argument incorrect, une image, un mode (1-3) et une simplification (0-3) attendus, le mode de debug (0-3)");
    }

    //> Recuperation de l'image
    Image I = lire_fichier_image(argv[1]);

    //> Affichage de l'image a l'ecran
    //? ecrire_image(I); printf("\n");

    //> Affichage du masque de l'image a l'ecran
    //? ecrire_masque(I); printf("\n");

    //> Calcul des multiples contours
    determiner_contour(I, atoi(argv[3]));
    

    //> Affichage du nombre de contours et segments a l'ecran + creation du .eps
    int mode = atoi(argv[2]);
    switch (atoi(argv[4])) {
        case 1:
            debug_contour(I);
            creer_eps(I, mode);
            break;
        case 2:
            debug_bezier2(I);
            creer_eps_bezier(I, atoi(argv[4]), mode);
            break;
        case 3:
            debug_bezier3(I);
            creer_eps_bezier(I, atoi(argv[4]), mode);
            break;
        default:
            creer_eps(I, mode);
            break;
    }

    return 0;
}