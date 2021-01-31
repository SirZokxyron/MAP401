#include "../interfaces/eps.h"

int main (int argc, char * argv[]) {

    //> Chargement de notre image au format PBM
    Image I = lire_fichier_image(argv[1]);

    //> Recherche du point de depart pour determiner le contour
    determiner_contour(I);

    //> Creer le fichier .eps correpondant
    creer_eps(I, atoi(argv[2]));

    return 0;
}