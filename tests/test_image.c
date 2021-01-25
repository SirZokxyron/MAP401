#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../interfaces/image.h"

int main (int argc, char * argv[]) {

    if (argc != 2) {
        ERREUR_FATALE("[Erreur]\ttest_image/main\tNombre d'argument incorrect, 1 argument attendu.");
    }

    // Lecture de l'image passee en argument du programme
    Image I = lire_fichier_image(argv[1]);
    
    // Affichage de l'image
    printf("Image avant modification : \n");
    ecrire_image(I);

    // Modification de l'image
    set_pixel_image(I, 6, 5, NOIR);
    set_pixel_image(I, 6, 6, NOIR);
    set_pixel_image(I, 6, 7, NOIR);

    // Nouvel affichage de l'image
    printf("Image apres modification : \n");
    ecrire_image(I); 
    
    // Suppression de l-image
    supprimer_image(&I);

    // Affichage de l'image pour verifier la bonne suppression
    ecrire_image(I); 

    return 0;
}